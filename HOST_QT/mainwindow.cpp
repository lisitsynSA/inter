#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tryButton, SIGNAL(pressed()), this, SLOT(start_hid()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_hid()
{
    qDebug() << "START HID CONNECTION";

    if(hid_open()>0){
        qDebug() << "HID device is opened (VID=0x483, PID=0x5711)";
        ui->statusLabel->setText(QString("Status: Connect"));
    }else{
        qDebug() << "HID device is not opened";
        ui->statusLabel->setText(QString("Status: Disconnect"));
        return;
    }
    return;
}

int MainWindow::hid_open()
{
    return rawhid_open(1, 0x483, 0x5711, -1, -1);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include <setupapi.h>
#include "ddk/hidsdi.h"

int HidUsbConnected=0;

// a list of all opened HID devices, so the caller can
// simply refer to them by number
typedef struct hid_struct hid_t;
static hid_t *first_hid = NULL;
static hid_t *last_hid = NULL;
struct hid_struct {
    HANDLE handle;
    int open;
    struct hid_struct *prev;
    struct hid_struct *next;
};
static HANDLE rx_event=NULL;
static HANDLE tx_event=NULL;
static CRITICAL_SECTION rx_mutex;
static CRITICAL_SECTION tx_mutex;

//HIDAPI BOOLEAN NTAPI
//HidD_FreePreparsedData(PHIDP_PREPARSED_DATA PreparsedData);
//HIDAPI BOOLEAN NTAPI
//HidD_GetPreparsedData(HANDLE HidDeviceObject,
//		      PHIDP_PREPARSED_DATA *PreparsedData);

//  rawhid_open - open 1 or more devices
//
//    Inputs:
//	max = maximum number of devices to open
//	vid = Vendor ID, or -1 if any
//	pid = Product ID, or -1 if any
//	usage_page = top level usage page, or -1 if any
//	usage = top level usage number, or -1 if any
//    Output:
//	actual number of devices opened
//
int rawhid_open(int max, int vid, int pid, int usage_page, int usage)
{
    GUID guid;
    HDEVINFO info;
    DWORD index=0, reqd_size;
    SP_DEVICE_INTERFACE_DATA iface;
    SP_DEVICE_INTERFACE_DETAIL_DATA *details;
    HIDD_ATTRIBUTES attrib;
    PHIDP_PREPARSED_DATA hid_data;
    HIDP_CAPS capabilities;
    HANDLE h;
    BOOL ret;
    hid_t *hid;
    int count=0;

    if (first_hid) free_all_hid();
    if (max < 1) return 0;
    if (!rx_event) {
        rx_event = CreateEvent(NULL, TRUE, TRUE, NULL);
        tx_event = CreateEvent(NULL, TRUE, TRUE, NULL);
        InitializeCriticalSection(&rx_mutex);
        InitializeCriticalSection(&tx_mutex);
    }
    HidD_GetHidGuid(&guid);
    info = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (info == INVALID_HANDLE_VALUE) return 0;
    for (index=0; 1 ;index++) {
        iface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        ret = SetupDiEnumDeviceInterfaces(info, NULL, &guid, index, &iface);
        if (!ret) return count;
        SetupDiGetInterfaceDeviceDetail(info, &iface, NULL, 0, &reqd_size, NULL);
        details = (SP_DEVICE_INTERFACE_DETAIL_DATA *)malloc(reqd_size);
        if (details == NULL) continue;

        memset(details, 0, reqd_size);
        details->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        ret = SetupDiGetDeviceInterfaceDetail(info, &iface, details,
            reqd_size, NULL, NULL);
        if (!ret) {
            free(details);
            continue;
        }
        h = CreateFile(details->DevicePath, GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
        free(details);
        if (h == INVALID_HANDLE_VALUE) continue;
        attrib.Size = sizeof(HIDD_ATTRIBUTES);
        ret = HidD_GetAttributes(h, &attrib);

        if (!ret || (vid > 0 && attrib.VendorID != vid) ||
          (pid > 0 && attrib.ProductID != pid) ||
          !HidD_GetPreparsedData(h, &hid_data)) {
            CloseHandle(h);
            continue;
        }

        HidP_GetCaps(hid_data, &capabilities);

        if (!HidP_GetCaps(hid_data, &capabilities) ||
          (usage_page > 0 && capabilities.UsagePage != usage_page) ||
          (usage > 0 && capabilities.Usage != usage)) {
            HidD_FreePreparsedData(hid_data);
            CloseHandle(h);
            continue;
        }
        HidD_FreePreparsedData(hid_data);
        hid = (struct hid_struct *)malloc(sizeof(struct hid_struct));
        if (!hid) {
            CloseHandle(h);
            continue;
        }
        hid->handle = h;
        hid->open = 1;
        add_hid(hid);
        count++;
        if (count >= max) return count;
    }
    return count;
}

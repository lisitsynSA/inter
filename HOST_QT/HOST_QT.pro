#-------------------------------------------------
#
# Project created by QtCreator 2017-02-02T15:36:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HOST_QT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lhid -lsetupapi

SOURCES += main.cpp\
        mainwindow.cpp \
    hid.cpp

HEADERS  += mainwindow.h \
    ddk/atm.h \
    ddk/batclass.h \
    ddk/cfg.h \
    ddk/cfgmgr32.h \
    ddk/d4drvif.h \
    ddk/d4iface.h \
    ddk/ddkmapi.h \
    ddk/hidclass.h \
    ddk/hidpi.h \
    ddk/hidsdi.h \
    ddk/hidusage.h \
    ddk/kbdmou.h \
    ddk/mcd.h \
    ddk/miniport.h \
    ddk/minitape.h \
    ddk/mountdev.h \
    ddk/mountmgr.h \
    ddk/ndis.h \
    ddk/ndisguid.h \
    ddk/ndistapi.h \
    ddk/ndiswan.h \
    ddk/netevent.h \
    ddk/netpnp.h \
    ddk/newdev.h \
    ddk/ntapi.h \
    ddk/ntdd8042.h \
    ddk/ntddbeep.h \
    ddk/ntddcdrm.h \
    ddk/ntddcdvd.h \
    ddk/ntddchgr.h \
    ddk/ntdddisk.h \
    ddk/ntddkbd.h \
    ddk/ntddmou.h \
    ddk/ntddndis.h \
    ddk/ntddpar.h \
    ddk/ntddpcm.h \
    ddk/ntddscsi.h \
    ddk/ntddser.h \
    ddk/ntddstor.h \
    ddk/ntddtape.h \
    ddk/ntddtdi.h \
    ddk/ntddvdeo.h \
    ddk/ntddvol.h \
    ddk/ntifs.h \
    ddk/ntpoapi.h \
    ddk/ntstatus.h \
    ddk/parallel.h \
    ddk/pfhook.h \
    ddk/poclass.h \
    ddk/scsi.h \
    ddk/scsiscan.h \
    ddk/scsiwmi.h \
    ddk/smbus.h \
    ddk/srb.h \
    ddk/storport.h \
    ddk/tdi.h \
    ddk/tdiinfo.h \
    ddk/tdikrnl.h \
    ddk/tdistat.h \
    ddk/tvout.h \
    ddk/upssvc.h \
    ddk/usb.h \
    ddk/usb100.h \
    ddk/usbcamdi.h \
    ddk/usbdi.h \
    ddk/usbioctl.h \
    ddk/usbiodef.h \
    ddk/usbscan.h \
    ddk/usbuser.h \
    ddk/video.h \
    ddk/videoagp.h \
    ddk/win2k.h \
    ddk/winddi.h \
    ddk/winnt4.h \
    ddk/winxp.h \
    ddk/ws2san.h \
    ddk/xfilter.h \
    ddk/ntddk.h \
    ddk/winddk.h

FORMS    += mainwindow.ui

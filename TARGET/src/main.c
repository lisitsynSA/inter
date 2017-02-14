//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "diag/Trace.h"

#include "usbd_def.h"
#include "usbd_customhid.h"
#include "Timer.h"
#include "BlinkLed.h"
#include "hid_code.h"

#define DATA_SIZE 1024

void MX_GPIO_Init(void);
void USB_DEVICE_Init(void);

struct RecieveData{
	int Pointer;
	char Data[DATA_SIZE];
} recieveData;

void InitData()
{
	recieveData.Pointer = 0;
}

void AddData(uint8_t *inbuf)
{
	int len = 0;

	//InData [1][Data max 64 bytes]
	len=strlen((char *)inbuf+1);

	if (recieveData.Pointer + len < DATA_SIZE)
	{
		strcpy((char*)recieveData.Data + recieveData.Pointer, (char*)inbuf+1);
		recieveData.Pointer += len;
	} else
		trace_printf("END OF MEMORY!!!");
}


void DumpData()
{
	trace_printf("DATA: %s\n", recieveData.Data);
}


// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

int counter=0;

int main()
{
	// Send a greeting to the trace device (skipped on Release).
  //trace_puts("Hello ARM World!");

	InitData();
	timer_start();


	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	USB_DEVICE_Init();

	uint32_t seconds = 0;

	// Infinite loop
	while (1)
	{
		blink_led_on();
		timer_sleep(seconds == 0 ? TIMER_FREQUENCY_HZ : BLINK_ON_TICKS);

		blink_led_off();
		timer_sleep(BLINK_OFF_TICKS);
		trace_printf("Second %u\n", seconds);

		++seconds;

	}
  // Infinite loop, never return.
}

// HID proccesing
// Вызывается функция из обработчика прерывания по получению данных (USBD_CUSTOM_HID_DataOut)
// inbuf - выделяется драйвером длина (64 байт)

void CommandProcess(USBD_HandleTypeDef *pdev, uint8_t *inbuf)
{

	int len;
	char s[65] = {'c','a','m', ' '};
	//itoa(counter,s,10);


	//AddData(inbuf);
	inbuf[0]=2; //report to PC (remove on PC side by driver)
	char code = inbuf[1];
	char size = inbuf[2];
	trace_printf("RECV: (code %d, size %d) %s\nDATA %d\n", code, size, inbuf+4);

	switch (code) {
	    case ECHO:
			memcpy(s+4, inbuf+4, size);
			size += 4;
			inbuf[2] = size;
			memcpy(inbuf+4, s, size);
		case PING:
			USBD_CUSTOM_HID_SendReport(pdev, inbuf, 65);
			trace_printf("SEND: (code %d, size %d) %s\nDATA %d\n", code, size, inbuf+4);
	    	break;
		case STATUS:
		case RUN:
	    case FILENAME:
	    case FILEDATA:
	    case IO:
	        break;
	    default:
	        break;
	    }
	//InData [1][Data max 64 bytes]
	//Response [2][Data max 64 bytes]

	//blink_led_on();
	//timer_sleep(TIMER_FREQUENCY_HZ);
	//USBD_CUSTOM_HID_SendReport(pdev, inbuf, 65); //Функция ставит в очередь передачу данных в PC

	//DumpData();
	//counter++;
}


// ----------------------------------------------------------------------------

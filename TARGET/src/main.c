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

void MX_GPIO_Init(void);
void USB_DEVICE_Init(void);


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
	  char s[65] = {};
	  //itoa(counter,s,10);


      trace_printf("RECV: %s\n", inbuf+1);

	  //InData [1][Data max 64 bytes]
	  len=strlen((char *)inbuf+1);
	  inbuf[len+1]=' ';
	  strcpy((char *)inbuf+len+2,s);
	  strcpy(s, (char*)inbuf+1);
	  inbuf[1]='c';
	  inbuf[2]='a';
	  inbuf[3]='m';
	  inbuf[4]='_';
	  strcpy((char *)inbuf+5, (char*)s);


	  //Response [2][Data max 64 bytes]
	  inbuf[0]=2; //report to PC (remove on PC side by driver)
	  blink_led_on();
	  //timer_sleep(TIMER_FREQUENCY_HZ);
	  USBD_CUSTOM_HID_SendReport(pdev, inbuf, 65); //Функция ставит в очередь передачу данных в PC

      trace_printf("SEND: %s\n", inbuf+1);

	  counter++;
}


// ----------------------------------------------------------------------------

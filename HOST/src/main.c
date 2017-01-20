#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hid.h"

#define wait_timeout 3000 //300

unsigned char TransmitBuffer[65];
unsigned char ReceiveBuffer[65];


int main(int argc, char* argv[])
{
	int ReceiveLength;

  	if(hid_open()>0){
		printf("HID device is opened (VID=0x483, PID=0x5711)\nHit any key (q - exit)\n");
	}else{
		printf("HID device is not opened\n");
		return 0;
	}

  	int fd = open("main.bc",O_RDONLY);
  	if (fd > 0){
		printf("FILE main.bc is opened\n");
	}else{
		printf("FILE main.bc is not opened\n");
		return 0;
	}

  	int head = 0;
  	int ReadLength = 0;
  	int size = 0;

  	TransmitBuffer[0]=1; //HID command send
  	TransmitBuffer[5]=0; //End of byte

  	ReadLength = read(fd, &head, sizeof(head));
  	size += ReadLength;

  	printf("HEAD: %c %c %x %x\n\n", head, head >> 8, head >> 16 & 0b11111111, head >> 24 & 0b11111111);

  	while (ReadLength > 0){
  		*(int*) (TransmitBuffer + 1) = head;
		//Всегда передаем 65 байт
		if(rawhid_send(0, TransmitBuffer, 65, wait_timeout)==-1){
			printf("HID device error\n");
			return 0;
		}

		//Всегда принимаем 65 байт
		ReceiveLength=rawhid_recv(0, ReceiveBuffer, 65, wait_timeout);
		if(ReceiveLength==-1){
			printf("HID device error\n");
			return 0;
		}

		printf("RECV (%d): %s\nDATA %d\n", ReceiveLength, ReceiveBuffer, size);
		ReadLength = read(fd, &head, sizeof(head));
	  	size += ReadLength;
	}


  	close(fd);


	TransmitBuffer[0]=1; //HID command send

	//strcpy((char *)TransmitBuffer+1,"Hello World");

	while ('q'!= getch()){
		scanf("%s", TransmitBuffer+1);
		//Всегда передаем 65 байт
		if(rawhid_send(0, TransmitBuffer, 65, wait_timeout)==-1){
			printf("HID device error\n");
			return 0;
		}

		//Всегда принимаем 65 байт
		ReceiveLength=rawhid_recv(0, ReceiveBuffer, 65, wait_timeout);
		if(ReceiveLength==-1){
			printf("HID device error\n");
			return 0;
		}

		printf("RECV (%d): %s\n", ReceiveLength, ReceiveBuffer);
	}
	return 0;
}




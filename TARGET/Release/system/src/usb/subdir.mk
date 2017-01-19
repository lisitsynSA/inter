################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/usb/usb_device.c \
../system/src/usb/usbd_conf.c \
../system/src/usb/usbd_core.c \
../system/src/usb/usbd_ctlreq.c \
../system/src/usb/usbd_custom_hid_if.c \
../system/src/usb/usbd_customhid.c \
../system/src/usb/usbd_desc.c \
../system/src/usb/usbd_ioreq.c 

OBJS += \
./system/src/usb/usb_device.o \
./system/src/usb/usbd_conf.o \
./system/src/usb/usbd_core.o \
./system/src/usb/usbd_ctlreq.o \
./system/src/usb/usbd_custom_hid_if.o \
./system/src/usb/usbd_customhid.o \
./system/src/usb/usbd_desc.o \
./system/src/usb/usbd_ioreq.o 

C_DEPS += \
./system/src/usb/usb_device.d \
./system/src/usb/usbd_conf.d \
./system/src/usb/usbd_core.d \
./system/src/usb/usbd_ctlreq.d \
./system/src/usb/usbd_custom_hid_if.d \
./system/src/usb/usbd_customhid.d \
./system/src/usb/usbd_desc.d \
./system/src/usb/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/usb/%.o: ../system/src/usb/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DSTM32F405xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"../system/include/usb" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



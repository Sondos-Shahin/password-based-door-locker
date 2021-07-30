################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Timer.c \
../device_functions.c \
../external_eeprom.c \
../i2c.c \
../lcd.c \
../main_slave.c \
../uart.c 

OBJS += \
./Timer.o \
./device_functions.o \
./external_eeprom.o \
./i2c.o \
./lcd.o \
./main_slave.o \
./uart.o 

C_DEPS += \
./Timer.d \
./device_functions.d \
./external_eeprom.d \
./i2c.d \
./lcd.d \
./main_slave.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



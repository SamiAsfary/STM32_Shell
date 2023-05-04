################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Shell/shell.c 

OBJS += \
./Drivers/Shell/shell.o 

C_DEPS += \
./Drivers/Shell/shell.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Shell/%.o Drivers/Shell/%.su Drivers/Shell/%.cyclo: ../Drivers/Shell/%.c Drivers/Shell/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Shell

clean-Drivers-2f-Shell:
	-$(RM) ./Drivers/Shell/shell.cyclo ./Drivers/Shell/shell.d ./Drivers/Shell/shell.o ./Drivers/Shell/shell.su

.PHONY: clean-Drivers-2f-Shell


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/iic.c \
../Core/Src/main.c \
../Core/Src/mpu6050.c \
../Core/Src/oled.c \
../Core/Src/rgb.c \
../Core/Src/spi.c \
../Core/Src/stm32g0xx_it.c \
../Core/Src/system_stm32g0xx.c \
../Core/Src/tim.c \
../Core/Src/uart.c \
../Core/Src/ws2812.c 

OBJS += \
./Core/Src/iic.o \
./Core/Src/main.o \
./Core/Src/mpu6050.o \
./Core/Src/oled.o \
./Core/Src/rgb.o \
./Core/Src/spi.o \
./Core/Src/stm32g0xx_it.o \
./Core/Src/system_stm32g0xx.o \
./Core/Src/tim.o \
./Core/Src/uart.o \
./Core/Src/ws2812.o 

C_DEPS += \
./Core/Src/iic.d \
./Core/Src/main.d \
./Core/Src/mpu6050.d \
./Core/Src/oled.d \
./Core/Src/rgb.d \
./Core/Src/spi.d \
./Core/Src/stm32g0xx_it.d \
./Core/Src/system_stm32g0xx.d \
./Core/Src/tim.d \
./Core/Src/uart.d \
./Core/Src/ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/iic.o: ../Core/Src/iic.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/iic.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/mpu6050.o: ../Core/Src/mpu6050.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/mpu6050.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/oled.o: ../Core/Src/oled.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/oled.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/rgb.o: ../Core/Src/rgb.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/rgb.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/spi.o: ../Core/Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/spi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32g0xx_it.o: ../Core/Src/stm32g0xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32g0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/system_stm32g0xx.o: ../Core/Src/system_stm32g0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32g0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/tim.o: ../Core/Src/tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/tim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/uart.o: ../Core/Src/uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/ws2812.o: ../Core/Src/ws2812.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' -DUSE_FULL_LL_DRIVER -DSTM32G030xx '-DPREFETCH_ENABLE=0' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/ws2812.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


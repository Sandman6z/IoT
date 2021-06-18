################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MX_G030.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MX_G030.list \

OBJCOPY_BIN += \
MX_G030.bin \


# All Target
all: MX_G030.elf secondary-outputs

# Tool invocations
MX_G030.elf: $(OBJS) $(USER_OBJS) C:\Users\zhong\Desktop\NETUBE\Dwarf_IOT_1\CUBEIDE\MX_G030\STM32G030C8TX_FLASH.ld
	arm-none-eabi-gcc -o "MX_G030.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\zhong\Desktop\NETUBE\Dwarf_IOT_1\CUBEIDE\MX_G030\STM32G030C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MX_G030.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MX_G030.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MX_G030.list"
	@echo 'Finished building: $@'
	@echo ' '

MX_G030.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "MX_G030.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

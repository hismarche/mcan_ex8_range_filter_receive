################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/arch" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet/third_party/lwip/lwip-2.1.2/src/include" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f2838x/driverlib" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=CPU1 --define=_FLASH --define=DEBUG --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/CPU1_FLASH/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

device/%.obj: ../device/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/arch" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet/third_party/lwip/lwip-2.1.2/src/include" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f2838x/driverlib" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=CPU1 --define=_FLASH --define=DEBUG --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/CPU1_FLASH/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



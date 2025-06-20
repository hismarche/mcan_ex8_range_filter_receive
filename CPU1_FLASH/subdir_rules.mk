################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-622680337: ../c2000.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2011/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/c2000.syscfg" -o "syscfg" -s "C:/ti/C2000Ware_5_04_00_00/.metadata/sdk.json" -d "F2838x" -p "337bga" -r "F2838x_337bga" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-622680337 ../c2000.syscfg
syscfg/board.h: build-622680337
syscfg/board.cmd.genlibs: build-622680337
syscfg/board.opt: build-622680337
syscfg/board.json: build-622680337
syscfg/pinmux.csv: build-622680337
syscfg/c2000ware_libraries.cmd.genlibs: build-622680337
syscfg/c2000ware_libraries.opt: build-622680337
syscfg/c2000ware_libraries.c: build-622680337
syscfg/c2000ware_libraries.h: build-622680337
syscfg/clocktree.h: build-622680337
syscfg: build-622680337

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/arch" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet/third_party/lwip/lwip-2.1.2/src/include" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f2838x/driverlib" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=CPU1 --define=_FLASH --define=DEBUG --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/CPU1_FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/arch" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet/third_party/lwip/lwip-2.1.2/src/include" --include_path="C:/ti/C2000Ware_5_04_00_00/libraries/communications/ethernet" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f2838x/driverlib" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=CPU1 --define=_FLASH --define=DEBUG --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/HismarFernandezBatre/workspace_ccstheia/mcan_ex8_range_filter_receive/CPU1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



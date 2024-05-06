#######################################
# download to mcu flash
#######################################
flash:
	openocd -f cmsis-dap.cfg -f stm32f1x.cfg -c  "program build/astra.elf verify reset exit"
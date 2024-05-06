#######################################
#use cmake build
#######################################
all:
	"C:/Program Files (x86)/GUNTOOLS/CMake/bin/cmake.exe" --build d:/STM32CubeIDE/oled-ui-astra/build --config Debug --target astra.elf --

#######################################
# download to mcu flash 
#######################################
flash: all
	openocd -f cmsis-dap.cfg -f stm32f1x.cfg -c  "program build/astra.elf verify reset exit"
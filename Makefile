#######################################
#use cmake build
#######################################
all:
	mkdir -p build
	"C:/Program Files (x86)/GUNTOOLS/CMake/bin/cmake.exe" --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE "-DCMAKE_C_COMPILER:FILEPATH=C:\Program Files (x86)\GUNTOOLS\arm-none-eabi-gcc-10.30-23\bin\arm-none-eabi-gcc.exe" "-DCMAKE_CXX_COMPILER:FILEPATH=C:\Program Files (x86)\GUNTOOLS\arm-none-eabi-gcc-10.30-23\bin\arm-none-eabi-g++.exe" -SD:/STM32CubeIDE/oled-ui-astra -Bd:/STM32CubeIDE/oled-ui-astra/build -G Ninja
	"C:/Program Files (x86)/GUNTOOLS/CMake/bin/cmake.exe" --build d:/STM32CubeIDE/oled-ui-astra/build --config Debug --target astra.elf --

#######################################
#clean project
#######################################
clean:
	rm -rf build
#######################################
# download to mcu flash 
#######################################
flash: all
	openocd -f cmsis-dap.cfg -f stm32f1x.cfg -c  "program build/astra.elf verify reset exit"
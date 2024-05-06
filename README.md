## powered by astra UI.

# [Releases](https://github.com/dcfsswindy/oled-ui-astra/releases)

# [Wiki](https://github.com/dcfsswindy/oled-ui-astra/wiki)

# [Video](https://www.bilibili.com/video/BV16x421S7qc)



# iic驱动的说明

iic的驱动的修改位置为Core\Src\hal\hal_dreamCore\components\oled\hal_oled.cpp

宏定义修改IIC_ODE即可切换原来的spi通道

# 开发环境

原工程是基于cubemx的6.4，0版本，我更新为了6.11.0版本

原工程是基于STM32cube ide的CMAKE工程，配个clion，我更新为了GNU工具链，配合vscode，后续会更新openocd的调试脚本文件

需要的GNU组件：arm-none-eabi-gcc,cmake,make,ninja,bc 以及 openocd

## powered by astra UI.

# [Releases](https://github.com/dcfsswindy/oled-ui-astra/releases)

# [Wiki](https://github.com/dcfsswindy/oled-ui-astra/wiki)

# [Video](https://www.bilibili.com/video/BV16x421S7qc)



# iic驱动的说明

iic的驱动的修改位置为Core\Src\hal\hal_dreamCore\components\oled\hal_oled.cpp

宏定义修改IIC_ODE即可切换原来的spi通道

由于手头没有103CBT6 主控我使用的是STM32103RCT6,按键引脚更改为了PC4 PC5

使用的是硬件IIC1 PB6->SCL  PB7->SDA FastMode 400k

# 开发环境

原工程是基于cubemx的6.4.0版本，我更新为了6.11.0版本

原工程是基于STM32cube ide的CMAKE工程,clion，我更新为了GNU工具链，配合vscode

在原camke基础上套了一层make以方便终端调试下载等

需要的GNU组件：arm-none-eabi-gcc,cmake,make,ninja,bc,openocd,git

注意:windows环境下执行make命令需要git的bash作为shell，powershell与cmd不能正常使用

## debug：

使用的是opencod调试,在.vscode文件夹内launch.json文件就是执行openocd的脚本命令

这个功能需要vscode 的 cortex-debug 插件支持; 并且将vscode的默认启动shell设置为bash(安装git后附带的终端)

同时你的openocd以及编译链路等不得有中文路径（如果你的windows用户名是中文的话：例如‘C:/User/喜羊羊’，有大概率卡进程，无法进入debug在线调试）

## 命令：

make  执行编译

make flash 编译并下载 使用的是daplink(如果需要使用stlink自行添stlink.cfg配置文件后修改makefile文件内对象即可)


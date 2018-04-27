# TLV5638_Driver

基于stm32f4单片机写的TLV5638驱动

使用标准库

[TOC]

##TLV5638

###芯片构造简图

![image-20180424213055979](https://github.com/Hehesheng/TLV5638_Driver/blob/master/README.assets/image-20180424213055979.png?raw=true)

### 时序图(SPI通讯)

![image-20180424213907834](/Users/huanghuisheng/Desktop/Mydesign/TLV5638_Driver/README.assets/image-20180424213907834.png)

- CS**下降沿**使能开始,上升沿结束
- 在SCLK的**下降沿**获取数据
- 一次数据**16位**

### 功能简述

> The TLV5638 is a dual 12-bit, single supply DAC, based on a resistor string architecture. It consists of a serial interface, a speed and power-down control logic, a programmable internal reference, a resistor string, and a rail-to-rail output buffer.

大致翻译:

> TLV5638双通道,12位单独DAC,寄存器控制

最大输出电压根据REF电压提供

计算:2REF*(CODE/0x1000)[V]

CODE Between 0x000 and 0xFFF

### 寄存器简介

- D15,D12: R1,R2(Mode control bit)

- D14: SPD(Speed control bit)

- D13: PWR(Power control bit)

- D0-D11: 12 Data bits

- D0,D1: REF0,REF1

  ​

  | SPD  |           | PWR  |                  |
  | :--: | :-------: | :--: | :--------------: |
  |  1   | fast mode |  1   |    power down    |
  |  0   | slow mode |  0   | normal operatiSP |

|  R1  |  R2  | Mode                                                     |
| :--: | :--: | :------------------------------------------------------- |
|  0   |  0   | Write data to DAC B and BUFFER                           |
|  0   |  1   | Write data to BUFFER                                     |
|  1   |  0   | Write data to DAC A and update DAC B with BUFFER content |
|  1   |  1   | Write data to control register                           |

如果是控制模式(R1,R2都置1),则

| REF1 | REF0 | Mode     |
| :--: | :--: | :------- |
|  0   |  0   | External |
|  0   |  1   | 1.024 V  |
|  1   |  0   | 2.048 V  |
|  1   |  1   | External |

### Example


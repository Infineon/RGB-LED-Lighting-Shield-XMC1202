# RGB-LED-Lighting-Shield-XMC1202

[![Build Status](https://travis-ci.org/Infineon/RGB-LED-Lighting-Shield-XMC1202.svg?branch=master)](https://travis-ci.org/Infineon/RGB-LED-Lighting-Shield-XMC1202)

<img src="https://www.infineon.com/export/sites/default/media/products/Microcontrollers/RGB_LED_Shield_with_XMC1202_plain.jpg_1716340521.jpg" width="300">

Library of Infineon's [RGB LED Lighting Shield XMC1202](https://www.infineon.com/cms/de/product/evaluation-boards/kit_led_xmc1202_as_01/) for Arduino.

## Summary
The [RGB LED Lighting Shield XMC1202](https://www.infineon.com/cms/de/product/evaluation-boards/kit_led_xmc1202_as_01/) from Infineon Technologies is one of the first intelligent evaluation boards compatible with Arduino as well as Infineon’s XMC evaluation boards. It is designed to be easily configurable and combinable for different LED light engines and lamps, for fast prototyping and in-expensive evaluation of LED lighting applications. 
The RGB LED Lighting Shield with XMC1202 uses a DC/DC buck topology and is able to drive up to 3 LED channels with constant current. The shield itself is powered by a programmable XMC 32-bit ARM® MCU with embedded Brightness Color Control Unit (BCCU, XMC1200 MCU series), for flicker-free LED dimming and color control. 
The BCCU enables extreme low-cost but high quality LED lighting solutions, with minimal user code. The RGB LED lighting shield has also been designed to provide options for the evaluation of smooth, eye-friendly dimming, color mixing for different topologies, and it can be extended with for example DALI/DMX or radar.

## Key Features and Benefits
* Compatible with Arduino Uno R3 and XMC1100 Boot Kit from Infineon
* Easy configurable for various light engines and any input voltage (within operating conditions)
* Wide DC input voltage range
* Simple I 2C interface
* Fast prototyping of LED lighting
* Flicker-free light thanks to high-speed pulse density modulation
* Easy-to-use dynamic dimming and color control
* Small size thanks to high-frequency current control (high power density)
* Backdoor access to on-board-microcontroller for advanced users and parameterization

## Quick Start and Board Manual
Please find the quick start guide [here](https://www.infineon.com/dgdl/Infineon-Quick_Start_Guide_RGB_LED_Lighting_Shield_with_XMC1202_for_Arduino.pdf-GS-v01_00-EN.pdf?fileId=5546d46249be182c0149cceef31d7373). The board manual can be found [here](https://www.infineon.com/dgdl/Infineon-Board_Manual_-_XMC1202_-_RGB_LED_Lighting_Shield_with_XMC1202_for_Arduino_-_v1_0-UM-v01_00-EN.pdf?fileId=5546d46249be182c0149ccca3860734d).

## Installation

### Integration of Library
Please download this repository from GitHub by clicking on the following field in the latest [release](https://github.com/Infineon/RGB-LED-Lighting-Shield-XMC1202/releases) of this repository or directly [here](https://github.com/Infineon/RGB-LED-Lighting-Shield-XMC1202/releases/download/v1.0.0/RGB-LED-Lighting-Shield-XMC1202.zip):

![Download Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Releases_Generic.jpg)

To install the RGB LED Lighting Shield XMC1202 library in the Arduino IDE, please go now to **Sketch** > **Include Library** > **Add .ZIP Library...** in the Arduino IDE and navigate to the downloaded .ZIP file of this repository. The library will be installed in your Arduino sketch folder in libraries and you can select as well as include this one to your project under **Sketch** > **Include Library** > **RGB LED Lighting Shield XMC1202**.

![Install Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Library_Install_ZIP.png)

## Usage
Please follow the example sketches in the /examples directory in this library to learn more about the usage of the library. For more information, please consult the board manual [here](https://www.infineon.com/dgdl/Infineon-Board_Manual_-_XMC1202_-_RGB_LED_Lighting_Shield_with_XMC1202_for_Arduino_-_v1_0-UM-v01_00-EN.pdf?fileId=5546d46249be182c0149ccca3860734d).

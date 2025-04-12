### CYD2USB v3 (ESP32-2432S028)

This project is a sample setup for the **ESP32-2432S028** (aka **CYD – Cheap Yellow Display**), featuring a 240x320 resistive touchscreen with an **ST7739** driver. It aims to help developers get started with the device, especially those who have struggled to get both the display and touchscreen working together.

## Why?

There are many ESP32-2432S028 clones, and not all are designed the same. For the particular device this sample targets, the touch controller and display controller are decoupled — one is connected via HSPI, the other via VSPI. While [Bodmer’s TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library is widely used for ESP32-controlled displays, it can be difficult—or even impossible—to get both the touchscreen and display working simultaneously on some CYD variants.

To address this, the [TFT_eTouch](https://github.com/achillhasler/TFT_eTouch) library is used to decouple the touchscreen GPIOs from the display ones.

That’s it, in a nutshell.

## Dependencies & configuration

This project is build in VS Code with PlatformIO, however feel free to manage it however you wish. Also, as said before, this project relies on ``TFT_eTouch`` library that needs to be added manually to ``.pio/libdeps/esp32doit-devkit-v1/`` upon clone or download & unzip. 

In the root directory you will also find ``User_Setup.h`` that is already pre-configured. Copy and replace it with the one in ``.pio/libdeps/esp32doit-devkit-v1/TFT_eSPI``.

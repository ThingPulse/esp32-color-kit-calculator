# esp32-color-kit-calculator

Sample project for the ESP32 Color Kit Grande. This project shows how to design a UI for LVGL with EEZ Studio (https://www.envox.eu/studio/studio-introduction/), run it on Mac OS X with SDL as well as port it to the ESP32 Color Kit Grande.

<img src="/resources/images/Calculator.png" alt="ESP32 Color Kit Grande" width="200"/>

## Working with the UI Editor

The project contains a file for the UI editor: Calculator.eez-project. You can open this file in the editor, edit it and export it to the project. All generated files are located in `src/ui/`. Never edit these files, as they will be overwritten with the next export from the UI editor. Follow these steps to start with the editor:

1. Download the editor from https://www.envox.eu/studio/studio-introduction/ and install the editor
2. Open the `Calculator.eez-project` file in the editor
3. Change UI according to your needs, e.g. change color or shape of the buttons.
4. Click the wrench icon in the toolbar to export your changes to the `src/ui` folder: <img src="/resources/images/EEZStudioToolbarWrench.png" alt="EEZ Studio Toolbar" width="200"/>
5. Run the application in the SDL2 emulator or the ESP32 Color Kit Grande

## Organization of the code

* `src/main.cpp`: main application file, only contains the loop for Arduino and SDL2
* `src/calculator.h`: contains the application logic for the calculator and the binding between UI and "business" logic. Also the callbacks for the buttons
* `src/ui`: code generated by the UI editor. Don't change this as it will be overwritten by the next export
* `hal/mac_arm64`: abstraction for the emulator running on Mac OS X (Apple Silicon)
* `hal/esp32`: abstraction for esp32. Place hardware specific code here.

## Supported Environments

Check out `platformio.ini` for currently supported environments. You can select a target by clicking on the `env:*` button in the footer of Visual Studio Code. This will show a popup window:

<img src="/resources/images/Environments.png" alt="ESP32 Color Kit Grande"/>

* mac_arm64: emulator for the UI to test and develop the UI on Mac OS X (Apple Silicon). Use this as a template to add support for Linux and Windows
* color-kit-grande: compile and run the calculator on the [https://thingpulse.com/products/color-kit-grande/](ThingPulse Color Kit Grande) 
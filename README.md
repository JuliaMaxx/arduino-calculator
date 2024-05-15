# Arduino Calculator with Keypad and LCD Display
## Live Preview: [Tinkercad simulation](https://www.tinkercad.com/things/cg71L9BXYzw-calculator?sharecode=8GIsgzeH8243MdvWXv1_LWUI52EgQwZqfvHf4XdYYgo)
![Calculator (2)](https://github.com/JuliaMaxx/arduino_calculator/assets/121096183/38378620-4c5c-4565-b552-e8add041b9fb)

## Overview
This project implements a simple calculator using an Arduino, a 4x4 keypad, and a 16x2 LCD display. The calculator allows users to perform basic arithmetic operations such as addition, subtraction, multiplication, and division.

## Components Used
- Arduino Uno
- 4x4 membrane keypad
- 16x2 LCD display with I2C interface
- Breadboard and jumper wires
- Lightbulb

## Libraries
- **LiquidCrystal_I2C:** This library allows easy interfacing with the I2C backpack for LCD displays.
- **Keypad:** The keypad library simplifies the handling of keypad inputs.

## Functionality
The calculator supports the following features:
- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/)
- Clearing the input (C)
- Calculating the result (=)

## How It Works
### Initialization
- The necessary libraries are included at the beginning of the code.
- Pins for the keypad rows and columns are defined, and a Keypad instance is created.
- The LCD display is initialized, and the backlight is turned on.

### Input Handling
- The loop continuously scans for keypad input.
- Upon pressing a key, the program checks if it corresponds to a valid input (numbers, operators, or the clear and equal sign).
- Depending on the current cursor position and input type, the program updates the display and stores the input values.

### Calculation
- When the equal sign is pressed and both operands are provided, the program performs the corresponding arithmetic operation.
- The result is displayed on the LCD screen.

### Clearing
- Pressing the 'C' key clears all input and resets the calculator.

## Usage
- Connect the keypad and LCD display to the Arduino following the pin mappings specified in the code.
- Upload the code to the Arduino board using the Arduino IDE or any compatible software.
- Once uploaded, the calculator is ready to use.
- Press keys on the keypad to input numbers and operators.
- Press '=' to calculate the result.
- Press 'C' to clear the input and start over.

## Notes
- The calculator supports integer input up to three digits.
- Division by zero is handled, and an error message is displayed in such cases.
- The result is displayed with one decimal point precision.

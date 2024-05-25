This project leverages the ESP8266 microcontroller along with a light sensor and a buzzer to encode and transmit Morse code messages. The decoded messages are displayed on an I2C-enabled LCD screen. 
This setup includes a laser module for transmitting Morse code signals using light.

Features->
Light and Sound Transmission: Utilizes a buzzer for sound and a laser module for light transmission of Morse code.
LCD Display: Features an I2C-enabled LCD screen that displays status updates and transmitted messages.
Customizable Timing: Adjustable Morse code timing for dot, dash, inter-symbol, inter-letter, and inter-word spaces.
Real-Time Encoding: Instantly encodes text input from the serial monitor into Morse code.

Components:
ESP8266 microcontroller
I2C LCD display
Buzzer
Laser module
Light sensor (LDR)
Breadboard and jumper wires
Appropriate resistors and transistors as shown in the schematic

Setup and Installation->
Assemble the Hardware:
Connect the components on the breadboard as shown in the schematic. Ensure to connect the I2C pins (SDA and SCL) correctly to the LCD.
Attach the buzzer and laser module directly to the breadboard or use extension cables as per your setup.
Adjust the contrast of the LCD if necessary using the adjustment screw on the back of the display.

Configure the Arduino Environment:
Upload the Morse code transmission sketch to the ESP8266 using the Arduino IDE.

Power the Device:
Connect the ESP8266 to a suitable power source such as a USB power adapter or battery pack.

Usage:
After powering up, use the serial monitor to send text messages to the ESP8266. The text will be converted into Morse code and transmitted via both sound (buzzer) and light (laser). Messages and status updates will be displayed on the LCD.

Hardware Schema: 
![image](https://github.com/hilmiserttas/MorseCodeTransmitter/assets/170796718/42ed165d-18c5-452c-8424-39385273839f)

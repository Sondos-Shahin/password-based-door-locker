# password-based-door-locker
it's an atmega16 based application that uses uart as a communication protocol between two MCU's 
one for the human interface which is connected to a keypad (to write the first password) and a lcd to
display the entered password and other massages ,and the second MCU is connected to the door(servo motor),
external eeprom(to store the first password) and a buzzer (a led that lights when the second password is entered repeatedly wrong for three times ) .

# HTTP Hacks - 2025 [Electro Hackers]
## Our Project Idea
Often, I have been up in my room when my wifi bugs out and stops working.  
The only way to fix it? Going all the way downstairs and resetting it.  
This project allows you to *wirelessly* reset your wifi with the press of a button.

## How it Works
It uses two ESP32s which communicate with each other using the "espnow" protocol.  
This protocol does not require the ESPs to connect to a network, so it's perfect for this application.

## How to use it
To use:
- Plug the black power supply into the wall
- Plug the USB-A into a USB-A receptacle (I recommend a computer port for ease)
- Press the button and hold it for at least 1 second

It's that simple! The code is precompiled onto the ESPs and does not need to be run again.  

## Expected Outcome
After the button is pressed for a moment, the router will turn off (indicated by the blue leds).  
In a short moment the router will turn back on (indicated by the blue leds).  


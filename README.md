# HTTP Hacks - 2025 [Electro Hackers]
## Our Project Idea
Often, I have been up in my room when my wifi bugs out and stops working.
The only way to fix it? Going all the way downstairs and resetting it.
This project allows you to reset your wifi with the press of a button.

## How it Works
It uses two ESP32s which communicate with each other using the "espnow" protocol.
This protocol does not require the ESPs to connect to a network, so it's perfect for this application.

# How to use it
To use:
- Press the button

It's that simple! The code is precompiled onto the ESPs and does not need to be run again, although it can be.

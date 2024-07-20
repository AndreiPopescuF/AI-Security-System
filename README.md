# AI Security System

## Introduction

The following project consists of developing a security system with AI recognition that aims at detecting the presence of a person within a specified range and activating the alarm system, which is made up of the following steps:

•	Turning on the camera

•	Ringing the alarm

•	Showing a message for the intruder

•	Interpreting the images displayed by the camera

•	Accesible live images on the phone with the application Telegram

## Tehnical support

The hardware components used in this project to provide the necessary functionalities are as following:

•	1 Microcontroller ESP32-Wrover 

•	1 Microcontroller ESP32 CAM

•	1 Distance sensor HC-SR04

•	1 Buzzer

•	1 LED Dot Matrix Display

Image 1. Schematic of the components

![image](https://github.com/user-attachments/assets/db17a792-5de2-437b-ac0f-fb3461c7ba6d)

The components are connected as such:

•	HC-SR04 – VCC to 5V; GND to GND; TRIG to PIN 15; ECHO to PIN 14;

•	LED Dot Matrix Display – VCC to 5V; GND to GND; DIN to PIN 23; CS to PIN 5; CLK to PIN 18;

•	Buzzer – VCC to 5V; GND to GND;

## Functionality

Upon the detection of presence by the distance sensor, the camera on the ESP32 CAM is turned on, the buzzer starts ringing the alarm, the message “Intruder” is shown on to the LED Matrix and the images are interpreted with Tensorflow in Python to check for human presence.

Image 2. The interpreted image by the AI

![image](https://github.com/user-attachments/assets/0c871208-95b3-4cb4-8689-1a7e391de5bc)

The ESP32 Wrover communicates with the ESP32 CAM through the CoAP protocol, sending the signal “0” when the distance is greater than 30 cm, and the signal “1” when the distance is smaller than 30 cm, which is when the system begins.

The user can request for live images with the help of the Telegram bot by sending the command “/photo” on the phone



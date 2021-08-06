# Simple TX

Simple open RC transmitter. Inspired by OpenTX mixer. Based on Pic-txmod.

## Development Environment

This project assumes the following set-up:

- [Microchip XC8](http://www.microchip.com/mplab/compilers) compiler
- [usbpicprog](http://usbpicprog.org/) programmer
- GNU make

## Build, Install etc.

Read the Makefile. The available commands are fairly obvious. The following are the most commonly used commands:

    make          ;# builds project 
    make tidy     ;# deletes temporary build files
    make clean    ;# deletes all generated files
    make install  ;# upload/burn program to CPU
    make verify   ;# verify uploaded program
    make backup   ;# download program from CPU (including trim settings)
    make restore  ;# upload/burn backup to CPU



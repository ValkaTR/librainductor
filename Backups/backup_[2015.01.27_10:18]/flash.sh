#!/bin/bash

#screen /dev/ttyACM0 1200
stty --file /dev/ttyACM0 1200
#bossac -i -d --port=ttyACM0 -U false -e -w -v -b build/librainductor.cpp.bin -R
bossac --info --port=ttyACM0 --force_usb_port false --erase --write --boot=1 build/librainductor.cpp.bin --reset
screen /dev/ttyACM0 115200

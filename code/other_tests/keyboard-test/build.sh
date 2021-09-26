#!/bin/sh

set -e

arduino-cli compile --fqbn adafruit:avr:feather32u4 adafruit:avr
arduino-cli upload -p /dev/ttyACM0 --fqbn adafruit:avr:feather32u4 adafruit:avr

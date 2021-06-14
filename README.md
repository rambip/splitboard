# Splitboard

This is the ressources we use to create our split, type matrix, bluetooth, mecanical custom keyboard.


Still in construction !

We used a lot of different technologies (solidworks for example), so you probably will not be able to recreate exactly the same keyboard.

But we added ressources you can use if you want to make your own !


![3d model](img/3d_1.png)

![result1](img/result1.png)

## Description

pcb + 3d-printed box + aluminium plate + brown switches + adafruit feather 32u4

### Design goals:

- comfortable
	Ergonomics was the first goal of this model.
	Even if we had to make tradeoffs, the first choices (2 parts, mechanical switches, design of a new layout) were made to increase comfort.

- portable
	It is a tiny keyboard: 46 keys, measure less than 24x12 cm
	Every key has to be reachable without moving your hands at all !


- robust
	I didn't broke it yet !
	

- usb and bluetooth

Our keyboard supports usb and bluetooth (BLE) communication with the *hid* specification.


## Content:

 - board design, with all components (kicad and gerber files) -> `pcb`
 - arduino code -> `code`
 - 3d modeling of the entire keyboard (solidworks and printable files) -> `3d`


## 3d structure:

multiple layers:

- support

- box

- pcb

- plate

- switches

We chose the [cherry mx brown](https://www.cherrymx.de/en/mx-original/mx-brown.html).

Before buying, try to find a second-hand broken keyboard somewhere !

## PCB and electronics:

We used the [adafruit 32u4](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview).

Go check out their [github account](https://github.com/adafruit), they have a lot of cool stuff !



## Software:

### Arduino

you can test our sketches if you have a 32u4 adafruit feather.


linux with arduino-cli:

First, make sure you are part of the `uucp` group.
If not, use the command `gpasswd -a $USER uucp`

`arduino-cli core install adafruit:avr`

find the board connected to usb (look at the *Port* path):
`arduino-cli board list` 

`arduino-cli board attach adafruit:avr:feather32u4`
`arduino-cli compile`
`arduino-cli upload`


### Ressources:
https://wiki.osdev.org/USB_Human_Interface_Devices


## TODO:

- [ ] convert all 3d modeling to .step
- [ ] add links to documentation
- [ ] code

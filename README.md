# 1-Wire addresses (uint8_t)

* Main bus listener: 'M'
* Rotary encoders: 'R'
* Potentiometers: 'P'
* Vertical Linear Potentiometers 'V'
* Horizontal Linear Potentiometers 'H'
* Buttons: 'B'
* Start: 'S'


# 1-Wire Mixer commands

## Declare link to the wall \[4 Bytes\]

* Serder type (see 1-Wire address for types) \[1 Byte\]
* Link command 'L' \[1 Byte\]
* Mixer coordinate \[1 Byte\]
* Wall coordinate \[1 Byte\]


## Break link to the wall \[4 Bytes\]

* Serder type (see 1-Wire address for types) \[1 Byte\]
* Unlink command 'U' \[1 Byte\]
* Mixer coordinate \[1 Byte\]
* Wall coordinate \[1 Byte\]


## Send controler value \[3 Bytes\]

* Serder type (see 1-Wire address for types) \[1 Byte\]
* Mixer coordinate \[1 Byte\]
* Value command 'V' \[1 Byte\]

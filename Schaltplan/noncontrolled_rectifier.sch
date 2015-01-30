EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:omron_g2r-1
LIBS:schrak_-_rt425024
LIBS:takamisawa_-_na24w-k
LIBS:te_connectivity
LIBS:valkatr
LIBS:arduino_shieldsNCL
LIBS:libreinductor-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 12
Title ""
Date "20 nov 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4900 4300 5500 4300
Wire Wire Line
	5500 4300 6200 4300
$Comp
L DIODE D?
U 1 1 544EDFCD
P 4900 2700
F 0 "D?" H 4900 2800 40  0000 C CNN
F 1 "DIODE" H 4900 2600 40  0000 C CNN
F 2 "~" H 4900 2700 60  0000 C CNN
F 3 "~" H 4900 2700 60  0000 C CNN
	1    4900 2700
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 544EDFD3
P 4900 3900
F 0 "D?" H 4900 4000 40  0000 C CNN
F 1 "DIODE" H 4900 3800 40  0000 C CNN
F 2 "~" H 4900 3900 60  0000 C CNN
F 3 "~" H 4900 3900 60  0000 C CNN
	1    4900 3900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 544EDFD9
P 5500 2700
F 0 "D?" H 5500 2800 40  0000 C CNN
F 1 "DIODE" H 5500 2600 40  0000 C CNN
F 2 "~" H 5500 2700 60  0000 C CNN
F 3 "~" H 5500 2700 60  0000 C CNN
	1    5500 2700
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 544EDFDF
P 5500 3900
F 0 "D?" H 5500 4000 40  0000 C CNN
F 1 "DIODE" H 5500 3800 40  0000 C CNN
F 2 "~" H 5500 3900 60  0000 C CNN
F 3 "~" H 5500 3900 60  0000 C CNN
	1    5500 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 2900 4900 3500
Wire Wire Line
	4900 3500 4900 3700
Wire Wire Line
	5500 2900 5500 3100
Wire Wire Line
	5500 3100 5500 3700
Wire Wire Line
	4600 3500 4900 3500
Connection ~ 4900 3500
Wire Wire Line
	4600 3100 5500 3100
Connection ~ 5500 3100
Wire Wire Line
	4900 2500 4900 2300
Wire Wire Line
	4900 2300 5500 2300
Wire Wire Line
	5500 2300 6200 2300
Wire Wire Line
	5500 2300 5500 2500
Wire Wire Line
	4900 4100 4900 4300
Wire Wire Line
	5500 4300 5500 4100
Connection ~ 5500 2300
Connection ~ 5500 4300
Text HLabel 4600 3100 0    60   Input ~ 0
IN2
Text HLabel 4600 3500 0    60   Input ~ 0
IN1
Text HLabel 6200 2300 2    60   Output ~ 0
OUT2
Text HLabel 6200 4300 2    60   Output ~ 0
OUT1
$EndSCHEMATC

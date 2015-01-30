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
Sheet 2 12
Title ""
Date "20 nov 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_MEGA_SHIELD SHIELD?
U 1 1 54515ED2
P 3900 3750
F 0 "SHIELD?" H 3500 6250 60  0000 C CNN
F 1 "ARDUINO_MEGA_SHIELD" H 3800 1050 60  0000 C CNN
F 2 "" H 3900 3750 60  0000 C CNN
F 3 "" H 3900 3750 60  0000 C CNN
	1    3900 3750
	1    0    0    -1  
$EndComp
Text Label 4950 5650 0    60   ~ 0
PWML0
Text Label 4950 5750 0    60   ~ 0
PWMH0
Text Label 4950 5850 0    60   ~ 0
PWML1
Text Label 4950 5950 0    60   ~ 0
PWMH1
Text Label 2750 6200 2    60   ~ 0
PWML2
Text Label 2750 6100 2    60   ~ 0
PWMH2
Text Label 2750 6000 2    60   ~ 0
PWML3
Text Label 2750 5900 2    60   ~ 0
PWMH3
Wire Wire Line
	4800 5650 5400 5650
Wire Wire Line
	4800 5750 5400 5750
Wire Wire Line
	4800 5850 5400 5850
Wire Wire Line
	4800 5950 5400 5950
Wire Wire Line
	2900 5900 2750 5900
Wire Wire Line
	2900 6000 2750 6000
Wire Wire Line
	2900 6100 2750 6100
Wire Wire Line
	2900 6200 2750 6200
Text HLabel 5400 5650 2    60   Output ~ 0
GATE_1L
Text HLabel 5400 5750 2    60   Output ~ 0
GATE_1H
Text HLabel 5400 5850 2    60   Output ~ 0
GATE_2L
Text HLabel 5400 5950 2    60   Output ~ 0
GATE_2H
Text HLabel 5000 2800 2    60   Input ~ 0
START
Text HLabel 5000 2700 2    60   Input ~ 0
STOP
Text HLabel 2700 2500 0    60   Input ~ 0
AD0
Text HLabel 2700 2600 0    60   Input ~ 0
AD1
Wire Wire Line
	4800 2700 5000 2700
Wire Wire Line
	4800 2800 5000 2800
Wire Wire Line
	2900 2500 2700 2500
Wire Wire Line
	2700 2600 2900 2600
Text HLabel 2700 2700 0    60   Input ~ 0
AD2
Text HLabel 2700 2800 0    60   Input ~ 0
AD3
Text HLabel 2700 2900 0    60   Input ~ 0
AD4
Wire Wire Line
	2700 2700 2900 2700
Wire Wire Line
	2700 2800 2900 2800
Wire Wire Line
	2700 2900 2900 2900
Text HLabel 2700 3000 0    60   Input ~ 0
AD5
Wire Wire Line
	2700 3000 2900 3000
$EndSCHEMATC

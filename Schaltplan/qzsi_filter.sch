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
Sheet 4 12
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
L INDUCTOR L?
U 1 1 544F2B44
P 4700 2800
F 0 "L?" V 4650 2800 40  0000 C CNN
F 1 "INDUCTOR" V 4800 2800 40  0000 C CNN
F 2 "~" H 4700 2800 60  0000 C CNN
F 3 "~" H 4700 2800 60  0000 C CNN
	1    4700 2800
	0    -1   -1   0   
$EndComp
$Comp
L INDUCTOR L?
U 1 1 544F2B4A
P 6500 2800
F 0 "L?" V 6450 2800 40  0000 C CNN
F 1 "INDUCTOR" V 6600 2800 40  0000 C CNN
F 2 "~" H 6500 2800 60  0000 C CNN
F 3 "~" H 6500 2800 60  0000 C CNN
	1    6500 2800
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 544F2B50
P 6000 3800
F 0 "C?" H 6000 3900 40  0000 L CNN
F 1 "C" H 6006 3715 40  0000 L CNN
F 2 "~" H 6038 3650 30  0000 C CNN
F 3 "~" H 6000 3800 60  0000 C CNN
	1    6000 3800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 544F2B56
P 6000 2300
F 0 "C?" H 6000 2400 40  0000 L CNN
F 1 "C" H 6006 2215 40  0000 L CNN
F 2 "~" H 6038 2150 30  0000 C CNN
F 3 "~" H 6000 2300 60  0000 C CNN
	1    6000 2300
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 544F2B5C
P 5600 2800
F 0 "D?" H 5600 2900 40  0000 C CNN
F 1 "DIODE" H 5600 2700 40  0000 C CNN
F 2 "~" H 5600 2800 60  0000 C CNN
F 3 "~" H 5600 2800 60  0000 C CNN
	1    5600 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2800 5200 2800
Wire Wire Line
	5200 2800 5400 2800
Wire Wire Line
	5200 2800 5200 2300
Wire Wire Line
	5200 2300 5800 2300
Connection ~ 5200 2800
Wire Wire Line
	6200 2300 7000 2300
Wire Wire Line
	7000 2300 7000 2800
Wire Wire Line
	6800 2800 7000 2800
Wire Wire Line
	7000 2800 7450 2800
Wire Wire Line
	5800 2800 6000 2800
Wire Wire Line
	6000 2800 6200 2800
Wire Wire Line
	6000 2800 6000 3600
Connection ~ 6000 2800
Wire Wire Line
	6000 4800 6000 4000
Wire Wire Line
	3700 4800 6000 4800
Wire Wire Line
	6000 4800 7450 4800
Connection ~ 6000 4800
Wire Wire Line
	3700 2800 4400 2800
Connection ~ 7000 2800
Text Notes 6200 3150 0    60   ~ 0
Voltage Fed qZSI with\nContinuous Input Current\nFilter
Text HLabel 3700 2800 0    60   Input ~ 0
IN2
Text HLabel 3700 4800 0    60   Input ~ 0
IN1
Text HLabel 7450 2800 2    60   Output ~ 0
OUT2
Text HLabel 7450 4800 2    60   Output ~ 0
OUT1
$EndSCHEMATC

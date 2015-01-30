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
Sheet 10 12
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
L TRANSFO T?
U 1 1 54517BCD
P 2200 2400
F 0 "T?" H 2200 2650 70  0000 C CNN
F 1 "TRANSFO" H 2200 2100 70  0000 C CNN
F 2 "~" H 2200 2400 60  0000 C CNN
F 3 "~" H 2200 2400 60  0000 C CNN
	1    2200 2400
	1    0    0    -1  
$EndComp
$Comp
L DIODE D?
U 1 1 54517BDC
P 3200 1900
F 0 "D?" H 3200 2000 40  0000 C CNN
F 1 "DIODE" H 3200 1800 40  0000 C CNN
F 2 "~" H 3200 1900 60  0000 C CNN
F 3 "~" H 3200 1900 60  0000 C CNN
	1    3200 1900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 54517BEB
P 3700 1900
F 0 "D?" H 3700 2000 40  0000 C CNN
F 1 "DIODE" H 3700 1800 40  0000 C CNN
F 2 "~" H 3700 1900 60  0000 C CNN
F 3 "~" H 3700 1900 60  0000 C CNN
	1    3700 1900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 54517BFA
P 3200 2900
F 0 "D?" H 3200 3000 40  0000 C CNN
F 1 "DIODE" H 3200 2800 40  0000 C CNN
F 2 "~" H 3200 2900 60  0000 C CNN
F 3 "~" H 3200 2900 60  0000 C CNN
	1    3200 2900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D?
U 1 1 54517C09
P 3700 2900
F 0 "D?" H 3700 3000 40  0000 C CNN
F 1 "DIODE" H 3700 2800 40  0000 C CNN
F 2 "~" H 3700 2900 60  0000 C CNN
F 3 "~" H 3700 2900 60  0000 C CNN
	1    3700 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 2100 3200 2700
Wire Wire Line
	3700 2100 3700 2700
Wire Wire Line
	2600 2600 3200 2600
Connection ~ 3200 2600
Wire Wire Line
	2600 2200 3700 2200
Connection ~ 3700 2200
Wire Wire Line
	3200 1700 3200 1600
Wire Wire Line
	3200 1600 5400 1600
Wire Wire Line
	3700 1700 3700 1600
Connection ~ 3700 1600
Wire Wire Line
	3200 3100 3200 3200
Wire Wire Line
	3200 3200 6500 3200
Wire Wire Line
	3700 3100 3700 3200
Connection ~ 3700 3200
Text HLabel 1500 2200 0    60   Input ~ 0
L1
Text HLabel 1500 2600 0    60   Input ~ 0
N
Wire Wire Line
	1500 2200 1800 2200
Wire Wire Line
	1500 2600 1800 2600
$Comp
L C C?
U 1 1 54517CCD
P 4200 2400
F 0 "C?" H 4200 2500 40  0000 L CNN
F 1 "0.47 µF" H 4206 2315 40  0000 L CNN
F 2 "~" H 4238 2250 30  0000 C CNN
F 3 "~" H 4200 2400 60  0000 C CNN
	1    4200 2400
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 54517CDC
P 4600 2400
F 0 "C?" H 4600 2500 40  0000 L CNN
F 1 "0.1 µF" H 4606 2315 40  0000 L CNN
F 2 "~" H 4638 2250 30  0000 C CNN
F 3 "~" H 4600 2400 60  0000 C CNN
	1    4600 2400
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 54517CEB
P 5000 2400
F 0 "C?" H 5050 2500 50  0000 L CNN
F 1 "4.7 µF" H 5050 2300 50  0000 L CNN
F 2 "~" H 5000 2400 60  0000 C CNN
F 3 "~" H 5000 2400 60  0000 C CNN
	1    5000 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2200 4200 2100
Wire Wire Line
	4200 2100 5000 2100
Wire Wire Line
	5000 2100 5000 2200
Wire Wire Line
	4600 1300 4600 2200
Connection ~ 4600 2100
Wire Wire Line
	4200 2600 4200 2700
Wire Wire Line
	4200 2700 5000 2700
Wire Wire Line
	5000 2700 5000 2600
Wire Wire Line
	4600 2600 4600 3500
Connection ~ 4600 2700
Text HLabel 4800 3500 2    60   Output ~ 0
GND
Text HLabel 4800 1300 2    60   Output ~ 0
+7..12 V
Connection ~ 4600 1600
Connection ~ 4600 3200
Wire Wire Line
	4600 1300 4800 1300
Wire Wire Line
	4600 3500 4800 3500
$Comp
L LM7805 U?
U 1 1 54517F97
P 5800 1650
F 0 "U?" H 5950 1454 60  0000 C CNN
F 1 "LM7805" H 5800 1850 60  0000 C CNN
F 2 "" H 5800 1650 60  0000 C CNN
F 3 "" H 5800 1650 60  0000 C CNN
	1    5800 1650
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 54517FA4
P 6500 2400
F 0 "C?" H 6500 2500 40  0000 L CNN
F 1 "0.1 µF" H 6506 2315 40  0000 L CNN
F 2 "~" H 6538 2250 30  0000 C CNN
F 3 "~" H 6500 2400 60  0000 C CNN
	1    6500 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1600 7000 1600
Wire Wire Line
	6500 1600 6500 2200
Wire Wire Line
	6500 3200 6500 2600
Wire Wire Line
	5800 1900 5800 3200
Connection ~ 5800 3200
Text HLabel 7000 1600 2    60   Output ~ 0
+5 V
Connection ~ 6500 1600
$EndSCHEMATC

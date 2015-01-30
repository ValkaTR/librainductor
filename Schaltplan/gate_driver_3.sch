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
Sheet 8 12
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
L ROM-0512S D?
U 1 1 544B25BF
P 4050 4050
F 0 "D?" H 3750 4350 60  0000 L CNN
F 1 "ROM-0512S" H 3750 3750 60  0000 L CNN
F 2 "" H 4050 4050 60  0000 C CNN
F 3 "" H 4050 4050 60  0000 C CNN
	1    4050 4050
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 544B25C5
P 3150 2650
F 0 "R?" V 3230 2650 40  0000 C CNN
F 1 "700 Ω" V 3157 2651 40  0000 C CNN
F 2 "~" V 3080 2650 30  0000 C CNN
F 3 "~" H 3150 2650 30  0000 C CNN
	1    3150 2650
	0    -1   -1   0   
$EndComp
$Comp
L HCPL-2200 U?
U 1 1 544B25CB
P 4050 2500
F 0 "U?" H 3750 2650 60  0000 L CNN
F 1 "HCPL-2200" H 3750 1900 60  0000 L CNN
F 2 "" H 4150 2150 60  0000 C CNN
F 3 "" H 4150 2150 60  0000 C CNN
	1    4050 2500
	1    0    0    -1  
$EndComp
$Comp
L MCP14E10 U?
U 1 1 544B25D1
P 6100 2500
F 0 "U?" H 5800 2650 60  0000 L CNN
F 1 "MCP14E10" H 5800 1900 60  0000 L CNN
F 2 "" H 6200 2150 60  0000 C CNN
F 3 "" H 6200 2150 60  0000 C CNN
	1    6100 2500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 544B25D7
P 7350 2650
F 0 "R?" V 7430 2650 40  0000 C CNN
F 1 "40 Ω" V 7357 2651 40  0000 C CNN
F 2 "~" V 7280 2650 30  0000 C CNN
F 3 "~" H 7350 2650 30  0000 C CNN
	1    7350 2650
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 544B25DD
P 5500 3850
F 0 "C?" H 5500 3950 40  0000 L CNN
F 1 "470 nF" H 5506 3765 40  0000 L CNN
F 2 "~" H 5538 3700 30  0000 C CNN
F 3 "~" H 5500 3850 60  0000 C CNN
	1    5500 3850
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 544B25E3
P 3000 3900
F 0 "C?" H 3000 4000 40  0000 L CNN
F 1 "100 nF" H 3006 3815 40  0000 L CNN
F 2 "~" H 3038 3750 30  0000 C CNN
F 3 "~" H 3000 3900 60  0000 C CNN
	1    3000 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	2700 4200 3450 4200
Connection ~ 3000 4200
Wire Wire Line
	2700 3550 3300 3550
Wire Wire Line
	3000 3550 3000 3700
Wire Wire Line
	3300 3900 3450 3900
Connection ~ 3000 3550
Wire Wire Line
	3400 2650 3450 2650
Wire Wire Line
	2700 2800 3450 2800
Wire Wire Line
	6850 3550 4800 3550
Wire Wire Line
	5000 3550 5000 2500
Wire Wire Line
	4650 2500 5500 2500
Wire Wire Line
	4650 2950 5200 2950
Wire Wire Line
	5200 4200 5200 2800
Wire Wire Line
	4600 4200 8250 4200
Wire Wire Line
	5200 2800 5500 2800
Connection ~ 5200 2950
Connection ~ 5000 3550
Wire Wire Line
	4650 2650 5500 2650
Wire Wire Line
	5500 2950 5350 2950
Wire Wire Line
	5350 2950 5350 2650
Connection ~ 5350 2650
Wire Wire Line
	4650 2800 4800 2800
Connection ~ 5000 2500
Wire Wire Line
	4800 2800 4800 2950
Connection ~ 4800 2950
Wire Wire Line
	6700 2800 6850 2800
Wire Wire Line
	6850 2500 6850 3550
Wire Wire Line
	6700 2500 6850 2500
Connection ~ 6850 2800
$Comp
L R R?
U 1 1 544B2606
P 7350 2950
F 0 "R?" V 7430 2950 40  0000 C CNN
F 1 "40 Ω" V 7357 2951 40  0000 C CNN
F 2 "~" V 7280 2950 30  0000 C CNN
F 3 "~" H 7350 2950 30  0000 C CNN
	1    7350 2950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 2650 7100 2650
Wire Wire Line
	6700 2950 7100 2950
Wire Wire Line
	7600 2650 8250 2650
Wire Wire Line
	7600 2950 7800 2950
Wire Wire Line
	7800 2950 7800 2650
Connection ~ 7800 2650
Connection ~ 5200 4200
Text HLabel 2700 2650 0    60   Input ~ 0
IN
Text HLabel 2700 2800 0    60   Input ~ 0
DGND
Wire Wire Line
	2700 2650 2900 2650
Text HLabel 2700 3550 0    60   Input ~ 0
+5V
Text HLabel 2700 4200 0    60   Input ~ 0
PGND
Text HLabel 8250 2650 2    60   Output ~ 0
GATE
Text HLabel 8250 4200 2    60   Output ~ 0
EMITTER
Wire Wire Line
	3000 4100 3000 4200
Wire Wire Line
	3300 3550 3300 3900
Wire Wire Line
	4600 3900 4800 3900
Wire Wire Line
	4800 3900 4800 3550
Wire Wire Line
	5500 3650 5500 3550
Connection ~ 5500 3550
Wire Wire Line
	5500 4050 5500 4200
Connection ~ 5500 4200
$EndSCHEMATC

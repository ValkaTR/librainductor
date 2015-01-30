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
Sheet 9 12
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
U 1 1 544B4AD2
P 4350 3350
F 0 "D?" H 4050 3650 60  0000 L CNN
F 1 "ROM-0512S" H 4050 3050 60  0000 L CNN
F 2 "" H 4350 3350 60  0000 C CNN
F 3 "" H 4350 3350 60  0000 C CNN
	1    4350 3350
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 544B4AD8
P 3450 1950
F 0 "R?" V 3530 1950 40  0000 C CNN
F 1 "700 Ω" V 3457 1951 40  0000 C CNN
F 2 "~" V 3380 1950 30  0000 C CNN
F 3 "~" H 3450 1950 30  0000 C CNN
	1    3450 1950
	0    -1   -1   0   
$EndComp
$Comp
L HCPL-2200 U?
U 1 1 544B4ADE
P 4350 1800
F 0 "U?" H 4050 1950 60  0000 L CNN
F 1 "HCPL-2200" H 4050 1200 60  0000 L CNN
F 2 "" H 4450 1450 60  0000 C CNN
F 3 "" H 4450 1450 60  0000 C CNN
	1    4350 1800
	1    0    0    -1  
$EndComp
$Comp
L MCP14E10 U?
U 1 1 544B4AE4
P 6400 1800
F 0 "U?" H 6100 1950 60  0000 L CNN
F 1 "MCP14E10" H 6100 1200 60  0000 L CNN
F 2 "" H 6500 1450 60  0000 C CNN
F 3 "" H 6500 1450 60  0000 C CNN
	1    6400 1800
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 544B4AEA
P 7650 1950
F 0 "R?" V 7730 1950 40  0000 C CNN
F 1 "40 Ω" V 7657 1951 40  0000 C CNN
F 2 "~" V 7580 1950 30  0000 C CNN
F 3 "~" H 7650 1950 30  0000 C CNN
	1    7650 1950
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 544B4AF0
P 5800 3150
F 0 "C?" H 5800 3250 40  0000 L CNN
F 1 "470 nF" H 5806 3065 40  0000 L CNN
F 2 "~" H 5838 3000 30  0000 C CNN
F 3 "~" H 5800 3150 60  0000 C CNN
	1    5800 3150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 544B4AF6
P 3300 3200
F 0 "C?" H 3300 3300 40  0000 L CNN
F 1 "100 nF" H 3306 3115 40  0000 L CNN
F 2 "~" H 3338 3050 30  0000 C CNN
F 3 "~" H 3300 3200 60  0000 C CNN
	1    3300 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3000 3500 3750 3500
Connection ~ 3300 3500
Wire Wire Line
	3000 2850 3600 2850
Wire Wire Line
	3300 2850 3300 3000
Wire Wire Line
	3600 3200 3750 3200
Connection ~ 3300 2850
Wire Wire Line
	3700 1950 3750 1950
Wire Wire Line
	3000 2100 3750 2100
Wire Wire Line
	7150 2850 5100 2850
Wire Wire Line
	5300 2850 5300 1800
Wire Wire Line
	4950 1800 5800 1800
Wire Wire Line
	4950 2250 5500 2250
Wire Wire Line
	5500 3500 5500 2100
Wire Wire Line
	4900 3500 8550 3500
Wire Wire Line
	5500 2100 5800 2100
Connection ~ 5500 2250
Connection ~ 5300 2850
Wire Wire Line
	4950 1950 5800 1950
Wire Wire Line
	5800 2250 5650 2250
Wire Wire Line
	5650 2250 5650 1950
Connection ~ 5650 1950
Wire Wire Line
	4950 2100 5100 2100
Connection ~ 5300 1800
Wire Wire Line
	5100 2100 5100 2250
Connection ~ 5100 2250
Wire Wire Line
	7000 2100 7150 2100
Wire Wire Line
	7150 1800 7150 2850
Wire Wire Line
	7000 1800 7150 1800
Connection ~ 7150 2100
$Comp
L R R?
U 1 1 544B4B19
P 7650 2250
F 0 "R?" V 7730 2250 40  0000 C CNN
F 1 "40 Ω" V 7657 2251 40  0000 C CNN
F 2 "~" V 7580 2250 30  0000 C CNN
F 3 "~" H 7650 2250 30  0000 C CNN
	1    7650 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7000 1950 7400 1950
Wire Wire Line
	7000 2250 7400 2250
Wire Wire Line
	7900 1950 8550 1950
Wire Wire Line
	7900 2250 8100 2250
Wire Wire Line
	8100 2250 8100 1950
Connection ~ 8100 1950
Connection ~ 5500 3500
Text HLabel 3000 1950 0    60   Input ~ 0
IN
Text HLabel 3000 2100 0    60   Input ~ 0
DGND
Wire Wire Line
	3000 1950 3200 1950
Text HLabel 3000 2850 0    60   Input ~ 0
+5V
Text HLabel 3000 3500 0    60   Input ~ 0
PGND
Text HLabel 8550 1950 2    60   Output ~ 0
GATE
Text HLabel 8550 3500 2    60   Output ~ 0
EMITTER
Wire Wire Line
	3300 3400 3300 3500
Wire Wire Line
	3600 2850 3600 3200
Wire Wire Line
	4900 3200 5100 3200
Wire Wire Line
	5100 3200 5100 2850
Wire Wire Line
	5800 2950 5800 2850
Connection ~ 5800 2850
Wire Wire Line
	5800 3350 5800 3500
Connection ~ 5800 3500
$EndSCHEMATC

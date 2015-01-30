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
Sheet 6 12
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
U 1 1 54496A30
P 4250 4000
AR Path="/544969CF/54496A30" Ref="D?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A30" Ref="D?"  Part="1" 
F 0 "D?" H 3950 4300 60  0000 L CNN
F 1 "ROM-0512S" H 3950 3700 60  0000 L CNN
F 2 "" H 4250 4000 60  0000 C CNN
F 3 "" H 4250 4000 60  0000 C CNN
	1    4250 4000
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 54496A36
P 3350 2600
AR Path="/544969CF/54496A36" Ref="R?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A36" Ref="R?"  Part="1" 
F 0 "R?" V 3430 2600 40  0000 C CNN
F 1 "700 Ω" V 3357 2601 40  0000 C CNN
F 2 "~" V 3280 2600 30  0000 C CNN
F 3 "~" H 3350 2600 30  0000 C CNN
	1    3350 2600
	0    -1   -1   0   
$EndComp
$Comp
L HCPL-2200 U?
U 1 1 54496A3C
P 4250 2450
AR Path="/544969CF/54496A3C" Ref="U?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A3C" Ref="U?"  Part="1" 
F 0 "U?" H 3950 2600 60  0000 L CNN
F 1 "HCPL-2200" H 3950 1850 60  0000 L CNN
F 2 "" H 4350 2100 60  0000 C CNN
F 3 "" H 4350 2100 60  0000 C CNN
	1    4250 2450
	1    0    0    -1  
$EndComp
$Comp
L MCP14E10 U?
U 1 1 54496A42
P 6300 2450
AR Path="/544969CF/54496A42" Ref="U?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A42" Ref="U?"  Part="1" 
F 0 "U?" H 6000 2600 60  0000 L CNN
F 1 "MCP14E10" H 6000 1850 60  0000 L CNN
F 2 "" H 6400 2100 60  0000 C CNN
F 3 "" H 6400 2100 60  0000 C CNN
	1    6300 2450
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 54496A48
P 7550 2600
AR Path="/544969CF/54496A48" Ref="R?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A48" Ref="R?"  Part="1" 
F 0 "R?" V 7630 2600 40  0000 C CNN
F 1 "40 Ω" V 7557 2601 40  0000 C CNN
F 2 "~" V 7480 2600 30  0000 C CNN
F 3 "~" H 7550 2600 30  0000 C CNN
	1    7550 2600
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 54496A4E
P 5700 3800
AR Path="/544969CF/54496A4E" Ref="C?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A4E" Ref="C?"  Part="1" 
F 0 "C?" H 5700 3900 40  0000 L CNN
F 1 "470 nF" H 5706 3715 40  0000 L CNN
F 2 "~" H 5738 3650 30  0000 C CNN
F 3 "~" H 5700 3800 60  0000 C CNN
	1    5700 3800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 54496A60
P 3200 3850
AR Path="/544969CF/54496A60" Ref="C?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A60" Ref="C?"  Part="1" 
F 0 "C?" H 3200 3950 40  0000 L CNN
F 1 "100 nF" H 3206 3765 40  0000 L CNN
F 2 "~" H 3238 3700 30  0000 C CNN
F 3 "~" H 3200 3850 60  0000 C CNN
	1    3200 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 4150 3650 4150
Connection ~ 3200 4150
Wire Wire Line
	2900 3500 3500 3500
Wire Wire Line
	3200 3500 3200 3650
Wire Wire Line
	3500 3850 3650 3850
Connection ~ 3200 3500
Wire Wire Line
	3600 2600 3650 2600
Wire Wire Line
	2900 2750 3650 2750
Wire Wire Line
	7050 3500 5000 3500
Wire Wire Line
	5200 3500 5200 2450
Wire Wire Line
	4850 2450 5700 2450
Wire Wire Line
	4850 2900 5400 2900
Wire Wire Line
	5400 4150 5400 2750
Wire Wire Line
	4800 4150 8450 4150
Wire Wire Line
	5400 2750 5700 2750
Connection ~ 5400 2900
Connection ~ 5200 3500
Wire Wire Line
	4850 2600 5700 2600
Wire Wire Line
	5700 2900 5550 2900
Wire Wire Line
	5550 2900 5550 2600
Connection ~ 5550 2600
Wire Wire Line
	4850 2750 5000 2750
Connection ~ 5200 2450
Wire Wire Line
	5000 2750 5000 2900
Connection ~ 5000 2900
Wire Wire Line
	6900 2750 7050 2750
Wire Wire Line
	7050 2450 7050 3500
Wire Wire Line
	6900 2450 7050 2450
Connection ~ 7050 2750
$Comp
L R R?
U 1 1 54496A87
P 7550 2900
AR Path="/544969CF/54496A87" Ref="R?"  Part="1" 
AR Path="/544FB8C5/544969CF/54496A87" Ref="R?"  Part="1" 
F 0 "R?" V 7630 2900 40  0000 C CNN
F 1 "40 Ω" V 7557 2901 40  0000 C CNN
F 2 "~" V 7480 2900 30  0000 C CNN
F 3 "~" H 7550 2900 30  0000 C CNN
	1    7550 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 2600 7300 2600
Wire Wire Line
	6900 2900 7300 2900
Wire Wire Line
	7800 2600 8450 2600
Wire Wire Line
	7800 2900 8000 2900
Wire Wire Line
	8000 2900 8000 2600
Connection ~ 8000 2600
Connection ~ 5400 4150
Text HLabel 2900 2600 0    60   Input ~ 0
IN
Text HLabel 2900 2750 0    60   Input ~ 0
DGND
Wire Wire Line
	2900 2600 3100 2600
Text HLabel 2900 3500 0    60   Input ~ 0
+5V
Text HLabel 2900 4150 0    60   Input ~ 0
PGND
Text HLabel 8450 2600 2    60   Output ~ 0
GATE
Text HLabel 8450 4150 2    60   Output ~ 0
EMITTER
Wire Wire Line
	3200 4050 3200 4150
Wire Wire Line
	3500 3500 3500 3850
Wire Wire Line
	4800 3850 5000 3850
Wire Wire Line
	5000 3850 5000 3500
Wire Wire Line
	5700 3600 5700 3500
Connection ~ 5700 3500
Wire Wire Line
	5700 4000 5700 4150
Connection ~ 5700 4150
$EndSCHEMATC

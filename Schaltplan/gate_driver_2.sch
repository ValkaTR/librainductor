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
Sheet 7 12
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
U 1 1 544ADD54
P 4000 4050
AR Path="/544AD8DC/544ADD54" Ref="D?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD54" Ref="D?"  Part="1" 
F 0 "D?" H 3700 4350 60  0000 L CNN
F 1 "ROM-0512S" H 3700 3750 60  0000 L CNN
F 2 "" H 4000 4050 60  0000 C CNN
F 3 "" H 4000 4050 60  0000 C CNN
	1    4000 4050
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 544ADD5A
P 3100 2650
AR Path="/544AD8DC/544ADD5A" Ref="R?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD5A" Ref="R?"  Part="1" 
F 0 "R?" V 3180 2650 40  0000 C CNN
F 1 "700 Ω" V 3107 2651 40  0000 C CNN
F 2 "~" V 3030 2650 30  0000 C CNN
F 3 "~" H 3100 2650 30  0000 C CNN
	1    3100 2650
	0    -1   -1   0   
$EndComp
$Comp
L HCPL-2200 U?
U 1 1 544ADD60
P 4000 2500
AR Path="/544AD8DC/544ADD60" Ref="U?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD60" Ref="U?"  Part="1" 
F 0 "U?" H 3700 2650 60  0000 L CNN
F 1 "HCPL-2200" H 3700 1900 60  0000 L CNN
F 2 "" H 4100 2150 60  0000 C CNN
F 3 "" H 4100 2150 60  0000 C CNN
	1    4000 2500
	1    0    0    -1  
$EndComp
$Comp
L MCP14E10 U?
U 1 1 544ADD66
P 6050 2500
AR Path="/544AD8DC/544ADD66" Ref="U?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD66" Ref="U?"  Part="1" 
F 0 "U?" H 5750 2650 60  0000 L CNN
F 1 "MCP14E10" H 5750 1900 60  0000 L CNN
F 2 "" H 6150 2150 60  0000 C CNN
F 3 "" H 6150 2150 60  0000 C CNN
	1    6050 2500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 544ADD6C
P 7300 2650
AR Path="/544AD8DC/544ADD6C" Ref="R?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD6C" Ref="R?"  Part="1" 
F 0 "R?" V 7380 2650 40  0000 C CNN
F 1 "40 Ω" V 7307 2651 40  0000 C CNN
F 2 "~" V 7230 2650 30  0000 C CNN
F 3 "~" H 7300 2650 30  0000 C CNN
	1    7300 2650
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 544ADD72
P 5450 3850
AR Path="/544AD8DC/544ADD72" Ref="C?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD72" Ref="C?"  Part="1" 
F 0 "C?" H 5450 3950 40  0000 L CNN
F 1 "470 nF" H 5456 3765 40  0000 L CNN
F 2 "~" H 5488 3700 30  0000 C CNN
F 3 "~" H 5450 3850 60  0000 C CNN
	1    5450 3850
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 544ADD78
P 2950 3900
AR Path="/544AD8DC/544ADD78" Ref="C?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD78" Ref="C?"  Part="1" 
F 0 "C?" H 2950 4000 40  0000 L CNN
F 1 "100 nF" H 2956 3815 40  0000 L CNN
F 2 "~" H 2988 3750 30  0000 C CNN
F 3 "~" H 2950 3900 60  0000 C CNN
	1    2950 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	2650 4200 3400 4200
Connection ~ 2950 4200
Wire Wire Line
	2650 3550 3250 3550
Wire Wire Line
	2950 3550 2950 3700
Wire Wire Line
	3250 3900 3400 3900
Connection ~ 2950 3550
Wire Wire Line
	3350 2650 3400 2650
Wire Wire Line
	2650 2800 3400 2800
Wire Wire Line
	6800 3550 4750 3550
Wire Wire Line
	4950 3550 4950 2500
Wire Wire Line
	4600 2500 5450 2500
Wire Wire Line
	4600 2950 5150 2950
Wire Wire Line
	5150 4200 5150 2800
Wire Wire Line
	4550 4200 8200 4200
Wire Wire Line
	5150 2800 5450 2800
Connection ~ 5150 2950
Connection ~ 4950 3550
Wire Wire Line
	4600 2650 5450 2650
Wire Wire Line
	5450 2950 5300 2950
Wire Wire Line
	5300 2950 5300 2650
Connection ~ 5300 2650
Wire Wire Line
	4600 2800 4750 2800
Connection ~ 4950 2500
Wire Wire Line
	4750 2800 4750 2950
Connection ~ 4750 2950
Wire Wire Line
	6650 2800 6800 2800
Wire Wire Line
	6800 2500 6800 3550
Wire Wire Line
	6650 2500 6800 2500
Connection ~ 6800 2800
$Comp
L R R?
U 1 1 544ADD9B
P 7300 2950
AR Path="/544AD8DC/544ADD9B" Ref="R?"  Part="1" 
AR Path="/544FB8C5/544AD8DC/544ADD9B" Ref="R?"  Part="1" 
F 0 "R?" V 7380 2950 40  0000 C CNN
F 1 "40 Ω" V 7307 2951 40  0000 C CNN
F 2 "~" V 7230 2950 30  0000 C CNN
F 3 "~" H 7300 2950 30  0000 C CNN
	1    7300 2950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 2650 7050 2650
Wire Wire Line
	6650 2950 7050 2950
Wire Wire Line
	7550 2650 8200 2650
Wire Wire Line
	7550 2950 7750 2950
Wire Wire Line
	7750 2950 7750 2650
Connection ~ 7750 2650
Connection ~ 5150 4200
Text HLabel 2650 2650 0    60   Input ~ 0
IN
Text HLabel 2650 2800 0    60   Input ~ 0
DGND
Wire Wire Line
	2650 2650 2850 2650
Text HLabel 2650 3550 0    60   Input ~ 0
+5V
Text HLabel 2650 4200 0    60   Input ~ 0
PGND
Text HLabel 8200 2650 2    60   Output ~ 0
GATE
Text HLabel 8200 4200 2    60   Output ~ 0
EMITTER
Wire Wire Line
	2950 4100 2950 4200
Wire Wire Line
	3250 3550 3250 3900
Wire Wire Line
	4550 3900 4750 3900
Wire Wire Line
	4750 3900 4750 3550
Wire Wire Line
	5450 3650 5450 3550
Connection ~ 5450 3550
Wire Wire Line
	5450 4050 5450 4200
Connection ~ 5450 4200
$EndSCHEMATC

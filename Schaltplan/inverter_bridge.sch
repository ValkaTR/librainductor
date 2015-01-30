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
Sheet 5 12
Title ""
Date "20 nov 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3050 2600 850  600 
U 544969CF
F0 "Gate Driver - 1 High" 50
F1 "gate_driver_1.sch" 50
F2 "IN" I L 3050 2700 60 
F3 "DGND" I L 3050 2800 60 
F4 "+5V" I L 3050 3000 60 
F5 "PGND" I L 3050 3100 60 
F6 "GATE" O R 3900 2700 60 
F7 "EMITTER" O R 3900 2800 60 
$EndSheet
$Comp
L IGBT_N Q1H?
U 1 1 544FFF22
P 4500 3050
F 0 "Q1H?" H 4375 3350 60  0000 R CNN
F 1 "IGBT_N" H 4400 2950 60  0000 R CNN
F 2 "~" H 4500 3150 60  0000 C CNN
F 3 "~" H 4500 3150 60  0000 C CNN
	1    4500 3050
	1    0    0    -1  
$EndComp
$Comp
L IGBT_N Q1L?
U 1 1 544FFF28
P 4500 5250
F 0 "Q1L?" H 4375 5550 60  0000 R CNN
F 1 "IGBT_N" H 4400 5150 60  0000 R CNN
F 2 "~" H 4500 5350 60  0000 C CNN
F 3 "~" H 4500 5350 60  0000 C CNN
	1    4500 5250
	1    0    0    -1  
$EndComp
$Comp
L IGBT_N Q2H?
U 1 1 544FFF2E
P 7200 3050
F 0 "Q2H?" H 7075 3350 60  0000 R CNN
F 1 "IGBT_N" H 7100 2950 60  0000 R CNN
F 2 "~" H 7200 3150 60  0000 C CNN
F 3 "~" H 7200 3150 60  0000 C CNN
	1    7200 3050
	1    0    0    -1  
$EndComp
$Comp
L IGBT_N Q2L?
U 1 1 544FFF34
P 7200 5250
F 0 "Q2L?" H 7075 5550 60  0000 R CNN
F 1 "IGBT_N" H 7100 5150 60  0000 R CNN
F 2 "~" H 7200 5350 60  0000 C CNN
F 3 "~" H 7200 5350 60  0000 C CNN
	1    7200 5250
	1    0    0    -1  
$EndComp
$Sheet
S 5750 2600 850  600 
U 544AD8DC
F0 "Gate Driver - 2 High" 50
F1 "gate_driver_2.sch" 50
F2 "IN" I L 5750 2700 60 
F3 "DGND" I L 5750 2800 60 
F4 "+5V" I L 5750 3000 60 
F5 "PGND" I L 5750 3100 60 
F6 "GATE" O R 6600 2700 60 
F7 "EMITTER" O R 6600 2800 60 
$EndSheet
$Sheet
S 3050 4800 850  600 
U 544AD902
F0 "Gate Driver - 1 Low" 50
F1 "gate_driver_3.sch" 50
F2 "IN" I L 3050 4900 60 
F3 "DGND" I L 3050 5000 60 
F4 "+5V" I L 3050 5200 60 
F5 "PGND" I L 3050 5300 60 
F6 "GATE" O R 3900 4900 60 
F7 "EMITTER" O R 3900 5000 60 
$EndSheet
$Sheet
S 5750 4800 850  600 
U 544AD904
F0 "Gate Driver  - 2 Low" 50
F1 "gate_driver_4.sch" 50
F2 "IN" I L 5750 4900 60 
F3 "DGND" I L 5750 5000 60 
F4 "+5V" I L 5750 5200 60 
F5 "PGND" I L 5750 5300 60 
F6 "GATE" O R 6600 4900 60 
F7 "EMITTER" O R 6600 5000 60 
$EndSheet
Wire Wire Line
	7200 2400 7200 2750
Wire Wire Line
	1800 2400 7200 2400
Wire Wire Line
	4500 2400 4500 2700
Wire Wire Line
	4500 5400 4500 5700
Wire Wire Line
	1800 5700 7200 5700
Wire Wire Line
	7200 5700 7200 5400
Connection ~ 4500 5700
Connection ~ 4500 2400
Wire Wire Line
	2900 2800 3050 2800
Wire Wire Line
	2900 2800 2900 3300
$Comp
L DGND #PWR?
U 1 1 544FFF94
P 2900 3300
F 0 "#PWR?" H 2900 3300 40  0001 C CNN
F 1 "DGND" H 2900 3230 40  0000 C CNN
F 2 "" H 2900 3300 60  0000 C CNN
F 3 "" H 2900 3300 60  0000 C CNN
	1    2900 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2800 5750 2800
Wire Wire Line
	5600 2800 5600 3300
$Comp
L DGND #PWR?
U 1 1 544FFF9D
P 5600 3300
F 0 "#PWR?" H 5600 3300 40  0001 C CNN
F 1 "DGND" H 5600 3230 40  0000 C CNN
F 2 "" H 5600 3300 60  0000 C CNN
F 3 "" H 5600 3300 60  0000 C CNN
	1    5600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5000 3050 5000
Wire Wire Line
	2900 5000 2900 5500
$Comp
L DGND #PWR?
U 1 1 544FFFA6
P 2900 5500
F 0 "#PWR?" H 2900 5500 40  0001 C CNN
F 1 "DGND" H 2900 5430 40  0000 C CNN
F 2 "" H 2900 5500 60  0000 C CNN
F 3 "" H 2900 5500 60  0000 C CNN
	1    2900 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 5000 5750 5000
Wire Wire Line
	5600 5000 5600 5500
$Comp
L DGND #PWR?
U 1 1 544FFFAF
P 5600 5500
F 0 "#PWR?" H 5600 5500 40  0001 C CNN
F 1 "DGND" H 5600 5430 40  0000 C CNN
F 2 "" H 5600 5500 60  0000 C CNN
F 3 "" H 5600 5500 60  0000 C CNN
	1    5600 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5300 5600 5300
Connection ~ 5600 5300
Wire Wire Line
	3050 5300 2900 5300
Connection ~ 2900 5300
Wire Wire Line
	5750 3100 5600 3100
Connection ~ 5600 3100
Wire Wire Line
	3050 3100 2900 3100
Connection ~ 2900 3100
$Comp
L +5V #PWR?
U 1 1 544FFFBD
P 5500 2900
F 0 "#PWR?" H 5500 2990 20  0001 C CNN
F 1 "+5V" H 5500 2990 30  0000 C CNN
F 2 "" H 5500 2900 60  0000 C CNN
F 3 "" H 5500 2900 60  0000 C CNN
	1    5500 2900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 544FFFC3
P 2800 2900
F 0 "#PWR?" H 2800 2990 20  0001 C CNN
F 1 "+5V" H 2800 2990 30  0000 C CNN
F 2 "" H 2800 2900 60  0000 C CNN
F 3 "" H 2800 2900 60  0000 C CNN
	1    2800 2900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 544FFFC9
P 2800 5100
F 0 "#PWR?" H 2800 5190 20  0001 C CNN
F 1 "+5V" H 2800 5190 30  0000 C CNN
F 2 "" H 2800 5100 60  0000 C CNN
F 3 "" H 2800 5100 60  0000 C CNN
	1    2800 5100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 544FFFCF
P 5500 5100
F 0 "#PWR?" H 5500 5190 20  0001 C CNN
F 1 "+5V" H 5500 5190 30  0000 C CNN
F 2 "" H 5500 5100 60  0000 C CNN
F 3 "" H 5500 5100 60  0000 C CNN
	1    5500 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 3000 2800 3000
Wire Wire Line
	2800 3000 2800 2900
Wire Wire Line
	5750 3000 5500 3000
Wire Wire Line
	5500 3000 5500 2900
Wire Wire Line
	3050 5200 2800 5200
Wire Wire Line
	2800 5200 2800 5100
Wire Wire Line
	5750 5200 5500 5200
Wire Wire Line
	5500 5200 5500 5100
Wire Wire Line
	4500 3200 4500 4900
Wire Wire Line
	7200 3200 7200 4900
Wire Wire Line
	4500 4600 7950 4600
Connection ~ 4500 4600
Wire Wire Line
	7200 3500 7950 3500
Connection ~ 7200 3500
Wire Wire Line
	3900 2700 4100 2700
Wire Wire Line
	4100 2700 4100 3050
Wire Wire Line
	4100 3050 4250 3050
Wire Wire Line
	3900 2800 4000 2800
Wire Wire Line
	4000 2800 4000 3300
Wire Wire Line
	4000 3300 4500 3300
Connection ~ 4500 3300
Wire Wire Line
	6600 2700 6800 2700
Wire Wire Line
	6800 2700 6800 3050
Wire Wire Line
	6800 3050 6950 3050
Wire Wire Line
	6600 2800 6700 2800
Wire Wire Line
	6700 2800 6700 3300
Wire Wire Line
	6700 3300 7200 3300
Wire Wire Line
	6600 4900 6800 4900
Wire Wire Line
	6800 4900 6800 5250
Wire Wire Line
	6800 5250 6950 5250
Wire Wire Line
	6600 5000 6700 5000
Wire Wire Line
	6700 5000 6700 5500
Wire Wire Line
	6700 5500 7200 5500
Wire Wire Line
	3900 4900 4100 4900
Wire Wire Line
	4100 4900 4100 5250
Wire Wire Line
	4100 5250 4250 5250
Wire Wire Line
	3900 5000 4000 5000
Wire Wire Line
	4000 5000 4000 5500
Wire Wire Line
	4000 5500 4500 5500
Connection ~ 7200 3300
Connection ~ 7200 5500
Connection ~ 4500 5500
Wire Wire Line
	2900 2700 3050 2700
Wire Wire Line
	2900 4900 3050 4900
Wire Wire Line
	5600 4900 5750 4900
Wire Wire Line
	5600 2700 5750 2700
Text HLabel 7950 3500 2    60   Output ~ 0
OUT2
Text HLabel 7950 4600 2    60   Output ~ 0
OUT1
Text HLabel 1800 2400 0    60   Input ~ 0
DC+
Text HLabel 1800 5700 0    60   Input ~ 0
DC-
Text HLabel 2900 2700 0    60   Input ~ 0
GATE_1H
Text HLabel 2900 4900 0    60   Input ~ 0
GATE_1L
Text HLabel 5600 2700 0    60   Input ~ 0
GATE_2H
Text HLabel 5600 4900 0    60   Input ~ 0
GATE_2L
$EndSCHEMATC

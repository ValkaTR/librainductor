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
Sheet 12 12
Title ""
Date "20 nov 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2450 1550 0    60   Input ~ 0
VOLTAGE1+
Text HLabel 2450 1700 0    60   Input ~ 0
VOLTAGE1-
Text HLabel 2450 3500 0    60   Input ~ 0
VOLTAGE2+
Text HLabel 2450 3650 0    60   Input ~ 0
VOLTAGE2-
Text HLabel 3050 5600 0    60   Input ~ 0
CURRENT1+
Text HLabel 3050 5800 0    60   Input ~ 0
CURRENT1-
Text HLabel 7700 2150 2    60   Output ~ 0
VOLTAGE1_OUT
Text HLabel 7700 4100 2    60   Output ~ 0
VOLTAGE2_OUT
Text HLabel 7550 6200 2    60   Output ~ 0
CURRENT1_OUT
$Comp
L OPA237 U?
U 1 1 546EF82D
P 6800 2150
F 0 "U?" H 6950 2450 70  0000 C CNN
F 1 "OPA237" H 6950 2350 70  0000 C CNN
F 2 "" H 6800 2150 60  0000 C CNN
F 3 "" H 6800 2150 60  0000 C CNN
	1    6800 2150
	1    0    0    -1  
$EndComp
$Comp
L ACPL-C87X U?
U 1 1 546EF83C
P 4600 2150
F 0 "U?" H 4600 2450 60  0000 C CNN
F 1 "ACPL-C87X" H 4600 1850 60  0000 C CNN
F 2 "" H 4700 1900 60  0000 C CNN
F 3 "" H 4700 1900 60  0000 C CNN
	1    4600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2000 5450 2000
Wire Wire Line
	5250 2300 5450 2300
Wire Wire Line
	5250 2100 5650 2100
Wire Wire Line
	5650 2100 5800 2250
Wire Wire Line
	5800 2250 5900 2250
Wire Wire Line
	5250 2200 5650 2200
Wire Wire Line
	5650 2200 5800 2050
Wire Wire Line
	5800 2050 5900 2050
Wire Wire Line
	6100 2050 6300 2050
Wire Wire Line
	6100 2250 6300 2250
$Comp
L AGND #PWR?
U 1 1 546EF928
P 6700 2650
F 0 "#PWR?" H 6700 2650 40  0001 C CNN
F 1 "AGND" H 6700 2580 50  0000 C CNN
F 2 "" H 6700 2650 60  0000 C CNN
F 3 "" H 6700 2650 60  0000 C CNN
	1    6700 2650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546EF937
P 6700 1650
F 0 "#PWR?" H 6700 1740 20  0001 C CNN
F 1 "+5V" H 6700 1740 30  0000 C CNN
F 2 "" H 6700 1650 60  0000 C CNN
F 3 "" H 6700 1650 60  0000 C CNN
	1    6700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1750 6700 1650
Wire Wire Line
	6700 2550 6700 2650
Wire Wire Line
	6400 1350 6600 1350
Wire Wire Line
	6400 1150 6400 1350
Wire Wire Line
	6400 1150 6600 1150
Wire Wire Line
	6800 1150 7000 1150
Wire Wire Line
	7000 1150 7000 1350
Wire Wire Line
	7000 1350 6800 1350
Wire Wire Line
	6400 1250 6200 1250
Wire Wire Line
	6200 1250 6200 2050
Connection ~ 6200 2050
Connection ~ 6400 1250
Wire Wire Line
	7000 1250 7400 1250
Wire Wire Line
	7300 2150 7700 2150
Connection ~ 7000 1250
Wire Wire Line
	7400 1250 7400 2150
$Comp
L CAPACITOR C?
U 1 1 546EFF1E
P 3650 2200
F 0 "C?" H 3700 2300 40  0000 L CNN
F 1 "100 pF" H 3700 2100 40  0000 L CNN
F 2 "~" H 3688 2050 30  0000 C CNN
F 3 "~" H 3650 2200 60  0000 C CNN
	1    3650 2200
	1    0    0    -1  
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546EFF2D
P 3300 2100
F 0 "C?" H 3350 2200 40  0000 L CNN
F 1 "100 pF" H 3350 2000 40  0000 L CNN
F 2 "~" H 3338 1950 30  0000 C CNN
F 3 "~" H 3300 2100 60  0000 C CNN
	1    3300 2100
	1    0    0    -1  
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F02E8
P 3000 2200
F 0 "R?" V 2950 2200 40  0000 C CNN
F 1 "10 kΩ" V 3050 2200 40  0000 C CNN
F 2 "~" V 2930 2200 30  0000 C CNN
F 3 "~" H 3000 2200 30  0000 C CNN
	1    3000 2200
	1    0    0    -1  
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F02F7
P 3000 1800
F 0 "R?" V 2950 1800 40  0000 C CNN
F 1 "RESISTOR" V 3050 1800 40  0000 C CNN
F 2 "~" V 2930 1800 30  0000 C CNN
F 3 "~" H 3000 1800 30  0000 C CNN
	1    3000 1800
	1    0    0    -1  
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F031C
P 5450 2150
F 0 "C?" H 5500 2250 40  0000 L CNN
F 1 "100 nF" H 5500 2050 40  0000 L CNN
F 2 "~" H 5488 2000 30  0000 C CNN
F 3 "~" H 5450 2150 60  0000 C CNN
	1    5450 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1650 5450 2050
Wire Wire Line
	5450 2250 5450 2650
Connection ~ 3650 2300
Wire Wire Line
	3000 2100 3950 2100
Text Notes 3250 1600 0    60   ~ 0
Uout = Uin * R1 / (R1 + R2)
Text Notes 3250 1750 0    60   ~ 0
ACPL-C87x, U_{in. max.} = 0 … 2 V
Connection ~ 3300 2300
Wire Wire Line
	3000 2100 3000 1900
Connection ~ 3650 2100
Wire Wire Line
	3300 2300 3300 2200
Wire Wire Line
	2450 1550 3000 1550
Wire Wire Line
	3000 1550 3000 1700
Connection ~ 3000 2300
Connection ~ 7400 2150
$Comp
L RESISTOR R?
U 1 1 546F06FF
P 6000 2050
F 0 "R?" V 5950 2050 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6050 2050 40  0000 C CNN
F 2 "~" V 5930 2050 30  0000 C CNN
F 3 "~" H 6000 2050 30  0000 C CNN
	1    6000 2050
	0    -1   -1   0   
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F071B
P 6000 2250
F 0 "R?" V 5950 2250 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6050 2250 40  0000 C CNN
F 2 "~" V 5930 2250 30  0000 C CNN
F 3 "~" H 6000 2250 30  0000 C CNN
	1    6000 2250
	0    -1   -1   0   
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F0728
P 6700 1350
F 0 "R?" V 6650 1350 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6750 1350 40  0000 C CNN
F 2 "~" V 6630 1350 30  0000 C CNN
F 3 "~" H 6700 1350 30  0000 C CNN
	1    6700 1350
	0    -1   -1   0   
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F072E
P 6700 1150
F 0 "C?" H 6750 1250 40  0000 L CNN
F 1 "100 pF" H 6750 1050 40  0000 L CNN
F 2 "~" H 6738 1000 30  0000 C CNN
F 3 "~" H 6700 1150 60  0000 C CNN
	1    6700 1150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 2200 3850 2200
Wire Wire Line
	3850 2200 3850 2300
Connection ~ 3850 2300
$Comp
L ROM-0505S D?
U 1 1 546F16F9
P 2100 2150
F 0 "D?" H 1800 2450 60  0000 L CNN
F 1 "ROM-0505S" H 1800 1850 60  0000 L CNN
F 2 "~" H 2125 2150 60  0000 C CNN
F 3 "~" H 2125 2150 60  0000 C CNN
	1    2100 2150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546F1717
P 1450 1700
F 0 "#PWR?" H 1450 1790 20  0001 C CNN
F 1 "+5V" H 1450 1790 30  0000 C CNN
F 2 "" H 1450 1700 60  0000 C CNN
F 3 "" H 1450 1700 60  0000 C CNN
	1    1450 1700
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR?
U 1 1 546F174F
P 1450 2650
F 0 "#PWR?" H 1450 2650 40  0001 C CNN
F 1 "DGND" H 1450 2580 40  0000 C CNN
F 2 "" H 1450 2650 60  0000 C CNN
F 3 "" H 1450 2650 60  0000 C CNN
	1    1450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1700 1450 2000
Wire Wire Line
	1450 2000 1500 2000
Wire Wire Line
	1450 2650 1450 2300
Wire Wire Line
	1450 2300 1500 2300
Connection ~ 3300 2000
Wire Wire Line
	2750 1700 2750 2300
Wire Wire Line
	2650 2300 3950 2300
Connection ~ 2750 2300
Wire Wire Line
	2650 2000 3950 2000
Wire Wire Line
	2450 1700 2750 1700
$Comp
L AGND #PWR?
U 1 1 546F1A6B
P 5450 2650
F 0 "#PWR?" H 5450 2650 40  0001 C CNN
F 1 "AGND" H 5450 2580 50  0000 C CNN
F 2 "" H 5450 2650 60  0000 C CNN
F 3 "" H 5450 2650 60  0000 C CNN
	1    5450 2650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546F1A71
P 5450 1650
F 0 "#PWR?" H 5450 1740 20  0001 C CNN
F 1 "+5V" H 5450 1740 30  0000 C CNN
F 2 "" H 5450 1650 60  0000 C CNN
F 3 "" H 5450 1650 60  0000 C CNN
	1    5450 1650
	1    0    0    -1  
$EndComp
Connection ~ 5450 2000
Connection ~ 5450 2300
$Comp
L OPA237 U?
U 1 1 546F1CEF
P 6800 4100
F 0 "U?" H 6950 4400 70  0000 C CNN
F 1 "OPA237" H 6950 4300 70  0000 C CNN
F 2 "" H 6800 4100 60  0000 C CNN
F 3 "" H 6800 4100 60  0000 C CNN
	1    6800 4100
	1    0    0    -1  
$EndComp
$Comp
L ACPL-C87X U?
U 1 1 546F1CF5
P 4600 4100
F 0 "U?" H 4600 4400 60  0000 C CNN
F 1 "ACPL-C87X" H 4600 3800 60  0000 C CNN
F 2 "" H 4700 3850 60  0000 C CNN
F 3 "" H 4700 3850 60  0000 C CNN
	1    4600 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3950 5450 3950
Wire Wire Line
	5250 4250 5450 4250
Wire Wire Line
	5250 4050 5650 4050
Wire Wire Line
	5650 4050 5800 4200
Wire Wire Line
	5800 4200 5900 4200
Wire Wire Line
	5250 4150 5650 4150
Wire Wire Line
	5650 4150 5800 4000
Wire Wire Line
	5800 4000 5900 4000
Wire Wire Line
	6100 4000 6300 4000
Wire Wire Line
	6100 4200 6300 4200
$Comp
L AGND #PWR?
U 1 1 546F1D05
P 6700 4600
F 0 "#PWR?" H 6700 4600 40  0001 C CNN
F 1 "AGND" H 6700 4530 50  0000 C CNN
F 2 "" H 6700 4600 60  0000 C CNN
F 3 "" H 6700 4600 60  0000 C CNN
	1    6700 4600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546F1D0B
P 6700 3600
F 0 "#PWR?" H 6700 3690 20  0001 C CNN
F 1 "+5V" H 6700 3690 30  0000 C CNN
F 2 "" H 6700 3600 60  0000 C CNN
F 3 "" H 6700 3600 60  0000 C CNN
	1    6700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3700 6700 3600
Wire Wire Line
	6700 4500 6700 4600
Wire Wire Line
	6400 3300 6600 3300
Wire Wire Line
	6400 3100 6400 3300
Wire Wire Line
	6400 3100 6600 3100
Wire Wire Line
	6800 3100 7000 3100
Wire Wire Line
	7000 3100 7000 3300
Wire Wire Line
	7000 3300 6800 3300
Wire Wire Line
	6400 3200 6200 3200
Wire Wire Line
	6200 3200 6200 4000
Connection ~ 6200 4000
Connection ~ 6400 3200
Wire Wire Line
	7000 3200 7400 3200
Wire Wire Line
	7300 4100 7700 4100
Connection ~ 7000 3200
Wire Wire Line
	7400 3200 7400 4100
$Comp
L CAPACITOR C?
U 1 1 546F1D21
P 3650 4150
F 0 "C?" H 3700 4250 40  0000 L CNN
F 1 "100 pF" H 3700 4050 40  0000 L CNN
F 2 "~" H 3688 4000 30  0000 C CNN
F 3 "~" H 3650 4150 60  0000 C CNN
	1    3650 4150
	1    0    0    -1  
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F1D27
P 3300 4050
F 0 "C?" H 3350 4150 40  0000 L CNN
F 1 "100 pF" H 3350 3950 40  0000 L CNN
F 2 "~" H 3338 3900 30  0000 C CNN
F 3 "~" H 3300 4050 60  0000 C CNN
	1    3300 4050
	1    0    0    -1  
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F1D2D
P 3000 4150
F 0 "R?" V 2950 4150 40  0000 C CNN
F 1 "10 kΩ" V 3050 4150 40  0000 C CNN
F 2 "~" V 2930 4150 30  0000 C CNN
F 3 "~" H 3000 4150 30  0000 C CNN
	1    3000 4150
	1    0    0    -1  
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F1D33
P 3000 3750
F 0 "R?" V 2950 3750 40  0000 C CNN
F 1 "RESISTOR" V 3050 3750 40  0000 C CNN
F 2 "~" V 2930 3750 30  0000 C CNN
F 3 "~" H 3000 3750 30  0000 C CNN
	1    3000 3750
	1    0    0    -1  
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F1D39
P 5450 4100
F 0 "C?" H 5500 4200 40  0000 L CNN
F 1 "100 nF" H 5500 4000 40  0000 L CNN
F 2 "~" H 5488 3950 30  0000 C CNN
F 3 "~" H 5450 4100 60  0000 C CNN
	1    5450 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3600 5450 4000
Wire Wire Line
	5450 4200 5450 4600
Connection ~ 3650 4250
Wire Wire Line
	3000 4050 3950 4050
Connection ~ 3300 4250
Wire Wire Line
	3000 4050 3000 3850
Connection ~ 3650 4050
Wire Wire Line
	3300 4250 3300 4150
Wire Wire Line
	2450 3500 3000 3500
Wire Wire Line
	3000 3500 3000 3650
Connection ~ 3000 4250
Connection ~ 7400 4100
$Comp
L RESISTOR R?
U 1 1 546F1D4D
P 6000 4000
F 0 "R?" V 5950 4000 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6050 4000 40  0000 C CNN
F 2 "~" V 5930 4000 30  0000 C CNN
F 3 "~" H 6000 4000 30  0000 C CNN
	1    6000 4000
	0    -1   -1   0   
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F1D53
P 6000 4200
F 0 "R?" V 5950 4200 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6050 4200 40  0000 C CNN
F 2 "~" V 5930 4200 30  0000 C CNN
F 3 "~" H 6000 4200 30  0000 C CNN
	1    6000 4200
	0    -1   -1   0   
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F1D59
P 6700 3300
F 0 "R?" V 6650 3300 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6750 3300 40  0000 C CNN
F 2 "~" V 6630 3300 30  0000 C CNN
F 3 "~" H 6700 3300 30  0000 C CNN
	1    6700 3300
	0    -1   -1   0   
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F1D5F
P 6700 3100
F 0 "C?" H 6750 3200 40  0000 L CNN
F 1 "100 pF" H 6750 3000 40  0000 L CNN
F 2 "~" H 6738 2950 30  0000 C CNN
F 3 "~" H 6700 3100 60  0000 C CNN
	1    6700 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 4150 3850 4150
Wire Wire Line
	3850 4150 3850 4250
Connection ~ 3850 4250
$Comp
L ROM-0505S D?
U 1 1 546F1D68
P 2100 4100
F 0 "D?" H 1800 4400 60  0000 L CNN
F 1 "ROM-0505S" H 1800 3800 60  0000 L CNN
F 2 "~" H 2125 4100 60  0000 C CNN
F 3 "~" H 2125 4100 60  0000 C CNN
	1    2100 4100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546F1D6E
P 1450 3650
F 0 "#PWR?" H 1450 3740 20  0001 C CNN
F 1 "+5V" H 1450 3740 30  0000 C CNN
F 2 "" H 1450 3650 60  0000 C CNN
F 3 "" H 1450 3650 60  0000 C CNN
	1    1450 3650
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR?
U 1 1 546F1D74
P 1450 4600
F 0 "#PWR?" H 1450 4600 40  0001 C CNN
F 1 "DGND" H 1450 4530 40  0000 C CNN
F 2 "" H 1450 4600 60  0000 C CNN
F 3 "" H 1450 4600 60  0000 C CNN
	1    1450 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 3650 1450 3950
Wire Wire Line
	1450 3950 1500 3950
Wire Wire Line
	1450 4600 1450 4250
Wire Wire Line
	1450 4250 1500 4250
Connection ~ 3300 3950
Wire Wire Line
	2750 3650 2750 4250
Wire Wire Line
	2650 4250 3950 4250
Connection ~ 2750 4250
Wire Wire Line
	2650 3950 3950 3950
Wire Wire Line
	2450 3650 2750 3650
$Comp
L AGND #PWR?
U 1 1 546F1D84
P 5450 4600
F 0 "#PWR?" H 5450 4600 40  0001 C CNN
F 1 "AGND" H 5450 4530 50  0000 C CNN
F 2 "" H 5450 4600 60  0000 C CNN
F 3 "" H 5450 4600 60  0000 C CNN
	1    5450 4600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546F1D8A
P 5450 3600
F 0 "#PWR?" H 5450 3690 20  0001 C CNN
F 1 "+5V" H 5450 3690 30  0000 C CNN
F 2 "" H 5450 3600 60  0000 C CNN
F 3 "" H 5450 3600 60  0000 C CNN
	1    5450 3600
	1    0    0    -1  
$EndComp
Connection ~ 5450 3950
Connection ~ 5450 4250
$Comp
L ACPL-C79X U?
U 1 1 546F23CC
P 4600 6200
F 0 "U?" H 4600 6500 60  0000 C CNN
F 1 "ACPL-C79X" H 4600 5900 60  0000 C CNN
F 2 "" H 4700 5950 60  0000 C CNN
F 3 "" H 4700 5950 60  0000 C CNN
	1    4600 6200
	1    0    0    -1  
$EndComp
$Comp
L TL03X U?
U 1 1 546F23E5
P 6800 6200
F 0 "U?" H 6950 6500 70  0000 C CNN
F 1 "TL03X" H 6950 6400 70  0000 C CNN
F 2 "" H 6800 6200 60  0000 C CNN
F 3 "" H 6800 6200 60  0000 C CNN
	1    6800 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 6050 5450 6050
Wire Wire Line
	5250 6350 5450 6350
Wire Wire Line
	5250 6150 5650 6150
Wire Wire Line
	5650 6150 5800 6300
Wire Wire Line
	5800 6300 5900 6300
Wire Wire Line
	5250 6250 5650 6250
Wire Wire Line
	5650 6250 5800 6100
Wire Wire Line
	5800 6100 5900 6100
Wire Wire Line
	6100 6100 6300 6100
Wire Wire Line
	6100 6300 6300 6300
Wire Wire Line
	6400 5300 6200 5300
Wire Wire Line
	6200 5300 6200 6100
Connection ~ 6200 6100
$Comp
L CAPACITOR C?
U 1 1 546F23FF
P 5450 6200
F 0 "C?" H 5500 6300 40  0000 L CNN
F 1 "0,1 µF" H 5500 6100 40  0000 L CNN
F 2 "~" H 5488 6050 30  0000 C CNN
F 3 "~" H 5450 6200 60  0000 C CNN
	1    5450 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5700 5450 6100
Wire Wire Line
	5450 6300 5450 6700
$Comp
L RESISTOR R?
U 1 1 546F2407
P 6000 6100
F 0 "R?" V 5950 6100 40  0000 C CNN
F 1 "2 kΩ" V 6050 6100 40  0000 C CNN
F 2 "~" V 5930 6100 30  0000 C CNN
F 3 "~" H 6000 6100 30  0000 C CNN
	1    6000 6100
	0    -1   -1   0   
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F240D
P 6000 6300
F 0 "R?" V 5950 6300 40  0000 C CNN
F 1 "2 kΩ" V 6050 6300 40  0000 C CNN
F 2 "~" V 5930 6300 30  0000 C CNN
F 3 "~" H 6000 6300 30  0000 C CNN
	1    6000 6300
	0    -1   -1   0   
$EndComp
$Comp
L AGND #PWR?
U 1 1 546F2413
P 5450 6700
F 0 "#PWR?" H 5450 6700 40  0001 C CNN
F 1 "AGND" H 5450 6630 50  0000 C CNN
F 2 "" H 5450 6700 60  0000 C CNN
F 3 "" H 5450 6700 60  0000 C CNN
	1    5450 6700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 546F2419
P 5450 5700
F 0 "#PWR?" H 5450 5790 20  0001 C CNN
F 1 "+5V" H 5450 5790 30  0000 C CNN
F 2 "" H 5450 5700 60  0000 C CNN
F 3 "" H 5450 5700 60  0000 C CNN
	1    5450 5700
	1    0    0    -1  
$EndComp
Connection ~ 5450 6050
Connection ~ 5450 6350
Wire Wire Line
	6700 5800 6700 5700
Wire Wire Line
	6400 5400 6600 5400
Wire Wire Line
	6400 5200 6600 5200
Wire Wire Line
	6800 5200 7000 5200
Wire Wire Line
	7000 5200 7000 5400
Wire Wire Line
	7000 5400 6800 5400
Wire Wire Line
	7000 5300 7400 5300
Connection ~ 7000 5300
Wire Wire Line
	7400 5300 7400 6200
$Comp
L RESISTOR R?
U 1 1 546F2430
P 6700 5400
F 0 "R?" V 6650 5400 40  0000 C CNN
F 1 "10 kΩ, 1%" V 6750 5400 40  0000 C CNN
F 2 "~" V 6630 5400 30  0000 C CNN
F 3 "~" H 6700 5400 30  0000 C CNN
	1    6700 5400
	0    -1   -1   0   
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F2436
P 6700 5200
F 0 "C?" H 6750 5300 40  0000 L CNN
F 1 "100 pF" H 6750 5100 40  0000 L CNN
F 2 "~" H 6738 5050 30  0000 C CNN
F 3 "~" H 6700 5200 60  0000 C CNN
	1    6700 5200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6400 5200 6400 5400
Connection ~ 6400 5300
Wire Wire Line
	6700 6600 6700 6700
$Comp
L CAPACITOR C?
U 1 1 546F25A9
P 3500 5700
F 0 "C?" H 3550 5800 40  0000 L CNN
F 1 "47 nF" H 3550 5600 40  0000 L CNN
F 2 "~" H 3538 5550 30  0000 C CNN
F 3 "~" H 3500 5700 60  0000 C CNN
	1    3500 5700
	1    0    0    -1  
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F25AF
P 3500 6150
F 0 "C?" H 3550 6250 40  0000 L CNN
F 1 "0,1 µF" H 3550 6050 40  0000 L CNN
F 2 "~" H 3538 6000 30  0000 C CNN
F 3 "~" H 3500 6150 60  0000 C CNN
	1    3500 6150
	1    0    0    -1  
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F25BB
P 3250 5600
F 0 "R?" V 3200 5600 40  0000 C CNN
F 1 "10 Ω" V 3300 5600 40  0000 C CNN
F 2 "~" V 3180 5600 30  0000 C CNN
F 3 "~" H 3250 5600 30  0000 C CNN
	1    3250 5600
	0    -1   -1   0   
$EndComp
Text Notes 2450 5400 0    60   ~ 0
ACPL-C79x, U_{in. max.} = -0,3 … +0,3 V
Connection ~ 3500 6350
Wire Wire Line
	3500 6350 3500 6250
Wire Wire Line
	3950 6250 3850 6250
Connection ~ 3850 6350
$Comp
L +5V #PWR?
U 1 1 546F25D6
P 2000 5750
F 0 "#PWR?" H 2000 5840 20  0001 C CNN
F 1 "+5V" H 2000 5840 30  0000 C CNN
F 2 "" H 2000 5750 60  0000 C CNN
F 3 "" H 2000 5750 60  0000 C CNN
	1    2000 5750
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR?
U 1 1 546F25DC
P 2000 6700
F 0 "#PWR?" H 2000 6700 40  0001 C CNN
F 1 "DGND" H 2000 6630 40  0000 C CNN
F 2 "" H 2000 6700 60  0000 C CNN
F 3 "" H 2000 6700 60  0000 C CNN
	1    2000 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5750 2000 6050
Wire Wire Line
	2000 6050 2050 6050
Wire Wire Line
	2000 6700 2000 6350
Wire Wire Line
	2000 6350 2050 6350
Connection ~ 3500 6050
Wire Wire Line
	3200 6350 3950 6350
Wire Wire Line
	3200 6050 3950 6050
$Comp
L ROM-0505S D?
U 1 1 546F25D0
P 2650 6200
F 0 "D?" H 2350 6500 60  0000 L CNN
F 1 "ROM-0505S" H 2350 5900 60  0000 L CNN
F 2 "~" H 2675 6200 60  0000 C CNN
F 3 "~" H 2675 6200 60  0000 C CNN
	1    2650 6200
	1    0    0    -1  
$EndComp
Connection ~ 3200 6350
Wire Wire Line
	3950 6150 3900 6150
Wire Wire Line
	3900 6150 3900 5600
Wire Wire Line
	3900 5600 3350 5600
Connection ~ 3500 5600
Connection ~ 3500 5800
Wire Wire Line
	3150 5600 3050 5600
Wire Wire Line
	3850 6250 3850 6350
Wire Wire Line
	3050 5800 3750 5800
Wire Wire Line
	3750 5800 3750 6350
Connection ~ 3750 6350
Wire Wire Line
	7300 6200 7550 6200
Connection ~ 7400 6200
$Comp
L CAPACITOR C?
U 1 1 546F2FCA
P 6100 6650
F 0 "C?" H 6150 6750 40  0000 L CNN
F 1 "47 pF" H 6150 6550 40  0000 L CNN
F 2 "~" H 6138 6500 30  0000 C CNN
F 3 "~" H 6100 6650 60  0000 C CNN
	1    6100 6650
	-1   0    0    1   
$EndComp
$Comp
L RESISTOR R?
U 1 1 546F2FD0
P 6300 6650
F 0 "R?" V 6250 6650 40  0000 C CNN
F 1 "10 kΩ" V 6350 6650 40  0000 C CNN
F 2 "~" V 6230 6650 30  0000 C CNN
F 3 "~" H 6300 6650 30  0000 C CNN
	1    6300 6650
	-1   0    0    1   
$EndComp
Wire Wire Line
	6100 6550 6100 6500
Wire Wire Line
	6100 6500 6300 6500
Wire Wire Line
	6300 6500 6300 6550
Wire Wire Line
	6100 6750 6100 6800
Wire Wire Line
	6100 6800 6300 6800
Wire Wire Line
	6300 6800 6300 6750
Wire Wire Line
	6200 6500 6200 6300
Connection ~ 6200 6300
Connection ~ 6200 6500
$Comp
L AGND #PWR?
U 1 1 546F31C0
P 6200 6950
F 0 "#PWR?" H 6200 6950 40  0001 C CNN
F 1 "AGND" H 6200 6880 50  0000 C CNN
F 2 "" H 6200 6950 60  0000 C CNN
F 3 "" H 6200 6950 60  0000 C CNN
	1    6200 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 6950 6200 6800
Connection ~ 6200 6800
$Comp
L +15V #PWR?
U 1 1 546F36F9
P 6700 5700
F 0 "#PWR?" H 6700 5650 20  0001 C CNN
F 1 "+15V" H 6700 5800 30  0000 C CNN
F 2 "" H 6700 5700 60  0000 C CNN
F 3 "" H 6700 5700 60  0000 C CNN
	1    6700 5700
	1    0    0    -1  
$EndComp
$Comp
L -15V #PWR?
U 1 1 546F3708
P 6700 6700
F 0 "#PWR?" H 6700 6830 20  0001 C CNN
F 1 "-15V" H 6700 6800 30  0000 C CNN
F 2 "" H 6700 6700 60  0000 C CNN
F 3 "" H 6700 6700 60  0000 C CNN
	1    6700 6700
	-1   0    0    1   
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F371F
P 6900 5750
F 0 "C?" H 6950 5850 40  0000 L CNN
F 1 "0,1 µF" H 6950 5650 40  0000 L CNN
F 2 "~" H 6938 5600 30  0000 C CNN
F 3 "~" H 6900 5750 60  0000 C CNN
	1    6900 5750
	0    -1   -1   0   
$EndComp
$Comp
L CAPACITOR C?
U 1 1 546F3725
P 6900 6650
F 0 "C?" H 6950 6750 40  0000 L CNN
F 1 "0,1 µF" H 6950 6550 40  0000 L CNN
F 2 "~" H 6938 6500 30  0000 C CNN
F 3 "~" H 6900 6650 60  0000 C CNN
	1    6900 6650
	0    -1   -1   0   
$EndComp
$Comp
L AGND #PWR?
U 1 1 546F372B
P 7100 5750
F 0 "#PWR?" H 7100 5750 40  0001 C CNN
F 1 "AGND" H 7100 5680 50  0000 C CNN
F 2 "" H 7100 5750 60  0000 C CNN
F 3 "" H 7100 5750 60  0000 C CNN
	1    7100 5750
	0    -1   -1   0   
$EndComp
$Comp
L AGND #PWR?
U 1 1 546F3731
P 7100 6650
F 0 "#PWR?" H 7100 6650 40  0001 C CNN
F 1 "AGND" H 7100 6580 50  0000 C CNN
F 2 "" H 7100 6650 60  0000 C CNN
F 3 "" H 7100 6650 60  0000 C CNN
	1    7100 6650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 5750 6800 5750
Connection ~ 6700 5750
Wire Wire Line
	7000 5750 7100 5750
Wire Wire Line
	6700 6650 6800 6650
Connection ~ 6700 6650
Wire Wire Line
	7000 6650 7100 6650
$EndSCHEMATC

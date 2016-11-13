EESchema Schematic File Version 2
LIBS:rfid-rescue
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
LIBS:custom
LIBS:rfid-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "20 dec 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND-RESCUE-rfid #PWR01
U 1 1 56623C49
P 5550 3550
F 0 "#PWR01" H 5550 3550 30  0001 C CNN
F 1 "GND" H 5550 3480 30  0001 C CNN
F 2 "" H 5550 3550 60  0000 C CNN
F 3 "" H 5550 3550 60  0000 C CNN
	1    5550 3550
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR02
U 1 1 56623CD0
P 5550 3450
F 0 "#PWR02" H 5550 3550 30  0001 C CNN
F 1 "VDD" H 5550 3560 30  0000 C CNN
F 2 "" H 5550 3450 60  0000 C CNN
F 3 "" H 5550 3450 60  0000 C CNN
	1    5550 3450
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR03
U 1 1 56623CE3
P 3850 3450
F 0 "#PWR03" H 3850 3550 30  0001 C CNN
F 1 "VDD" H 3850 3560 30  0000 C CNN
F 2 "" H 3850 3450 60  0000 C CNN
F 3 "" H 3850 3450 60  0000 C CNN
	1    3850 3450
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR04
U 1 1 56623D83
P 2550 1450
F 0 "#PWR04" H 2550 1540 20  0001 C CNN
F 1 "+5V" H 2550 1540 30  0000 C CNN
F 2 "" H 2550 1450 60  0000 C CNN
F 3 "" H 2550 1450 60  0000 C CNN
	1    2550 1450
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR05
U 1 1 56623D9C
P 2550 1850
F 0 "#PWR05" H 2550 1850 30  0001 C CNN
F 1 "GND" H 2550 1780 30  0001 C CNN
F 2 "" H 2550 1850 60  0000 C CNN
F 3 "" H 2550 1850 60  0000 C CNN
	1    2550 1850
	0    -1   -1   0   
$EndComp
Text Label 2750 1550 0    60   ~ 0
USB_DM
Text Label 2750 1650 0    60   ~ 0
USB_DP
$Comp
L GND-RESCUE-rfid #PWR06
U 1 1 56623EF3
P 4200 2050
F 0 "#PWR06" H 4200 2050 30  0001 C CNN
F 1 "GND" H 4200 1980 30  0001 C CNN
F 2 "" H 4200 2050 60  0000 C CNN
F 3 "" H 4200 2050 60  0000 C CNN
	1    4200 2050
	-1   0    0    1   
$EndComp
$Comp
L R-RESCUE-rfid R8
U 1 1 56623F16
P 4200 2300
F 0 "R8" V 4280 2300 40  0000 C CNN
F 1 "100K" V 4207 2301 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4130 2300 30  0001 C CNN
F 3 "~" H 4200 2300 30  0000 C CNN
	1    4200 2300
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR07
U 1 1 56623F4F
P 2750 4050
F 0 "#PWR07" H 2750 4150 30  0001 C CNN
F 1 "VDD" H 2750 4160 30  0000 C CNN
F 2 "" H 2750 4050 60  0000 C CNN
F 3 "" H 2750 4050 60  0000 C CNN
	1    2750 4050
	1    0    0    -1  
$EndComp
$Comp
L TACT SW2
U 1 1 566240F3
P 3700 2250
F 0 "SW2" H 3700 2550 60  0000 C CNN
F 1 "MODE" H 3700 2100 60  0000 C CNN
F 2 "tact:TACT-SW-SMD" H 3700 2250 60  0001 C CNN
F 3 "~" H 3700 2250 60  0000 C CNN
	1    3700 2250
	1    0    0    -1  
$EndComp
NoConn ~ 3400 2550
NoConn ~ 4000 1950
$Comp
L BATTERY BT1
U 1 1 5664F34D
P 1900 6300
F 0 "BT1" H 1900 6500 50  0000 C CNN
F 1 "BATTERY" H 1900 6110 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1900 6300 60  0001 C CNN
F 3 "~" H 1900 6300 60  0000 C CNN
	1    1900 6300
	0    1    1    0   
$EndComp
$Comp
L +BATT #PWR08
U 1 1 5664F3AA
P 3350 6000
F 0 "#PWR08" H 3350 5950 20  0001 C CNN
F 1 "+BATT" H 3350 6100 30  0000 C CNN
F 2 "" H 3350 6000 60  0000 C CNN
F 3 "" H 3350 6000 60  0000 C CNN
	1    3350 6000
	0    1    1    0   
$EndComp
$Comp
L SWITCH_INV SW1
U 1 1 5664F5C7
P 2700 6000
F 0 "SW1" H 2500 6150 50  0000 C CNN
F 1 "POWER" H 2550 5850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 2700 6000 60  0001 C CNN
F 3 "~" H 2700 6000 60  0000 C CNN
	1    2700 6000
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-rfid C11
U 1 1 5664F6F8
P 9450 2950
F 0 "C11" H 9450 3050 40  0000 L CNN
F 1 "1n" H 9456 2865 40  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 9488 2800 30  0001 C CNN
F 3 "~" H 9450 2950 60  0000 C CNN
	1    9450 2950
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 5664F707
P 9450 3450
F 0 "L1" V 9400 3450 40  0000 C CNN
F 1 "COIL" V 9550 3450 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 9450 3450 60  0001 C CNN
F 3 "~" H 9450 3450 60  0000 C CNN
	1    9450 3450
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C1
U 1 1 56650527
P 1100 4250
F 0 "C1" H 1100 4350 40  0000 L CNN
F 1 "1u" H 1106 4165 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1138 4100 30  0001 C CNN
F 3 "" H 1100 4250 60  0000 C CNN
	1    1100 4250
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR09
U 1 1 5665052D
P 1100 4450
F 0 "#PWR09" H 1100 4450 30  0001 C CNN
F 1 "GND" H 1100 4380 30  0001 C CNN
F 2 "" H 1100 4450 60  0000 C CNN
F 3 "" H 1100 4450 60  0000 C CNN
	1    1100 4450
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C2
U 1 1 56650534
P 2750 4250
F 0 "C2" H 2750 4350 40  0000 L CNN
F 1 "1u" H 2756 4165 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2788 4100 30  0001 C CNN
F 3 "" H 2750 4250 60  0000 C CNN
	1    2750 4250
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR010
U 1 1 5665053A
P 2750 4450
F 0 "#PWR010" H 2750 4450 30  0001 C CNN
F 1 "GND" H 2750 4380 30  0001 C CNN
F 2 "" H 2750 4450 60  0000 C CNN
F 3 "" H 2750 4450 60  0000 C CNN
	1    2750 4450
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C7
U 1 1 56650567
P 4750 1050
F 0 "C7" H 4750 1150 40  0000 L CNN
F 1 "2u2" H 4756 965 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4788 900 30  0001 C CNN
F 3 "" H 4750 1050 60  0000 C CNN
	1    4750 1050
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R11
U 1 1 566506F2
P 8200 2500
F 0 "R11" V 8280 2500 40  0000 C CNN
F 1 "470R" V 8207 2501 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 8130 2500 30  0001 C CNN
F 3 "~" H 8200 2500 30  0000 C CNN
	1    8200 2500
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C8
U 1 1 56650714
P 5000 1050
F 0 "C8" H 5000 1150 40  0000 L CNN
F 1 "100n" H 5006 965 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5038 900 30  0001 C CNN
F 3 "" H 5000 1050 60  0000 C CNN
	1    5000 1050
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C5
U 1 1 5665071A
P 4500 1050
F 0 "C5" H 4500 1150 40  0000 L CNN
F 1 "47u" H 4506 965 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4538 900 30  0001 C CNN
F 3 "" H 4500 1050 60  0000 C CNN
	1    4500 1050
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR011
U 1 1 566507A5
P 4750 850
F 0 "#PWR011" H 4750 800 20  0001 C CNN
F 1 "+BATT" H 4750 950 30  0000 C CNN
F 2 "" H 4750 850 60  0000 C CNN
F 3 "" H 4750 850 60  0000 C CNN
	1    4750 850 
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR012
U 1 1 566507AD
P 4750 1300
F 0 "#PWR012" H 4750 1300 30  0001 C CNN
F 1 "GND" H 4750 1230 30  0001 C CNN
F 2 "" H 4750 1300 60  0000 C CNN
F 3 "" H 4750 1300 60  0000 C CNN
	1    4750 1300
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C6
U 1 1 56650FDD
P 4700 4500
F 0 "C6" H 4700 4600 40  0000 L CNN
F 1 "100n" H 4706 4415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4738 4350 30  0001 C CNN
F 3 "~" H 4700 4500 60  0000 C CNN
	1    4700 4500
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR013
U 1 1 56650FEA
P 4700 4300
F 0 "#PWR013" H 4700 4400 30  0001 C CNN
F 1 "VDD" H 4700 4410 30  0000 C CNN
F 2 "" H 4700 4300 60  0000 C CNN
F 3 "" H 4700 4300 60  0000 C CNN
	1    4700 4300
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR014
U 1 1 56650FF0
P 4700 4700
F 0 "#PWR014" H 4700 4700 30  0001 C CNN
F 1 "GND" H 4700 4630 30  0001 C CNN
F 2 "" H 4700 4700 60  0000 C CNN
F 3 "" H 4700 4700 60  0000 C CNN
	1    4700 4700
	1    0    0    -1  
$EndComp
$Comp
L MCP7383x U2
U 1 1 56651AD8
P 2650 5100
F 0 "U2" H 2650 5000 50  0000 C CNN
F 1 "MCP7383X" H 2650 5200 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 2650 5100 50  0001 C CNN
F 3 "DOCUMENTATION" H 2650 5100 50  0001 C CNN
	1    2650 5100
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R7
U 1 1 56651AF1
P 3650 5000
F 0 "R7" V 3730 5000 40  0000 C CNN
F 1 "2K2" V 3657 5001 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3580 5000 30  0001 C CNN
F 3 "~" H 3650 5000 30  0000 C CNN
	1    3650 5000
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR015
U 1 1 56651B00
P 3900 5000
F 0 "#PWR015" H 3900 5000 30  0001 C CNN
F 1 "GND" H 3900 4930 30  0001 C CNN
F 2 "" H 3900 5000 60  0000 C CNN
F 3 "" H 3900 5000 60  0000 C CNN
	1    3900 5000
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR016
U 1 1 56651B29
P 1900 5100
F 0 "#PWR016" H 1900 5100 30  0001 C CNN
F 1 "GND" H 1900 5030 30  0001 C CNN
F 2 "" H 1900 5100 60  0000 C CNN
F 3 "" H 1900 5100 60  0000 C CNN
	1    1900 5100
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR017
U 1 1 56651B36
P 3400 5200
F 0 "#PWR017" H 3400 5290 20  0001 C CNN
F 1 "+5V" H 3400 5290 30  0000 C CNN
F 2 "" H 3400 5200 60  0000 C CNN
F 3 "" H 3400 5200 60  0000 C CNN
	1    3400 5200
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-rfid C3
U 1 1 56651B3C
P 2800 1150
F 0 "C3" H 2800 1250 40  0000 L CNN
F 1 "1u" H 2806 1065 40  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2838 1000 30  0001 C CNN
F 3 "" H 2800 1150 60  0000 C CNN
	1    2800 1150
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR018
U 1 1 56651B44
P 2800 1350
F 0 "#PWR018" H 2800 1350 30  0001 C CNN
F 1 "GND" H 2800 1280 30  0001 C CNN
F 2 "" H 2800 1350 60  0000 C CNN
F 3 "" H 2800 1350 60  0000 C CNN
	1    2800 1350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR019
U 1 1 56651B51
P 2800 950
F 0 "#PWR019" H 2800 1040 20  0001 C CNN
F 1 "+5V" H 2800 1040 30  0000 C CNN
F 2 "" H 2800 950 60  0000 C CNN
F 3 "" H 2800 950 60  0000 C CNN
	1    2800 950 
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R3
U 1 1 566523FF
P 1250 5000
F 0 "R3" V 1330 5000 40  0000 C CNN
F 1 "560R" V 1257 5001 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1180 5000 30  0001 C CNN
F 3 "~" H 1250 5000 30  0000 C CNN
	1    1250 5000
	0    -1   -1   0   
$EndComp
NoConn ~ 2200 6100
$Comp
L GND-RESCUE-rfid #PWR020
U 1 1 56652615
P 1900 6600
F 0 "#PWR020" H 1900 6600 30  0001 C CNN
F 1 "GND" H 1900 6530 30  0001 C CNN
F 2 "" H 1900 6600 60  0000 C CNN
F 3 "" H 1900 6600 60  0000 C CNN
	1    1900 6600
	1    0    0    -1  
$EndComp
Text Label 7550 2750 0    60   ~ 0
COIL_DRIVE
$Comp
L VDD #PWR021
U 1 1 56652FD3
P 3400 1950
F 0 "#PWR021" H 3400 2050 30  0001 C CNN
F 1 "VDD" H 3400 2060 30  0000 C CNN
F 2 "" H 3400 1950 60  0000 C CNN
F 3 "" H 3400 1950 60  0000 C CNN
	1    3400 1950
	1    0    0    -1  
$EndComp
$Comp
L MICRO-SD U3
U 1 1 566537AE
P 4350 6950
F 0 "U3" H 4750 6600 60  0000 C CNN
F 1 "MICRO-SD" H 4550 6900 60  0000 C CNN
F 2 "custom:DM3BT" H 4350 6950 60  0001 C CNN
F 3 "" H 4350 6950 60  0000 C CNN
	1    4350 6950
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR022
U 1 1 566537B4
P 5100 6650
F 0 "#PWR022" H 5100 6650 30  0001 C CNN
F 1 "GND" H 5100 6580 30  0001 C CNN
F 2 "" H 5100 6650 60  0000 C CNN
F 3 "" H 5100 6650 60  0000 C CNN
	1    5100 6650
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR023
U 1 1 566537BA
P 5100 6750
F 0 "#PWR023" H 5100 6750 30  0001 C CNN
F 1 "GND" H 5100 6680 30  0001 C CNN
F 2 "" H 5100 6750 60  0000 C CNN
F 3 "" H 5100 6750 60  0000 C CNN
	1    5100 6750
	0    -1   -1   0   
$EndComp
NoConn ~ 4000 6150
Text Label 4100 6150 1    60   ~ 0
SPI_CS
Text Label 4200 6050 1    60   ~ 0
SPI_MOSI
$Comp
L VDD #PWR024
U 1 1 566537C5
P 4300 6150
F 0 "#PWR024" H 4300 6250 30  0001 C CNN
F 1 "VDD" H 4300 6260 30  0000 C CNN
F 2 "" H 4300 6150 60  0000 C CNN
F 3 "" H 4300 6150 60  0000 C CNN
	1    4300 6150
	1    0    0    -1  
$EndComp
Text Label 4400 6000 1    60   ~ 0
SPI_SCK
$Comp
L GND-RESCUE-rfid #PWR025
U 1 1 566537CD
P 4500 6150
F 0 "#PWR025" H 4500 6150 30  0001 C CNN
F 1 "GND" H 4500 6080 30  0001 C CNN
F 2 "" H 4500 6150 60  0000 C CNN
F 3 "" H 4500 6150 60  0000 C CNN
	1    4500 6150
	-1   0    0    1   
$EndComp
Text Label 4600 6050 1    60   ~ 0
SPI_MISO
NoConn ~ 4700 6150
$Comp
L GND-RESCUE-rfid #PWR026
U 1 1 566537D6
P 3600 7050
F 0 "#PWR026" H 3600 7050 30  0001 C CNN
F 1 "GND" H 3600 6980 30  0001 C CNN
F 2 "" H 3600 7050 60  0000 C CNN
F 3 "" H 3600 7050 60  0000 C CNN
	1    3600 7050
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR027
U 1 1 566537DC
P 3600 7150
F 0 "#PWR027" H 3600 7150 30  0001 C CNN
F 1 "GND" H 3600 7080 30  0001 C CNN
F 2 "" H 3600 7150 60  0000 C CNN
F 3 "" H 3600 7150 60  0000 C CNN
	1    3600 7150
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR028
U 1 1 566537E2
P 3600 7250
F 0 "#PWR028" H 3600 7250 30  0001 C CNN
F 1 "GND" H 3600 7180 30  0001 C CNN
F 2 "" H 3600 7250 60  0000 C CNN
F 3 "" H 3600 7250 60  0000 C CNN
	1    3600 7250
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-rfid C4
U 1 1 566537E8
P 3700 6450
F 0 "C4" H 3700 6550 40  0000 L CNN
F 1 "100n" H 3706 6365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 3738 6300 30  0001 C CNN
F 3 "" H 3700 6450 60  0000 C CNN
	1    3700 6450
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR029
U 1 1 566537EE
P 3700 6650
F 0 "#PWR029" H 3700 6650 30  0001 C CNN
F 1 "GND" H 3700 6580 30  0001 C CNN
F 2 "" H 3700 6650 60  0000 C CNN
F 3 "" H 3700 6650 60  0000 C CNN
	1    3700 6650
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR030
U 1 1 566537F4
P 3700 6250
F 0 "#PWR030" H 3700 6350 30  0001 C CNN
F 1 "VDD" H 3700 6360 30  0000 C CNN
F 2 "" H 3700 6250 60  0000 C CNN
F 3 "" H 3700 6250 60  0000 C CNN
	1    3700 6250
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR031
U 1 1 566537FA
P 3600 6950
F 0 "#PWR031" H 3600 6950 30  0001 C CNN
F 1 "GND" H 3600 6880 30  0001 C CNN
F 2 "" H 3600 6950 60  0000 C CNN
F 3 "" H 3600 6950 60  0000 C CNN
	1    3600 6950
	0    1    1    0   
$EndComp
Text Label 5650 3350 0    60   ~ 0
USB_DM
Text Label 5650 3250 0    60   ~ 0
USB_DP
Text Label 5650 3050 0    60   ~ 0
SWCLK
Text Label 5650 3150 0    60   ~ 0
SWDAT
$Comp
L STM32F030-20 U4
U 1 1 566543CC
P 4700 3500
F 0 "U4" H 4700 3400 50  0000 C CNN
F 1 "STM32F030-20" H 4700 3600 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 4700 3500 50  0001 C CNN
F 3 "DOCUMENTATION" H 4700 3500 50  0001 C CNN
	1    4700 3500
	1    0    0    -1  
$EndComp
NoConn ~ 3850 3350
Text Label 4350 2550 0    60   ~ 0
BOOT
Text Label 3600 3050 0    60   ~ 0
BOOT
Text Label 5650 3650 0    60   ~ 0
COIL_DRIVE
Text Label 3450 3950 0    60   ~ 0
SPI_CS
Text Label 5650 3950 0    60   ~ 0
SPI_SCK
Text Label 5650 3850 0    60   ~ 0
SPI_MISO
Text Label 5650 3750 0    60   ~ 0
SPI_MOSI
Text Label 3050 3850 0    60   ~ 0
COIL_DETUNE
Text Label 3050 3750 0    60   ~ 0
COIL_READ
Text Label 3250 3150 0    60   ~ 0
SPOOF
Text Label 3250 3250 0    60   ~ 0
WRITE
Text Label 3250 3550 0    60   ~ 0
READ
$Comp
L GND-RESCUE-rfid #PWR032
U 1 1 5665623E
P 1650 2800
F 0 "#PWR032" H 1650 2800 30  0001 C CNN
F 1 "GND" H 1650 2730 30  0001 C CNN
F 2 "" H 1650 2800 60  0000 C CNN
F 3 "" H 1650 2800 60  0000 C CNN
	1    1650 2800
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR033
U 1 1 5665624B
P 1650 3100
F 0 "#PWR033" H 1650 3100 30  0001 C CNN
F 1 "GND" H 1650 3030 30  0001 C CNN
F 2 "" H 1650 3100 60  0000 C CNN
F 3 "" H 1650 3100 60  0000 C CNN
	1    1650 3100
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR034
U 1 1 56656251
P 1650 3400
F 0 "#PWR034" H 1650 3400 30  0001 C CNN
F 1 "GND" H 1650 3330 30  0001 C CNN
F 2 "" H 1650 3400 60  0000 C CNN
F 3 "" H 1650 3400 60  0000 C CNN
	1    1650 3400
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-rfid R4
U 1 1 56656263
P 2300 2800
F 0 "R4" V 2380 2800 40  0000 C CNN
F 1 "330R" V 2307 2801 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2230 2800 30  0001 C CNN
F 3 "~" H 2300 2800 30  0000 C CNN
	1    2300 2800
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-rfid R5
U 1 1 56656270
P 2300 3100
F 0 "R5" V 2380 3100 40  0000 C CNN
F 1 "330R" V 2307 3101 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2230 3100 30  0001 C CNN
F 3 "~" H 2300 3100 30  0000 C CNN
	1    2300 3100
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-rfid R6
U 1 1 56656276
P 2300 3400
F 0 "R6" V 2380 3400 40  0000 C CNN
F 1 "330R" V 2307 3401 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 2230 3400 30  0001 C CNN
F 3 "~" H 2300 3400 30  0000 C CNN
	1    2300 3400
	0    -1   -1   0   
$EndComp
Text Label 2650 2800 0    60   ~ 0
READ
Text Label 2650 3100 0    60   ~ 0
WRITE
Text Label 2650 3400 0    60   ~ 0
SPOOF
$Comp
L R-RESCUE-rfid R1
U 1 1 5665668A
P 1250 2850
F 0 "R1" V 1330 2850 40  0000 C CNN
F 1 "330R" V 1257 2851 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1180 2850 30  0001 C CNN
F 3 "~" H 1250 2850 30  0000 C CNN
	1    1250 2850
	-1   0    0    1   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR035
U 1 1 56656692
P 1250 3500
F 0 "#PWR035" H 1250 3500 30  0001 C CNN
F 1 "GND" H 1250 3430 30  0001 C CNN
F 2 "" H 1250 3500 60  0000 C CNN
F 3 "" H 1250 3500 60  0000 C CNN
	1    1250 3500
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR036
U 1 1 5665669F
P 1250 2600
F 0 "#PWR036" H 1250 2700 30  0001 C CNN
F 1 "VDD" H 1250 2710 30  0000 C CNN
F 2 "" H 1250 2600 60  0000 C CNN
F 3 "" H 1250 2600 60  0000 C CNN
	1    1250 2600
	1    0    0    -1  
$EndComp
$Comp
L MCP1824 U1
U 1 1 56657211
P 1850 3950
F 0 "U1" V 1550 4250 60  0000 C CNN
F 1 "MCP1824" V 1550 3850 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 1850 3950 60  0001 C CNN
F 3 "~" H 1850 3950 60  0000 C CNN
	1    1850 3950
	0    1    -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR037
U 1 1 566572C2
P 1200 3950
F 0 "#PWR037" H 1200 3950 30  0001 C CNN
F 1 "GND" H 1200 3880 30  0001 C CNN
F 2 "" H 1200 3950 60  0000 C CNN
F 3 "" H 1200 3950 60  0000 C CNN
	1    1200 3950
	0    1    1    0   
$EndComp
$Comp
L +BATT #PWR038
U 1 1 5665738C
P 1100 3750
F 0 "#PWR038" H 1100 3700 20  0001 C CNN
F 1 "+BATT" H 1100 3850 30  0000 C CNN
F 2 "" H 1100 3750 60  0000 C CNN
F 3 "" H 1100 3750 60  0000 C CNN
	1    1100 3750
	1    0    0    -1  
$EndComp
NoConn ~ 2500 3850
Text Label 6700 3750 0    60   ~ 0
COIL_DETUNE
$Comp
L GND-RESCUE-rfid #PWR039
U 1 1 56678BD9
P 8950 4150
F 0 "#PWR039" H 8950 4150 30  0001 C CNN
F 1 "GND" H 8950 4080 30  0001 C CNN
F 2 "" H 8950 4150 60  0000 C CNN
F 3 "" H 8950 4150 60  0000 C CNN
	1    8950 4150
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR040
U 1 1 56678BE8
P 9450 3750
F 0 "#PWR040" H 9450 3750 30  0001 C CNN
F 1 "GND" H 9450 3680 30  0001 C CNN
F 2 "" H 9450 3750 60  0000 C CNN
F 3 "" H 9450 3750 60  0000 C CNN
	1    9450 3750
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR041
U 1 1 566F76AA
P 8650 3150
F 0 "#PWR041" H 8650 3150 30  0001 C CNN
F 1 "GND" H 8650 3080 30  0001 C CNN
F 2 "" H 8650 3150 60  0000 C CNN
F 3 "" H 8650 3150 60  0000 C CNN
	1    8650 3150
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR042
U 1 1 566F76B9
P 8650 2250
F 0 "#PWR042" H 8650 2200 20  0001 C CNN
F 1 "+BATT" H 8650 2350 30  0000 C CNN
F 2 "" H 8650 2250 60  0000 C CNN
F 3 "" H 8650 2250 60  0000 C CNN
	1    8650 2250
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R13
U 1 1 566F784A
P 8450 3800
F 0 "R13" V 8530 3800 40  0000 C CNN
F 1 "100K" V 8457 3801 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 8380 3800 30  0001 C CNN
F 3 "~" H 8450 3800 30  0000 C CNN
	1    8450 3800
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-rfid R12
U 1 1 566F7AFA
P 7950 3950
F 0 "R12" V 8030 3950 40  0000 C CNN
F 1 "1K" V 7957 3951 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 7880 3950 30  0001 C CNN
F 3 "~" H 7950 3950 30  0000 C CNN
	1    7950 3950
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-rfid R2
U 1 1 566F7FE6
P 1250 4700
F 0 "R2" V 1330 4700 40  0000 C CNN
F 1 "680R" V 1257 4701 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 1180 4700 30  0001 C CNN
F 3 "~" H 1250 4700 30  0000 C CNN
	1    1250 4700
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR043
U 1 1 566F7FF5
P 1900 4700
F 0 "#PWR043" H 1900 4700 30  0001 C CNN
F 1 "GND" H 1900 4630 30  0001 C CNN
F 2 "" H 1900 4700 60  0000 C CNN
F 3 "" H 1900 4700 60  0000 C CNN
	1    1900 4700
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR044
U 1 1 566F8002
P 1000 4700
F 0 "#PWR044" H 1000 4790 20  0001 C CNN
F 1 "+5V" H 1000 4790 30  0000 C CNN
F 2 "" H 1000 4700 60  0000 C CNN
F 3 "" H 1000 4700 60  0000 C CNN
	1    1000 4700
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR045
U 1 1 566F82F6
P 7700 3550
F 0 "#PWR045" H 7700 3650 30  0001 C CNN
F 1 "VDD" H 7700 3660 30  0000 C CNN
F 2 "" H 7700 3550 60  0000 C CNN
F 3 "" H 7700 3550 60  0000 C CNN
	1    7700 3550
	1    0    0    -1  
$EndComp
$Comp
L LM324-RESCUE-rfid U5
U 2 1 566FCAFB
P 6950 5250
F 0 "U5" H 7000 5450 60  0000 C CNN
F 1 "LM324" H 7100 5050 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-14_4.4x5mm_Pitch0.65mm" H 6950 5250 60  0001 C CNN
F 3 "" H 6950 5250 60  0000 C CNN
	2    6950 5250
	1    0    0    -1  
$EndComp
$Comp
L LM324-RESCUE-rfid U5
U 1 1 566FCB08
P 6500 6450
F 0 "U5" H 6550 6650 60  0000 C CNN
F 1 "LM324" H 6650 6250 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-14_4.4x5mm_Pitch0.65mm" H 6500 6450 60  0001 C CNN
F 3 "" H 6500 6450 60  0000 C CNN
	1    6500 6450
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R9
U 1 1 566FCBC1
P 5750 5600
F 0 "R9" V 5830 5600 40  0000 C CNN
F 1 "470K" V 5757 5601 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 5680 5600 30  0001 C CNN
F 3 "~" H 5750 5600 30  0000 C CNN
	1    5750 5600
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R10
U 1 1 566FCBD0
P 5750 6100
F 0 "R10" V 5830 6100 40  0000 C CNN
F 1 "10K" V 5757 6101 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 5680 6100 30  0001 C CNN
F 3 "~" H 5750 6100 30  0000 C CNN
	1    5750 6100
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR046
U 1 1 566FCBDF
P 5750 6350
F 0 "#PWR046" H 5750 6350 30  0001 C CNN
F 1 "GND" H 5750 6280 30  0001 C CNN
F 2 "" H 5750 6350 60  0000 C CNN
F 3 "" H 5750 6350 60  0000 C CNN
	1    5750 6350
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR047
U 1 1 566FCC41
P 6850 5650
F 0 "#PWR047" H 6850 5650 30  0001 C CNN
F 1 "GND" H 6850 5580 30  0001 C CNN
F 2 "" H 6850 5650 60  0000 C CNN
F 3 "" H 6850 5650 60  0000 C CNN
	1    6850 5650
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR048
U 1 1 566FCC50
P 6850 4850
F 0 "#PWR048" H 6850 4950 30  0001 C CNN
F 1 "VDD" H 6850 4960 30  0000 C CNN
F 2 "" H 6850 4850 60  0000 C CNN
F 3 "" H 6850 4850 60  0000 C CNN
	1    6850 4850
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-rfid C9
U 1 1 566FCD0F
P 7900 6650
F 0 "C9" H 7900 6750 40  0000 L CNN
F 1 "1n" H 7906 6565 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 7938 6500 30  0001 C CNN
F 3 "~" H 7900 6650 60  0000 C CNN
	1    7900 6650
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R15
U 1 1 566FCD1E
P 8150 6700
F 0 "R15" V 8230 6700 40  0000 C CNN
F 1 "470K" V 8157 6701 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 8080 6700 30  0001 C CNN
F 3 "~" H 8150 6700 30  0000 C CNN
	1    8150 6700
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR049
U 1 1 566FCE1B
P 6400 6850
F 0 "#PWR049" H 6400 6850 30  0001 C CNN
F 1 "GND" H 6400 6780 30  0001 C CNN
F 2 "" H 6400 6850 60  0000 C CNN
F 3 "" H 6400 6850 60  0000 C CNN
	1    6400 6850
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR050
U 1 1 566FCE2A
P 7900 6850
F 0 "#PWR050" H 7900 6850 30  0001 C CNN
F 1 "GND" H 7900 6780 30  0001 C CNN
F 2 "" H 7900 6850 60  0000 C CNN
F 3 "" H 7900 6850 60  0000 C CNN
	1    7900 6850
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR051
U 1 1 566FCE39
P 8150 6950
F 0 "#PWR051" H 8150 6950 30  0001 C CNN
F 1 "GND" H 8150 6880 30  0001 C CNN
F 2 "" H 8150 6950 60  0000 C CNN
F 3 "" H 8150 6950 60  0000 C CNN
	1    8150 6950
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR052
U 1 1 566FCE48
P 5900 7350
F 0 "#PWR052" H 5900 7450 30  0001 C CNN
F 1 "VDD" H 5900 7460 30  0000 C CNN
F 2 "" H 5900 7350 60  0000 C CNN
F 3 "" H 5900 7350 60  0000 C CNN
	1    5900 7350
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR053
U 1 1 566FD077
P 6400 6050
F 0 "#PWR053" H 6400 6150 30  0001 C CNN
F 1 "VDD" H 6400 6160 30  0000 C CNN
F 2 "" H 6400 6050 60  0000 C CNN
F 3 "" H 6400 6050 60  0000 C CNN
	1    6400 6050
	1    0    0    -1  
$EndComp
$Comp
L LM324-RESCUE-rfid U5
U 3 1 566FD383
P 9000 6450
F 0 "U5" H 9050 6650 60  0000 C CNN
F 1 "LM324" H 9150 6250 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-14_4.4x5mm_Pitch0.65mm" H 9000 6450 60  0001 C CNN
F 3 "" H 9000 6450 60  0000 C CNN
	3    9000 6450
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR054
U 1 1 566FD38B
P 8900 6850
F 0 "#PWR054" H 8900 6850 30  0001 C CNN
F 1 "GND" H 8900 6780 30  0001 C CNN
F 2 "" H 8900 6850 60  0000 C CNN
F 3 "" H 8900 6850 60  0000 C CNN
	1    8900 6850
	1    0    0    -1  
$EndComp
$Comp
L LM324-RESCUE-rfid U5
U 4 1 566FD454
P 10500 5850
F 0 "U5" H 10550 6050 60  0000 C CNN
F 1 "LM324" H 10650 5650 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-14_4.4x5mm_Pitch0.65mm" H 10500 5850 60  0001 C CNN
F 3 "" H 10500 5850 60  0000 C CNN
	4    10500 5850
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R16
U 1 1 566FD45C
P 9750 5750
F 0 "R16" V 9830 5750 40  0000 C CNN
F 1 "1K" V 9757 5751 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 9680 5750 30  0001 C CNN
F 3 "~" H 9750 5750 30  0000 C CNN
	1    9750 5750
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-rfid R18
U 1 1 566FD46B
P 10250 5250
F 0 "R18" V 10330 5250 40  0000 C CNN
F 1 "470K" V 10257 5251 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 10180 5250 30  0001 C CNN
F 3 "~" H 10250 5250 30  0000 C CNN
	1    10250 5250
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-rfid R17
U 1 1 566FD47A
P 9750 5950
F 0 "R17" V 9830 5950 40  0000 C CNN
F 1 "1K" V 9757 5951 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 9680 5950 30  0001 C CNN
F 3 "~" H 9750 5950 30  0000 C CNN
	1    9750 5950
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-rfid R19
U 1 1 566FD489
P 10250 6450
F 0 "R19" V 10330 6450 40  0000 C CNN
F 1 "470K" V 10257 6451 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 10180 6450 30  0001 C CNN
F 3 "~" H 10250 6450 30  0000 C CNN
	1    10250 6450
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR055
U 1 1 566FD498
P 10400 6250
F 0 "#PWR055" H 10400 6250 30  0001 C CNN
F 1 "GND" H 10400 6180 30  0001 C CNN
F 2 "" H 10400 6250 60  0000 C CNN
F 3 "" H 10400 6250 60  0000 C CNN
	1    10400 6250
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR056
U 1 1 566FD4B1
P 10400 5450
F 0 "#PWR056" H 10400 5550 30  0001 C CNN
F 1 "VDD" H 10400 5560 30  0000 C CNN
F 2 "" H 10400 5450 60  0000 C CNN
F 3 "" H 10400 5450 60  0000 C CNN
	1    10400 5450
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR057
U 1 1 566FD577
P 10750 5400
F 0 "#PWR057" H 10750 5400 30  0001 C CNN
F 1 "GND" H 10750 5330 30  0001 C CNN
F 2 "" H 10750 5400 60  0000 C CNN
F 3 "" H 10750 5400 60  0000 C CNN
	1    10750 5400
	1    0    0    -1  
$EndComp
Text Label 11000 5850 0    60   ~ 0
COIL_READ
$Comp
L VDD #PWR058
U 1 1 566FE069
P 8900 6050
F 0 "#PWR058" H 8900 6150 30  0001 C CNN
F 1 "VDD" H 8900 6160 30  0000 C CNN
F 2 "" H 8900 6050 60  0000 C CNN
F 3 "" H 8900 6050 60  0000 C CNN
	1    8900 6050
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-rfid R14
U 1 1 566FE1E1
P 7650 6450
F 0 "R14" V 7730 6450 40  0000 C CNN
F 1 "100R" V 7657 6451 40  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 7580 6450 30  0001 C CNN
F 3 "~" H 7650 6450 30  0000 C CNN
	1    7650 6450
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-rfid C10
U 1 1 566FE89C
P 8100 5800
F 0 "C10" H 8100 5900 40  0000 L CNN
F 1 "100n" H 8106 5715 40  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 8138 5650 30  0001 C CNN
F 3 "~" H 8100 5800 60  0000 C CNN
	1    8100 5800
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR059
U 1 1 566FE8A2
P 8100 5600
F 0 "#PWR059" H 8100 5700 30  0001 C CNN
F 1 "VDD" H 8100 5710 30  0000 C CNN
F 2 "" H 8100 5600 60  0000 C CNN
F 3 "" H 8100 5600 60  0000 C CNN
	1    8100 5600
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-rfid #PWR060
U 1 1 566FE8A8
P 8100 6000
F 0 "#PWR060" H 8100 6000 30  0001 C CNN
F 1 "GND" H 8100 5930 30  0001 C CNN
F 2 "" H 8100 6000 60  0000 C CNN
F 3 "" H 8100 6000 60  0000 C CNN
	1    8100 6000
	1    0    0    -1  
$EndComp
Text Label 7500 4900 0    60   ~ 0
COIL_READ_AMP
Text Label 3050 3650 0    60   ~ 0
COIL_READ_AMP
$Comp
L USB_OTG P1
U 1 1 5705F2D1
P 2250 1650
F 0 "P1" H 2575 1525 50  0000 C CNN
F 1 "USB_OTG" H 2250 1850 50  0000 C CNN
F 2 "Connect:USB_Micro-B" V 2200 1550 50  0001 C CNN
F 3 "" V 2200 1550 50  0000 C CNN
	1    2250 1650
	0    -1   1    0   
$EndComp
NoConn ~ 2550 1750
$Comp
L GND #PWR061
U 1 1 5705FACA
P 2150 2050
F 0 "#PWR061" H 2150 1800 50  0001 C CNN
F 1 "GND" H 2150 1900 50  0000 C CNN
F 2 "" H 2150 2050 50  0000 C CNN
F 3 "" H 2150 2050 50  0000 C CNN
	1    2150 2050
	1    0    0    -1  
$EndComp
$Comp
L Q_PMOS_GSD Q2
U 1 1 57061DAD
P 8550 2550
F 0 "Q2" H 8850 2600 50  0000 R CNN
F 1 "Q_PMOS_GSD" H 9200 2500 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8750 2650 50  0001 C CNN
F 3 "" H 8550 2550 50  0000 C CNN
	1    8550 2550
	1    0    0    1   
$EndComp
$Comp
L Q_NMOS_GSD Q3
U 1 1 5706231C
P 8550 2950
F 0 "Q3" H 8850 3000 50  0000 R CNN
F 1 "Q_NMOS_GSD" H 9200 2900 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8750 3050 50  0001 C CNN
F 3 "" H 8550 2950 50  0000 C CNN
	1    8550 2950
	1    0    0    -1  
$EndComp
Connection ~ 8350 2750
Connection ~ 8200 2750
Wire Wire Line
	7450 2750 8350 2750
Wire Wire Line
	8350 2550 8350 2950
Connection ~ 1100 4050
Wire Wire Line
	3850 3650 3000 3650
Wire Wire Line
	7450 4900 8250 4900
Wire Wire Line
	7900 6450 8500 6450
Wire Wire Line
	9500 5950 9500 7000
Connection ~ 9500 6450
Connection ~ 7450 5250
Connection ~ 11000 5850
Wire Wire Line
	11000 5850 11500 5850
Wire Wire Line
	11000 6450 11000 5850
Wire Wire Line
	10500 6450 11000 6450
Wire Wire Line
	10750 5250 10750 5400
Wire Wire Line
	10500 5250 10750 5250
Connection ~ 8150 6450
Wire Wire Line
	8500 6450 8500 6350
Wire Wire Line
	9500 7000 8500 7000
Wire Wire Line
	8500 7000 8500 6550
Connection ~ 5750 5850
Connection ~ 6000 5850
Wire Wire Line
	6000 5150 6450 5150
Wire Wire Line
	6000 5150 6000 6350
Wire Wire Line
	5750 5850 6000 5850
Connection ~ 7400 6450
Connection ~ 7900 6450
Wire Wire Line
	7400 7000 7400 6450
Wire Wire Line
	6000 7000 7400 7000
Wire Wire Line
	6000 6550 6000 7000
Wire Wire Line
	7450 4900 7450 5800
Wire Wire Line
	7450 5800 6450 5800
Wire Wire Line
	6450 5800 6450 5350
Wire Wire Line
	5750 4450 5750 5050
Wire Wire Line
	5750 4450 10200 4450
Wire Wire Line
	8200 3950 8650 3950
Connection ~ 8950 3650
Connection ~ 8200 3950
Connection ~ 8200 3800
Connection ~ 8200 3500
Wire Wire Line
	8650 3350 8200 3350
Wire Wire Line
	8200 3350 8200 3950
Wire Wire Line
	8250 3500 8200 3500
Connection ~ 8700 3650
Wire Wire Line
	8700 3500 8700 3800
Wire Wire Line
	8650 3500 8700 3500
Wire Wire Line
	8950 3650 8700 3650
Connection ~ 8650 2250
Wire Wire Line
	8650 2250 8650 2350
Wire Wire Line
	8650 2250 8200 2250
Connection ~ 9450 3150
Wire Wire Line
	8950 3150 10200 3150
Wire Wire Line
	7400 3750 6650 3750
Wire Wire Line
	2500 4050 2750 4050
Connection ~ 1100 3850
Wire Wire Line
	1100 4050 1200 4050
Wire Wire Line
	1100 3750 1100 4050
Wire Wire Line
	1200 3850 1100 3850
Wire Wire Line
	2550 3400 2950 3400
Wire Wire Line
	2550 3100 2950 3100
Wire Wire Line
	2550 2800 2950 2800
Wire Wire Line
	3850 3550 3200 3550
Wire Wire Line
	3850 3250 3200 3250
Wire Wire Line
	3850 3150 3200 3150
Wire Wire Line
	3850 3750 3000 3750
Wire Wire Line
	3850 3850 3000 3850
Wire Wire Line
	5550 3750 6150 3750
Wire Wire Line
	5550 3850 6150 3850
Wire Wire Line
	5550 3950 6150 3950
Wire Wire Line
	3850 3950 3400 3950
Wire Wire Line
	5550 3650 6150 3650
Wire Wire Line
	3850 3050 3550 3050
Wire Wire Line
	5550 3050 6050 3050
Wire Wire Line
	5550 3150 6050 3150
Wire Wire Line
	5550 3250 6050 3250
Wire Wire Line
	5550 3350 6050 3350
Wire Wire Line
	4600 6150 4600 5600
Wire Wire Line
	4400 6150 4400 5600
Wire Wire Line
	4200 6150 4200 5600
Wire Wire Line
	4100 6150 4100 5600
Connection ~ 1900 6000
Connection ~ 1900 5200
Wire Wire Line
	1000 5200 1900 5200
Wire Wire Line
	1000 5000 1000 5200
Wire Wire Line
	1900 6000 2200 6000
Wire Wire Line
	1900 5200 1900 6000
Connection ~ 4750 850 
Connection ~ 4750 1250
Wire Wire Line
	4750 1300 4750 1250
Wire Wire Line
	4500 850  5000 850 
Wire Wire Line
	4500 1250 5000 1250
Connection ~ 2750 4050
Wire Wire Line
	2550 1550 3200 1550
Wire Wire Line
	2550 1650 3200 1650
Wire Wire Line
	4000 2550 4750 2550
Connection ~ 4200 2550
Connection ~ 8650 2750
$Comp
L Q_NMOS_GSD Q4
U 1 1 5706432C
P 8850 3350
F 0 "Q4" H 9150 3400 50  0000 R CNN
F 1 "Q_NMOS_GSD" H 9500 3300 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9050 3450 50  0001 C CNN
F 3 "" H 8850 3350 50  0000 C CNN
	1    8850 3350
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q5
U 1 1 5706442A
P 8850 3950
F 0 "Q5" H 9150 4000 50  0000 R CNN
F 1 "Q_NMOS_GSD" H 9500 3900 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9050 4050 50  0001 C CNN
F 3 "" H 8850 3950 50  0000 C CNN
	1    8850 3950
	1    0    0    1   
$EndComp
Wire Wire Line
	8950 3550 8950 3750
$Comp
L Q_PMOS_GSD Q1
U 1 1 57064CEC
P 7600 3750
F 0 "Q1" H 7900 3800 50  0000 R CNN
F 1 "Q_PMOS_GSD" H 8250 3700 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7800 3850 50  0001 C CNN
F 3 "" H 7600 3750 50  0000 C CNN
	1    7600 3750
	1    0    0    1   
$EndComp
Wire Wire Line
	8650 2750 9450 2750
Wire Wire Line
	10200 3150 10200 4450
$Comp
L CONN_01X04 P2
U 1 1 57067FDC
P 6450 2350
F 0 "P2" H 6450 2600 50  0000 C CNN
F 1 "SWD" V 6550 2350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 6450 2350 50  0001 C CNN
F 3 "" H 6450 2350 50  0000 C CNN
	1    6450 2350
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR062
U 1 1 570683E3
P 6250 2200
F 0 "#PWR062" H 6250 2300 30  0001 C CNN
F 1 "VDD" H 6250 2310 30  0000 C CNN
F 2 "" H 6250 2200 60  0000 C CNN
F 3 "" H 6250 2200 60  0000 C CNN
	1    6250 2200
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-rfid #PWR063
U 1 1 5706849C
P 6250 2400
F 0 "#PWR063" H 6250 2400 30  0001 C CNN
F 1 "GND" H 6250 2330 30  0001 C CNN
F 2 "" H 6250 2400 60  0000 C CNN
F 3 "" H 6250 2400 60  0000 C CNN
	1    6250 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 2300 5500 2300
Wire Wire Line
	6250 2500 5500 2500
Text Label 5600 2300 0    60   ~ 0
SWCLK
Text Label 5600 2500 0    60   ~ 0
SWDAT
Wire Wire Line
	3200 6000 3350 6000
Wire Wire Line
	2200 6000 2200 5900
$Comp
L LED D4
U 1 1 5706DAC4
P 1850 2800
F 0 "D4" H 1850 2900 50  0000 C CNN
F 1 "READ" H 1850 2700 50  0000 C CNN
F 2 "LEDs:LED_0603" H 1850 2800 50  0001 C CNN
F 3 "" H 1850 2800 50  0000 C CNN
	1    1850 2800
	1    0    0    -1  
$EndComp
$Comp
L LED D5
U 1 1 5706DBA4
P 1850 3100
F 0 "D5" H 1850 3200 50  0000 C CNN
F 1 "WRITE" H 1850 3000 50  0000 C CNN
F 2 "LEDs:LED_0603" H 1850 3100 50  0001 C CNN
F 3 "" H 1850 3100 50  0000 C CNN
	1    1850 3100
	1    0    0    -1  
$EndComp
$Comp
L LED D9
U 1 1 5706DC62
P 1850 3400
F 0 "D9" H 1850 3500 50  0000 C CNN
F 1 "SPOOF" H 1850 3300 50  0000 C CNN
F 2 "LEDs:LED_0603" H 1850 3400 50  0001 C CNN
F 3 "" H 1850 3400 50  0000 C CNN
	1    1850 3400
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5706DD1F
P 1250 3300
F 0 "D1" H 1250 3400 50  0000 C CNN
F 1 "PWR" H 1250 3200 50  0000 C CNN
F 2 "LEDs:LED_0603" H 1250 3300 50  0001 C CNN
F 3 "" H 1250 3300 50  0000 C CNN
	1    1250 3300
	0    -1   -1   0   
$EndComp
$Comp
L LED D2
U 1 1 5706DDEF
P 1700 4700
F 0 "D2" H 1700 4800 50  0000 C CNN
F 1 "USB" H 1700 4600 50  0000 C CNN
F 2 "LEDs:LED_0603" H 1700 4700 50  0001 C CNN
F 3 "" H 1700 4700 50  0000 C CNN
	1    1700 4700
	-1   0    0    1   
$EndComp
$Comp
L LED D3
U 1 1 5706DEEA
P 1700 5000
F 0 "D3" H 1700 5100 50  0000 C CNN
F 1 "CHARGE" H 1700 4900 50  0000 C CNN
F 2 "LEDs:LED_0603" H 1700 5000 50  0001 C CNN
F 3 "" H 1700 5000 50  0000 C CNN
	1    1700 5000
	-1   0    0    1   
$EndComp
Text Notes 2500 6300 0    60   ~ 0
MHSS1105
Wire Wire Line
	10000 5950 10000 6450
Wire Wire Line
	10000 5250 10000 5750
Connection ~ 10000 5750
Connection ~ 10000 5950
Wire Wire Line
	7450 5250 9500 5250
Wire Wire Line
	9500 5250 9500 5750
$Comp
L ZENER D8
U 1 1 57088930
P 8450 3500
F 0 "D8" H 8450 3600 50  0000 C CNN
F 1 "5V6" H 8450 3400 50  0000 C CNN
F 2 "Diodes_SMD:SOD-523" H 8450 3500 50  0001 C CNN
F 3 "" H 8450 3500 50  0000 C CNN
	1    8450 3500
	1    0    0    -1  
$EndComp
$Comp
L D D6
U 1 1 57088FAD
P 5750 5200
F 0 "D6" H 5750 5300 50  0000 C CNN
F 1 "1N4148" H 5750 5100 50  0000 C CNN
F 2 "Diodes_SMD:SOD-523" H 5750 5200 50  0001 C CNN
F 3 "" H 5750 5200 50  0000 C CNN
	1    5750 5200
	0    -1   -1   0   
$EndComp
$Comp
L D D7
U 1 1 57089360
P 7250 6450
F 0 "D7" H 7250 6550 50  0000 C CNN
F 1 "1N4148" H 7250 6350 50  0000 C CNN
F 2 "Diodes_SMD:SOD-523" H 7250 6450 50  0001 C CNN
F 3 "" H 7250 6450 50  0000 C CNN
	1    7250 6450
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 6450 7000 6450
Text Notes 5800 4650 0    60   ~ 0
TODO: make this first stage inverting, and use a better precision rectifier below
Text Notes 7450 6250 0    60   ~ 0
R14->2.2K
Text Notes 7500 2500 0    60   ~ 0
R11->180R
Text Notes 5150 5750 0    60   ~ 0
R9->82K
Text Notes 7600 5000 0    60   ~ 0
Remove this signal, instead route COIL_READ to two pins
$EndSCHEMATC
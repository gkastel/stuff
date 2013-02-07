# Send commands to roomba serial through any serial interface

import serial
import time


def bfo(ser, speed):
	ser.write( bytearray([137, 0, 60, 0, 0]))
	time.sleep(4.5)
	ser.write( bytearray([137, 255,70, 0, 0]))
	time.sleep(4.2)
	ser.write( bytearray([137, 0, 0, 0, 0]))
	time.sleep(4.5)


def test():

	ser = serial.Serial(port="COM7", baudrate=115200, parity=serial.PARITY_NONE )
	ser.write( bytearray([128,131]))

	time.sleep(1)
	for i in range(40):
		bfo(ser, 200)

	time.sleep(1)

	ser.write( bytearray([137, 0, 0, 0, 0]))
	ser.close()
		
	ser.close()
test()


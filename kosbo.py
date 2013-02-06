# this is to control the 10-digit nixie-tube display from kosbotubes.com

import serial
import time


def bfo(ser, speed):
	ser.write( bytearray([137, 0, 60, 0, 0]))
	time.sleep(0.5)
	ser.write( bytearray([137, 255,70, 0, 0]))
	time.sleep(0.2)
	ser.write( bytearray([137, 0, 0, 0, 0]))
	time.sleep(0.5)


def test():
	lets = ['1','2','3','4','5','6','7','8','9','0']
	ser = serial.Serial(port="COM8", baudrate=9600, parity=serial.PARITY_NONE, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, xonxoff=False, rtscts=False,dsrdtr=False )
	s = bytearray("11111111111")
	for i in range(8):
		print(chr(s[i]))
		ser.write(s) #chr(s[i]))
		time.sleep(1)

		
	ser.close()


test()

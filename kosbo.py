# this is to control the 8-digit nixie-tube  from kosbo.com : http://www.kosbo.com/index.php?page=shop.product_details&flypage=flypage.tpl&product_id=21&category_id=6&option=com_virtuemart&Itemid=18&vmcchk=1&Itemid=18
# It doesnt really work for me  ... 


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


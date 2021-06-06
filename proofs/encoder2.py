#fuentes:
# http://makezine.com/projects/tutorial-raspberry-pi-gpio-pins-and-python/
# http://raspi.tv/2014/rpi-gpio-update-and-detecting-both-rising-and-falling-edges
import smbus
import time
import sys
import RPi.GPIO as GPIO
from time import sleep     # this lets us have a time delay (see line 12)  
#set up GPIO using BCM numbering
GPIO.setmode(GPIO.BCM)
#setup GPIO using Board numbering
#GPIO.setmode(GPIO.BOARD)

faseA = 17
faseB = 27
encoderValue = 0
clockWise = True
GPIO.setup(faseA, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(faseB, GPIO.IN, pull_up_down = GPIO.PUD_UP)

def encoderFunction(channel):
		global encoderValue
		if GPIO.input(faseA) == GPIO.input(faseB):
			encoderValue += 1
		else:
			encoderValue -= 1
def encoderFunction2(channel):  
		global encoderValue
		if GPIO.input(faseA) == GPIO.input(faseB):
			encoderValue += 1
		else:
			encoderValue -= 1
GPIO.add_event_detect(faseA, GPIO.BOTH, callback=encoderFunction,bouncetime=200)
GPIO.add_event_detect(faseB, GPIO.BOTH, callback=encoderFunction2,bouncetime=200)

try:
	while True:
			print ("EN",encoderValue)
except (KeyboardInterrupt, SystemExit):
	print ('\n...Program Stopped Manually!')
	sys.exit()
		


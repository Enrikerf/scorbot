#fuentes:
# http://makezine.com/projects/tutorial-raspberry-pi-gpio-pins-and-python/
# http://raspi.tv/2014/rpi-gpio-update-and-detecting-both-rising-and-falling-edges
import RPi.GPIO as GPIO
from time import sleep     # this lets us have a time delay (see line 12)  
#set up GPIO using BCM numbering
GPIO.setmode(GPIO.BCM)
#setup GPIO using Board numbering
#GPIO.setmode(GPIO.BOARD)

faseA = 19
faseB = 26
encoderValue = 0
clockWise = True
GPIO.setup(faseA, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(faseB, GPIO.IN, pull_up_down = GPIO.PUD_UP)

def encoderFunction(channel):
    global encoderValue
    global clockWise
    if channel ==1:
        print("faseA")
    else:
        print("faseB")
    if GPIO.input(faseA) == GPIO.input(faseB): # if port 25 == 1
        encoderValue+=1
        clockWise = True
        print ("encodervalue:",encoderValue,"(clockWise=",clockWise,")")
    else:                  # if port 25 != 1  
        encoderValue-=1
        clockWise = False
        print ("encodervalue:",encoderValue,"(clockWise=",clockWise,")")

    
GPIO.add_event_detect(faseA, GPIO.BOTH, callback=encoderFunction)
GPIO.add_event_detect(faseB, GPIO.BOTH, callback=encoderFunction)
while True:
    sleep(30)
GPIO.cleanup()

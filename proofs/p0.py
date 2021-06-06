import RPi.GPIO as GPIO
#set up GPIO using BCM numbering
GPIO.setmode(GPIO.BCM)
#setup GPIO using Board numbering
#GPIO.setmode(GPIO.BOARD)

pullDownPin = 19
pullUpPin = 26
GPIO.setup(pullDownPin, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(pullUpPin, GPIO.IN, pull_up_down = GPIO.PUD_UP)
while True:
    GPIO.wait_for_edge(pullDownPin, GPIO.RISING)
    print("Button 1 Pressed")
    GPIO.wait_for_edge(pullDownPin, GPIO.FALLING)
    print("Button 1 Released")
    GPIO.wait_for_edge(pullUpPin, GPIO.FALLING)
    print("Button 2 Pressed")
    GPIO.wait_for_edge(pullUpPin, GPIO.RISING)
    print("Button 2 Released")
GPIO.cleanup()

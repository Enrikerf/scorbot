import RPi.GPIO as GPIO
#set up GPIO using BCM numbering
GPIO.setmode(GPIO.BCM)
#setup GPIO using Board numbering
#GPIO.setmode(GPIO.BOARD)

faseA = 19
faseB = 26
GPIO.setup(faseA, GPIO.IN, pull_up_down = GPIO.PUD_UP)
GPIO.setup(faseB, GPIO.IN, pull_up_down = GPIO.PUD_UP)
def printFunction(channel):
    print("Button faseA pressed!")
    print("Note how the bouncetime affects the button press")
GPIO.add_event_detect(faseA, GPIO.FALLING, callback=printFunction, bouncetime=300)
while True:
    GPIO.wait_for_edge(faseB, GPIO.FALLING)
    print("Button 2 Pressed")
    GPIO.wait_for_edge(faseB, GPIO.RISING)
    print("Button 2 Released")
GPIO.cleanup()

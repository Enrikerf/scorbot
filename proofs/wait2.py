import RPi.GPIO as GPIO
#set up GPIO using BCM numbering
GPIO.setmode(GPIO.BCM)
#setup GPIO using Board numbering
#GPIO.setmode(GPIO.BOARD)

faseA = 19
faseB = 26

GPIO.setup(faseA, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(faseB, GPIO.IN, pull_up_down = GPIO.PUD_UP)
while True:
    GPIO.wait_for_edge(faseA, GPIO.RISING)
    print("Button fase A Pressed")
    GPIO.wait_for_edge(faseB, GPIO.FALLING)
    print("Button fase A Released")
    GPIO.wait_for_edge(faseA, GPIO.FALLING)
    print("Button fase B Pressed")
    GPIO.wait_for_edge(faseB, GPIO.RISING)
    print("Button fase B Released")
GPIO.cleanup()

from enum import Enum
import orders
import sys
import functions as f
global I2C_BUFFER_LENGTH
I2C_BUFFER_LENGTH = 4

while True:
    try:
        givenString = ""
        parsedString = []
        givenString = input(">")   
        givenString += '\n' 
        encodedString = f.encodeString(givenString)
        print(encodedString)
        buffer = f.prepareSentence(encodedString)
        print(buffer)
    except (KeyboardInterrupt, SystemExit):
        print ('\n...Program Stopped Manually!')
        sys.exit()



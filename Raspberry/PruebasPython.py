# -* - coding: utf-8 -*-
import smbus
import time
from enum import Enum
import orders
import sys
import functions as f
global I2C_BUFFER_LENGTH
I2C_BUFFER_LENGTH = 4


# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)
# This is the address we setup in the Arduino Program
address = 0x04

def writeNumber(value):
    bus.write_byte(address, int(value))
    # bus.write_byte_data(address, 0, value)
    return -1
def writeBytes(bytes):
    bus.write_i2c_block_data(address,38,bytes)
    return -1
    
def readBytes():
    requestSentence = bus.read_i2c_block_data(address,38)
    return requestSentence

def readNumber():
    number = bus.read_byte(address)
    # number = bus.read_byte_data(address, 1)
    return number

while True:
    try:
        givenString = ""
        parsedString = []
        givenString = input(">")   
        givenString += '\n' 
        encodedString = f.encodeString(givenString)
        buffer = f.prepareSentence(encodedString)
        exception = '!' in buffer
        if  not exception:
                for stack in buffer:
                     print("-->Stack:",stack)
                     byteSentence = list(stack.encode('utf-8'))
                     writeBytes(byteSentence)
                #como recibir más de un stack?
                #En la respuesta tiene que haber un caracter clave y se piden hasta que no se encuentre
                requestSentence = readBytes()
                print ("-->Arduino said: ",  ''.join( chr(byte) for byte in requestSentence))
        else: 
            print("-->sentencia no valida")

        
    except (KeyboardInterrupt, SystemExit):
        print ('\n...Program Stopped Manually!')
        sys.exit()


#AXES SET_BRAKE_PIN 1 52
#AXES SET_DIR_PIN 1 53
#AXES SET_PWM_PIN 1 2
#AXES SET_BRAKE 1 0
#AXES SET_DIR 1 1 
#AXES SET_PWM 1 255

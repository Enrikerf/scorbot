import smbus
import time
# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

def writeNumber(value):
    bus.write_byte(address, int(value))
    # bus.write_byte_data(address, 0, value)
    return -1
def writeBytes(bytes):
    bus.write_i2c_block_data(address,48 ,bytes)
    return -1
    
def readBytes():
    requestSentence = bus.read_i2c_block_data(address,0,32)
    return requestSentence

def readNumber():
    number = bus.read_byte(address)
    # number = bus.read_byte_data(address, 1)
    return number

while True:
    sentence = input("introduce una secuencia terminada en intro:")
    if not sentence:
        continue
    sentence = sentence + "\n"
    byteSentence = list(sentence.encode('utf-8'))
    writeBytes(byteSentence)
    print ("RPI: Hi Arduino, I sent you :<",sentence,"> thats mean:<" , byteSentence,">")
    # sleep one second
    time.sleep(1)

    requestSentence = readBytes()
    print ("Arduino: Hey RPI, I received a digit ", requestSentence)

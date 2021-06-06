global I2C_BUFFER_LENGTH
I2C_BUFFER_LENGTH = 31
import orders as myOrders

def encodeString(givenString):
    encodedString = []
    parsedString = givenString.split(" ")    
    # If there are no three elements is not a valid sentence
    if(len(parsedString) >= 3):
        # if the first parsed element is a known command type
        if findCmdType(parsedString[0],encodedString):
            # if the second parsed element is a known command
            if findCmd(parsedString[1],encodedString):
                #if the thirth parsed element is a who type
                if findWhos(parsedString[2],encodedString):
                    print("-->comando con destinatario")
                else:
                    print("-->comando sin destinatario")
                del parsedString[:3]                
                for component in parsedString:
                    encodedString.append(component)                    
            else:
                 print("-->cmd invalido")
                 encodedString.append('!')    
        else:
            print("-->cmd_type invalido!")
            encodedString.append('!')
    else: 
        print("-->sentencia invalida")
        encodedString.append('!')
    return encodedString
#endef

def findCmdType(givenCmdType,encodedString):
    # compare to obtend the cmd type
    valid = False
    for cmdType in myOrders.CMD_TYPE: 
        if givenCmdType == cmdType.name:
            encodedString.append(cmdType.value)
            valid = True
    return valid
#endef

def findCmd(givenCmd,encodedString):
    # compare to obtend the cmd type
    valid = False
    for cmd in myOrders.cmds[encodedString[0]]:
        if givenCmd == cmd.name:
            encodedString.append(cmd.value)
            valid = True
    return valid
#endef

def findWhos(givenWhos,encodedString):
    # if the component has '(' character is a whos element
    existWhos = False
    if givenWhos.find("(") != -1 and givenWhos.find(")"):
        existWhos = True
    encodedString.append(givenWhos)
    return existWhos
#endef

def prepareSentence(encodedString):
    #falta añadirle el \n
    counter = 0
    buffer = []
    sentencePart = []
    stringEncodedString = ' '.join(map(str,encodedString))
    buffer = [stringEncodedString[i:i+I2C_BUFFER_LENGTH] for i in range(0,len(stringEncodedString),I2C_BUFFER_LENGTH)]
    return buffer
#endef

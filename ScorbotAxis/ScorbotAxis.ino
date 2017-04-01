/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

// Configuration files
#include "config.h"  
#define phaseAPin  3 // external interrupt #0 for encoder phase A signal
#define phaseBPin  4 // external interrupt #1 for encoder phase B signal
int encoderValue;
bool clockwise;
/**SETUP FUNCTION */
void setup() {  
    mySerial.init(); 
    myI2C.init();
    encoderValue = 0;
    clockwise = false;
    // Intentar que estas dos lineas estén en la clase myI2C; da problemas
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    pinMode(phaseAPin, INPUT_PULLUP);
    pinMode(phaseBPin, INPUT_PULLUP);
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);
    axis1.setId(1);
}

/**LOOP FUNCTION */
void loop() {  
 
    if(myI2C.getSentenceCompleteFlag()){
      myComm.setSentence(myI2C.getSentence());
      myComm.extractOrderOfSentence();
      myComm.logSentenceOrder();
      //myAxesController.processOrder(MyComm.getOrder());
      axis1.processCmd(myComm.getOrder().cmd,myComm.getOrder().args[0]);
      myComm.flush();
      myI2C.flush();
      
    }
    Serial.print(encoderValue);
    Serial.print("--");
    Serial.print(digitalRead(phaseAPin));
    Serial.print("--");
    Serial.print(digitalRead(phaseBPin));
    Serial.print("--");
    Serial.println(clockwise);
    delay(2500);        
}

/*
*------------------------------------------------------------------------------------------------
*  FUNCTIONS INTERRUPT ROUTINES
*------------------------------------------------------------------------------------------------
*/

// Serial interruption
void serialEvent(){
  serialError =  mySerial.mySerialEvent();
  mySerial.flush();
  if(serialError){
    mySerial.error("\n\n\n ---> Error: exceed Serial buffer size \n\n");
    mySerial.flush();
  }  
}


void receiveEvent(int nBytes){
  myI2C.receiveRoutine(nBytes);
}

void requestEvent(){
  myI2C.requestRoutine();
}

void doEncoderA () {
  if (digitalRead(phaseAPin) == digitalRead(phaseBPin)) {
    encoderValue++;
    clockwise = true;
  }
  else {
    encoderValue--;
    clockwise = false;
  }
}

/*
 * doEncoderB - ISR function for encoder phase B external interrupt
 *
 * If pinA and pinB are one high and the other low, it is spinning
 * forward. If they're equal, it's going backward.
*/
void doEncoderB () {
  if (digitalRead(phaseAPin) != digitalRead(phaseBPin)) {
    encoderValue++;
    clockwise = true;
  }
  else {
    encoderValue--;
    clockwise = false;
  }
}


/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

// Configuration files
#include "config.h"  


int number = 0;
/**SETUP FUNCTION */
void setup() {  
    mySerial.init(); 
    myI2C.init();
    // Intentar que estas dos lineas estén en la clase myI2C; da problemas
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

/**LOOP FUNCTION */
void loop() {  
 
    if(myI2C.getSentenceCompleteFlag()){
      myComm.setSentence(myI2C.getSentence());
      myComm.parseSentenceByOrders();
      myComm.logSentenceComponents();
      myI2C.flush();
    }
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



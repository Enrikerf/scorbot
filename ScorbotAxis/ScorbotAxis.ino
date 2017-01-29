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
    //mySerial.init(); 
    Serial.begin(serialBaud);
    myI2C.init();
    // Intentar que estas dos lineas estén en la clase myI2C; da problemas
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

/**LOOP FUNCTION */
void loop() {  

/** 1- READ ALL DIGITAL INPUTS; ACTUAL STATE. ACTUAL IMAGE OF STATE MACHINE */ 
/** 2- IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES (SEND ORDERS) ELSE: ?? */  
/*
    if(myController.getMasterFlag()){
        myController.serialCommunications();
        myController.filterMyOrders();
        myController.sendOrders2Slaves();     
    }else{
        //myController.I2CCommunications();   
    }   
*/
/** 4- PROCESS THE ORDERS */ 
   // myController.processMyOrders(); 
/** 5- ALL THE LOG WILL BE SHOWN */     
/** 6- UPDATE IMAGE VARIABLES OF STATE MACHINE  */
/** 7- PREPARE FOR ANOTHER LOOP  */   
    delay(2500);        
}

/*
*------------------------------------------------------------------------------------------------
*  FUNCTIONS INTERRUPT ROUTINES
*------------------------------------------------------------------------------------------------
*/
/*
// Serial interruption
void serialEvent(){
  serialError =  mySerial.mySerialEvent();
  mySerial.flush();
  if(serialError){
    mySerial.error("\n\n\n ---> Error: exceed Serial buffer size \n\n");
    mySerial.flush();
  }  
}
*/

void receiveEvent(int nBytes){
  myI2C.receiveRoutine(nBytes);
  myI2C.flush();
}

void requestEvent(){
  myI2C.requestRoutine();
}



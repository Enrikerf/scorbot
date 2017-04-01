/** 
* 
*  
*/

#include "MyI2C.h"

MyI2C::MyI2C(bool masterFlag, int slaveAddress){
    this->masterFlag = masterFlag;
    this->slaveAddress = slaveAddress;
    this->inputSentence       = "";
    this->sentenceCompleteFlag = false;
    this->endOfSentence = "\n";
    this->inputSentenceMaxLength = 200; //TODO: should be a param
    this->i2cBufferSize = 32;
}

void MyI2C::init(){
    // Begin Wire Comunication
    if(this->masterFlag){
        Wire.begin();  
    }else{
        Wire.begin(this->slaveAddress); 
    }
}

bool MyI2C::getSentenceCompleteFlag(){
    return this->sentenceCompleteFlag;
}

string MyI2C::getSentence(){
    return this->inputSentence;
}

void MyI2C::init(int slaveAddress){
    // Begin Wire Comunication
    this->slaveAddress = slaveAddress;
    if(this->masterFlag){
        Wire.begin();  
    }else{
        Wire.begin(this->slaveAddress); 
    }
}

void MyI2C::receiveRoutine(int nBytes){
	//Serial.print("MyI2C said-> New I2c Event, Number of bytes:");Serial.println(nBytes);    
    char inChar;
    char beginChar = Wire.read(); // is &
	while (Wire.available()) {		
		char inChar = Wire.read();
		if (inChar == '\n'){	
            this->sentenceCompleteFlag=true;
		}
		else{
		    this->inputSentence += inChar; 
            //Serial.print("char:");Serial.println(inChar);
		}   		
	}	
    if(!this->sentenceCompleteFlag){
        //Serial.println("MyI2C said-> Incomplete sentence; waiting for another stack.");
    }else{
       // Serial.print("MyI2C said-> Final Sentence:");Serial.println(this->inputSentence.c_str());
    }
    
}

void MyI2C::requestRoutine(){
    //Serial.print("MyI2C said-> respondo esta cant de bytes:");Serial.println(this->inputSentence.length());
    // Se tiene que responder con: NBuffers BufferX donde N son los buffers que quedan por dar
    string response = inputSentence + '\0';
    Wire.write(response.c_str(),response.length());
}

void MyI2C::flush(){
    this->inputSentence       = "";
    this->sentenceCompleteFlag = false;
    this->endOfSentence = "\n";
}
  

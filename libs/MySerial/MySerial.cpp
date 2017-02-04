/** 
* 
*  
*/

#include "MySerial.h"

MySerial::MySerial(){}

MySerial::MySerial(long newSerialBaud, Order newOrder, string newLogMode){	
	// Sentence variables	
		this->inputSentence       = "";        
		this->sentenceCompleteFlag  = false;        
		this->endOfSentence 		= '\n';
	// Serial communication variables	
		this->serialBaud          = newSerialBaud;  
		this->SERIAL_BUFFER_SIZE  = 63;
		this->logMode[0]=1;
		this->logMode[1]=1;
		this->logMode[2]=1;
		this->logMode[3]=1;
		this->logMode[4]=1;
		//setLogMode(this->order.recognizeArg(newLogMode),Order::ARG::ON);
}

void MySerial::init(){	 
    Serial.begin(this->serialBaud);
	while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
	}
}

void MySerial::init(long newSerialBaud){	
	serialBaud = newSerialBaud;
    Serial.begin(this->serialBaud);
}


// --------------------      SETS      --------------------

void MySerial::setLogMode(Order::ARG newLogMode, Order::ARG newStatus){
	this->debug( CR "MySerial said-> Mode to change:%d | new Status: %d " CR ,newLogMode,newStatus);
	int arrayPositionOfThisMode = getArrayPositionOfThisMode(newLogMode);
	if(newStatus == Order::ARG::ON){
		this->logMode[arrayPositionOfThisMode] = true;
	}else{
		this->logMode[arrayPositionOfThisMode] = false;
	}
		
}

// --------------------      GETS      --------------------

int MySerial::getArrayPositionOfThisMode(Order::ARG mode){
	int arrayPositionOfThisMode;
	switch(mode){
		case Order::ARG::NO_OUTPUT:
			arrayPositionOfThisMode = 0;
			break;	
		case Order::ARG::ERROR:	
			arrayPositionOfThisMode = 1;		
			break;	
		case Order::ARG::INFO:	
			arrayPositionOfThisMode = 2;		
			break;	
		case Order::ARG::DEBUG:		
			arrayPositionOfThisMode = 3;		
					break;	
		case Order::ARG::VERBOSE:	
			arrayPositionOfThisMode = 4;		
					break;					
		default:			
			this->error( CR "MySerial said-> setLogMode ARG newStatus unknown\n");
		break;
	}
	return arrayPositionOfThisMode;
}

string MySerial::getInputSentence(){
	return this->inputSentence;
};

bool MySerial::getSentenceCompleteFlag(){
	return sentenceCompleteFlag;
}



// --------------------      LOGS      --------------------


void MySerial::error(const char* msg, ...){
    if (shouldPrint(Order::ARG::ERROR)) {   
		print ("\n MySerial ERROR-> ",0);
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void MySerial::info(const char* msg, ...){
    if (shouldPrint(Order::ARG::INFO)) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void MySerial::debug(const char* msg, ...){
    if (shouldPrint(Order::ARG::DEBUG)) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void MySerial::verbose(const char* msg, ...){
    if (shouldPrint(Order::ARG::VERBOSE)) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

// --------------------      FUNCTIONALITIES     --------------------

bool MySerial::mySerialEvent(){
	info( CR "-----------------------------------------------------------");
	debug( CR "MySerial said-> New Serial Event, Number of bytes = %d",Serial.available());
	
	bool serialError = false;
	if(Serial.available()>=this->SERIAL_BUFFER_SIZE){
	    serialError = true;
	}
	while (Serial.available()) {		
		char inChar = (char)Serial.read();
		if (inChar == '\n'){				
            sentenceCompleteFlag = true;
			debug( CR "MySerial said-> Sentence complete (end by \ N) ");
		}
		else{
		    inputSentence += toupper(inChar); 
			//debug("\n MySerial said: char: %c",inChar);
		}   		
	}	
	debug( CR "MySerial said-> Final Sentence: %s",inputSentence.c_str());
	return serialError;
}

void MySerial::flush(){
	// Sentence variables
	inputSentence       = "";      		// Comprove if it is necesary
	sentenceCompleteFlag  = false;   		// whether the string is complete
}

// --------------------     PRIVATE METHODS      -------------------

/*!
* %s	replace with an string (char*)
* %c	replace with an character
* %d	replace with an integer value
* \%l	replace with an long value
* \%x	replace and convert integer value into hex
* \%X	like %x but combine with 0x123AB
* \%b	replace and convert integer value into binary
* \%B	like %x but combine with 0b10100011
* \%t	replace and convert boolean value into "t" or "f"
* \%T	like %t but convert into "true" or "false"
*/
void MySerial::print(const char *format, va_list args) {
    // loop through format string
    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
            if (*format == '\0') break;
            if (*format == '%') {
                Serial.print(*format);
                continue;
            }
            if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				Serial.print(s);
				continue;
			}
            if( *format == 'd' || *format == 'i') {
				Serial.print(va_arg( args, int ),DEC);
				continue;
			}
            if( *format == 'x' ) {
				Serial.print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'X' ) {
				Serial.print("0x");
				Serial.print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'b' ) {
				Serial.print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'B' ) {
				Serial.print("0b");
				Serial.print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'l' ) {
				Serial.print(va_arg( args, long ),DEC);
				continue;
			}

            if( *format == 'c' ) {
				Serial.print(va_arg( args, int ));
				continue;
			}
            if( *format == 't' ) {
				if (va_arg( args, int ) == 1) {
					Serial.print("T");
				}
				else {
					Serial.print("F");				
				}
				continue;
			}
            if( *format == 'T' ) {
				if (va_arg( args, int ) == 1) {
					Serial.print("true");
				}
				else {
					Serial.print("false");				
				}
				continue;
			}

        }
        Serial.print(*format);
    }
}
  
bool MySerial::shouldPrint(Order::ARG mode){
	bool result = false;
	int indexMode = getArrayPositionOfThisMode(mode);
	if(logMode[indexMode]) result = true;
	return result;
}




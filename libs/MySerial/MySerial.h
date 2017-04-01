#ifndef MySerial_h
#define MySerial_h
// include arduino's libraries
#include"Arduino.h"
// include extern libraries
#include <inttypes.h>
#include <stdarg.h>
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <ctype.h>
// include serf libraries


#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "pins_arduino.h"
extern "C" {
  #include <avr/io.h>
}

#define CR "\r\n"



using namespace std;

class MySerial {
	private:
		// Sentence variables
		string         inputSentence;        // String to hold incoming data
		boolean        sentenceCompleteFlag;   // whether the string is complete
		char           endOfSentence;		 // character to indicate end of Sentence
		// Serial communication variables	
		long           serialBaud;           // frecuency of serial communication
		short 		   SERIAL_BUFFER_SIZE;   // size of hardwareSerial buffer 64
		// Logger variables
		enum LOG_MODE{
			NOT_RECOGNIZED_CMD = -1,
			NO_OUTPUT 		= 0,
			INFO            = 1,
			DEBUG           = 2,
			ERROR           = 3,
			VERBOSE         = 4
		};
		bool logMode[5]; 	
		
	public:

		MySerial();
		MySerial(long newSerialBaud, string newLogMode);
		void init();
		void init(long newSerialBaud);	
		// --------------------      SETS      --------------------
		
		// --------------------      GETS      --------------------
		int getArrayPositionOfThisMode(MySerial::LOG_MODE mode);
		string getInputSentence();	
		bool getSentenceCompleteFlag();
		// --------------------      LOGS      --------------------
		void error(const char* msg, ...);
		void info(const char* msg, ...);
		void debug(const char* msg, ...);
		void verbose(const char* msg, ...);
		// --------------------      FUNCTIONALITIES     --------------------
		bool mySerialEvent();
		void flush();	

		~MySerial(){}; 
		
	private:		
		
		void print(const char *format, va_list args);
		bool shouldPrint(MySerial::LOG_MODE mode);

		
};


#endif

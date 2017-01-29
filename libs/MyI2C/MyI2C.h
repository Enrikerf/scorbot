#ifndef MyI2C_h
#define MyI2C_h
#include"Arduino.h"
#include <Wire.h>

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
//#include <sstream>
#include <vector>
//#include <iterator>
//#include <iostream>

using namespace std;

class MyI2C{
	
	private:
		bool masterFlag;
		int slaveAddress;
		// Sentence variables
		string inputSentence;
		boolean sentenceCompleteFlag;   // whether the string is complete
		char endOfSentence;		 // character to indicate end of Sentence
		short inputSentenceMaxLength;	
		short i2cBufferSize;
	public:
		MyI2C(bool masterFlag,int slaveAddress);	
		~MyI2C(){}; 
		void init();
		void init(int slaveAddress);
		void requestRoutine();
		void receiveRoutine(int nBytes);		
		void flush();
	private:
		
};
#endif

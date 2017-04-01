#ifndef MyCommunicator_h
#define MyCommunicator_h
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
#include <Array.h>
// include serf libraries
#include <Order.h>
#include <MySerial.h>

using namespace std;

class MyCommunicator {
	private:
		MySerial       * mySerial;
		string 		   sentence;
		vector<string> sentenceComponents; 	 // Hold sentence components
		char		   separatorOfComponents;	
		Order		   order;
		              	
	public:

		MyCommunicator(char newSeparatorOfComponents,MySerial *newMySerial);

		~MyCommunicator(){}; 

		string getSentence();
		vector<string> getSentenceComponents();
		Order getOrder();
		
		void setSentence(string newSentence);

		int parseSentenceByComponents(); // should be private
		bool extractOrderOfSentence();
		void flush();

		void logSentenceComponents();
		void logSentenceOrder();
			
	private:		
		int parseTool(string stringToParse, char token, vector<string> &stringParsed);
};


#endif

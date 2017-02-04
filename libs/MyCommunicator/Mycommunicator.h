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
		vector<Order>  orders;               // Hold the incoming orders		
	public:

		MyCommunicator(char newSeparatorOfComponents,MySerial *newMySerial);

		~MyCommunicator(){}; 

		vector<string> getSentenceComponents();

		vector<Order> getOrders();

		string getSentence();

		void setSentence(string newSentence);

		int parseSentenceByComponents();
	
		int	parseSentenceByOrders();

		void logSentenceComponents();

		void logSentenceOrders();

		void logSentenceOrders(vector<Order> orders2Plot);
			
	private:		
	
		/** STATUS:IC ||	PARSE THE INPUT SENTENCE BY ORDERS */
		int fillOrders(string cmdType, string cmd, vector<string> whos, vector<string> args);

		/** STATUS:IC ||	PARSE THE INPUT SENTENCE BY ORDERS */
		bool verifyWhos(vector<string> whos, vector<int> &whosInt);
			
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		int parseTool(string stringToParse, char token, vector<string> &stringParsed);
		
};


#endif

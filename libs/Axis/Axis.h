#ifndef Axis_h
#define Axis_h

#include"Arduino.h"
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

#include <MySerial.h>
#include <Order.h>

using namespace std;

class Axis{
	
	private:
		MySerial *mySerial;
		unsigned char id;
		unsigned char pwmPin;
		unsigned char dirPin;
		unsigned char brakePin;	
		unsigned char homePin;

		unsigned char pwmValue;
		unsigned char dirValue;
		unsigned char brakeValue;
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Axis(MySerial *newMySerial);	
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Axis(){};

		int processCmd( int newCmd, string args);

		unsigned char getId();
		void setId(unsigned char newId);

		unsigned char getPwmPin();
		void setPwmPin(string args);	

		unsigned char getDirPin();
		void setDirPin(string args);	

		unsigned char getBrakePin();
		void setBrakePin(string args);

		unsigned char getHomePin();
		void setHomePin(unsigned char newHomePin);
			
		void setPwmValue(string args);
		void setDirValue(string args);
		void setBrakeValue(string args);
		
		bool str2Int(string toConvert,int &converted);

};


#endif

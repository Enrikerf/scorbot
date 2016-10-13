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
		unsigned char encoderPhaseAPin;
		unsigned char encoderPhaseBPin;		
		
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Axis(MySerial *newMySerial);	
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Axis(){};

		void setId(unsigned char newId);		
		void setPwmPin(unsigned char newPwmPin);		
		void setDirPin(unsigned char newDirPin);		
		void setBrakePin(unsigned char newBrakePin);
		void setHomePin(unsigned char newHomePin);
		void setEncoderPhaseAPin(unsigned char newPhaseAPin);
		void setEncoderPhaseBPin(unsigned char newPhaseBPin);
				
		unsigned char getId();		
		unsigned char getPwmPin();		
		unsigned char getDirPin();		
		unsigned char getBrakePin();
		unsigned char getHomePin();
		unsigned char getEncoderPhaseAPin();
		unsigned char getEncoderPhaseBPin();

		/** STATUS:IC */
		int processOrder(Order newOrder);

		void brake(Order::ARG brakeMode);

		bool str2Int(string toConvert,int &converted);

};


#endif

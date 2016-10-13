#ifndef MyI2C_h
#define MyI2C_h
#include"Arduino.h"
#include <Wire.h>

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

#include <Order.h>
#include <MySerial.h>
using namespace std;

class MyI2C{
	
	private:
		vector<Order> orders;
		MySerial *mySerial;
	
	public:
		MyI2C(MySerial *newMySerial);	
		~MyI2C(){}; 
		void init();
		void sendOrders2Slaves(vector<Order> orders2Send);
	private:
	
};
#endif

#ifndef MyAxesController_h
#define MyAxesController_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

#include <Order.h>
#include <Axis.h>
#include <MySerial.h>
#include <MyI2C.h>

using namespace std;

class MyAxesController{
	private:
		MySerial *mySerial;
		MyI2C *myI2C;
		bool masterFlag;
		vector<Axis> axes;
		vector<Order> orders;
		vector<Order> orders2Slaves;
		
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		MyAxesController(MySerial *newMySerial,MyI2C *newMyI2C, bool newMasterFlag);	
		
		/** STATUS:IC  ||	CONSTRUCTOR SETTING AXES */
		MyAxesController(MySerial *newMySerial,MyI2C *newMyI2C, bool newMasterFlag, vector<int> axisId);
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~MyAxesController(){};
		
// -------------------- SETTERS GETTERS & PRINTS --------------------

		/** STATUS:IC  ||	set axis istances with id axisId */
		void setAxes( vector<int> axisId );

		bool getMasterFlag();

// --------------------     FUNCTIONALITIES      --------------------

		// Communications
		void serialCommunications();
		void I2CCommunications();
		void filterMyOrders();
		void sendOrders2Slaves();
		
		// ProcessOrders
		void processMyOrders();
		int  processMyOrder( Order order );
		void readStateMachine();
		void updateStateMachine();
		bool checkIfAxisIsMine(int who);


};
#endif

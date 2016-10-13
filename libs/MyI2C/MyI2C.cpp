/** 
* 
*  
*/

#include "MyI2C.h"

MyI2C::MyI2C(MySerial *newMySerial){
	this->mySerial = newMySerial;
}

void MyI2C::init(){
	Wire.begin();
}

void  MyI2C::sendOrders2Slaves(vector<Order> orders2Send){
	this->mySerial->logSentenceOrders(orders2Send);
}
	
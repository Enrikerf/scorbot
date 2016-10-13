/** 
* 
*  
*/

#include "MyAxesController.h"

MyAxesController::MyAxesController(MySerial *newMySerial,MyI2C *newMyI2C,bool newMasterFlag){
	masterFlag = newMasterFlag;
	//TODO: hay que ver si se juntan en una misma clase MyComm que herede de las dos
	this->mySerial = newMySerial;
	this->myI2C = newMyI2C;
}

MyAxesController::MyAxesController(MySerial *newMySerial,MyI2C *newMyI2C, bool newMasterFlag, vector<int> axisId){
	masterFlag = newMasterFlag;
	this->mySerial = newMySerial;
	this->myI2C = newMyI2C;
	Axis newAxis = Axis(this->mySerial);
	for (int i = 0; i < axisId.size() ; i++){
		newAxis.setId(axisId[i]);
		this->axes.push_back(newAxis);
	}
}

// -------------------- SETTERS GETTERS & PRINTS --------------------

void MyAxesController::setAxes( vector<int> axisId ){
	this->mySerial->info("Este arduino ha sido creado con los ejes:");
	Axis newAxis = Axis(this->mySerial);
	for (int i = 0; i < axisId.size() ; i++){
		this->mySerial->info("\t nuevo eje con ID:%d",axisId[i]);
		
		newAxis.setId(axisId[i]);
		this->axes.push_back(newAxis);
	}
		
}

bool MyAxesController::getMasterFlag(){
	return this->masterFlag;
}

// --------------------     FUNCTIONALITIES      --------------------

void MyAxesController::serialCommunications(){
	if(this->masterFlag){
		// check the serial port and process
		if(this->mySerial->getSentenceCompleteFlag()){            
			this->orders = this->mySerial->getOrders();    
			this->mySerial->logSentenceOrders();  
			this->mySerial->flush();
		};
	};  
}

void MyAxesController::sendOrders2Slaves(){
	if(this->orders2Slaves.size()>0){
		this->mySerial->debug(CR"Master Say: i am sending orders to my slaves"CR);		
		this->myI2C->sendOrders2Slaves(this->orders2Slaves);
		orders2Slaves.clear();
	};
}

void MyAxesController::I2CCommunications(){
	this->mySerial->debug(CR"Master Say: checking I2C recieved communications"CR);
}

void MyAxesController::processMyOrders(){
  int result;
  for(int nOrder=0; nOrder< this->orders.size(); nOrder++){
    switch( this->orders[nOrder].recognizeCmdType() ){    
      case Order::CMD_TYPE::AXES:  
		this->mySerial->debug(CR"MyAxesController said: i am proccesing a axes cmd");
		if(this->checkIfAxisIsMine(this->orders[nOrder].who)){
			axes[this->orders[nOrder].who].processOrder(this->orders[nOrder]);
		}else{
			this->mySerial->debug("that Axis doesnt belong to me; filterMyOrders is neccesary");
		}		
		break;
      case Order::CMD_TYPE::ARD:       
        result = this->processMyOrder(this->orders[0]);
		this->mySerial->debug(CR"MyAxesController said: i am proccesing a ard cmd");
        break;
      default:
        this->mySerial->error(CR"MyAxesController said: Cmd Type no válido");
        break;
    }  
  }
  // TODO: habría que hacer un flush con más cuidado
  this->orders.clear();

}

int MyAxesController::processMyOrder(Order newOrder){
	int resultOfProcessedOrder = -1; // error by default
	this->mySerial->debug(CR"MyAxesController said: mi cmd es:%s",newOrder.cmd.c_str());
	switch(newOrder.recognizeCmd()){
		case Order::CMD::LOG_MODE:
			this->mySerial->setLogMode(newOrder.vectorArgs[0],newOrder.vectorArgs[1]);
			break;		
		default:
			this->mySerial->debug(CR"MyAxesController: Comando Arduino desconocido");
			resultOfProcessedOrder = -1;
			break;
	}
	return resultOfProcessedOrder;
}

void MyAxesController::readStateMachine(){
	this->mySerial->debug(CR"Machine Pin state read");
}

void MyAxesController::updateStateMachine(){
	this->mySerial->debug(CR"Machine Pin state update");
}

void MyAxesController::filterMyOrders(){ 	
	
	for(int nOrder=0; nOrder< this->orders.size(); nOrder++){
		if( !this->checkIfAxisIsMine(this->orders[nOrder].who) ){
			this->mySerial->debug("Master Say: axis[%d] is not mine:",this->orders[nOrder].who);
			this->orders2Slaves.push_back(orders[nOrder]);
			this->orders.erase(nOrder);
		}
	}
	
	
}

bool MyAxesController::checkIfAxisIsMine(int who){
	bool isMine = false;
	for (int i = 0; i < axes.size() ; i++){
		if(who == axes[i].getId() || who == -1) 
			isMine = true;
	}
	return isMine;
}






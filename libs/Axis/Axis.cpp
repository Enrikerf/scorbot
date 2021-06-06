/** 
* 
*  
*/

#include "Axis.h"


Axis::Axis(MySerial *newMySerial){
	this->id = -1;
	this->pwmPin = -1;
	this->dirPin = -1;
	this->brakePin = -1;
	this->homePin = -1;
	this->pwmValue = 0;
	this->dirValue = 0;
	this->brakeValue = 0;
	this->mySerial = newMySerial;
	
}

int Axis::processCmd(int newCmd , string args){
	
	int resultOfProcessedOrder = -1; // error by default

	this->mySerial->debug(CR"AXIS[%d]said-> Doing CMD: %d|with arguments:",this->id,newCmd);
	Serial.println(args.c_str());

	switch(newCmd){
		case Order::CMD_AXES::SET_PWM_PIN:
			this->setPwmPin(args);
			resultOfProcessedOrder = 1;
			break;	
		case Order::CMD_AXES::SET_PWM:
			this->setPwmValue(args);
			resultOfProcessedOrder = 1;
			break;
		case Order::CMD_AXES::SET_DIR_PIN:
			this->setDirPin(args);
			resultOfProcessedOrder = 1;
			break;	
		case Order::CMD_AXES::SET_DIR:
			this->setDirValue(args);
			resultOfProcessedOrder = 1;
			break;
		case Order::CMD_AXES::SET_BRAKE_PIN:
			this->setBrakePin(args);
			resultOfProcessedOrder = 1;
			break;	
		case Order::CMD_AXES::SET_BRAKE:
			this->setBrakeValue(args);
			resultOfProcessedOrder = 1;
			break;
		default:		
			this->mySerial->error(CR"AXIS[%d]said-> Comando desconocido:",this->id);			
			resultOfProcessedOrder = -1;
			break;
	}
	return resultOfProcessedOrder;
}

void Axis::setId(unsigned char newId){
	this->id = newId;
}

void Axis::setPwmPin(string args){
	int newPwmPin;
	bool validArg = str2Int(args,newPwmPin);
	if(validArg){
		//TODO: check if it is a valid pin and unused
		if(this->pwmPin != -1){
			// for safety reason the last one pin as a pwm pin will set as a input
			//pinMode(this->pwmPin,INPUT);
		};
		this->pwmPin = newPwmPin;
		//pinMode(this->pwmPin, OUTPUT);
	}
}	

void Axis::setDirPin(string args){
	int newDirPin;
	bool validArg = str2Int(args,newDirPin);
	if(validArg){
		//TODO: check if it is a valid pin and unused
		if(this->dirPin != -1){
			// for safety reason the last one pin as a dir pin will set as a input
			pinMode(this->dirPin,INPUT);
		};
		this->dirPin = newDirPin;
		pinMode(this->dirPin, OUTPUT);
	}
}	

void Axis::setBrakePin(string args){
	int newBrakePin;
	bool validArg = str2Int(args,newBrakePin);
	if(validArg){
		//TODO: check if it is a valid pin and unused
		if(this->brakePin != -1){
			// for safety reason the last one pin as a brake pin will set as a input
			pinMode(this->brakePin,INPUT);
		};
		this->brakePin = newBrakePin;
		pinMode(this->brakePin, OUTPUT);
	}
}

void Axis::setHomePin(unsigned char newHomePin){
	this->homePin = newHomePin;
}

void Axis::setPwmValue(string args){
	int newPwmValue;
	bool validArg = str2Int(args,newPwmValue);
	if(validArg && this->pwmPin != -1){
		analogWrite(this->pwmPin, newPwmValue);	
	}
}

void Axis::setDirValue(string args){
	int newDirValue;
	bool validArg = str2Int(args,newDirValue);
	if(validArg && this->dirPin != -1){
		if(newDirValue == 1){
			digitalWrite(this->dirPin, HIGH);
		}
		else{
			digitalWrite(this->dirPin,LOW);
		}		
	}
}

void Axis::setBrakeValue(string args){
	int newBrakeValue;
	bool validArg = str2Int(args,newBrakeValue);
	if(validArg && this->brakePin != -1){
		if(newBrakeValue == 1){
			digitalWrite(this->brakePin, HIGH);
		}
		else{
			digitalWrite(this->brakePin,LOW);
		}		
	}
	 
}



/*
void Axis::brake(Order::ARG brakeMode){
	
	if(brakeMode == Order::ARG::ON){
		digitalWrite(this->brakePin,HIGH);
		this->mySerial->debug(CR"AXIS[%d]said-> brake ON ",this->id);
	}else{		
		digitalWrite(this->brakePin,LOW);
		this->mySerial->debug(CR"AXIS[%d]said-> brake OFF ",this->id);
	}
}
*/



unsigned char Axis::getId(){
	return this->id;
}

unsigned char Axis::getPwmPin(){
	return this->pwmPin;
}

unsigned char Axis::getDirPin(){
	return this->dirPin;
}

unsigned char Axis::getBrakePin(){
	this->brakePin;
}

unsigned char Axis::getHomePin(){
	return this->homePin;
}

bool Axis::str2Int(string toConvert,int &converted){
	
	bool areValid = false;
	char *end;	
	converted  = strtol(toConvert.c_str(),&end,10);
	if (!*end){
		areValid = true;
	}
	else{
		return areValid = false;
	}		
	
	return areValid;
}
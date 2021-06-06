/** 
* 
*  
*/

#include "Order.h"

/** Default constructor*/
Order::Order(){
	this->cmdType = -1;
	this->cmd = -1;	
}

bool Order::setCmdType(string sNewCmdType){
	bool isSet = false;
	int newCmdType = atoi( sNewCmdType.c_str());
	isSet = this->recognizeCmdType(newCmdType);
	if(isSet){
		this->cmdType = newCmdType;
	};
	return isSet;
}

bool Order::setCmd(string sNewCmdType,string sNewCmd){
	bool isSet = false;
	int newCmdType = atoi(sNewCmdType.c_str());
	int newCmd = atoi(sNewCmd.c_str());
	isSet = this->recognizeCmd(newCmdType,newCmd);
	if(isSet){
		this->cmd = newCmd;
	}else{
		Serial.print("no setted cmd:");Serial.println(newCmdType);Serial.println(newCmd);
	}
	return isSet;
}

bool Order::setWhos(string sNewWhos){
	bool isSet = false;
	isSet = this->extractWhos(sNewWhos);
	return isSet;
}

bool Order::setArgs(vector<string> newArgs){
	bool isSet = false;
	// sólo se pueden establecer los argumentos si la orden instanciada ya tiene los whos
	if(this->whos.size()>0){
		if(this->whos.size()==newArgs.size()){
			isSet = true;
			//Serial.println("setted args");
			//this->args = newArgs;
			for(int i = 0;i<newArgs.size();i++){
				this->args.push_back(newArgs[i].c_str());
				//Serial.print("setted arg:");Serial.println(this->args[i].c_str());
			}
		}
		else{
			Serial.println("diff tam:");
		}
	}
	else{
		Serial.println("no whos");
	}
	return isSet;
}

void Order::clear(){
	this->cmdType = -1;
	this->cmd = -1;
	this->whos.clear();	
	this->args.clear();	
}

bool Order::recognizeCmdType(int cmdType){
	bool recognized = false;
	if(cmdType>=0 && cmdType < Order::CMD_TYPE::sizeOff_CMD_TYPE){	
		recognized = true;
	}
	return recognized;
}

bool Order::recognizeCmd(int cmdType, int cmd){
	bool recognized = false;
	if(cmd>=0){
		switch(cmdType){
			case Order::CMD_TYPE::ARD:
				if(cmd>=0 && cmd < Order::CMD_ARD::sizeOff_CMD_ARD){	
					recognized = true;
				}
				break;
			case Order::CMD_TYPE::AXES:
				if(cmd>=0 && cmd < Order::CMD_AXES::sizeOff_CMD_AXES){	
					recognized = true;
				}
				break;
			case Order::CMD_TYPE::LOG:
				if(cmd>=0 && cmd < Order::CMD_LOG::sizeOff_CMD_LOG){	
					recognized = true;
				}
				break;
			default:
				break;
		}
	}
	return recognized;	
}

bool Order::extractWhos(string sWhos){
	//TODO: no hay ninguna comprobación de los whos
	bool isSet =true;
	vector<string> vsWhos;
	parseTool(sWhos,',',vsWhos);
	for (int i=0; i<vsWhos.size();i++){		
		this->whos.push_back(atoi(vsWhos[i].c_str()));
		//Serial.print("setted who:");Serial.println(this->whos[i]);
	}	
	return isSet;
}


int Order::parseTool(string stringToParse, char token, vector<string> &stringParsed){
	int numberOfParts = 0; 
	string part;
	stringstream ssStringToParse(stringToParse);		
	while(getline(ssStringToParse,part,token) && part.size() > 0){
		stringParsed.push_back(part);
		numberOfParts++;		
	}   
	return numberOfParts;
}

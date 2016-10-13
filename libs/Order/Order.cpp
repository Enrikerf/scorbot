/** 
* 
*  
*/

#include "Order.h"

/** Default constructor*/
Order::Order(){
	this->cmdType = "";
	this->cmd = "";
	this->who = -1;		
	this->args = "";
}

void Order::setVectorArgs(vector<string> parsedArgs){
	
	for(int nArg=0; nArg<parsedArgs.size();nArg++){
		vectorArgs.push_back(recognizeArg(parsedArgs[nArg]));
		Serial.print("\n Class Order say-> parsedArg:");
		Serial.print(parsedArgs[nArg].c_str());
		Serial.print("|> Equivale a:");
		Serial.print(recognizeArg(parsedArgs[nArg]));
	}	
}

Order::CMD_TYPE Order::recognizeCmdType(string CmdType){
	
	Order::CMD_TYPE recognizedCmdType;
	if(!strcmp(CmdType.c_str(),"AXES")){	
		recognizedCmdType = AXES;
	}else if(!strcmp(CmdType.c_str(),"ARD")){
		recognizedCmdType = ARD;
	}else{	
		recognizedCmdType = NO_RECONIZED_CMD_TYPE;
	} 
	return recognizedCmdType;
	
}

Order::CMD_TYPE Order::recognizeCmdType(){
	
	Order::CMD_TYPE recognizedCmdType = this->recognizeCmdType(this->cmdType);
	return recognizedCmdType;
	
}

Order::CMD Order::recognizeCmd(string Cmd){
	
	Order::CMD recognizedCmd;
	if(!strcmp(Cmd.c_str(),"BRAKE")){	
		recognizedCmd = BRAKE;
	}else if(!strcmp(cmd.c_str(),"LOG_MODE")){	
		recognizedCmd = LOG_MODE;
	}else if(!strcmp(cmd.c_str(),"SET_BRAKE_PIN")){	
		recognizedCmd = SET_BRAKE_PIN;
	}else{	
		recognizedCmd = NO_RECONIZED_CMD;
	} 
	return recognizedCmd;
	
}

Order::CMD Order::recognizeCmd(){	
	Order::CMD recognizedCmd = this->recognizeCmd(this->cmd);
	return recognizedCmd;
	
}

Order::ARG Order::recognizeArg(string arg){
		
	Order::ARG recognizedArg;
	if(!strcmp(arg.c_str(),"ALL")){	
		recognizedArg = ALL;
	}else if(!strcmp(arg.c_str(),"ON")){
		recognizedArg = ON;
	}else if(!strcmp(arg.c_str(),"OFF")){
		recognizedArg = OFF;
	}else if(!strcmp(arg.c_str(),"NO_OUTPUT")){	
		recognizedArg = NO_OUTPUT;
	}else if(!strcmp(arg.c_str(),"ERROR")){
		recognizedArg = ERROR;
	}else if(!strcmp(arg.c_str(),"INFO")){
		recognizedArg = INFO;
	}else if(!strcmp(arg.c_str(),"DEBUG")){
		recognizedArg = DEBUG;
	}else if(!strcmp(arg.c_str(),"VERBOSE")){
		recognizedArg = VERBOSE;
	}else{		
		recognizedArg = NO_RECONIZED_ARG;
	} 
	return recognizedArg;
	
	
}

Order::ARG Order::recognizeArg(){
	//se debe devolver un array de ARG
	return this->recognizeArg(this->args);	
}

void Order::clear(){
	this->cmdType = "";
	this->cmd = "";
	this->who = -1;		
	this->args = "";
	this->vectorArgs.clear();
}







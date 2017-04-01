/** 
* 
*  
*/

#include "MyCommunicator.h"

MyCommunicator::MyCommunicator(char newSeparatorOfComponents, MySerial *newMySerial){
	this->separatorOfComponents = newSeparatorOfComponents;
	this->mySerial = mySerial;
}


// --------------------      GETS      --------------------


vector<string>  MyCommunicator::getSentenceComponents(){
	return this->sentenceComponents;
}

Order MyCommunicator::getOrder(){	
	return this->order;
}

string MyCommunicator::getSentence(){
	return this->sentence;
};


// --------------------      SETS      --------------------


void MyCommunicator::setSentence(string newSentence){
	this->mySerial->debug(CR"------\n MyComm said--> nueva sentencia: %s"CR,newSentence.c_str());
	this->sentence = newSentence;
}


// --------------------      FUNCTIONALITIES     --------------------


int MyCommunicator::parseSentenceByComponents(){
	int numberOfSentenceComponents = parseTool(this->sentence,this->separatorOfComponents,this->sentenceComponents);
	return numberOfSentenceComponents;
};

bool MyCommunicator::extractOrderOfSentence(){
	
	bool isSet = false;	
	parseSentenceByComponents();
	
	if(this->sentenceComponents.size()>=4 ){
		/** Sentence are defined as: "cmdType cmd whos args"
		 Where whos is at least -1(none who)
		 and is set at least 1 argument
		*/
		vector <string> components (this->sentenceComponents);
		string cmdType = components[0];
		string cmd = components[1];
		string whos = components[2];
		components.erase (components.begin(),components.begin()+3);
		vector <string> args (components);
		// try to set the components to a order if its valid
		bool validCmdType = this->order.setCmdType(cmdType);
		bool validCmd     = this->order.setCmd(cmdType,cmd);
		bool validWhos    = this->order.setWhos(whos);
		bool validArgs 	  = this->order.setArgs(args);
		if( !validCmdType || !validCmd  || !validWhos || !validArgs){
			this->mySerial->debug(CR "MyComm said-->Sentencia Invalida:%d %d %d %d %d ",sentenceComponents.size(),validCmdType,validCmd,validWhos,validArgs);
		}
		else{
			this->mySerial->debug(CR "MyComm said-->Orden valida");
			isSet =true;
		}
	}else{
		this->mySerial->debug(CR "MyComm said-->Sentencia invalida no hay al menos 4 componentes");
	}


	return isSet;
};

void MyCommunicator::flush(){

    this->sentence       = "";          
    this->sentenceComponents.clear();
    this->order.clear(); 
}
// --------------------      LOGS      --------------------

void MyCommunicator::logSentenceComponents(){
	this->mySerial->debug(CR "MyComm said->  Number of components:%d",this->sentenceComponents.size());
	for (int i=0; i<this->sentenceComponents.size();i++){
		Serial.println(this->sentenceComponents[i].c_str());
		this->mySerial->debug( CR  "MyComm said-> Component [%d]: %s " CR ,i,this->sentenceComponents[i].c_str());
	}
  
}

void MyCommunicator::logSentenceOrder(){
	
	this->mySerial->debug(CR "MyComm said--> My actual order is:");
	this->mySerial->debug(CR "\t order cmdType:%d",this->order.cmdType);
	this->mySerial->debug(CR "\t cmd:%d"   ,this->order.cmd);
	this->mySerial->debug(CR ">%d Destinatarios",this->order.whos.size());
	this->mySerial->debug(CR ">%d argumentos",this->order.args.size());

	for(int i = 0;i<this->order.whos.size();i++){
		Serial.print("\t to/arg:");
		Serial.print(this->order.whos[i]);
		Serial.print("/");
		Serial.println(this->order.args[i].c_str());
	}		
}


// --------------------     PRIVATE METHODS      --------------------

int MyCommunicator::parseTool(string stringToParse, char token, vector<string> &stringParsed){
	int numberOfParts = 0; 
	string part;
	stringstream ssStringToParse(stringToParse);		
	while(getline(ssStringToParse,part,token) && part.size() > 0){
		stringParsed.push_back(part);
		numberOfParts++;		
	}   
	return numberOfParts;
}



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

vector<Order> MyCommunicator::getOrders(){	
	return this->orders;
}

string MyCommunicator::getSentence(){
	return this->sentence;
};


// --------------------      SETS      --------------------


void MyCommunicator::setSentence(string newSentence){
	this->mySerial->debug(CR"MyComm said--> %s"CR,newSentence.c_str());
	this->sentence = newSentence;
}


// --------------------      FUNCTIONALITIES     --------------------


int MyCommunicator::parseSentenceByComponents(){
	int numberOfSentenceComponents = parseTool(this->sentence,this->separatorOfComponents,this->sentenceComponents);
	return numberOfSentenceComponents;
};

int MyCommunicator::parseSentenceByOrders(){
	
	int toReturn;
	string cmdType;
	vector<string> whos;
	string cmd;
	vector<string> args;	
	
	// se divide la Sentence por components
	parseSentenceByComponents();
	
	// primero se coge el tipo de comando
	cmdType = sentenceComponents[0];
	
	// Segundo se coge el comando (Depurar cmd no es necesario). La clase axis sabrá si es correcto	
	cmd = sentenceComponents[1];
	
	// Depurar los demás sentenceComponents... 	
	for (int i=2; i<sentenceComponents.size();i++){
		// si el comando es de clase axes el primer args son los whos
		if(!strcmp(cmdType.c_str(),"AXES") && i == 2){ 
			// Depurar sentenceComponents[2] if == all --> 
			if(!strcmp(sentenceComponents[i].c_str(),"ALL")){		
				sentenceComponents[i] = "0,1,2,3,4,5";
			};
			// TODO: habría que verificar que son números
			this->parseTool(sentenceComponents[i],',',whos);
		}else{
			args.push_back(sentenceComponents[i]);
		}					
	}	
	
	toReturn = this->fillOrders(cmdType,cmd,whos,args);

	return toReturn;
};


// --------------------      LOGS      --------------------

void MySerial::logSentenceComponents(){
	this->mySerial->debug( CR "MySerial said->  Number of components:%d \n",this->sentenceComponents.size());
	for (int i=0; i<this->sentenceComponents.size();i++){
		this->mySerial->debug( CR  "MySerial said-> Component [%d]: %s " CR ,i,this->sentenceComponents[i].c_str());
	}
  
}


void MySerial::logSentenceOrders(){
	this->mySerial->debug("\n\n MySerial said: Number of orders:%d",this->orders.size());
	for (int i=0; i<this->orders.size();i++){
		this->mySerial->debug("\n order [%d]:"  CR ,i);
		this->mySerial->debug("\t cmd Type: %s"  CR ,this->orders[i].cmdType.c_str());		
		this->mySerial->debug("\t cmd: %s"  CR ,this->orders[i].cmd.c_str());
		this->mySerial->debug("\t who: %d"  CR ,this->orders[i].who);		
		this->mySerial->debug("\t vargs: %s "  CR ,this->orders[i].args.c_str());
		for (int j=0; j<this->orders[i].vectorArgs.size();j++){
			this->mySerial->debug("\t\t arg[%d]: %d \n",j,orders[i].vectorArgs[j]);
		}
	}  
}


void MySerial::logSentenceOrders(vector<Order> orders2Plot){
	this->mySerial->debug("\n\n MySerial said: Number of orders:%d",orders2Plot.size());
	for (int i=0; i<orders2Plot.size();i++){
		this->mySerial->debug("\n order [%d]:" CR ,i);
		this->mySerial->debug("\t cmd Type: %s" CR ,orders2Plot[i].cmdType.c_str());		
		this->mySerial->debug("\t cmd: %s" CR ,orders2Plot[i].cmd.c_str());
		this->mySerial->debug("\t who: %d" CR ,orders2Plot[i].who);		
		this->mySerial->debug("\t vargs: %s " CR ,orders2Plot[i].args.c_str());
		for (int j=0; j<orders2Plot[i].vectorArgs.size();j++){
			this->mySerial->debug("\t\t arg[%d]: %d \n",j,orders2Plot[i].vectorArgs[j]);
		}
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

int MyCommunicator::fillOrders(string cmdType, string cmd, vector<string> whos, vector<string> args){
	int toReturn = -1;
	vector<int> whosInt;	
	vector<string> parsedArgs;
	
	switch( this->order.recognizeCmdType(cmdType) ){		
		case Order::CMD_TYPE::AXES:		
			// verificar que los whos son numeros validos
			if(!this->verifyWhos(whos,whosInt)){
				this->mySerial->error( CR "MyCommunicator said-> Some who param is not a number or not valid");
				return toReturn;
			};
			// Verificar si hay el mismo numero args que de whos?
			if(whos.size() != args.size()){		
				this->mySerial->error( CR "MyCommunicator said-> Missing arguments in axes command: less args than axes ");
				return toReturn;
			};
			// Se rellena la variable orders de la clase.				
			for(int nOrder; nOrder<whos.size();nOrder++){
				this->order.cmdType = cmdType;
				this->order.cmd = cmd;
				this->order.who = whosInt[nOrder];					
				this->order.args = args[nOrder];
				// fill vector<ARG> vectorArgs in Order
				parseTool(this->order.args[nOrder],',',parsedArgs);
				this->order.setVectorArgs(parsedArgs);
				// push prepared order in vector and clear to fill another one
				this->orders.push_back(this->order);
				this->order.clear();
			}	
			toReturn = whos.size();
		break;
		case Order::CMD_TYPE::ARD:
			this->order.cmdType = cmdType;
			this->order.cmd = cmd;
			this->order.who = -1;					
			this->order.args = args[0];
			// fill vector<ARG> vectorArgs in Order
			parseTool(this->order.args,',',parsedArgs);
			this->order.setVectorArgs(parsedArgs);		
			
			this->orders.push_back(this->order);
			toReturn = orders.size();
		break;
		default:
			this->mySerial->error( CR "MyCommunicator said->: cmdType default fail");
			toReturn = -1;
		break;
	}		
		
	return toReturn;
}

bool MyCommunicator::verifyWhos(vector<string> whos,vector<int> &whosInt){
	
	bool areValid = false;
	char *end;
	for(int nOrder=0; nOrder<whos.size();nOrder++){
		whosInt[nOrder]  = strtol(whos[nOrder].c_str(),&end,10);
		if (!*end){
			this->mySerial->debug( CR "MyCommunicator said-> valid who = %d",whosInt[nOrder]);
			areValid = true;
		}
		else{
			this->mySerial->debug( CR "MyCommunicator said-> invalid who = %T",end);
			return areValid = false;
		}		
	}
	return areValid;
}



#ifndef Order_h
#define Order_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <Array.h>
using namespace std;

class Order{	
	public:

		enum CMD_TYPE {
			ARD             = 0,
			AXES            = 1,
			LOG             = 2,
			sizeOff_CMD_TYPE
			
		};

		enum CMD_ARD {
			NONE = 0,
			sizeOff_CMD_ARD
		};

		enum CMD_AXES{
			GET_BRAKE       = 0,
			GET_DIR         = 1,
			GET_PWM         = 2,
			SET_BRAKE       = 3,
			SET_DIR         = 4,
			SET_PWM         = 5,
			GET_BRAKE_PIN   = 6,
			GET_DIR_PIN     = 7,
			GET_PWM_PIN     = 8,
			SET_BRAKE_PIN   = 9,
			SET_DIR_PIN     = 10,
			SET_PWM_PIN     = 11,
			GET_SWITCH      = 12,
			SET_SWITCH_PIN  = 13,
			sizeOff_CMD_AXES
		};

		enum CMD_LOG{
			INFO            = 0,
			DEBUG           = 1,
			ERROR           = 2,
			VERBOSE         = 3,
			sizeOff_CMD_LOG
			
		};

		enum ARG{
			ON              = 0,
			OFF             = 1,
			sizeOff_ARG_LOG

		};

		int cmdType;
		int cmd;
		vector<int> whos;
		vector<string> args;


		
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Order();
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Order(){};

		bool setCmdType(string sNewCmdType);

		bool setCmd(string sNewCmdType,string sNewCmd);
		
		bool setWhos(string sNewWhos);

		bool setArgs(vector<string> newArgs);

		bool recognizeCmdType(int cmdType);

		bool recognizeCmd(int cmdType,int cmd);

		bool extractWhos(string whos);

		bool recognizeArgs(int cmd,int cmdType){};
		
		void clear();

	private:
		int parseTool(string stringToParse, char token, vector<string> &stringParsed);

};


#endif

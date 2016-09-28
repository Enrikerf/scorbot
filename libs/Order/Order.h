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

using namespace std;

class Order{	
	public:
	
		enum    CMD_TYPE {
			AXES=1,
			ARD,
			NO_RECONIZED_CMD_TYPE};
							
		enum    CMD {
			BRAKE=1,
			SET_BRAKE_PIN,
			LOG_MODE,			
			NO_RECONIZED_CMD=4};
			
		enum    ARG {
			ALL=1,
			ON,
			OFF,
			NO_OUTPUT,
			ERROR,
			INFO,
			DEBUG,
			VERBOSE,
			NO_RECONIZED_ARG};
		
		string cmdType;
		int    who;
		string cmd;
		string args;
		vector<ARG> vectorArgs;
		
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Order();
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Order(){};
		
		void setVectorArgs(vector<string> ParsedArgs);
		
		/** STATUS:IC || Recognize is a input string is a valid cmd type 	 
		*
		*  It is useful before set the cmdType variable; verify if it is valid before update or set the instance
		*/
		Order::CMD_TYPE recognizeCmdType(string Word);

		/** STATUS:IC || Pass a self string type to his enum value	 
		*
		*  It is useful to use the instance's variable cmdType inside a switch; pass string to enum
		*/
		Order::CMD_TYPE recognizeCmdType();
		
		/** STATUS:IC || Recognize is a input string is a valid cmd	 
		*
		*  It is useful before set the cmd variable; verify if it is valid before update or set the instance
		*/
		Order::CMD recognizeCmd(string Word);

		/** STATUS:IC || Pass a self string type to his enum value	 
		*
		*  It is useful to use the instance's variable cmd inside a switch; pass string to enum
		*/
		Order::CMD recognizeCmd();
		
		/** STATUS:IC ||	 */
		Order::ARG recognizeArg(string Word);
		
		/** STATUS:IC ||	 */
		Order::ARG recognizeArg();
		
		void clear();

	private:

};


#endif

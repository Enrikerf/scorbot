
/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

#ifndef config_h
#define config_h

#define FIRMWARE_VERSION "scorbotArduino Version 1.0.0 - 2016/09/11"

#include <Wire.h>

//#include <Order.h>
//#include <MySerial.h>
#include <MyI2C.h>
//#include <MyAxesController.h>

// Serial communication variables
char    token                 = ' ';              // token for separate arguments
int     serialBaud            = 9600; 

/**  GLOBAL VARIABLES ------------------------------------------------------------------------*/

bool          masterFlag    = false;
//vector<int>   axisId ={0,1,2};
int           slaveAddress = 4;

//Order         injectedOrder = Order();// hay que quitar la inyección de dependencia
//MySerial static     mySerial      = MySerial(serialBaud,token,injectedOrder,"DEBUG");
MyI2C    static     myI2C         = MyI2C(masterFlag,slaveAddress);
//MyAxesController     myController = MyAxesController(&mySerial,&myI2C,masterFlag,axisId);
bool          serialError  = false; 

#endif

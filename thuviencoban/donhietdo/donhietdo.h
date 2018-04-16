
#ifndef donhietdo_h
#define donhietdo_h

#include <Arduino.h>
#include <avr/interrupt.h>
#include "thuviennhietdo/thermistor.h"



// Nhập code vào đây

class DO_NHIET_DO
{
	public:
		
		 void begin();
		 void bat_tat_may_lanh();
	
};


extern DO_NHIET_DO Nhietdo;

#endif
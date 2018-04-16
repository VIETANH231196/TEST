/*
	Các hàm điều khiển và dừng động cơ
*/
#include <MBH.h>
#include "dongco.h"

const short int hang[6] = { 37, 36, 35, 34, 33, 32}; 
//							0_, 1_, 2_, 3_, 4_, 5_	
const short int cot[6] 	= { 7,	6,	42,	43,	44,	45};
//							_1,	_2, _3, _4, _5, _6

void DONG_CO::begin() // Cài đặt các chân động cơ
{
	for (int Pin = 0; Pin < 6; Pin++) 
	{
		pinMode(hang[Pin], OUTPUT);
		pinMode(cot[Pin], OUTPUT);
		digitalWrite(hang[Pin],LOW);
		digitalWrite(cot[Pin],LOW);
	}
}

void DONG_CO::quay_1_vong(unsigned char o_hang)
{
	//Serial.print("Động cơ bắt đầu quay: ");
	Serial.println(o_hang);
	// -------------------------------------
	// Tính toán số hàng và số cột			
	unsigned char pin_hang, pin_cot;		
	pin_hang = o_hang/10;					// Hàng chục của ô hàng là số pin của hàng
	pin_cot = o_hang%10 - 1;					// Hàng đơn vị của ô hàng là số pin của cột
	Serial.println(pin_hang);
	Serial.println(pin_cot);
	// -------------------------------------
	// Điều khiển động cơ tương ứng quay	
	digitalWrite(hang[pin_hang], HIGH);
	digitalWrite(cot[pin_cot], HIGH);
	//--------------------------------------
	// Chờ động cơ quay đủ 1 vòng thì xong
	delay(3000);
	/*int dem = 0;
	while(1)
	{
		int sensorValue = analogRead(A0);
		//float voltage = sensorValue * (5.0 / 1023.0);
		// print out the value you read:
		Serial.println(sensorValue);
		if(sensorValue==0)
		{
			dem ++ ;
		}
		else if (sensorValue!=0)
		{
			dem = 0;
		}
		if (dem==10) break;
	}
	dem = 0;*/
	//--------------------------------------
	// Dừng động cơ lại
	digitalWrite(hang[pin_hang], LOW);
	digitalWrite(cot[pin_cot], LOW);
	//Serial.println("Động cơ quay xong");
}


void DONG_CO::quay_1_vong_khong_cam_bien_roi(unsigned char o_hang)
{
	//Serial.print("Động cơ bắt đầu quay: ");
	Serial.println(o_hang);
	// -------------------------------------
	// Tính toán số hàng và số cột			
	unsigned char pin_hang, pin_cot;		
	pin_hang = o_hang/10;					// Hàng chục của ô hàng là số pin của hàng
	pin_cot = o_hang%10 - 1;					// Hàng đơn vị của ô hàng là số pin của cột
	Serial.println(pin_hang);
	Serial.println(pin_cot);
	// -------------------------------------
	// Điều khiển động cơ tương ứng quay	
	digitalWrite(hang[pin_hang], HIGH);
	digitalWrite(cot[pin_cot], HIGH);
	//--------------------------------------
	// Chờ động cơ quay đủ 1 vòng thì xong
	unsigned long thoi_gian_bat_dau_quay = millis();
    unsigned long thoi_gian_quay;
    
    while(1)
    {
       bat_diem_0();
       thoi_gian_quay=millis()-thoi_gian_bat_dau_quay;
       Serial.println(thoi_gian_quay);  
    
		if( thoi_gian_quay<155)
		{
		   digitalWrite(hang[pin_hang], LOW);
		   digitalWrite(cot[pin_cot], LOW);
		   //dong_co_ok = 0;
		   //Serial.println( dong_co_ok);
		   break;
		}

		 else if( thoi_gian_quay>160&& thoi_gian_quay<400)
		{
			digitalWrite(hang[pin_hang], HIGH);
			digitalWrite(cot[pin_cot], HIGH);
		 
		}
		
		else if( thoi_gian_quay>400&& thoi_gian_quay<1750)
		{
		  digitalWrite(hang[pin_hang], LOW);
		  digitalWrite(cot[pin_cot], LOW);
		  //dong_co_ok = 0;
		  //Serial.println( dong_co_ok);
		  break;
		}

		else if( thoi_gian_quay>1750&& thoi_gian_quay<2050) 
		{
		  digitalWrite(hang[pin_hang], LOW);
		  digitalWrite(cot[pin_cot], LOW);
		  //dong_co_ok = 1;
		  //Serial.println( dong_co_ok);
		  break;
		}

		  
		else if( thoi_gian_quay>2050) 
		{
		  digitalWrite(hang[pin_hang], LOW);
		  digitalWrite(cot[pin_cot], LOW);
		  //dong_co_ok = 0;
		  //Serial.println( dong_co_ok);
		  break;
		}
    }

		
}



 void DONG_CO::bat_diem_0()
{
	 int dem=0;
     unsigned long thoi_gian_bat_diem_0= millis();
     unsigned long thoi_gian_quay_bat_diem_0;
     while(1)
     {  
   
		 analogReference(INTERNAL1V1);
		 int sensorValue = analogRead(A0);
		  // float voltage = sensorValue * (5.0 / 1023.0);
		  // print out the value you read:
		 Serial.println(sensorValue);
		
		 if(sensorValue==0)dem ++ ;
	   
		 else if (sensorValue!=0)dem = 0;
		
		 if (dem==9)break;
		 thoi_gian_quay_bat_diem_0=millis()-thoi_gian_bat_diem_0;
		 if (thoi_gian_quay_bat_diem_0>2050) break;
 
     }
}


static DONG_CO Dongco;

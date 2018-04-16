

#include "donhietdo.h"
#include <bien_he_thong/bien_he_thong.h>

// Nhập code vào đây
#define NTC_PIN               A5

THERMISTOR thermistor(NTC_PIN,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor


 void DO_NHIET_DO::begin()
 {
    pinMode(4 , OUTPUT);
    pinMode(5 , OUTPUT);
 	
 }

void DO_NHIET_DO::bat_tat_may_lanh()
{
	value_tt_ML = 1;
	 if(value_tt_ML==1)
	 {
		 nhiet_do_hien_tai_cua_may = thermistor.read()/10+0.1*(thermistor.read()%100);   // Read temperature
		 if(nhiet_do_hien_tai_cua_may>=value_nhiet_do_cai_dat)///////BAT MAY LANH
		 {
		     digitalWrite(4, LOW);
		     digitalWrite(5 , LOW);
	   
	     }
	     else if(nhiet_do_hien_tai_cua_may<value_nhiet_do_cai_dat)  /// TAT MAY LANH
		 {
			 digitalWrite(4 , HIGH);
			 digitalWrite(5 , HIGH);
			
	     }
	 		  
	 }
	 if(value_tt_ML==0)  // tắt máy điều hòa
	 {
		 digitalWrite(4 , HIGH);
	     digitalWrite(5 , HIGH);
	 }
}
	
	
	
	
	
	
	
	
	
 /* void DO_NHIET_DO::ISR (TIMER1_OVF_vect) 
 { 
    //value_tt_ML=EEPROM.read(ADDR_TRANG_THAI_ML);
	//value_nhiet_do_cai_dat=EEPROM.read(ADDR_NHIET_DO_CAI_DAT);
	 if(value_tt_ML==1)
	 {
	     Serial.println("nhiet do");
	     Serial.println(value_nhiet_do_cai_dat);
	     Serial.println(value_trang_thai_led);
	     thoi_gian_bat_do_nhiet++;
	     if( thoi_gian_bat_do_nhiet>228)       ////// 228*0.262144s = 60s
	     {
			 thoi_gian_bat_do_nhiet=0;
			 nhiet_do_hien_tai_cua_may = thermistor.read()/10+0.1*(thermistor.read()%100);   // Read temperature
			 Serial.println( nhiet_do_hien_tai_cua_may);
			 if(nhiet_do_hien_tai_cua_may>=value_nhiet_do_cai_dat)///////BAT MAY LANH
			 {
				 digitalWrite(TEMP_PIN1 , LOW);
				 digitalWrite(TEMP_PIN2 , LOW);
			 }
			 else if(nhiet_do_hien_tai_cua_may<value_nhiet_do_cai_dat)/// TAT MAY LANH
			 { 
				 digitalWrite(TEMP_PIN1 , HIGH);
				 digitalWrite(TEMP_PIN2 , HIGH);
				
			 }
		 
			 thoi_gian_bat_do_nhiet=0;
	     }      
	  TCNT1 = 0;

	 }
	 if(value_tt_ML==0) // tắt máy điều hòa
	 {  
	     digitalWrite(TEMP_PIN1 , HIGH);
	     digitalWrite(TEMP_PIN2 , HIGH);
	 }
	 
 } */

static DO_NHIET_DO Nhietdo;
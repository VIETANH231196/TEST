/*
Thư viện thời gian thực RTC.h

*/


#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include <Wire.h>


class RTC	//I2C
{
	private:
	
		/* Địa chỉ của DS1307 */
		const byte DS1307 = 0x68;
		/* Số byte dữ liệu sẽ đọc từ DS1307 */
		const byte NumberOfFields = 7;
		/* khai báo các biến thời gian */
		
	public:
	
		int second, minute, hour, day, wday, month, year;
		
		void begin();
		
		void readDS1307();
		/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
		int bcd2dec(byte num);
		/* Chuyển từ Decimal sang BCD */
		int dec2bcd(byte num);
		
		void digitalClockDisplay();
 
		void printDigits(int digits);
 
		/* cài đặt thời gian cho DS1307 */
		void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr);
		
		
};

extern RTC Rtc;

#endif
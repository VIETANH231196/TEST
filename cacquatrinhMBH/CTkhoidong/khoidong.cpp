

#include <MBH.h>

void MAY_BAN_HANG::khoi_dong()
{
	if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
	{
		u8g.setColorIndex(255);     // white
	}
	else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) 
	{
		u8g.setColorIndex(3);         // max intensity
	}
	else if ( u8g.getMode() == U8G_MODE_BW ) 
	{
		u8g.setColorIndex(1);         // pixel on
	}
	else if ( u8g.getMode() == U8G_MODE_HICOLOR ) 
	{
		u8g.setHiColorByRGB(255,255,255);
	} 
	/*==================================================*/
	Serial.begin(115200);
		lcd_kd_may_36_ngan();
		for(char i=0; i<60; i++)
		{
			if((i%10==0)||(i%10==7)||(i%10==8)||(i%10==9))
				EEPROM.write(ADDR_LOI_DC[i], 2); delay(5); // Khóa các ô động cơ nằm ngoài vùng 36 ô chuẩn
		}
		// Đối với loại máy 36 ngăn
		delay(2900);
	// Kiểm tra lỗi SIM.
	EEPROM.write(2900, 0x87); delay(5);
	if(EEPROM.read(2900)!=0x87) // Kiểm tra ô nhớ số 2900
	{
		EEPROM_LOI = 0; // Lỗi
	}
	else
	{
		EEPROM_LOI = 1; // Không lỗi
	}
	Nhietdo.begin();
	Sim.Begin();
	Rtc.begin();
	Nv11.begin();
	Dongco.begin();
	lcd_check_loi_1();
	delay(3000);
	lcd_check_loi_2();
	delay(3000);
	lcd_check_loi_3();
	delay(3000);
	Sim_Gui_Server(0x61);
	
	pinMode (2, INPUT); // Đặt chân đọc cảm biến cửa là chân số 2
}
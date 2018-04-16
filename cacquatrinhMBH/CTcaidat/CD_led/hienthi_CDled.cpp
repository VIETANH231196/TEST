/*
	Hiển thị trong mục cài đặt bật tắt đèn led
*/

#include<MBH.h>

/**5*/	void MAY_BAN_HANG::lcd_cai_dat_led()
    {
      u8g.firstPage(); 
      do
      {
        u8g.setFont(u8g_font_unifont);
        u8g.setPrintPos(0, 13); 
        u8g.print("CAI DAT LED:");
		u8g.setPrintPos(50, 30); 
		 
		if( value_trang_thai_led==1)
		{
        u8g.print("ON");
		}
		else if( value_trang_thai_led==0)
		{
		u8g.print("OFF");
		}
        u8g.setPrintPos(0, 60); 
        u8g.print("LUU CAI DAT? E/C");
      }
      while(u8g.nextPage());
    }
/*
	Hiển thị LCD trong mục cài đặt máy lạnh
*/

#include <MBH.h>

/**8*/	void MAY_BAN_HANG::lcd_cai_dat_may_lanh()
    {
      u8g.firstPage(); 
      do
      {
        u8g.setFont(u8g_font_unifont);
		u8g.setPrintPos(0, 13); 
        u8g.print(">");
        u8g.setPrintPos(8, 13); 
        u8g.print("CD MAY LANH:");
		
	    if( value_tt_ML==1)
		{
        u8g.print("ON ");
		}
		else  if( value_tt_ML==0) 
		{
			u8g.print("OFF");
		}
		u8g.setPrintPos(8, 35);
		u8g.print("CD NHIET DO:");
		u8g.print(value_nhiet_do_cai_dat);
	    
		
		
		u8g.setPrintPos(0, 60); 
        u8g.print("LUU CAI DAT? E/C");
      }
      while(u8g.nextPage());
    }
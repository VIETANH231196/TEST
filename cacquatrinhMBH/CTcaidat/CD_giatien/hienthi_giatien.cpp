

#include <MBH.h>


/* 1-1: Cài đặt giá tiền ==========================*/
	void MAY_BAN_HANG::lcd_cai_dat_gia_tien()
	{
		
		char str_gia_tien[10], str_tu[10], str_den[10], str_gia[10];
		Str.str('G','I','A',' ','T','I','E','N', str_gia_tien[0]);
		Str.str('T','u',':', str_tu[0]);	
		Str.str('D','e','n',':', str_den[0]);	
		Str.str('G','i','a',':', str_gia[0]);			
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			switch(vi_tri_con_tro_lcd)
			{
				case 1: 
					u8g.setPrintPos(23, 30);
					u8g.print(">");
					break;
				case 2:
					u8g.setPrintPos(86, 30);
					u8g.print(">");
					break;
				case 3:
					u8g.setPrintPos(31, 50);
					u8g.print(">");
					break;
			}
			u8g.setPrintPos(0, 13);
			u8g.print(str_gia_tien);
			u8g.setPrintPos(0, 30); 
			u8g.print(str_tu);
			u8g.setPrintPos(30, 30);
			u8g.print(o_bat_dau);
			u8g.setPrintPos(55, 30); 
			u8g.print(str_den);
			u8g.setPrintPos(93, 30);
			u8g.print(o_ket_thuc);
			u8g.setPrintPos(0, 50);
			u8g.print(str_gia);
			u8g.setPrintPos(38, 50);
			u8g.print(gia_cai_dat);
		}
		while(u8g.nextPage());
	}
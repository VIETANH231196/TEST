/*
	Hiển thị màn hình LCD trong mục cài đặt số hàng
*/


#include <MBH.h>

/* 1-2: Cài đặt số hàng  ==========================*/
	void MAY_BAN_HANG::lcd_cai_dat_so_hang()
	{
		char str_so_hang[10], str_tu[10], str_den[10], str_SL[10];
		Str.str('S','O',' ','H','A','N','G', str_so_hang[0]);
		Str.str('T','u',':', str_tu[0]);	
		Str.str('D','e','n',':', str_den[0]);	
		Str.str('S','L',':', str_SL[0]);	
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
					u8g.setPrintPos(23, 50);
					u8g.print(">");
					break;
			}
			u8g.setPrintPos(0, 13);
			u8g.print(str_so_hang);
			u8g.setPrintPos(0, 30); 
			u8g.print(str_tu);
			u8g.setPrintPos(30, 30);
			u8g.print(o_bat_dau);
			u8g.setPrintPos(55, 30); 
			u8g.print(str_den);
			u8g.setPrintPos(93, 30);
			u8g.print(o_ket_thuc);
			u8g.setPrintPos(0, 50);
			u8g.print(str_SL);
			u8g.setPrintPos(30, 50);
			u8g.print(so_hang_cai_dat);
		}
		while(u8g.nextPage());
	}
	
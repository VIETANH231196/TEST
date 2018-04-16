/*
	Hiển thị trong mục cài đặt khoa ô hàng
*/

#include <MBH.h>

/* 1-3: Cài đặt ô hàng khóa =======================*/
	void MAY_BAN_HANG::lcd_cai_dat_khoa_o_hang()
	{
		char str_khoa_o_hang[16], str_tu[10], str_den[10], str_khoa[10], str_khong[10];
		Str.str('K','H','O','A',' ','O',' ','H','A','N','G', str_khoa_o_hang[0]);
		Str.str('T','u',':', str_tu[0]);	
		Str.str('D','e','n',':', str_den[0]);	
		Str.str('K','h','o','a',':','7', str_khoa[0]);	
		Str.str('K','h','o','n','g',':','9', str_khong[0]);
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
				case 3: break;
			}
			u8g.setPrintPos(0, 13);
			u8g.print(str_khoa_o_hang);
			u8g.setPrintPos(0, 30); 
			u8g.print(str_tu);
			u8g.setPrintPos(30, 30);
			u8g.print(o_bat_dau);
			u8g.setPrintPos(55, 30); 
			u8g.print(str_den);
			u8g.setPrintPos(93, 30);
			u8g.print(o_ket_thuc);
			if (vi_tri_con_tro_lcd==3) // Nếu con trỏ chuyển sang vị trí số 3 thì màn hình hiện thêm dòng sau:
			{
				u8g.setPrintPos(0, 63); 
				u8g.print(str_khoa);
				u8g.setPrintPos(64, 63);
				u8g.print(str_khong);
			}
		}
		while(u8g.nextPage());
	}

	
	

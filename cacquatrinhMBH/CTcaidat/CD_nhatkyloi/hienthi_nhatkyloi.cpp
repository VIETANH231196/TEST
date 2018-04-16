/*
	Hiển thị nhật ký lỗi trong mục cài đặt
*/

#include <MBH.h>

/* 2-2: Nhật ký lỗi ===============================*/
	void MAY_BAN_HANG::lcd_nhat_ky_loi()
	{
		char str_cd_nky_loi[32];
		char str_dc_loi[16];
		char str_xoa[8];
		Str.str('N','h','a','t',' ','k','y',' ','l','o','i', str_cd_nky_loi[0]);
		Str.str('D','o','n','g',' ','c','o',' ','l','o','i',':', str_dc_loi[0]);
		Str.str('X','o','a',':','9', str_xoa[0]);
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13);
			u8g.print(str_cd_nky_loi);
			switch(vi_tri_con_tro_lcd)
			{
				case 1:
				{
					u8g.setPrintPos(110, 30);
					u8g.print("<");
					break;
				}
				case 2: 
				{
					u8g.setPrintPos(110, 45);
					u8g.print("<");
					break;
				}
			}
			if(dong_1_lcd!=0) // Nếu dòng 1 có bản ghi thì in ra
			{
				u8g.setPrintPos(0, 30); 
				u8g.print(str_dc_loi);
				u8g.print(dong_1_lcd);
			}
			if(dong_2_lcd!=0)
			{
				u8g.setPrintPos(0, 45); 
				u8g.print(str_dc_loi);
				u8g.print(dong_2_lcd);
			}
			u8g.setPrintPos(85, 64); 
			u8g.print(str_xoa);
		}
		while(u8g.nextPage());
	}

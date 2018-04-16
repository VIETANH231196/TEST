/*
	Hiển thị màn hình LCD trong mục cài đặt thêm tiền trả lại
*/

#include <MBH.h>

/* 2-3: Thêm tiền trả lại =========================*/
	void MAY_BAN_HANG::lcd_them_tien_tra_lai()
	{
		char str_them_tien[16], str_dua_tien_vao[20], str_so_to_tien[16];
		Str.str('T','H','E','M',' ','T','I','E','N', str_them_tien[0]);
		Str.str('H','a','y',' ','d','u','a',' ','t','i','e','n',' ','v','a','o', str_dua_tien_vao[0]);
		Str.str('S','o',' ','t','o',' ','t','i','e','n',':',' ', str_so_to_tien[0]);
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13);
			u8g.print(str_them_tien);
			u8g.setPrintPos(0, 30);
			u8g.print(str_dua_tien_vao);			
			u8g.setPrintPos(0, 53); 
			u8g.print(str_so_to_tien);
			u8g.setPrintPos(30, 63); 
			u8g.print(so_to_tien_co_trong_bo_tra_lai);
		}
		while(u8g.nextPage());
	}

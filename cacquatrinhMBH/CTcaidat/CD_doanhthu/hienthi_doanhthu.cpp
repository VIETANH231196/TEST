/*
	Hiển thị trong mục cài đặt doanh thu
*/

#include <MBH.h>


// --------------------------------------------------
/* 2-1: Doanh thu =================================*/
	void MAY_BAN_HANG::lcd_xem_doanh_thu()
	{
		char dt[10], dt_ngay[10], dt_thang[10], dt_nam[10];
		Str.str('D','O','A','N','H',' ','T','H','U', dt[0]);
		Str.str('D','t',' ','n','g','a','y', dt_ngay[0]);
		Str.str('D','t',' ','t','h','a','n','g', dt_thang[0]);
		Str.str('D','t',' ','n','a','m', dt_nam[0]);
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13);
			u8g.print(dt);
			switch(vi_tri_con_tro_lcd)
			{
				case 1:
				{
					u8g.setPrintPos(110, 30); 
					u8g.print('<');
					break;
				}
				case 2:
				{
					u8g.setPrintPos(110, 45); 
					u8g.print('<');
					break;					
				}
				case 3:
				{
					u8g.setPrintPos(110, 60); 
					u8g.print('<');
					break;							
				}
			}
			u8g.setPrintPos(0, 30); 
			u8g.print(dt_ngay);
			u8g.setPrintPos(0, 45); 
			u8g.print(dt_thang);
			u8g.setPrintPos(0, 60); 
			u8g.print(dt_nam);
		}
		while(u8g.nextPage());
	}
	
	void MAY_BAN_HANG::lcd_doanh_thu_ngay(bool DL_hien_thi)
	{
		char k_du_lieu[20], tien_vao[10], dt[10], tien_ra[10];
		Str.str('D','o','a','n','h',' ','t','h','u', dt[0]);
		Str.str('T','i','e','n',' ','v','a','o', tien_vao[0]);
		Str.str('K','h','o','n','g',' ','c','o',' ','d','u',' ','l','i','e','u', k_du_lieu[0]);
		Str.str('T','i','e','n',' ','r','a', tien_ra[0]);
		switch(DL_hien_thi)
		{
			case 0:
			{
				u8g.firstPage();
				do
				{
					u8g.setFont(u8g_font_unifont);
					u8g.setPrintPos(0, 13);
					u8g.print(k_du_lieu);
				}
				while(u8g.nextPage());
				break;
			}
			case 1:
			{
				u8g.firstPage(); 
				do
				{
					u8g.setFont(u8g_font_unifont);
					u8g.setPrintPos(0, 13);
					u8g.print(nam_cua_o_nho);
					u8g.print("/");
					u8g.print(thang_cua_o_nho);
					u8g.print("/");
					u8g.print(ngay_cua_o_nho);
					
					u8g.setPrintPos(0, 30); 
					u8g.print(tien_vao);
					u8g.print(tien_vao_ngay);
					u8g.print("k");
					u8g.setPrintPos(0, 45); 
					u8g.print(dt);
					u8g.print(doanh_thu_ngay);
					u8g.print("k");
					u8g.setPrintPos(0, 60); 
					u8g.print(tien_ra);
					u8g.print(tien_ra_ngay);
					u8g.print("k");
				}
				while(u8g.nextPage());
				break;
			}
		}
	}
	
	void MAY_BAN_HANG::lcd_doanh_thu_thang(bool DL_hien_thi)
	{
		char k_du_lieu[20], tien_vao[10], dt[10], tien_ra[10];
		Str.str('D','o','a','n','h',' ','t','h','u', dt[0]);
		Str.str('T','i','e','n',' ','v','a','o', tien_vao[0]);
		Str.str('K','h','o','n','g',' ','c','o',' ','d','u',' ','l','i','e','u', k_du_lieu[0]);
		Str.str('T','i','e','n',' ','r','a', tien_ra[0]);		
		switch(DL_hien_thi)
		{
			case 0:
			{
				u8g.firstPage();
				do
				{
					u8g.setFont(u8g_font_unifont);
					u8g.setPrintPos(0, 13);
					u8g.print(k_du_lieu);
				}
				while(u8g.nextPage());
				break;
			}
			case 1:
			{
				u8g.firstPage(); 
				do
				{
					u8g.setFont(u8g_font_unifont);
					u8g.setPrintPos(0, 13);
					u8g.print(nam_cua_o_nho);
					u8g.print("/");
					u8g.print(thang_cua_o_nho);
					
					u8g.setPrintPos(0, 30); 
					u8g.print(tien_vao);
					u8g.print(tien_vao_thang);
					u8g.print("k");
					u8g.setPrintPos(0, 45); 
					u8g.print(dt);
					u8g.print(doanh_thu_thang);
					u8g.print("k");
					u8g.setPrintPos(0, 60); 
					u8g.print(tien_ra);
					u8g.print(tien_ra_thang);
					u8g.print("k");
				}
				while(u8g.nextPage());
				break;
			}
		}
	}
		
	void MAY_BAN_HANG::lcd_doanh_thu_nam(bool DL_hien_thi)
	{
		char k_du_lieu[20], tien_vao[10], dt[10], tien_ra[10];
		Str.str('D','o','a','n','h',' ','t','h','u', dt[0]);
		Str.str('T','i','e','n',' ','v','a','o', tien_vao[0]);
		Str.str('K','h','o','n','g',' ','c','o',' ','d','u',' ','l','i','e','u', k_du_lieu[0]);
		Str.str('T','i','e','n',' ','r','a', tien_ra[0]);		
		switch(DL_hien_thi)
		{
			case 0:
			{
				u8g.firstPage();
				do
				{
					u8g.setFont(u8g_font_unifont);
					u8g.setPrintPos(0, 13);
					u8g.print(k_du_lieu);
				}
				while(u8g.nextPage());
				break;
			}
			case 1:
			{
				u8g.firstPage(); 
				do
				{
					u8g.setFont(u8g_font_unifont);
					u8g.setPrintPos(0, 13);
					u8g.print(nam_cua_o_nho);
					
					u8g.setPrintPos(0, 30); 
					u8g.print(tien_vao);
					u8g.print(tien_vao_nam);
					u8g.print("k");
					u8g.setPrintPos(0, 45); 
					u8g.print(dt);
					u8g.print(doanh_thu_nam);
					u8g.print("k");
					u8g.setPrintPos(0, 60); 
					u8g.print(tien_ra);
					u8g.print(tien_ra_nam);
					u8g.print("k");
				}
				while(u8g.nextPage());
				break;
			}
		}
	}

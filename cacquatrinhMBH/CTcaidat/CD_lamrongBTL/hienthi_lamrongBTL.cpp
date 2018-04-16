
#include <MBH.h>


/* 3-1: Làm rỗng bộ trả lại =======================*/

	void MAY_BAN_HANG::lcd_lam_rong_bo_tra_lai_1()
	{
		char str_lam_rong[16], str_ban_co_muon_lam[20], str_rong_BTL[10], str_Y[5], str_N[5];
		Str.str('L','A','M',' ','R','O','N','G',' ','B','T','L', str_lam_rong[0]);
		Str.str('B','a','n',' ','c','o',' ','m','u','o','n',' ','l','a','m', str_ban_co_muon_lam[0]);	
		Str.str('r','o','n','g',' ','B','T','L','?', str_rong_BTL[0]);	
		Str.str('Y',':', str_Y[0]);
		Str.str('N',':', str_N[0]);		
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13);
			u8g.print(str_lam_rong);
			u8g.setPrintPos(0, 28); 
			u8g.print(str_ban_co_muon_lam);
			u8g.setPrintPos(0, 42); 
			u8g.print(str_rong_BTL);
			u8g.setPrintPos(0, 63); 
			u8g.print(str_Y);
			u8g.setPrintPos(100, 63); 
			u8g.print(str_N);
		}
		while(u8g.nextPage());
	}

	void MAY_BAN_HANG::lcd_lam_rong_bo_tra_lai_2()
	{
		char str_lam_rong[16], str_dang_lam_rong[20], str_xin_hay_doi[20];
		Str.str('L','A','M',' ','R','O','N','G',' ','B','T','L', str_lam_rong[0]);
		Str.str('D','a','n','g',' ','l','a','m',' ','r','o','n','g',' ','B','T','L', str_dang_lam_rong[0]);
		Str.str('X','i','n',' ','h','a','y',' ','d','o','i','!','!','!', str_xin_hay_doi[0]);		
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13);
			u8g.print(str_lam_rong);
			u8g.setPrintPos(0, 40); 
			u8g.print(str_dang_lam_rong);
			u8g.setPrintPos(0, 54); 
			u8g.print(str_xin_hay_doi);

		}
		while(u8g.nextPage());
	}

	void MAY_BAN_HANG::lcd_lam_rong_bo_tra_lai_xong()
	{
		char str_lam_rong[16], str_lam_rong_xong[20], str_nhan_cancel[25];
		Str.str('L','A','M',' ','R','O','N','G',' ','B','T','L', str_lam_rong[0]);
		Str.str('L','a','m',' ','r','o','n','g',' ','B','T','L',' ','x','o','n','g', str_lam_rong_xong[0]);
		Str.str('N','h','a','n',' ','#',' ','d','e',' ','t','h','o','a','t', str_nhan_cancel[0]);
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13);
			u8g.print(str_lam_rong);
			u8g.setPrintPos(0, 40); 
			u8g.print(str_lam_rong_xong);
			u8g.setPrintPos(0, 54); 
			u8g.print(str_nhan_cancel);
		}
		while(u8g.nextPage());
	}
/*
	Các hàm hiển thị màn hình LCD trong mục cài đặt
*/ 

#include <MBH.h>


// =======================================
// Các màn hình mục lục PASSWORD
/**0*/  void MAY_BAN_HANG::lcd_PASSWORD()
        {
			char nhap_PW[16], ky_tu[10];
			Str.str('N','H','A','P',' ','P','A','S','S','W','O','R','D', nhap_PW[0]);
			Str.str('*','*','*','*','*','*','*', ky_tu[0]);
			u8g.firstPage(); 
		    do
		    {
			 u8g.setFont(u8g_font_unifont);
             u8g.setPrintPos(11, 12); 
             u8g.print(nhap_PW);   
             u8g.setPrintPos(35, 40); 
			 u8g.print(ky_tu);
			}
			while(u8g.nextPage()); 
		}
		
/**0*/  void MAY_BAN_HANG::lcd_PASSWORD_hien_so()
        {
			char nhap_PW[16], ky_tu[10];
			Str.str('N','H','A','P',' ','P','A','S','S','W','O','R','D', nhap_PW[0]);
			Str.str('*','*','*','*','*','*','*', ky_tu[0]);
			u8g.firstPage(); 
		    do
		    {
				 u8g.setFont(u8g_font_unifont);
				 u8g.setPrintPos(11, 12); 
				 u8g.print(nhap_PW); 
				 if(password_chu_so==0)	
				 {		 
					 u8g.setPrintPos(35, 40); 
					 u8g.print( key);   
					 u8g.print("*****");	
				 }
				 if(password_chu_so==1)	
				 {		 
					 u8g.setPrintPos(35, 40);
					 u8g.print("*");
					 u8g.print( key);
					 u8g.print("****");			 
				 }
				 if(password_chu_so==2)	
				 {		 
					 u8g.setPrintPos(35, 40);
					 u8g.print("**");
					 u8g.print( key);
					 u8g.print("***");			 
				 }
				 if(password_chu_so==3)	
				 {		 
					 u8g.setPrintPos(35, 40);
					 u8g.print("***");
					 u8g.print( key);
					 u8g.print("**");			 
				 }
				 if(password_chu_so==4)	
				 {		 
					 u8g.setPrintPos(35, 40);
					 u8g.print("****");
					 u8g.print( key);
					 u8g.print("*");			 
				 }
				 if(password_chu_so==5)	
				 {		 
					 u8g.setPrintPos(35, 40);
					 u8g.print("*****");
					 u8g.print( key);
						 
				 }
			 
			}
			while(u8g.nextPage()); 
		}
						
/**0*/  void MAY_BAN_HANG::lcd_PASSWORD_sai()
        { 
			char sai_pw[20], nhap_lai[20];
			Str.str('S','A','I',' ','P','A','S','S','W','O','R','D', sai_pw[0]);
			Str.str('A','n',' ','#',' ','d','e',' ','n','h','a','p',' ','l','a','i', nhap_lai[0]);
		    u8g.firstPage(); 
		    do
		    {
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(13, 15); 
				u8g.print(sai_pw);
				u8g.setPrintPos(0, 40); 
				u8g.print(nhap_lai); 
			}
			while(u8g.nextPage()); 
		}

// =======================================
// Các màn hình mục lục cài đặt chung

/**1*/	void MAY_BAN_HANG::lcd_cai_dat_chung(char string_1[], char string_2[], char string_3[], char string_4[])
		{
			u8g.firstPage(); 
		    do
		    {
				u8g.setFont(u8g_font_unifont);
				switch(trang_cai_dat_duoc_lua_chon)
				{
					case 1:
						u8g.setDefaultForegroundColor(); 
					    u8g.drawBox(0, 4, 128, 12);
						u8g.setDefaultBackgroundColor();
						u8g.setPrintPos(3, 15); u8g.print(string_1);
						u8g.setDefaultForegroundColor(); 
						u8g.setPrintPos(3, 30); u8g.print(string_2);
						u8g.setPrintPos(3, 45); u8g.print(string_3);
						u8g.setPrintPos(3, 60); u8g.print(string_4);
						break;
					case 2:
						u8g.setDefaultForegroundColor(); 
						u8g.setPrintPos(3, 15); u8g.print(string_1);
						u8g.drawBox(0, 19, 128, 12);
						u8g.setDefaultBackgroundColor();
						u8g.setPrintPos(3, 30); u8g.print(string_2);
						u8g.setDefaultForegroundColor();
						u8g.setPrintPos(3, 45); u8g.print(string_3);
						u8g.setPrintPos(3, 60); u8g.print(string_4);					
						break;
					case 3:
						u8g.setDefaultForegroundColor(); 
						u8g.setPrintPos(3, 15); u8g.print(string_1);
						u8g.setPrintPos(3, 30); u8g.print(string_2);
						u8g.drawBox(0, 34, 128, 12);
						u8g.setDefaultBackgroundColor();						
						u8g.setPrintPos(3, 45); u8g.print(string_3);
						u8g.setDefaultForegroundColor();
						u8g.setPrintPos(3, 60); u8g.print(string_4);						
						break;
					case 4:
						u8g.setDefaultForegroundColor(); 
						u8g.setPrintPos(3, 15); u8g.print(string_1);
						u8g.setPrintPos(3, 30); u8g.print(string_2);
						u8g.setPrintPos(3, 45); u8g.print(string_3);
						u8g.drawBox(0, 49, 128, 12);	
						u8g.setDefaultBackgroundColor();
						u8g.setPrintPos(3, 60); u8g.print(string_4);
						u8g.setDefaultForegroundColor(); 
						break;
				}
			}
			while(u8g.nextPage()); 
		}
			
// -----------------------------------------------------------------------------------------------
// Màn hình sử dụng chung của các mục cài đặt:

	void MAY_BAN_HANG::lcd_xong()
	{
		char xong[10];
		Str.str('X','O','N','G',' ','!','!','!', xong[0]);
		u8g.firstPage(); 
		do
		{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(45, 37);
			u8g.print(xong);
		}
		while(u8g.nextPage());
	}
		
	
	
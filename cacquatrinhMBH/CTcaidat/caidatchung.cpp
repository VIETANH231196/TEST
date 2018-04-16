/*
	Các hàm sử dụng trong mục cài đặt
*/

#include <MBH.h>

void MAY_BAN_HANG::NHAP_PASSWORD()
    {    
		// quet_ban_phim();
		lcd_PASSWORD();
		password_ok=0;
		password_ok_admin=0;

		while(password_ok!=6||password_ok_admin!=6)
		{   
	        for( password_chu_so=0; password_chu_so<6; password_chu_so++)
		    {
				key = 0;
			    while(key==0)
					key = keypad.getKey(); // Quét bàn phím
				// lcd_PASSWORD();
			    if(key=='*')password_chu_so=6;
				else if(key=='#')NHAP_PASSWORD();
				else 
				{
			        key = key-0x30;
					password_nhap[password_chu_so]=key;
					lcd_PASSWORD_hien_so();
			    }
		    }
			for(password_chu_so=0; password_chu_so<6; password_chu_so++)
		    { 
				if(password_nhap[password_chu_so]==value_password_admin[password_chu_so]) password_ok_admin++;
			    else
				{
					password_ok_admin=0;
				}
			} 
			
			if(password_ok_admin!=6)
			{  
		        while(key!=0x23)
				{
					lcd_PASSWORD_sai();
					password_ok=0;
					password_ok_admin=0;
					key = 0;
					while(key==0)
						key = keypad.getKey(); // Quét bàn phím
					lcd_PASSWORD();
			    }
			}
		
			if(password_ok_admin==6)
			{    
				lua_chon_trang_cai_dat_chinh();
			}
		}
    }

void MAY_BAN_HANG::lua_chon_trang_cai_dat_chinh()
{	
	trang_muc_luc_cai_dat = 1; // Trang mục lục chính mặc định là trang số 1
	trang_cai_dat_duoc_lua_chon = 1; // Vị trí trang được bôi đen là 1
    while(1) // Mục cài đặt chính gồm có 4-5 trang mục lục chính
	{ 
		switch(trang_muc_luc_cai_dat)
		{
			case 0: trang_muc_luc_cai_dat = 5; break;
			case 1: trang_muc_luc_cai_dat_chung_1(); break;
			case 2: trang_muc_luc_cai_dat_chung_2(); break;
			case 3: trang_muc_luc_cai_dat_chung_3(); break;
			case 4: trang_muc_luc_cai_dat_chung_4(); break;
			case 5: trang_muc_luc_cai_dat_chung_5(); break;
			case 6: trang_muc_luc_cai_dat = 1; break;
		}
	}
}

char str[] = "";

/** DƯỚI ĐÂY LÀ 5 TRANG MỤC LỤC CÀI ĐẶT CHÍNH */
/*1*/void MAY_BAN_HANG::trang_muc_luc_cai_dat_chung_1()
	{
		char str_cd_gia[32];
		char str_cd_so_hang[32];
		char str_cd_khoa_o_hang[32];
		char str_cd_nky_loi[32];
		Str.str('C','D',' ','g','i','a',' ','t','i','e','n', str_cd_gia[0]);
		Str.str('C','D',' ','s','o',' ','h','a','n','g', str_cd_so_hang[0]);
		Str.str('C','D',' ','k','h','o','a',' ','o',' ','h','a','n','g', str_cd_khoa_o_hang[0]);
		Str.str('N','h','a','t',' ','k','y',' ','l','o','i', str_cd_nky_loi[0]);
		// vi_tri_con_tro_lcd = 1; // Con trỏ LCD luôn đặt ở vị trí đầu tiên của 1 trang LCD mới
		while(1)
		{
			lcd_cai_dat_chung(str_cd_gia, str_cd_so_hang, str_cd_khoa_o_hang, str_cd_nky_loi);	// Hiển thị giao diện của trang trên LCD
			quet_ban_phim(); 		// Quét bàn phím để đọc lệnh của người dùng
			switch(key)
			{
				case 0x30:	// Nút xuống
					trang_cai_dat_duoc_lua_chon++;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=1;
						trang_muc_luc_cai_dat++;
						goto thoat_trang_muc_luc_cai_dat_1;
					}
					break;
				case 0x38:	// Nút lên
					trang_cai_dat_duoc_lua_chon--;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=4;
						trang_muc_luc_cai_dat--;
						goto thoat_trang_muc_luc_cai_dat_1;	
					}
					break;
				
				case 0x23: break;	// Phím CANCEL
				case 0x2A:			// Phím ENTER
					switch(trang_cai_dat_duoc_lua_chon)
					{
						case 1: trang_cai_dat_gia_tien(); break;
						case 2:	trang_cai_dat_so_hang(); break;
						case 3:	trang_cai_dat_khoa_o_hang(); break;
						case 4:	trang_cai_dat_xem_nhat_ky_loi(); break;
					}
					break;
			}
		}
		thoat_trang_muc_luc_cai_dat_1: {}
	}

/*2*/void MAY_BAN_HANG::trang_muc_luc_cai_dat_chung_2()
	{
		char str_cd_dthu[32];
		char str_cd_them_tien[32];
		char str_cd_lam_rong[32];
		char str_cd_led[16];
		Str.str('X','e','m',' ','d','o','a','n','h',' ','t','h','u', str_cd_dthu[0]);
		Str.str('T','h','e','m',' ','t','i','e','m',' ','t','r','a',' ','l','a','i', str_cd_them_tien[0]);
		Str.str('L','a','m',' ','r','o','n','g',' ','B','T','L', str_cd_lam_rong[0]);
		Str.str('C','D',' ','l','e','d', str_cd_led[0]);
		while(1)
		{
			lcd_cai_dat_chung(str_cd_dthu, str_cd_them_tien, str_cd_lam_rong, str_cd_led);	// Hiển thị giao diện của trang trên LCD
			quet_ban_phim(); 		// Quét bàn phím để đọc lệnh của người dùng
			switch(key)
			{
				case 0x30:	// Nút xuống
					trang_cai_dat_duoc_lua_chon++;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=1;
						trang_muc_luc_cai_dat++;
						goto thoat_trang_muc_luc_cai_dat_2;
					}
					break;
					
				case 0x38:	// Nút lên
					trang_cai_dat_duoc_lua_chon--;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=4;
						trang_muc_luc_cai_dat--;
						goto thoat_trang_muc_luc_cai_dat_2;	
					}						
					break;
				
				case 0x23: break;// Phím CANCEL
				case 0x2A:	// Phím ENTER
					switch(trang_cai_dat_duoc_lua_chon)
					{
						case 1: trang_cai_dat_xem_doanh_thu(); break;
						case 2:	trang_cai_dat_them_tien_tra_lai(); break;
						case 3:	trang_cai_dat_lam_rong_bo_tra_lai(); break;
						case 4: trang_cai_dat_led(); break;
					}
				break;
			}
		}
		thoat_trang_muc_luc_cai_dat_2: {}		
	}

/*3*/void MAY_BAN_HANG::trang_muc_luc_cai_dat_chung_3()
	{
		// vi_tri_con_tro_lcd = 1; // Con trỏ LCD luôn đặt ở vị trí đầu tiên của 1 trang LCD mới
		while(1)
		{
			char str_cd_may_lanh[32];
			char str_cd_nhiet_do[32];
			Str.str('C','D',' ','m','a','y',' ','l','a','n','h', str_cd_may_lanh[0]);
			Str.str('C','D',' ','n','h','i','e','t',' ','d','o', str_cd_nhiet_do[0]);
			lcd_cai_dat_chung(str_cd_may_lanh, str_cd_nhiet_do, str, str);	// Hiển thị giao diện của trang trên LCD
			quet_ban_phim(); 		// Quét bàn phím để đọc lệnh của người dùng
			switch(key)
			{
				case 0x30:	// Nút xuống
					trang_cai_dat_duoc_lua_chon++;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=1;
						trang_muc_luc_cai_dat++;
						goto thoat_trang_muc_luc_cai_dat_3;
					}
					break;
					
				case 0x38:	// Nút lên
					trang_cai_dat_duoc_lua_chon--;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=4;
						trang_muc_luc_cai_dat--;
						goto thoat_trang_muc_luc_cai_dat_3;	
					}						
					break;
				
				case 0x23: break;// Phím CANCEL
				case 0x2A:	// Phím ENTER
					switch(trang_cai_dat_duoc_lua_chon)
					{
						case 1: trang_cai_dat_may_lanh(); break;
						case 2:	trang_cai_dat_nhiet_do(); break;
						case 3:	break;
						case 4:	break;
					}
				break;
			}
		}
		thoat_trang_muc_luc_cai_dat_3: {}	
	}

/*4*/void MAY_BAN_HANG::trang_muc_luc_cai_dat_chung_4()
	{
		// vi_tri_con_tro_lcd = 1; // Con trỏ LCD luôn đặt ở vị trí đầu tiên của 1 trang LCD mới
		while(1)
		{
			lcd_cai_dat_chung(str, str, str, str);	// Hiển thị giao diện của trang trên LCD
			quet_ban_phim(); 		// Quét bàn phím để đọc lệnh của người dùng
			switch(key)
			{
				case 0x30:	// Nút xuống
					trang_cai_dat_duoc_lua_chon++;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=1;
						trang_muc_luc_cai_dat++;
						goto thoat_trang_muc_luc_cai_dat_4;
					}
					break;
					
				case 0x38:	// Nút lên
					trang_cai_dat_duoc_lua_chon--;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=4;
						trang_muc_luc_cai_dat--;
						goto thoat_trang_muc_luc_cai_dat_4;		
					}						
					break;
				
				case 0x23: break;// Phím CANCEL
				case 0x2A:	// Phím ENTER
					switch(trang_cai_dat_duoc_lua_chon)
					{
						case 1: break;
						case 2:	break;
						case 3:	break;
						case 4:	break;
					}
				break;
			}
		}
		thoat_trang_muc_luc_cai_dat_4: {}		
	}

/*5*/void MAY_BAN_HANG::trang_muc_luc_cai_dat_chung_5()
	{
		// vi_tri_trang_duoc_chon = 1; // Con trỏ LCD luôn đặt ở vị trí đầu tiên của 1 trang LCD mới
		while(1)
		{
			lcd_cai_dat_chung(str, str, str, str);	// Hiển thị giao diện của trang trên LCD
			quet_ban_phim(); 		// Quét bàn phím để đọc lệnh của người dùng
			switch(key)
			{
				case 0x30:	// Nút xuống
					trang_cai_dat_duoc_lua_chon++;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=1;
						trang_muc_luc_cai_dat++;
						goto thoat_trang_muc_luc_cai_dat_5;
					}
					break;
					
				case 0x38:	// Nút lên
					trang_cai_dat_duoc_lua_chon--;
					if((trang_cai_dat_duoc_lua_chon==5)||(trang_cai_dat_duoc_lua_chon==0))
					{
						trang_cai_dat_duoc_lua_chon=4;
						trang_muc_luc_cai_dat--;
						goto thoat_trang_muc_luc_cai_dat_5;	
					}						
					break;
				
				case 0x23: break;// Phím CANCEL
				case 0x2A:	// Phím ENTER
					switch(trang_cai_dat_duoc_lua_chon)
					{
						case 1: break;
						case 2:	break;
						case 3:	break;
						case 4:	break;
					}
				break;
			}
		}
		thoat_trang_muc_luc_cai_dat_5: {}	
	}
			
/**--------------------------------------------------------------------------**/
/** CÁC HÀM BỔ TRỢ ----------------------------------------------------------**/
		void MAY_BAN_HANG::quet_ban_phim()
		{
			key = 0; dem_thoi_gian_quet_phim = 0;
			while(key==0)
			{
				key = keypad.getKey(); // Quét bàn phím
				dem_thoi_gian_quet_phim++;
				if (dem_thoi_gian_quet_phim == 2) break;
			}
		}

		void MAY_BAN_HANG::lua_chon_o_bat_dau()
		{
			da_nhap++;
			switch(da_nhap)
			{
				case 1: 
					o_bat_dau = key - 0x30;
					if(o_bat_dau==0)
						da_nhap = 0;
					break;
				case 2:
					o_bat_dau = o_bat_dau*10 + key - 0x30;
					da_nhap = 0;
					break;
			}
		}

		void MAY_BAN_HANG::lua_chon_o_ket_thuc()
		{
			da_nhap++;
			switch(da_nhap)
			{
				case 1: 
					o_ket_thuc = key - 0x30;
					if(o_ket_thuc==0)
						da_nhap = 0;
					break;
				case 2:
					o_ket_thuc = o_ket_thuc*10 + key - 0x30;
					da_nhap = 0;
					break;
			}
		}

/**0*/ void MAY_BAN_HANG::doc_ban_phim_cd()
      {
	      key = 0;
	      while (key==0x00)
	      {
		    key = keypad.getKey(); 						// Quét bàn phím
		    delay(10);
	      }
	
      }


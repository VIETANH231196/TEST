/*
	Các hàm hiển thị màn hình LCD
*/

#include <MBH.h>

		/*void MAY_BAN_HANG::lcd_start1_tab1()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 20); 
				u8g.print("KIEM TRA MAY: ");
			}
			while(u8g.nextPage());
		}
		
		void MAY_BAN_HANG::lcd_start2_tab1()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 20); 
				u8g.print("KIEM TRA MAY: ");
				u8g.setPrintPos(0, 40); 
				u8g.print("Eeprom: ");
				switch (LOI.EEPROM)
				{
					case 0x00: u8g.print("Ok"); break;
					case 0x01: u8g.print("Erro"); break;
				}
			}
			while(u8g.nextPage());
		}
		
		void MAY_BAN_HANG::lcd_start3_tab1()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 20); 
				u8g.print("KIEM TRA MAY: ");
				u8g.setPrintPos(0, 40); 
				u8g.print("Eeprom: ");
				switch (LOI.EEPROM)
				{
					case 0x00: u8g.print("Ok"); break;
					case 0x01: u8g.print("Erro"); break;
				}
				u8g.setPrintPos(0, 60); 
				u8g.print("NV11: ");
				switch (LOI.NV11)
				{
					case 0x00: u8g.print("Ok"); break;
					case 0x01: u8g.print("Erro"); break;
				}
			}
			while(u8g.nextPage());
		}
		*/
		
/**1*/	void MAY_BAN_HANG::lcd_start1_tab2()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 20); 
				u8g.print("SIM: ???");
				u8g.setPrintPos(0, 40); 
				u8g.print("THOI GIAN: ");
				u8g.setPrintPos(0, 60); 
				u8g.print(Rtc.hour);
				u8g.print(":");
				u8g.print(Rtc.minute);
				u8g.print(":");
				u8g.print(Rtc.second);
			}
			while(u8g.nextPage());
		}
		
/* 0 */	void MAY_BAN_HANG::lcd_khong_o_trong_thoi_gian_hoat_dong() //Màn hình LCD thông báo máy không hoạt động
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("VENDING MACHINE: SLEEPING");
			}
			while(u8g.nextPage());
		}
	
/**1*/	void MAY_BAN_HANG::lcd_hay_chon_hang_can_mua()// Màn hình thanh toán 1 [HAY CHON HANG CAN MUA]
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("HAY CHON HANG");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::hien_thi_so_nhap_tu_ban_phim()// Màn hình thanh toán 2 [12]
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(13, 13); 
				if ((phim_1>0x2F)&&(phim_1<0x3A))// Nếu phím nhấn thứ nhất = "0-9"
				{
					u8g.print(phim_1-0x30);
					if ((phim_2>0x2F)&&(phim_2<0x3A))
					{
						u8g.setPrintPos(20, 13); 
						u8g.print(phim_2-0x30);
					}
					else 
					{
						//Không làm gì cả
					}
				}
				else
				{
					//Không làm gì cả
				}
			}
			while(u8g.nextPage());
		}
		
/* 0 */	void MAY_BAN_HANG::lcd_mua_hang_thanh_cong()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("MUA HANG");
				u8g.setPrintPos(0, 40); 
				u8g.print("THANH CONG");
			}
			while(u8g.nextPage());
		}
		
/* 0 */	void MAY_BAN_HANG::lcd_huy_giao_dich()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("Da huy giao dich");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::lcd_balance_item()			// 		|ITEM: 		|
														//		|BALANCE:	|
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("Tai khoan:");
				u8g.setPrintPos(30, 26);
				u8g.print(tai_khoan);
				if(tai_khoan!=0)
				{
					u8g.print("000");
				}
				u8g.setPrintPos(0, 45); 
				u8g.print("O hang:");
				u8g.setPrintPos(30, 58); 
				u8g.print(phim);
				u8g.print("-");
				u8g.print(gia_tien[phim]);
				if(gia_tien[phim]!=0)
				{
					u8g.print("000");
				}
			}
			while(u8g.nextPage());
		}
		
/* 0 */	void MAY_BAN_HANG::lcd_xac_nhan_mua_hang()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("BALANCE: ");
				u8g.print(tai_khoan*1000);
				u8g.setPrintPos(0, 40); 
				u8g.print("ITEM: ");
				u8g.print(phim);
				u8g.print("-");
				u8g.print(gia_tien[phim]);
				u8g.setPrintPos(0, 60); 
				u8g.print("MUA HANG? E/C");
			}
			while(u8g.nextPage());
		}
		
/* 0 */	void MAY_BAN_HANG::lcd_ban_co_muon_dua_them_tien_vao_may()
		{
			u8g.firstPage(); 
			do
			{
			u8g.setFont(u8g_font_unifont);
			u8g.setPrintPos(0, 13); 
			u8g.print("Tai khoan khong du");
			u8g.print(tai_khoan*1000);
			u8g.setPrintPos(0, 40); 
			u8g.print("Nap them tien?");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::lcd_mua_hang_tiep()			
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("Tai khoan:");
				u8g.setPrintPos(30, 26);
				u8g.print(tai_khoan);
				if(tai_khoan!=0)
				{
					u8g.print("000");
				}
				u8g.setPrintPos(0, 40); 
				u8g.print("MUA HANG TIEP?");
				u8g.setPrintPos(0, 60); 
				u8g.print("E/C");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::lcd_dang_tra_lai_tien()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("Dang tra lai");
				u8g.setPrintPos(0, 40);
				u8g.print("Xin hay doi!!!");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::lcd_da_het_tien_tra_lai_xin_mua_hang_tiep()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("Dang het tien");
				u8g.setPrintPos(0, 40);
				u8g.print("tra lai");
				u8g.setPrintPos(0, 60); 
				u8g.print("Xin mua tiep");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::cap_nhat_lcd()
		{
			if (phim_1!=0) // Nếu nhấn từ phím 1 tới phím 9 thì hiện màn hình số
			{
				hien_thi_so_nhap_tu_ban_phim();
			}
			else if ((key==0)&&(phim_1==0)&&(tai_khoan==0)&&(phim==0)&&(man_hinh==trang_0))
			{
				lcd_hay_chon_hang_can_mua();	// Ban đầu hiển thị màn hình [HAY CHON HANG CAN MUA]
			}
			else if ((tai_khoan!=0)||(phim!=0)&&(key==0))	// Nếu tài khoản hoặc bàn phím khác 0 thì chuyển màn hình hiển thị
			{
				lcd_balance_item();
			}
		}
		
		//===================================================	
/**1*/	void MAY_BAN_HANG::lcd_quay_dong_co()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("Dong co dang quay");
				u8g.setPrintPos(0, 40); 
				u8g.print("Xin hay doi!!!");
			}
			while(u8g.nextPage());
		}
		
/**1*/	void MAY_BAN_HANG::lcd_thong_bao_chon_hang_sai()
		{
			u8g.firstPage(); 
			do
			{
				u8g.setFont(u8g_font_unifont);
				u8g.setPrintPos(0, 13); 
				u8g.print("O hang khong ton");
				u8g.setPrintPos(0, 40); 
				u8g.print("tai hoac bi khoa!!!");
			}
			while(u8g.nextPage());
		}
		
		
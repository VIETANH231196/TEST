/*
	Cài đặt khóa ô hàng
*/

#include <MBH.h>

		//----------------------------------------------------------------------
/* OK */void MAY_BAN_HANG::trang_cai_dat_khoa_o_hang()				// Trang 1-3
		{
			vi_tri_con_tro_lcd = 1; // Đặt con trỏ mặc định ở vị trí 1 khi vào hàm cài đặt
			o_bat_dau = 0; o_ket_thuc = 0; o_hang_khoa_cai_dat = 0; da_nhap = 0;
			while (trang_cai_dat_duoc_lua_chon)
			{
				lcd_cai_dat_khoa_o_hang();
				// Đọc bàn phím để xử lý bước tiếp theo
				quet_ban_phim();
				// Phân tích phím đọc được sau khi quét bàn phím
				switch(vi_tri_con_tro_lcd)
				{
					case 1:
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: lua_chon_o_bat_dau(); break;		// Phím số 0
							case 0x31: lua_chon_o_bat_dau(); break;		// Phím số 1
							case 0x32: lua_chon_o_bat_dau(); break;		// Phím số 2
							case 0x33: lua_chon_o_bat_dau(); break;		// Phím số 3
							case 0x34: lua_chon_o_bat_dau(); break;		// Phím số 4
							case 0x35: lua_chon_o_bat_dau(); break;		// Phím số 5
							case 0x36: lua_chon_o_bat_dau(); break;		// Phím số 6
							case 0x37: lua_chon_o_bat_dau(); break;		// Phím số 7
							case 0x38: lua_chon_o_bat_dau(); break;		// Phím số 8
							case 0x39: lua_chon_o_bat_dau(); break;		// Phím số 9
							
							case 0x23: 			// Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0;
								goto thoat_cai_dat_khoa_o_hang; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							case 0x2A:  		// Phím ENTER
								if(o_bat_dau>=60)
									o_bat_dau = 0;
								else
									vi_tri_con_tro_lcd++;
								da_nhap = 0;
								break;
						}
						break;
					}
					
					case 2:
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: lua_chon_o_ket_thuc(); break;	// Phím số 0
							case 0x31: lua_chon_o_ket_thuc(); break;	// Phím số 1
							case 0x32: lua_chon_o_ket_thuc(); break;	// Phím số 2
							case 0x33: lua_chon_o_ket_thuc(); break;	// Phím số 3
							case 0x34: lua_chon_o_ket_thuc(); break;	// Phím số 4
							case 0x35: lua_chon_o_ket_thuc(); break;	// Phím số 5
							case 0x36: lua_chon_o_ket_thuc(); break;	// Phím số 6
							case 0x37: lua_chon_o_ket_thuc(); break;	// Phím số 7
							case 0x38: lua_chon_o_ket_thuc(); break;	// Phím số 8
							case 0x39: lua_chon_o_ket_thuc(); break;	// Phím số 9
							
							case 0x23: 			// Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0;
								goto thoat_cai_dat_khoa_o_hang; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							case 0x2A:  		// Phím ENTER
								if(o_ket_thuc>=60)
								{
									o_ket_thuc = 0;
									vi_tri_con_tro_lcd = 2; // Giữ nguyên vị trí con trỏ
								}
								else
								{
									if (o_bat_dau<=o_ket_thuc)
									{
										vi_tri_con_tro_lcd++;// Chuyển sang mục nhập giá tiền
										da_nhap = 0;
									}
									else 
									{
										vi_tri_con_tro_lcd = 1;
										o_bat_dau = 0; o_ket_thuc = 0; da_nhap = 0;
									}
								}
						}
						break;
					}
					
					case 3:
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: break;	// Phím số 0
							case 0x31: break;	// Phím số 1											
							case 0x32: break;	// Phím số 2								
							case 0x33: break;	// Phím số 3
							case 0x34: break; 	// Phím số 4
							case 0x35: break; 	// Phím số 5
							case 0x36: break; 	// Phím số 6
							case 0x37: break;	// Phím số 7
							{
								o_hang_khoa_cai_dat = khoa;
								lua_chon_o_hang_khoa();
								lcd_xong();
								delay(1000); 	// Cần sửa hàm delay
								break;						
							}
							case 0x38: break;	// Phím số 8
							case 0x39: 			// Phím số 9
							{
								o_hang_khoa_cai_dat = khong_khoa_khong_loi;
								lua_chon_o_hang_khoa();
								lcd_xong();
								delay(1000);	// Cần sửa hàm delay
								break;						
							}
							
							case 0x23: 			// Phím CANCEL
								goto thoat_cai_dat_khoa_o_hang; break;
							case 0x2A: break;		// Phím ENTER
						}
						break;
					}
				}
			}
			thoat_cai_dat_khoa_o_hang: 
			{
				trang_cai_dat_duoc_lua_chon = 3;
			}
		}
		
		void MAY_BAN_HANG::lua_chon_o_hang_khoa()
		{
			if (o_bat_dau<=o_ket_thuc)
			{
				if((o_bat_dau==0)&&(o_ket_thuc==0))
				{
					o_hang_khoa_cai_dat = 0;
					vi_tri_con_tro_lcd = 1;
					da_nhap = 0;
					goto thoat_lua_chon_o_hang_khoa;
				}
				else if((o_bat_dau==0)&&(o_ket_thuc!=0))
				{
					o_bat_dau = 1;
				}
				// Cài đặt ô hàng khóa
				for (unsigned char i=o_bat_dau; i<=o_ket_thuc; i++)
				{
					o_hang_loi[i] = o_hang_khoa_cai_dat;
					if ((i%10==0)||(i%10==7)||(i%10==8)||(i%10==9)) // Mặc định: khóa các ô hàng có hàng đơn vị là 0; 7; 8; 9
					{
						EEPROM.write(ADDR_LOI_DC[i], khoa); delay(5);
					}
					else
					{
						EEPROM.write(ADDR_LOI_DC[i], o_hang_loi[i]); delay(5);
					}
				}
				vi_tri_con_tro_lcd = 1;// Chuyển sang mục nhập giá tiền
				da_nhap = 0;
				o_bat_dau = o_ket_thuc + 1; o_ket_thuc = o_ket_thuc + 1;
				if(o_bat_dau>=60)		o_bat_dau = 0;
				if (o_ket_thuc>=60) 	o_ket_thuc = 0;
				o_hang_khoa_cai_dat = 0;
				goto thoat_lua_chon_o_hang_khoa;
				//--------------------------------------
				// Thoát khỏi mục cài đặt
			}
			else 
			{
				vi_tri_con_tro_lcd = 1;
				o_bat_dau = 0; o_ket_thuc = 0;
				da_nhap = 0;
			}
			thoat_lua_chon_o_hang_khoa:
			{
				// Không làm gì cả
			}
		}
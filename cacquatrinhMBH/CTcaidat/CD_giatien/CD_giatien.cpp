/*
	Mục cài đặt giá tiền
*/

#include <MBH.h>


		//----------------------------------------------------------------------
/* OK */void MAY_BAN_HANG::trang_cai_dat_gia_tien()					// Trang 1-1	
		{
			vi_tri_con_tro_lcd = 1; // Đặt con trỏ mặc định ở vị trí 1 khi vào hàm cài đặt
			o_bat_dau = 0; o_ket_thuc = 0; gia_cai_dat = 0; da_nhap = 0;
			while (trang_cai_dat_duoc_lua_chon)
			{
				lcd_cai_dat_gia_tien();
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
								vi_tri_con_tro_lcd = 1;
								da_nhap = 0;
								goto thoat_cai_dat_gia_tien; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
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
							case 0x33: lua_chon_o_ket_thuc(); break; 	// Phím số 3
							case 0x34: lua_chon_o_ket_thuc(); break;	// Phím số 4
							case 0x35: lua_chon_o_ket_thuc(); break;	// Phím số 5
							case 0x36: lua_chon_o_ket_thuc(); break;	// Phím số 6
							case 0x37: lua_chon_o_ket_thuc(); break;	// Phím số 7
							case 0x38: lua_chon_o_ket_thuc(); break;	// Phím số 8
							case 0x39: lua_chon_o_ket_thuc(); break;	// Phím số 9
							
							case 0x23: 			// Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0;
								vi_tri_con_tro_lcd = 1;
								da_nhap = 0;
								goto thoat_cai_dat_gia_tien; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
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
								break;
						}
						break;
					}
					
					case 3:
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: lua_chon_gia_tien();	break;		// Phím số 0
							case 0x31: lua_chon_gia_tien();	break;		// Phím số 1					
							case 0x32: lua_chon_gia_tien();	break;		// Phím số 2					
							case 0x33: lua_chon_gia_tien();	break;		// Phím số 3					
							case 0x34: lua_chon_gia_tien();	break;		// Phím số 4				
							case 0x35: lua_chon_gia_tien();	break; 		// Phím số 5					
							case 0x36: lua_chon_gia_tien();	break;		// Phím số 6					
							case 0x37: lua_chon_gia_tien();	break;		// Phím số 7					
							case 0x38: lua_chon_gia_tien();	break;		// Phím số 8					
							case 0x39: lua_chon_gia_tien();	break;		// Phím số 9					
							
							case 0x23: 			// Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0;
								vi_tri_con_tro_lcd = 1;
								da_nhap = 0;
								goto thoat_cai_dat_gia_tien; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							case 0x2A:  		// Phím ENTER
								if (o_bat_dau<=o_ket_thuc)
								{
									if((o_bat_dau==0)&&(o_ket_thuc==0))
									{
										gia_cai_dat = 0;
										vi_tri_con_tro_lcd = 1;
										da_nhap = 0;
										goto thoat_cai_dat_gia_tien;
									}
									else if((o_bat_dau==0)&&(o_ket_thuc!=0))
									{
										o_bat_dau = 1;
									}
									// Cài đặt giá tiền theo ô bắt đầu và ô kết thúc
									// Lưu giá tiền vào bộ nhớ EEPROM
									for (char i=o_bat_dau; i<=o_ket_thuc; i++)
									{
										gia_tien[i] = gia_cai_dat/1000;
										EEPROM.write(ADDR_GIA_TIEN[i], gia_tien[i]); delay(5);// lưu vào bộ nhớ EEPROM
									}
									lcd_xong();
									delay(1000);			// Cần sửa hàm delay
									vi_tri_con_tro_lcd = 1;// Chuyển sang mục nhập giá tiền
									da_nhap = 0;
									o_bat_dau = o_ket_thuc + 1;
									o_ket_thuc = o_ket_thuc + 1;
									if (o_bat_dau>=60)		o_bat_dau = 0;
									if (o_ket_thuc>=60) 	o_ket_thuc = 0;
									gia_cai_dat = 0;
									goto thoat_cai_dat_gia_tien;
									//--------------------------------------
									// Thoát khỏi mục cài đặt
								}
								else 
								{
									vi_tri_con_tro_lcd = 1;
									o_bat_dau = 0; o_ket_thuc = 0;
									da_nhap = 0;
								}
								break;
						}
						break;
					}
				}
			}
			thoat_cai_dat_gia_tien: 
			{
				trang_cai_dat_duoc_lua_chon = 1;
			}
		}
		
		
		void MAY_BAN_HANG::lua_chon_gia_tien()
		{
			da_nhap++;
			switch(da_nhap)
			{
				case 1: gia_cai_dat = key - 0x30;
					if(gia_cai_dat==0)
						da_nhap = 0;
					break;
				case 2: gia_cai_dat = gia_cai_dat*10 + key - 0x30; break;
				case 3: gia_cai_dat = gia_cai_dat*10 + key - 0x30; break;
				case 4: gia_cai_dat = gia_cai_dat*10 + key - 0x30; break;
				case 5: gia_cai_dat = gia_cai_dat*10 + key - 0x30;
					if (gia_cai_dat>=50000)
						gia_cai_dat = 50000;
					da_nhap = 0;
					break;			
			}
		}
		
		
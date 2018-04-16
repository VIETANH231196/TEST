/*
	Cài đặt: Mục nhật ký lỗi
*/

#include <MBH.h>

//----------------------------------------------------------------------
/* OK */void MAY_BAN_HANG::trang_cai_dat_xem_nhat_ky_loi()			// Trang 2-2
		{
			vi_tri_con_tro_lcd = 1; // Đặt con trỏ mặc định ở vị trí 1 khi vào hàm cài đặt
			// Đọc lỗi từ bộ nhớ EEPROM
			unsigned short int so_dong_co_loi = 0;	// Tổng số động cơ bị lỗi - tương ứng số dòng cần hiển thị
			unsigned char ma_dong_co_loi[37];		// Với bản 36 động cơ hoạt động
			unsigned char dong_loi = 1;				// Luôn hiển thị bắt đầu từ dòng 1
			for (unsigned char i=1; i<100; i++)
			{
				o_hang_loi[i] = EEPROM.read(ADDR_LOI_DC[i]);
				if(o_hang_loi[i]==0)
				{
					so_dong_co_loi ++;
					ma_dong_co_loi[so_dong_co_loi] = i;
				}
			}
			while (trang_cai_dat_duoc_lua_chon)
			{
				// Phần cài đặt cho hiển thị
				if(so_dong_co_loi==0)
				{
					// Không có bản ghi nào
					dong_1_lcd = 0;
					dong_2_lcd = 0;
					vi_tri_con_tro_lcd = 1;
				}
				else if(so_dong_co_loi==1)
				{
					dong_1_lcd = ma_dong_co_loi[dong_loi];
					dong_2_lcd = 0;
					vi_tri_con_tro_lcd = 1;
				}
				else 
				{
					dong_1_lcd = ma_dong_co_loi[dong_loi];
					if(dong_loi<so_dong_co_loi)
					{
						dong_2_lcd = ma_dong_co_loi[dong_loi+1];
					}
					else
					{
						dong_2_lcd = 0;
					}
				}
				lcd_nhat_ky_loi();
				// Đọc bàn phím để xử lý bước tiếp theo
				quet_ban_phim();
				// Phân tích phím đọc được sau khi quét bàn phím
				switch(vi_tri_con_tro_lcd)
				{
					case 1: // Con trỏ ở dòng 1
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: 			// Phím số 0
							{
								if((so_dong_co_loi==0)||(so_dong_co_loi==1)) // Nếu chỉ có 1 hoặc 0 động cơ lỗi thì ...
								{
									vi_tri_con_tro_lcd = 1; // Giữ nguyên vị trí con trỏ
								}
								else if(so_dong_co_loi>=2)
								{
									vi_tri_con_tro_lcd++; 	// Cho con trỏ trỏ tới dòng thứ 2
								}
								break; // Trường hợp này chỉ chuyển vị trí con trỏ, các dòng trong trang vẫn giữ nguyên giá trị
							}
							case 0x31: break;
							case 0x32: break;
							case 0x33: break;
							case 0x34: break;
							case 0x35: break;
							case 0x36: break;
							case 0x37: break;
							case 0x38: 
							{
								// Không thay đổi vị trí con trỏ
								vi_tri_con_tro_lcd = 1;
								if(dong_loi==1)
								{
									// Nếu đang hiển thị dòng lỗi 1 thì không làm gì cả
									// Các dòng vẫn giữ nguyên
								}
								else if(dong_loi>=2)
								{
									dong_loi --; // Giảm dòng lỗi đi 1 đơn vị
									// Thay đổi hiển thị
								}
								break; 
							}
							case 0x39: 			// Phím 9: Xóa ô động cơ bị lỗi
							{
								o_hang_loi[ma_dong_co_loi[dong_loi]] = 1;
								EEPROM.write(ADDR_LOI_DC[ma_dong_co_loi[dong_loi]], 1);
								delay(5);
								// Về mặt hiển thị:
								if((dong_loi==so_dong_co_loi)&&(dong_loi>1)&&(dong_2_lcd==0))
								{
									ma_dong_co_loi[dong_loi] = ma_dong_co_loi[dong_loi-1];
									dong_loi = dong_loi-1;
								}
								for (unsigned char i=dong_loi; i<so_dong_co_loi; i++)
								{
									ma_dong_co_loi[i] = ma_dong_co_loi[i+1];
								}
								/*so_dong_co_loi = 0;
								for (int i=1; i<100; i++)
								{
									o_hang_loi[i] = EEPROM.read(ADDR_LOI_DC[i]);
									if(o_hang_loi[i]==0)
									{
										so_dong_co_loi ++;
										ma_dong_co_loi[so_dong_co_loi] = i;
									}
								}*/
								
								if(so_dong_co_loi>0)
								{
									so_dong_co_loi--; // Giảm số động cơ bị lỗi đi 1 sau khi xóa
								}
								break;
							}
							
							case 0x23: // Phím CANCEL
							{
								goto thoat_cai_dat_nhat_ky_loi; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							}
							case 0x2A: break; // Phím ENTER
						}
						break;
					}
					case 2: // Con trỏ ở dòng 2
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: 			// Phím số 0
							{
								// Có thay đổi màn hình
								if(dong_loi+1<so_dong_co_loi)// Nếu dòng 2 chưa hiện đến động cơ lỗi cuối cùng thì...
								{
									dong_loi++;
								}
								vi_tri_con_tro_lcd = 2;
								break;
							}
							case 0x31: break;
							case 0x32: break;
							case 0x33: break;
							case 0x34: break;
							case 0x35: break;
							case 0x36: break;
							case 0x37: break;
							case 0x38: 
							{
								// Trường hợp này chỉ chuyển vị trí con trỏ lên trên, các giá trị khác giữ nguyên
								vi_tri_con_tro_lcd--;
								break; 
							}
							case 0x39: 			// Phím 9: Xóa ô động cơ bị lỗi
							{								
								o_hang_loi[ma_dong_co_loi[dong_loi+1]] = 1;					// Dòng lỗi thứ 2 bị xóa
								EEPROM.write(ADDR_LOI_DC[ma_dong_co_loi[dong_loi+1]], 1);	// Dòng lỗi thứ 2 bị xóa trong bộ nhớ
								delay(5);
								// Về mặt hiển thị:
								for (unsigned char i=dong_loi+1; i<so_dong_co_loi; i++)
								{
									ma_dong_co_loi[i] = ma_dong_co_loi[i+1];
								}
								if(dong_loi+1==so_dong_co_loi)
								{
									ma_dong_co_loi[dong_loi+1] = 0;
								}
								/*so_dong_co_loi = 0;
								for (int i=1; i<100; i++)
								{
									o_hang_loi[i] = EEPROM.read(ADDR_LOI_DC[i]);
									if(o_hang_loi[i]==0)
									{
										so_dong_co_loi ++;
										ma_dong_co_loi[so_dong_co_loi] = i;
									}
								}*/
								
								if(so_dong_co_loi>0)
								{
									so_dong_co_loi--; // Giảm số động cơ bị lỗi đi 1 sau khi xóa
								}
								break;
							}
							
							case 0x23: // Phím CANCEL
							{
								goto thoat_cai_dat_nhat_ky_loi; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							}
							case 0x2A: break; // Phím ENTER
						}
						break;
					}
				}
			}
			thoat_cai_dat_nhat_ky_loi:
			{
				trang_cai_dat_duoc_lua_chon = 4;
			}
		}

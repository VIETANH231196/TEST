/*
	Tính toán và hiển thị doanh thu trong mục cài đặt
*/


#include <MBH.h>


		// ----------------------------------------------------------------------
		void MAY_BAN_HANG::trang_cai_dat_xem_doanh_thu()			// Trang 2-1
		{
			// Rtc.readDS1307();		// Đọc thời gian ở thời điểm hiện tại từ IC thời gian thực
			/** Sau khi đọc thời gian thực thì so sánh với các biến lưu trong EEPROM xem thời gian thực có lỗi k */
			
			/** Nếu không tồn tại lỗi nghĩa là thời gian thực đọc đúng thì đọc các giá trị doanh thu theo biến 
				được lưu trong bộ nhớ EEPROM */
			// Đọc giá trị năm nay và tháng này và ngày hôm nay
			//		Rtc.month: tháng này
			// 		Rtc.day: ngày hôm nay
			// Khối code tính toán doanh thu năm nay từ các byte trong bộ nhớ		
			vi_tri_con_tro_lcd = 1; // Đặt con trỏ mặc định ở vị trí 1 khi vào hàm cài đặt
			while (trang_cai_dat_duoc_lua_chon)
			{
				lcd_xem_doanh_thu();
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
							case 0x30: 			// Phím số 0: Xuống 1 dòng
								vi_tri_con_tro_lcd++;
								break; 
							case 0x31: break;
							case 0x32: break;
							case 0x33: break;
							case 0x34: break;
							case 0x35: break;
							case 0x36: break;
							case 0x37: break;
							case 0x38: 
								vi_tri_con_tro_lcd = 3; // Nhảy xuống dòng cuối: dòng số 3
								break;
							case 0x39: break;
							
							case 0x23: // Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							case 0x2A: 
								thong_ke_doanh_thu_ngay();
								vi_tri_con_tro_lcd = 1;
								break; // Phím ENTER
						}
						break;
					}
					case 2:
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: 			// Phím số 0: Xuống 1 dòng
								vi_tri_con_tro_lcd++;
								break; 
							case 0x31: break;
							case 0x32: break;
							case 0x33: break;
							case 0x34: break;
							case 0x35: break;
							case 0x36: break;
							case 0x37: break;
							case 0x38: 
								vi_tri_con_tro_lcd--; // Nhảy xuống dòng cuối: dòng số 3
								break;
							case 0x39: break;
							
							case 0x23: // Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							case 0x2A: // Phím ENTER
								thong_ke_doanh_thu_thang();
								vi_tri_con_tro_lcd = 2;
								break; 
						}						
						break;
					}
					case 3: 
					{
						switch(key)
						{
							case 0x00: break; 	// Không đọc được phím nào cả
							case 0x30: 			// Phím số 0: Xuống 1 dòng
								vi_tri_con_tro_lcd = 1; // Trở về dòng đầu tiên
								break; 
							case 0x31: break;
							case 0x32: break;
							case 0x33: break;
							case 0x34: break;
							case 0x35: break;
							case 0x36: break;
							case 0x37: break;
							case 0x38: 
								vi_tri_con_tro_lcd--; // Nhảy xuống dòng cuối: dòng số 3
								break;
							case 0x39: break;
							
							case 0x23: // Phím CANCEL
								trang_cai_dat_duoc_lua_chon = 0; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
								break;
							case 0x2A: // Phím ENTER
								thong_ke_doanh_thu_nam();
								vi_tri_con_tro_lcd = 3;
								break;
						}						
						break;
					}
				}
			}
			thoat_cai_dat_xem_doanh_thu:
			{
				trang_cai_dat_duoc_lua_chon = 1;
			}
		}

		// CÁC HÀM CON CỦA MỤC CÀI ĐẶT: THỐNG KÊ DOANH THU: NĂM, THÁNG, NGÀY
		// ----------------------------------------------------------------------
		void MAY_BAN_HANG::thong_ke_doanh_thu_nam()
		{
			/** Xem địa chỉ của gói tin doanh thu hiện tại */
			unsigned int DC_goi_tin_DT_nam = EEPROM.read(ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[1]);
			DC_goi_tin_DT_nam = (DC_goi_tin_DT_nam<<8)|EEPROM.read(ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[0]);
			// Kiểm tra xem có tồn tại dữ liệu.
			bool da_co_dia_chi = false;
			{
				for(int i=0; i<31; i++)
				{
					if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[i]) 
					{
						da_co_dia_chi = true; // Đã có địa chỉ đúng
						break;
					}
				}
				if(da_co_dia_chi==true)
				{
					if(EEPROM.read(DC_goi_tin_DT_nam)!=0x01) 
					{
						da_co_dia_chi=false;
					}
				}
				if(da_co_dia_chi==false)
				{
					lcd_doanh_thu_nam(false);
					delay(3000);
					goto thoat_doanh_thu_nam;
				}
			}
			
			while (1)
			{
				doc_doanh_thu_nam_tu_EEPROM(DC_goi_tin_DT_nam);
				lcd_doanh_thu_nam(true);	// Hiển thị màn hình doanh thu LCD theo năm
				quet_ban_phim();
				switch(key)
				{
					case 0x00: break; 		// Không đọc được phím nào cả
					case 0x30: 				// Phím số 0: Xuống 1 dòng
					{
						for(unsigned char i=0; i<3; i++)
						{
							if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[i]) 
							{
								unsigned char j = i;
								// Bắt đầu kiểm tra từ ô nhớ thứ j và tăng dần
								while(1)
								{
									j++; // Tăng địa chỉ cần kiểm tra lên 1 đơn vị (mảng)	
									if(j==3) j=0;										
									DC_goi_tin_DT_nam = ADDR_BAT_DAU_GOI_TIN_DT_NAM[j];
									if(EEPROM.read(DC_goi_tin_DT_nam)!=0x01) 
									{
										// Không có gói tin => tiếp tục kiểm tra địa chỉ kế
									}
									else
									{
										// Có gói tin => thoát khỏi vòng lặp
										goto chuyen_trang_duoi_DT_nam;
									}
									if(j==i) 
									{
										goto chuyen_trang_duoi_DT_nam;
									}
								}
							}
						}
						chuyen_trang_duoi_DT_nam:
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
						for(unsigned char i=2; i>=0; i--)
						{
							if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[i]) 
							{
								unsigned char j = i;
								// Bắt đầu kiểm tra từ ô nhớ thứ j và tăng dần
								while(1)
								{
									j--; // Tăng địa chỉ cần kiểm tra lên 1 đơn vị (mảng)	
									if(j==255) j=2;										
									DC_goi_tin_DT_nam = ADDR_BAT_DAU_GOI_TIN_DT_NAM[j];
									if(EEPROM.read(DC_goi_tin_DT_nam)!=0x01) 
									{
										// Không có gói tin => tiếp tục kiểm tra địa chỉ kế
									}
									else
									{
										// Có gói tin => thoát khỏi vòng lặp
										goto chuyen_trang_tren_DT_nam;
									}
									if(j==i) 
									{
										goto chuyen_trang_tren_DT_nam;
									}
								}
							}
						}
						chuyen_trang_tren_DT_nam:						
						break;
					}
					case 0x39: break;
						
					case 0x23: // Phím CANCEL
						goto thoat_doanh_thu_nam;
						break;
					case 0x2A: break; // Phím ENTER
				}				
			}
			thoat_doanh_thu_nam:
			{
				// Không làm gì cả
			}
		}

		void MAY_BAN_HANG::doc_doanh_thu_nam_tu_EEPROM(unsigned int dia_chi_bat_dau) // Hàm đọc doanh thu từ 
		{
			Serial.println(dia_chi_bat_dau);
			if(EEPROM.read(dia_chi_bat_dau)==1) // Nếu có dữ liệu thì đọc dữ liệu
			{
				unsigned char o_nho[14]; // Dữ liệu được lưu gồm 10 byte
				for (int i=0; i<14; i++)
				{
					o_nho[i] = EEPROM.read(dia_chi_bat_dau+1+i);
				}
				nam_cua_o_nho = o_nho[1];
				nam_cua_o_nho = (nam_cua_o_nho<<8)|o_nho[0];
				
				tien_vao_nam = o_nho[5];
				tien_vao_nam = (tien_vao_nam<<8)|o_nho[4];
				tien_vao_nam = (tien_vao_nam<<8)|o_nho[3];
				tien_vao_nam = (tien_vao_nam<<8)|o_nho[2];
				doanh_thu_nam = o_nho[9];
				doanh_thu_nam = (doanh_thu_nam<<8)|o_nho[8];
				doanh_thu_nam = (doanh_thu_nam<<8)|o_nho[7];
				doanh_thu_nam = (doanh_thu_nam<<8)|o_nho[6];
				tien_ra_nam = o_nho[13];
				tien_ra_nam = (tien_ra_nam<<8)|o_nho[12];	
				tien_ra_nam = (tien_ra_nam<<8)|o_nho[11];	
				tien_ra_nam = (tien_ra_nam<<8)|o_nho[10];				
			}
		}
		
		// ----------------------------------------------------------------------
		void MAY_BAN_HANG::thong_ke_doanh_thu_thang()
		{
			/** Xem địa chỉ của gói tin doanh thu hiện tại */
			unsigned int DC_goi_tin_DT_thang = EEPROM.read(ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[1]);
			DC_goi_tin_DT_thang = (DC_goi_tin_DT_thang<<8)|EEPROM.read(ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[0]);
			// Kiểm tra xem có tồn tại dữ liệu.
			bool da_co_dia_chi = false;
			{
				for(int i=0; i<31; i++)
				{
					if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[i]) 
					{
						da_co_dia_chi = true; // Đã có địa chỉ đúng
						break;
					}
				}
				if(da_co_dia_chi==true)
				{
					if(EEPROM.read(DC_goi_tin_DT_thang)!=0x01) 
					{
						da_co_dia_chi=false;
					}
				}
				if(da_co_dia_chi==false)
				{
					lcd_doanh_thu_thang(false);
					delay(3000);
					goto thoat_doanh_thu_thang;
				}
			}
			
			while (1)
			{
				doc_doanh_thu_thang_tu_EEPROM(DC_goi_tin_DT_thang);
				lcd_doanh_thu_thang(true);	// Hiển thị màn hình doanh thu LCD theo năm
				quet_ban_phim();
				switch(key)
				{
					case 0x00: break; 		// Không đọc được phím nào cả
					case 0x30: 				// Phím số 0: Xuống 1 dòng
					{
						for(unsigned char i=0; i<13; i++)
						{
							if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[i]) 
							{
								unsigned char j = i;
								// Bắt đầu kiểm tra từ ô nhớ thứ j và tăng dần
								while(1)
								{
									j++; // Tăng địa chỉ cần kiểm tra lên 1 đơn vị (mảng)	
									if(j==13) j=0;										
									DC_goi_tin_DT_thang = ADDR_BAT_DAU_GOI_TIN_DT_THANG[j];
									if(EEPROM.read(DC_goi_tin_DT_thang)!=0x01) 
									{
										// Không có gói tin => tiếp tục kiểm tra địa chỉ kế
									}
									else
									{
										// Có gói tin => thoát khỏi vòng lặp
										goto chuyen_trang_duoi_DT_thang;
									}
									if(j==i) 
									{
										goto chuyen_trang_duoi_DT_thang;
									}
								}
							}
						}
						chuyen_trang_duoi_DT_thang:
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
						for(unsigned char i=12; i>=0; i--)
						{
							if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[i]) 
							{
								unsigned char j = i;
								// Bắt đầu kiểm tra từ ô nhớ thứ j và tăng dần
								while(1)
								{
									j--; // Tăng địa chỉ cần kiểm tra lên 1 đơn vị (mảng)	
									if(j==255) j=12;										
									DC_goi_tin_DT_thang = ADDR_BAT_DAU_GOI_TIN_DT_THANG[j];
									if(EEPROM.read(DC_goi_tin_DT_thang)!=0x01) 
									{
										// Không có gói tin => tiếp tục kiểm tra địa chỉ kế
									}
									else
									{
										// Có gói tin => thoát khỏi vòng lặp
										goto chuyen_trang_tren_DT_thang;
									}
									if(j==i) 
									{
										goto chuyen_trang_tren_DT_thang;
									}
								}
							}
						}
						chuyen_trang_tren_DT_thang:						
						break;
					}
					case 0x39: break;
						
					case 0x23: // Phím CANCEL
						goto thoat_doanh_thu_thang;
						break;
					case 0x2A: break; // Phím ENTER
				}				
			}
			thoat_doanh_thu_thang:
			{
				// Không làm gì cả
			}
		}
				
		void MAY_BAN_HANG::doc_doanh_thu_thang_tu_EEPROM(unsigned int dia_chi_bat_dau)
		{
			if(EEPROM.read(dia_chi_bat_dau)==1) // Nếu có dữ liệu thì đọc dữ liệu
			{
				unsigned char o_nho[15]; // Dữ liệu được lưu gồm 10 byte
				for (int i=0; i<15; i++)
				{
					o_nho[i] = EEPROM.read(dia_chi_bat_dau+1+i);
				}
				nam_cua_o_nho = o_nho[1];
				nam_cua_o_nho = (nam_cua_o_nho<<8)|o_nho[0];
				thang_cua_o_nho = o_nho[2];
				
				tien_vao_thang = o_nho[6];
				tien_vao_thang = (tien_vao_thang<<8)|o_nho[5];
				tien_vao_thang = (tien_vao_thang<<8)|o_nho[4];
				tien_vao_thang = (tien_vao_thang<<8)|o_nho[3];
				doanh_thu_thang = o_nho[10];
				doanh_thu_thang = (doanh_thu_thang<<8)|o_nho[9];
				doanh_thu_thang = (doanh_thu_thang<<8)|o_nho[8];
				doanh_thu_thang = (doanh_thu_thang<<8)|o_nho[7];
				tien_ra_thang = o_nho[14];
				tien_ra_thang = (tien_ra_thang<<8)|o_nho[13];	
				tien_ra_thang = (tien_ra_thang<<8)|o_nho[12];	
				tien_ra_thang = (tien_ra_thang<<8)|o_nho[11];				
			}
		}
		
		// ----------------------------------------------------------------------
		void MAY_BAN_HANG::thong_ke_doanh_thu_ngay()
		{
			/** Xem địa chỉ của gói tin doanh thu hiện tại */
			unsigned int DC_goi_tin_DT_ngay = EEPROM.read(ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[1]);
			DC_goi_tin_DT_ngay = (DC_goi_tin_DT_ngay<<8)|EEPROM.read(ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[0]);
			// Kiểm tra xem có tồn tại dữ liệu.
			bool da_co_dia_chi = false;
			{
				for(int i=0; i<31; i++)
				{
					if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i]) 
					{
						da_co_dia_chi = true; // Đã có địa chỉ đúng
						break;
					}
				}
				if(da_co_dia_chi==true)
				{
					if(EEPROM.read(DC_goi_tin_DT_ngay)!=0x01) 
					{
						da_co_dia_chi=false;
					}
				}
				if(da_co_dia_chi==false)
				{
					lcd_doanh_thu_ngay(false);
					delay(3000);
					goto thoat_doanh_thu_ngay;
				}
			}
			
			while (1)
			{
				doc_doanh_thu_ngay_tu_EEPROM(DC_goi_tin_DT_ngay);
				lcd_doanh_thu_ngay(true);	// Hiển thị màn hình doanh thu LCD theo năm
				quet_ban_phim();
				switch(key)
				{
					case 0x00: break; 		// Không đọc được phím nào cả
					case 0x30: 				// Phím số 0: Xuống 1 dòng
					{
						for(unsigned char i=0; i<31; i++)
						{
							if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i]) 
							{
								unsigned char j = i;
								// Bắt đầu kiểm tra từ ô nhớ thứ j và tăng dần
								while(1)
								{
									j++; // Tăng địa chỉ cần kiểm tra lên 1 đơn vị (mảng)	
									if(j==31) j=0;										
									DC_goi_tin_DT_ngay = ADDR_BAT_DAU_GOI_TIN_DT_NGAY[j];
									if(EEPROM.read(DC_goi_tin_DT_ngay)!=0x01) 
									{
										// Không có gói tin => tiếp tục kiểm tra địa chỉ kế
									}
									else
									{
										// Có gói tin => thoát khỏi vòng lặp
										goto chuyen_trang_duoi_DT_ngay;
									}
									if(j==i) 
									{
										goto chuyen_trang_duoi_DT_ngay;
									}
								}
							}
						}
						chuyen_trang_duoi_DT_ngay:
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
						for(unsigned char i=30; i>=0; i--)
						{
							if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i]) 
							{
								unsigned char j = i;
								// Bắt đầu kiểm tra từ ô nhớ thứ j và tăng dần
								while(1)
								{
									j--; // Tăng địa chỉ cần kiểm tra lên 1 đơn vị (mảng)	
									if(j==255) j=30;										
									DC_goi_tin_DT_ngay = ADDR_BAT_DAU_GOI_TIN_DT_NGAY[j];
									if(EEPROM.read(DC_goi_tin_DT_ngay)!=0x01) 
									{
										// Không có gói tin => tiếp tục kiểm tra địa chỉ kế
									}
									else
									{
										// Có gói tin => thoát khỏi vòng lặp
										goto chuyen_trang_tren_DT_ngay;
									}
									if(j==i) 
									{
										goto chuyen_trang_tren_DT_ngay;
									}
								}
							}
						}
						chuyen_trang_tren_DT_ngay:						
						break;
					}
					case 0x39: break;
						
					case 0x23: // Phím CANCEL
						goto thoat_doanh_thu_ngay;
						break;
					case 0x2A: break; // Phím ENTER
				}				
			}
			thoat_doanh_thu_ngay:
			{
				
			}
		}
			
		void MAY_BAN_HANG::doc_doanh_thu_ngay_tu_EEPROM(unsigned int dia_chi_bat_dau)
		{
			unsigned char o_nho[10]; // Dữ liệu được lưu gồm 10 byte
			for (unsigned char i=0; i<10; i++)
			{
				o_nho[i] = EEPROM.read(dia_chi_bat_dau+1+i);
			}
			nam_cua_o_nho = o_nho[1];
			nam_cua_o_nho = (nam_cua_o_nho<<8)|o_nho[0];
			thang_cua_o_nho = o_nho[2];
			ngay_cua_o_nho = o_nho[3];
			tien_vao_ngay = o_nho[5];
			tien_vao_ngay = (tien_vao_ngay<<8)|o_nho[4];
			doanh_thu_ngay = o_nho[7];
			doanh_thu_ngay = (doanh_thu_ngay<<8)|o_nho[6];
			tien_ra_ngay = o_nho[9];
			tien_ra_ngay = (tien_ra_ngay<<8)|o_nho[8];
		}

		
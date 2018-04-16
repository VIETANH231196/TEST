/*
	Phần tính toán và lưu doanh thu, tiền ra, tiền vào trong quá trình thanh toán
*/

#include <MBH.h>

// Đầu vào: Số dư lúc trước, số tiền đưa vào, số tiền trả lại, số dư lúc sau - Thời gian: các ngày phân biệt nhau - thời gian thực
// unsigned int so_tien_nuot_vao, so_du_luc_truoc, so_tien_tra_lai, so_du_luc_sau;

// Đầu ra: Tổng số tiền vào trong 1 ngày, tổng doanh thu trong 1 ngày, tổng số tiền trả lại trong 1 ngày lưu trong 1 ngăn bộ nhớ
// unsigned int tien_vao_ngay, doanh_thu_ngay, tien_ra_ngay;

void MAY_BAN_HANG::tinh_va_luu_doanh_thu()
{
	/** B1: Xác định tổng số gói tin ở thời điểm này và địa chỉ gói tin lưu doanh thu hôm nay */
	/*  1. Ngày */
	unsigned int DC_goi_tin_DT_ngay = EEPROM.read(ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[1]);
	DC_goi_tin_DT_ngay = (DC_goi_tin_DT_ngay<<8)|EEPROM.read(ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[0]);
	// So sánh địa chỉ gói tin hiện tại và các địa chỉ bắt đầu trong mảng
	{
		bool da_co_dia_chi = false;
		for(unsigned char i=0; i<31; i++)
		{
			if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i]) 
			{
				da_co_dia_chi = true; // Đã có địa chỉ đúng
				break;
			}
		}
		if(da_co_dia_chi==false)
		{
			DC_goi_tin_DT_ngay = ADDR_BAT_DAU_GOI_TIN_DT_NGAY[0];
		}
	}
	/*  2. Tháng */
	unsigned int DC_goi_tin_DT_thang = EEPROM.read(ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[1]);
	DC_goi_tin_DT_thang = (DC_goi_tin_DT_thang<<8)|EEPROM.read(ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[0]);
	{
		bool da_co_dia_chi = false;
		for(unsigned char i=0; i<13; i++)
		{
			if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[i]) 
			{
				da_co_dia_chi = true; // Đã có địa chỉ đúng
				break;
			}
		}
		if(da_co_dia_chi==false)
		{
			DC_goi_tin_DT_thang = ADDR_BAT_DAU_GOI_TIN_DT_THANG[0];
		}
	}
	/*  3. Năm */
	unsigned int DC_goi_tin_DT_nam = EEPROM.read(ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[1]);
	DC_goi_tin_DT_nam = (DC_goi_tin_DT_nam<<8)|EEPROM.read(ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[0]);
	{
		bool da_co_dia_chi = false;
		for(unsigned char i=0; i<3; i++)
		{
			if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[i]) 
			{
				da_co_dia_chi = true; // Đã có địa chỉ đúng
				break;
			}
		}
		if(da_co_dia_chi==false)
		{
			DC_goi_tin_DT_nam = ADDR_BAT_DAU_GOI_TIN_DT_NAM[0];
		}
	}
	/** B2: So sánh với thời gian thực ********************************************************/
	Rtc.readDS1307();
	ngay_hom_nay = Rtc.day; thang_nay = Rtc.month; nam_nay = Rtc.year;		// Đọc ngày tháng năm từ thời gian thực
	// Đọc giá trị ngày/tháng/năm ở mảng ô nhớ lưu doanh thu hôm nay (coi là ngày hôm qua)
	/*  1. Ngày */
	{ 
		unsigned char o_nho[5];
		for(unsigned char i=0; i<5; i++) 	// Tạm thời không dùng giá trị trong ô nhớ đầu tiên
		{
			o_nho[i] = EEPROM.read(DC_goi_tin_DT_ngay+i);
		}
		nam_cua_o_nho = o_nho[2];
		nam_cua_o_nho = nam_cua_o_nho<<8|o_nho[1];
		thang_cua_o_nho = o_nho[3];
		ngay_cua_o_nho = o_nho[4];
			// Serial.print(nam_cua_o_nho); Serial.print("/");
			// Serial.print(thang_cua_o_nho); Serial.print("/");
			// Serial.println(ngay_cua_o_nho);
		// So sánh thời gian trong ô nhớ với thời gian thực để xác định ngày được lưu trong ô nhớ có phải hôm nay không
			// Serial.print(nam_nay); Serial.print("/");
			// Serial.print(thang_nay); Serial.print("/");
			// Serial.println(ngay_hom_nay);
		if((ngay_hom_nay==ngay_cua_o_nho)&&(thang_nay==thang_cua_o_nho)&&(nam_nay==nam_cua_o_nho))
		{
			// DC_goi_tin_DT_ngay không đổi
		}
		else // Nếu đã sang ngày khác thì lưu gói tin mới -> địa chỉ mới -> xóa dữ liệu tại ô đó và ô sau
		{
			// Trỏ đến địa chỉ ô nhớ tiếp theo
			if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[30])
			{
				DC_goi_tin_DT_ngay = ADDR_BAT_DAU_GOI_TIN_DT_NGAY[0];
			}
			else
			{
				for(unsigned char i=0; i<30; i++)
				{
					if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i]) 
					{
						DC_goi_tin_DT_ngay = ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i+1];
						break;
					}
				}
			}
			
			EEPROM.write(ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[0], (unsigned char)DC_goi_tin_DT_ngay); delay(5);
			EEPROM.write(ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[1], (unsigned char)(DC_goi_tin_DT_ngay>>8)); delay(5);
			// Xóa gói tin tại điểm mới và đứng ngay sau nó, tạo chỗ trống về sau.
			// ------------------------------------------------------------------
			if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[30])
			{
				xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NGAY[30], 11);
				xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NGAY[0], 11);
			}
			else
			{
				for(unsigned char i=0; i<30; i++)
				{
					if(DC_goi_tin_DT_ngay==ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i]) 
					{
						xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i], 11);
						xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NGAY[i+1], 11);
						break;
					}
				}			
			}	
		}
	}
	/*  2. Tháng */
	{
		unsigned char o_nho[4];
		for(unsigned char i=0; i<4; i++) 	// Tạm thời không dùng giá trị trong ô nhớ đầu tiên
		{
			o_nho[i] = EEPROM.read(DC_goi_tin_DT_thang+i);
		}
		nam_cua_o_nho = o_nho[2];
		nam_cua_o_nho = nam_cua_o_nho<<8|o_nho[1];
		thang_cua_o_nho = o_nho[3];
		// So sánh thời gian trong ô nhớ với thời gian thực để xác định ngày được lưu trong ô nhớ có phải hôm nay không
		if((thang_nay==thang_cua_o_nho)&&(nam_nay==nam_cua_o_nho))
		{
			// DC_goi_tin_DT_thang không đổi
		}
		else // Nếu đã sang ngày khác thì lưu gói tin mới -> địa chỉ mới -> xóa dữ liệu tại ô đó và ô sau
		{
			// Trỏ đến địa chỉ ô nhớ tiếp theo
			if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[12])
			{
				DC_goi_tin_DT_thang = ADDR_BAT_DAU_GOI_TIN_DT_THANG[0];
			}
			else
			{
				for(unsigned char i=0; i<12; i++)
				{
					if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[i]) 
					{
						DC_goi_tin_DT_thang = ADDR_BAT_DAU_GOI_TIN_DT_THANG[i+1];
						break;
					}
				}
			}
			
			EEPROM.write(ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[0], (unsigned char)DC_goi_tin_DT_thang); delay(5);
			EEPROM.write(ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[1], (unsigned char)(DC_goi_tin_DT_thang>>8)); delay(5);
			// Xóa gói tin tại điểm mới và đứng ngay sau nó, tạo chỗ trống về sau.
			// ------------------------------------------------------------------
			if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[12])
			{
				xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_THANG[12], 16);
				xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_THANG[0], 16);
			}
			else
			{
				for(unsigned char i=0; i<12; i++)
				{
					if(DC_goi_tin_DT_thang==ADDR_BAT_DAU_GOI_TIN_DT_THANG[i]) 
					{
						xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_THANG[i], 16);
						xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_THANG[i+1], 16);
						break;
					}
				}			
			}	
		}		
	}
	/*  3. Năm */
	{
		unsigned char o_nho[3];
		for(unsigned char i=0; i<3; i++) 	// Tạm thời không dùng giá trị trong ô nhớ đầu tiên
		{
			o_nho[i] = EEPROM.read(DC_goi_tin_DT_nam+i);
		}
		nam_cua_o_nho = o_nho[2];
		nam_cua_o_nho = nam_cua_o_nho<<8|o_nho[1];
		// So sánh thời gian trong ô nhớ với thời gian thực để xác định ngày được lưu trong ô nhớ có phải hôm nay không
		if(nam_nay==nam_cua_o_nho)
		{
			// DC_goi_tin_DT_nam không đổi
		}
		else // Nếu đã sang ngày khác thì lưu gói tin mới -> địa chỉ mới -> xóa dữ liệu tại ô đó và ô sau
		{
			Serial.println(DC_goi_tin_DT_nam);
			// Trỏ đến địa chỉ ô nhớ tiếp theo
			if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[2])
			{
				DC_goi_tin_DT_nam = ADDR_BAT_DAU_GOI_TIN_DT_NAM[0];
			}
			else
			{
				for(unsigned char i=0; i<2; i++)
				{
					if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[i]) 
					{
						DC_goi_tin_DT_nam = ADDR_BAT_DAU_GOI_TIN_DT_NAM[i+1];
						break;
					}
				}
			}
			
			EEPROM.write(ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[0], (unsigned char)DC_goi_tin_DT_nam); delay(5);
			EEPROM.write(ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[1], (unsigned char)(DC_goi_tin_DT_nam>>8)); delay(5);
			// Xóa gói tin tại điểm mới và đứng ngay sau nó, tạo chỗ trống về sau.
			// ------------------------------------------------------------------
			if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[2])
			{
				xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NAM[2], 15);
				xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NAM[0], 15);
			}
			else
			{
				for(unsigned char i=0; i<2; i++)
				{
					if(DC_goi_tin_DT_nam==ADDR_BAT_DAU_GOI_TIN_DT_NAM[i]) 
					{
						xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NAM[i], 15);
						xoa_goi_tin_EEPROM(ADDR_BAT_DAU_GOI_TIN_DT_NAM[i+1], 15);
						break;
					}
				}			
			}	
		}		
	}
	tinh_DT_ngay(DC_goi_tin_DT_ngay);
	tinh_DT_thang(DC_goi_tin_DT_thang);
	tinh_DT_nam(DC_goi_tin_DT_nam);
}

void MAY_BAN_HANG::tinh_DT_ngay(unsigned int dia_chi_bat_dau) 	// Tính toán DT ngày/tháng/năm dựa trên 1 lần mua thành công
{
	unsigned char tong_so_goi_tin = EEPROM.read(ADDR_TONG_SO_GOI_TIN);
	
	/** Tính doanh thu 1 lần mua hàng -------------------------------- */
	doanh_thu_1_lan_mua_hang = so_du_luc_truoc + so_tien_nuot_vao - so_tien_tra_lai - so_du_luc_sau; // Tính toán doanh thu 1 lần mua hàng
	Serial.println(so_du_luc_truoc); Serial.println(so_tien_nuot_vao); Serial.println(so_tien_tra_lai); Serial.println(so_du_luc_sau);
	
	/** Đọc cả gói tin ----------------------------------------------- */
	unsigned char o_nho[11];
	for(int i=0; i<11; i++)
	{
		o_nho[i] = EEPROM.read(dia_chi_bat_dau+i);
	}
	{	// Chuyển đổi từ byte đơn lẻ sang số nguyên
		tien_vao_ngay = o_nho[6];
		tien_vao_ngay = (tien_vao_ngay<<8)|o_nho[5];
		doanh_thu_ngay = o_nho[8];
		doanh_thu_ngay = (doanh_thu_ngay<<8)|o_nho[7];	
		tien_ra_ngay = o_nho[10];
		tien_ra_ngay = (tien_ra_ngay<<8)|o_nho[9];
	}
	/** Tính doanh thu cả ngày --------------------------------------- */
	tien_vao_ngay+=so_tien_nuot_vao; doanh_thu_ngay+=doanh_thu_1_lan_mua_hang; tien_ra_ngay+=so_tien_tra_lai;
	
	/** Lưu doanh thu cả ngày lại vào bộ nhớ EEPROM ------------------ */
	for (unsigned char i=0; i<11; i++) // Xóa mảng, lưu lại
	{
		o_nho[i] = 0x00; 
	}
	{ 	// Chuyển dữ liệu sang dạng byte để ghi vào ô nhớ
		o_nho[0] = 0x01;
		o_nho[1] = nam_nay;
		o_nho[2] = nam_nay>>8;
		o_nho[3] = thang_nay;
		o_nho[4] = ngay_hom_nay;
		o_nho[5] = tien_vao_ngay;
		o_nho[6] = tien_vao_ngay>>8;
		o_nho[7] = doanh_thu_ngay;
		o_nho[8] = doanh_thu_ngay>>8;		
		o_nho[9] = tien_ra_ngay;
		o_nho[10] = tien_ra_ngay>>8;
	}	
	{	// In ra màn hình Serial để kiểm tra kết quả
		Serial.print(nam_nay);
		Serial.print("/");
		Serial.print(thang_nay);
		Serial.print("/");
		Serial.print(ngay_hom_nay);
		Serial.println(":");
		Serial.print("Số tiền nuốt vào là: ");
		Serial.print(tien_vao_ngay);
		Serial.print("Doanh thu là: ");
		Serial.print(doanh_thu_ngay);
		Serial.print("Số tiền trả lại là: ");
		Serial.println(tien_ra_ngay);	
	}
	tien_vao_ngay = 0; doanh_thu_ngay = 0; tien_ra_ngay = 0; // Reset các biến
	
	for(int i=0; i<11; i++)
	{
		EEPROM.write(dia_chi_bat_dau+i, o_nho[i]); delay(5);
	}
}

void MAY_BAN_HANG::tinh_DT_thang(unsigned int dia_chi_bat_dau)
{
	unsigned char tong_so_goi_tin = EEPROM.read(ADDR_TONG_SO_GOI_TIN_DT_THANG);
	
	/** Tính doanh thu 1 lần mua hàng -------------------------------- */
	doanh_thu_1_lan_mua_hang = so_du_luc_truoc + so_tien_nuot_vao - so_tien_tra_lai - so_du_luc_sau; // Tính toán doanh thu 1 lần mua hàng
	// Serial.println(so_du_luc_truoc); Serial.println(so_tien_nuot_vao); Serial.println(so_tien_tra_lai); Serial.println(so_du_luc_sau);
	
	/** Đọc cả gói tin ----------------------------------------------- */
	unsigned char o_nho[16];
	for(int i=0; i<16; i++)
	{
		o_nho[i] = EEPROM.read(dia_chi_bat_dau+i);
	}
	{	// Chuyển đổi từ byte đơn lẻ sang số nguyên
		tien_vao_thang = o_nho[7];
		tien_vao_thang = (tien_vao_thang<<8)|o_nho[6];
		tien_vao_thang = (tien_vao_thang<<8)|o_nho[5];
		tien_vao_thang = (tien_vao_thang<<8)|o_nho[4];
		doanh_thu_thang = o_nho[11];
		doanh_thu_thang = (doanh_thu_thang<<8)|o_nho[10];	
		doanh_thu_thang = (doanh_thu_thang<<8)|o_nho[9];
		doanh_thu_thang = (doanh_thu_thang<<8)|o_nho[8];
		tien_ra_thang = o_nho[15];
		tien_ra_thang = (tien_ra_thang<<8)|o_nho[14];
		tien_ra_thang = (tien_ra_thang<<8)|o_nho[13];
		tien_ra_thang = (tien_ra_thang<<8)|o_nho[12];
	}
	/** Tính doanh thu cả ngày --------------------------------------- */
	tien_vao_thang+=so_tien_nuot_vao; doanh_thu_thang+=doanh_thu_1_lan_mua_hang; tien_ra_thang+=so_tien_tra_lai;
	
	/** Lưu doanh thu cả ngày lại vào bộ nhớ EEPROM ------------------ */
	for (unsigned char i=0; i<16; i++) // Xóa mảng, lưu lại
	{
		o_nho[i] = 0x00; 
	}
	{ 	// Chuyển dữ liệu sang dạng byte để ghi vào ô nhớ
		o_nho[0] = 0x01;
		o_nho[1] = nam_nay;
		o_nho[2] = nam_nay>>8;
		o_nho[3] = thang_nay;
		o_nho[4] = tien_vao_thang;
		o_nho[5] = tien_vao_thang>>8;
		o_nho[6] = tien_vao_thang>>16;
		o_nho[7] = tien_vao_thang>>24;
		o_nho[8] = doanh_thu_thang;
		o_nho[9] = doanh_thu_thang>>8;		
		o_nho[10] = doanh_thu_thang>>16;
		o_nho[11] = doanh_thu_thang>>24;
		o_nho[12] = tien_ra_thang;
		o_nho[13] = tien_ra_thang>>8;
		o_nho[14] = tien_ra_thang>>16;
		o_nho[15] = tien_ra_thang>>24;
	}	
	{	// In ra màn hình Serial để kiểm tra kết quả
		/*Serial.print(nam_nay);
		Serial.print("/");
		Serial.print(thang_nay);
		Serial.println(":");
		Serial.print("Số tiền nuốt vào tháng là: ");
		Serial.print(tien_vao_thang);
		Serial.print("Doanh thu tháng là: ");
		Serial.print(doanh_thu_thang);
		Serial.print("Số tiền trả lại tháng là: ");
		Serial.println(tien_ra_thang);	*/
	}
	tien_vao_thang = 0; doanh_thu_thang = 0; tien_ra_thang = 0; // Reset các biến
	
	for(int i=0; i<16; i++)
	{
		EEPROM.write(dia_chi_bat_dau+i, o_nho[i]); delay(5);
	}	
}

void MAY_BAN_HANG::tinh_DT_nam(unsigned int dia_chi_bat_dau)
{
	unsigned char tong_so_goi_tin = EEPROM.read(ADDR_TONG_SO_GOI_TIN_DT_NAM);
	
	/** Tính doanh thu 1 lần mua hàng -------------------------------- */
	doanh_thu_1_lan_mua_hang = so_du_luc_truoc + so_tien_nuot_vao - so_tien_tra_lai - so_du_luc_sau; // Tính toán doanh thu 1 lần mua hàng
	// Serial.println(so_du_luc_truoc); Serial.println(so_tien_nuot_vao); Serial.println(so_tien_tra_lai); Serial.println(so_du_luc_sau);
	
	/** Đọc cả gói tin ----------------------------------------------- */
	unsigned char o_nho[15];
	for(int i=0; i<15; i++)
	{
		o_nho[i] = EEPROM.read(dia_chi_bat_dau+i);
	}
	{	// Chuyển đổi từ byte đơn lẻ sang số nguyên
		tien_vao_nam = o_nho[6];
		tien_vao_nam = (tien_vao_nam<<8)|o_nho[5];
		tien_vao_nam = (tien_vao_nam<<8)|o_nho[4];
		tien_vao_nam = (tien_vao_nam<<8)|o_nho[3];
		doanh_thu_nam = o_nho[10];
		doanh_thu_nam = (doanh_thu_nam<<8)|o_nho[9];
		doanh_thu_nam = (doanh_thu_nam<<8)|o_nho[8];
		doanh_thu_nam = (doanh_thu_nam<<8)|o_nho[7];		
		tien_ra_nam = o_nho[14];
		tien_ra_nam = (tien_ra_nam<<8)|o_nho[13];
		tien_ra_nam = (tien_ra_nam<<8)|o_nho[12];
		tien_ra_nam = (tien_ra_nam<<8)|o_nho[11];
	}
	/** Tính doanh thu cả ngày --------------------------------------- */
	tien_vao_nam+=so_tien_nuot_vao; doanh_thu_nam+=doanh_thu_1_lan_mua_hang; tien_ra_nam+=so_tien_tra_lai;
	
	/** Lưu doanh thu cả ngày lại vào bộ nhớ EEPROM ------------------ */
	for (unsigned char i=0; i<15; i++) // Xóa mảng, lưu lại
	{
		o_nho[i] = 0x00; 
	}
	{ 	// Chuyển dữ liệu sang dạng byte để ghi vào ô nhớ
		o_nho[0] = 0x01;
		o_nho[1] = nam_nay;
		o_nho[2] = nam_nay>>8;
		o_nho[3] = tien_vao_nam;
		o_nho[4] = tien_vao_nam>>8;
		o_nho[5] = tien_vao_nam>>16;
		o_nho[6] = tien_vao_nam>>24;
		o_nho[7] = doanh_thu_nam;
		o_nho[8] = doanh_thu_nam>>8;		
		o_nho[9] = doanh_thu_nam>>16;
		o_nho[10] = doanh_thu_nam>>24;
		o_nho[11] = tien_ra_nam;
		o_nho[12] = tien_ra_nam>>8;		
		o_nho[13] = tien_ra_nam>>16;
		o_nho[14] = tien_ra_nam>>24;		
	}	
	{	// In ra màn hình Serial để kiểm tra kết quả
		/* Serial.print(nam_nay);
		Serial.println(":");
		Serial.print("Số tiền nuốt vào năm là: ");
		Serial.print(tien_vao_nam);
		Serial.print("Doanh thu năm là: ");
		Serial.print(doanh_thu_nam);
		Serial.print("Số tiền trả lại năm là: ");
		Serial.println(tien_ra_nam);	*/
	}
	tien_vao_nam = 0; doanh_thu_nam = 0; tien_ra_nam = 0; // Reset các biến
	
	for(int i=0; i<15; i++)
	{
		EEPROM.write(dia_chi_bat_dau+i, o_nho[i]); delay(5);
	}	
}

// =========================================================================
void MAY_BAN_HANG::xoa_goi_tin_EEPROM(unsigned int dia_chi_bat_dau, unsigned char kich_thuoc)
{
	for (int DC=dia_chi_bat_dau; DC<dia_chi_bat_dau+kich_thuoc; DC++)
	{
		EEPROM.write(DC, 0x00); delay(5);
	}
}

void MAY_BAN_HANG::kiem_tra_bo_nho()
{
	for(int i=498; i<842; i++)
	{
		Serial.print(i);
		Serial.print("		");
		Serial.println(EEPROM.read(i));
	}
	for(int i=1198; i<1400; i++)
	{
		Serial.print(i);
		Serial.print("		");
		Serial.println(EEPROM.read(i));		
	}
	for(int i=1598; i<1646; i++)
	{
		Serial.print(i);
		Serial.print("		");
		Serial.println(EEPROM.read(i));		
	}	
}




#include <MBH.h>
#include <bien_he_thong/bien_he_thong.h>

void MAY_BAN_HANG::gui_lenh_cho_nv11()
{
	if(dem_thoi_gian_quet_phim%15000==0)
	{
		if(trang_thai_dau_ngam==khong_co_tien) // Không có tiền được giữ ở đầu ngậm
			Nv11.gui_lenh_tham_do();
		else
			Nv11.gui_lenh_giu_tien();
		trang_thai_gui_goi_tin = da_gui;
	}
}

void MAY_BAN_HANG::doc_ban_phim()
{
	key = 0;
	while (key==0x00)
	{
		key = keypad.getKey(); 								// Quét bàn phím

		dem_thoi_gian_quet_phim++;
		trang_thai_ban_phim();
		
		dem_thoi_gian_khong_nhan_phim();
		trang_thai_chon_hang();

		if (dem_thoi_gian_quet_phim%5000==0) break;
	}
	thong_bao_lcd_neu_chon_o_hang_sai();
}

//---------------------------------------------------
void MAY_BAN_HANG::doc_tien()
{
	if(trang_thai_gui_goi_tin == da_gui)
	{
		Nv11.receive(); // Nhận câu trả lời thăm dò
		if(trang_thai_dau_ngam==khong_co_tien) // Không có tiền được giữ ở đầu ngậm
			phan_tich_cau_tra_loi_tham_do();
		else // Có tiền được giữ ở đầu ngậm
			phan_tich_cau_tra_loi_giu_tien();
		
		if (menh_gia_tien_dang_giu!=0) // Nếu mệnh giá != 0 nghĩa là đang có tiền trong đầu ngậm
			trang_thai_dau_ngam = co_tien;
		else
			trang_thai_dau_ngam = khong_co_tien;
		trang_thai_gui_goi_tin = chua_gui;
	}
}

void MAY_BAN_HANG::phan_tich_cau_tra_loi_giu_tien()
{
	switch (Nv11.ERX[5])
	{
		case 0xF0: 	trang_thai_dau_ngam = co_tien; 		break;
		case 0xF5: 	trang_thai_dau_ngam = khong_co_tien; 
					menh_gia_tien_dang_giu = 0;
					tai_khoan = EEPROM.read(ADDR_TAI_KHOAN[1]);
					tai_khoan = (tai_khoan<<8)|(EEPROM.read(ADDR_TAI_KHOAN[0]));
					// Không lưu tài khoản khi giữ tiền
					// EEPROM.write(ADDR_TAI_KHOAN, tai_khoan); delay(5);
					break;
	}
}

void MAY_BAN_HANG::phan_tich_cau_tra_loi_tham_do()
{
	if(Nv11.ERX[5]!=0xF0)
	{
		return false;
	}
	else
	{
		for(unsigned char i=6; i<Nv11.ERX[0]+5; i++) // ERX[0] là độ dài gói câu trả lời nhận được
		{ // Dữ liệu gói tin bắt đầu được lưu từ byte thứ 6 trong mảng
			switch(Nv11.ERX[i]) // Nv11.ERX[5] = 0xF0, bắt đầu tính từ byte Nv11.ERX[6]
			{
/* 1 */			case 0xF1:	// NV11 đang khởi động
				{
					break;
				}
/* 2 */			case 0xEF:	// NV11 đang đọc giá trị tiền
				{
					switch(Nv11.ERX[i+1]) // Phân tích byte tiếp theo
					{
						case 0: menh_gia_tien_dang_giu = 0; break;
						case 1: menh_gia_tien_dang_giu = 1; break;
						case 2: menh_gia_tien_dang_giu = 2; break;
						case 3: menh_gia_tien_dang_giu = 5; break;
						case 4: menh_gia_tien_dang_giu = 10; break;
						case 5: menh_gia_tien_dang_giu = 20; break;
						case 6: menh_gia_tien_dang_giu = 50; break;
						case 7: menh_gia_tien_dang_giu = 100; break;
						case 8: menh_gia_tien_dang_giu = 200; break;
						case 9: menh_gia_tien_dang_giu = 500; break;
					}
					if(Nv11.ERX[i+1]!=0)
					{
						// Serial.print("Tiền trong ngăn chứa: ");
						// Serial.println(menh_gia_tien_dang_giu);	
						tai_khoan += menh_gia_tien_dang_giu;
						if(tai_khoan>1000)// Nếu tài khoản lớn hơn 1 triệu thì từ chối tờ tiền
							Nv11.tu_choi_tien();
						// Do chưa nuốt hẳn tiền nên k lưu vào bộ nhớ
						// Serial.print("Tài khoản là: ");
						// Serial.println(tai_khoan);
					}
					trang_thai_cua_nv11 = _dang_nhan_dang_tien;
					i++;
					break;
				}
/* 3 */			case 0xEE:	// NV11 Credit
				{
					switch(Nv11.ERX[i+1]) // Phân tích byte tiếp theo
					{
						case 0: menh_gia_tien_da_nuot = 0; break;
						case 1: menh_gia_tien_da_nuot = 1; break;
						case 2: menh_gia_tien_da_nuot = 2; break;
						case 3: menh_gia_tien_da_nuot = 5; break;
						case 4: menh_gia_tien_da_nuot = 10; break;
						case 5: menh_gia_tien_da_nuot = 20; break;
						case 6: menh_gia_tien_da_nuot = 50; break;
						case 7: menh_gia_tien_da_nuot = 100; break;
						case 8: menh_gia_tien_da_nuot = 200; break;
						case 9: menh_gia_tien_da_nuot = 500; break;
					}
					if(Nv11.ERX[i+1]!=0)
					{
						// Serial.print("Tiền đã nuốt: ");
						// Serial.println(menh_gia_tien_da_nuot);	
					}
					trang_thai_dau_ngam = khong_co_tien;
					trang_thai_cua_nv11 = _da_credited;
					i++;					
					break;
				}
/* 4 */			case 0xED:	// Đang từ chối
				{
					//Serial.print("Tài khoản là: ");
					//Serial.println(tai_khoan);
					trang_thai_dau_ngam = khong_co_tien;					
					trang_thai_cua_nv11 = _dang_tu_choi_tien;				
					break;
				}
/* 5 */			case 0xEC:	// Đã từ chối
				{
					tai_khoan -= menh_gia_tien_dang_giu;
					menh_gia_tien_dang_giu = 0;				
					// Cập nhật lại dữ liệu
					//Serial.print("Tài khoản là: ");
					//Serial.println(tai_khoan);	
					trang_thai_dau_ngam = khong_co_tien;
					trang_thai_cua_nv11	= _da_tu_choi_to_tien;				
					break;
				}
/* 6 */			case 0xCC:	// Đang nuốt tiền
				{	
					trang_thai_dau_ngam = khong_co_tien;
					//Serial.print("Tài khoản là: ");
					//Serial.println(tai_khoan);	
					trang_thai_cua_nv11	= _dang_nuot_tien;				
					break;
				}
/* 7 */			case 0xEB:	// Đã đưa tiền xuống Stacker
				{
					//tai_khoan -= menh_gia_tien_dang_giu;
					menh_gia_tien_dang_giu = 0;	
					trang_thai_dau_ngam = khong_co_tien;
					trang_thai_cua_nv11 = _da_dua_tien_xuong_stack;
					//Serial.print("Tài khoản là: ");
					//Serial.println(tai_khoan);						
					break;
				}
/* 8 */			case 0xEA:	// 
					break;
/* 9 */			case 0xE9:	//
					break;
/* 10 */		case 0xE8:	//
					trang_thai_cua_nv11 = _da_mat_ket_noi;
					Nv11.enable();
					break;
/* 11 */		case 0xE6:	break;//				
/* 12 */		case 0xE7:	break;//				
/* 13 */		case 0xE1:	break;//				
/* 14 */		case 0xE2:	break;//				
/* 15 */		case 0xE3:	break;//				
/* 16 */		case 0xE4:	break;//
/* 17 */		case 0xDB:	//
					trang_thai_dau_ngam = khong_co_tien;
					menh_gia_tien_dang_giu = 0;	
					trang_thai_cua_nv11 = _da_dua_tien_len_note_float;
					break;
/* 18 */		case 0xDA:	break;//
/* 19 */		case 0xD2:	break;//
/* 20 */		case 0xC9:	break;//
/* 21 */		case 0xC3:	break;//
/* 22 */		case 0xCA:	break;//
/* 23 */		case 0xCB:	break;//
/* 24 */		case 0xCD:	break;//
/* 25 */		case 0xC6:	break;//
/* 26 */		case 0xC7:	break;//
/* 27 */		case 0xC8:	break;//
/* 28 */		case 0xCE:	break;//
/* 29 */		case 0xCF:	break;//
/* 30 */		case 0xB5:	break;//
			}
			if(i>=15) break; // Không phân tích các byte lớn hơn 15
		}
	}	
}

//---------------------------------------------------
unsigned char MAY_BAN_HANG::trang_thai_ban_phim()
{
	if ((key==0)&&(phim_1==0)&&(phim_2==0)&&(phim==0))
	{
		//Trạng thái 0: ban đầu của bàn phím: Không nhấn gì cả
		man_hinh = trang_0;
		return 0;
	}
	else if((key>0x2F)&&(key<0x3A)&&(phim_1==0)&&(phim_2==0)&&(phim==0))
	{//Nếu key có giá trị 0 đến 9 và phim1 = 0 và phím 2 =0 và phím = 0
		//Trạng thái 1: Nhấn phím đầu tiên
		phim_1 = key;
		man_hinh = trang_1;
		return 1;
	}
	else if((key==0)&&(phim_1>0x2F)&&(phim_1<0x3A)&&(phim_2==0)&&(phim==0))
	{
		//Trạng thái 2: Nhả phím đầu tiên
		man_hinh = trang_1;
		return 2;
	}
	else if((key>0x2F)&&(key<0x3A)&&(phim_1>0x2F)&&(phim_1<0x3A)&&(phim_2==0)&&(phim==0))
	{
		//Trạng thái 3: Nhấn phím tiếp theo
		phim_2 = key;
		return 3;
	}
	else if((key==0)&&(phim_1>0x2F)&&(phim_1<0x3A)&&(phim_2>0x2F)&&(phim_2<0x3A)&&(phim==0))
	{
		//Trạng thái 4: Nhả phím số 2
		phim_1 = phim_1-0x30;
		phim_2 = phim_2-0x30;
		phim = phim_1*10+phim_2;
		phim_1 = 0; phim_2 = 0;//Trả về giá trị ban đầu cho 2 phím
		return 4;
	}
	else if((key==0)&&(phim_1==0)&&(phim_2==0)&&(phim!=0))
	{
		//Trạng thái 5: Nhấn xong phím, chờ thay đổi phím
		//Serial.println("6");
		return 5;
	}
	else if ((key>0x2F)&&(key<0x3A)&&(phim_1==0)&&(phim_2==0)&&(phim!=0))
	{
		//Trạng thái 6: Nhấn phím thay đổi 1
		phim_1 = key;
		return 6;
	}
	else if ((key==0)&&(phim_1>0x2F)&&(phim_1<0x3A)&&(phim_2==0)&&(phim!=0))
	{
		//Trạng thái 7: Nhả phím thay đổi 1
		return 7;
	}
	else if ((key>0x2F)&&(key<0x3A)&&(phim_1>0x2F)&&(phim_1<0x3A)&&(phim_2==0)&&(phim!=0))
	{
		//Trạng thái 8: Nhấn phím thay đổi 2
		phim_2 = key;
		return 8;
	}
	else if((key==0)&&(phim_1>0x2F)&&(phim_1<0x3A)&&(phim_2>0x2F)&&(phim_2<0x3A)&&(phim!=0))
	{
		//Trạng thái 9: Nhả phím thay đổi 2
		phim_1 = phim_1-0x30;
		phim_2 = phim_2-0x30;
		phim = phim_1*10+phim_2;
		phim_1 = 0; phim_2 = 0;//Trả về giá trị ban đầu cho 2 phím
		return 9;
	}
	else if (key==0x2A)// Phím ENTER
	{
		// Không làm gì cả
		phim_1 = 0; phim_2 = 0;// Trả về giá trị ban đầu cho 2 phím
		return 10;
	}
	else if (key==0x23)// Phím CANCEL
	{
		phim_1 = 0; phim_2 = 0; phim = 0;// Trả về giá trị ban đầu cho 2 phím
		// Serial.println("Đã nhấn cancel");
		if (trang_thai_dau_ngam == co_tien)
		{
			delay(100);
			Nv11.tu_choi_tien();
			delay(100);
		}
		return 11;
	}
}

bool MAY_BAN_HANG::dem_thoi_gian_khong_nhan_phim()
{
	if ((key>0x2F)&&(key<0x3A))// Nếu nhấn phím từ 1 tới 9 thì hiện màn hình số
	{
		dem_thoi_gian_chuyen_man_hinh = 0;
		return 1;	
	}
	else if (key == 0)// Nếu không nhấn phím nào thì giữ nguyên dạng màn hình ban đầu
	{
		dem_thoi_gian_chuyen_man_hinh++;
		if (dem_thoi_gian_chuyen_man_hinh==100000)// Nếu đang k nhấn phím nào và đủ thời gian thì chuyển về màn hình đầu tiên
		{
			dem_thoi_gian_chuyen_man_hinh = 0;
			man_hinh = trang_0;
			phim_1 = 0; phim_2 = 0;
			return 0;
		}
		else if(dem_thoi_gian_chuyen_man_hinh<=100000)
		{
			return 1;
		}
	}
}// Nếu nhấn 1 phím bất kỳ trước thời gian định trước thì 

bool MAY_BAN_HANG::kiem_tra_tinh_hop_le_cua_o_hang()
{
	if ((phim!=0)&&(trang_thai_dau_ngam==co_tien)&&(tai_khoan!=0))
	{
		cap_nhat_lcd();
		nuot_tien();
	}
}

void MAY_BAN_HANG::trang_thai_chon_hang(void)
{
	if (phim==0)
	{
		TRANG_THAI_CHON_HANG = chua_chon;
	}
	else
	{
		if (phim>=60)
		{
			TRANG_THAI_CHON_HANG=chon_sai;
		}
		else
		{
			if ((o_hang_loi[phim]==loi)||(o_hang_loi[phim]==khoa)) // Nếu chọn vào ô hàng lỗi hoặc khóa nghĩa là chọn sai
			{
				TRANG_THAI_CHON_HANG = chon_sai;
			}
			else if (o_hang_loi[phim]==khong_khoa_khong_loi)
			{
				if (tai_khoan<gia_tien[phim])
				{
					TRANG_THAI_CHON_HANG = chon_dung_nhung_chua_hop_le;
				}
				else if (tai_khoan>=gia_tien[phim])
				{
					TRANG_THAI_CHON_HANG = chon_dung_hop_le;
				}
			}
		}
	}
}

void MAY_BAN_HANG::thong_bao_lcd_neu_chon_o_hang_sai()
{
	if (TRANG_THAI_CHON_HANG == chon_sai)
	{
		lcd_thong_bao_chon_hang_sai();
		delay(1000);
		TRANG_THAI_CHON_HANG = chua_chon;
		phim = 0;
	}
	else if (TRANG_THAI_CHON_HANG==chua_chon)
	{
		//
	}
	else 
	{
		// Không làm gì cả nếu chưa chọn hoặc chọn đúng
	}
}

void MAY_BAN_HANG::nuot_tien()
{

	if((trang_thai_dau_ngam==co_tien)||(trang_thai_cua_nv11==_dang_nhan_dang_tien))
	{
		do
		{
			Nv11.gui_lenh_tham_do();
			delay(300); 
			Nv11.receive();
			phan_tich_cau_tra_loi_tham_do();
		}
		while((trang_thai_cua_nv11!=_da_dua_tien_len_note_float)&&(trang_thai_cua_nv11!=_da_dua_tien_xuong_stack)&&(trang_thai_cua_nv11!=_da_tu_choi_to_tien));
		
		EEPROM.write(ADDR_TAI_KHOAN[0], (unsigned char) tai_khoan); delay(5); // Chỉ lưu tài khoản khi sau khi nuốt tiền
		EEPROM.write(ADDR_TAI_KHOAN[1], (unsigned char)(tai_khoan>>8)); delay(5);
		so_tien_nuot_vao+= menh_gia_tien_da_nuot;
		// Serial.print("Số tiền nuốt vào là: ");
		// Serial.println(so_tien_nuot_vao);
		trang_thai_dau_ngam = khong_co_tien;
		trang_thai_cua_nv11 = _trang_thai_cho;
	}
	// Sau khi nuốt tiền thì số tiền đã nuốt tăng lên đúng bằng mệnh giá đã nuốt
}

void MAY_BAN_HANG::dua_hang_ra()
{
	cap_nhat_lcd();
	TRANG_THAI_MUA_HANG = xong;
	
	tai_khoan -= gia_tien[phim];
	EEPROM.write(ADDR_TAI_KHOAN[0], (unsigned char) tai_khoan); delay(5); 
	EEPROM.write(ADDR_TAI_KHOAN[1], (unsigned char)(tai_khoan>>8)); delay(5);
	if(tai_khoan>=65000)
	{
		// Serial.println("Lỗi mua hàng");
	}
	Nv11.enable();
}

void MAY_BAN_HANG::quay_dong_co()
{
	lcd_quay_dong_co();
	Dongco.quay_1_vong_khong_cam_bien_roi(phim);
}

void MAY_BAN_HANG::tru_hang_hoac_khoa_o_hang()
{
	switch(o_hang_loi[phim])
	{
		case 0: // Trường hợp ô hàng lỗi
		{
			// Khóa ô hàng đó lại và lưu vào nhật ký lỗi
			EEPROM.write(ADDR_LOI_DC[phim], o_hang_loi[phim]); // Lưu lại lỗi vào EEPROM
			delay(5);
			break;
		}
		case 1:	// Trường hợp ô hàng bình thường: không lỗi và cũng không bị khóa
		{
			// Ô hàng bình thường nên phải giảm số hàng đi 1 đơn vị
			so_hang[phim] = so_hang[phim] - 1;
			EEPROM.write(ADDR_SO_HANG[phim], so_hang[phim]); // Lưu số hàng còn lại vào EEPROM
			delay(5);
			break;
		}
		case 2: // Trường hợp ô hàng bị khóa (có thể do người dùng khóa hoặc khóa theo loại máy bán hàng)
		{
			// Vì đã khóa sẵn theo phiên bản nên không làm gì cả
			break;
		}
	}
}

void MAY_BAN_HANG::enter_hay_cancel()
{
	key = 0; //Gán cho biến key giá trị = 0 trước khi bắt đầu quét bàn phím
	dem_thoi_gian_quet_phim = 0; // Gán cho biến key = 0
	while (key == 0x00)
	{
		key = keypad.getKey();
		dem_thoi_gian_quet_phim++;
		// Serial.print("Thời gian quét ENTER/CANCEL là: ");
		Serial.println(dem_thoi_gian_quet_phim);
		if (dem_thoi_gian_quet_phim==50000) break;
	}
	if ((key=='*')||(key==0x00))//phím ENTER hoặc không nhấn
	{
		phim_xac_nhan = '*';
	}
	else if (key=='#') //Phím CANCEL
	{
		phim_xac_nhan = '#';
	}
	dem_thoi_gian_quet_phim = 0;
}

void MAY_BAN_HANG::tra_lai_tien()
{
	Nv11.tra_loi_theo_kenh();
	Nv11.tra_cuu_so_tien_tra_lai();							// Hỏi Nv11 số tiền có trong bộ trả lại của nó
	so_to_tien_co_trong_bo_tra_lai = Nv11.ERX[6];			// Số tờ tiền trong bộ trả lại là ...
	// Serial.print("Số tờ tiền có trong BTL là: ");
	// Serial.println(so_to_tien_co_trong_bo_tra_lai);
	tong_so_tien_co_trong_bo_tra_lai = so_to_tien_co_trong_bo_tra_lai*5; // => Tổng số tiền có thể trả lại là ...
	so_tien_tra_lai = 0;
	if (tong_so_tien_co_trong_bo_tra_lai >= tai_khoan) 		//Nếu số tiền có trong bộ trả lại lớn hơn tài khoản khách hàng thì trả lại tiền
	{
		lcd_dang_tra_lai_tien();
		so_to_can_dua_ra = tai_khoan/5; 					//Tính toán số tờ tiền cần đưa ra
		// Serial.print("Số tiền cần đưa ra là: ");
		// Serial.println(so_to_can_dua_ra);
		while (so_to_can_dua_ra!=0) 						// Lặp lại việc trả lại tiền cho tới khi trả lại đủ tiền
		{
			Nv11.tham_do();
			Nv11.tra_lai_tien();
			so_to_can_dua_ra --; 							// Giảm số tờ tiền cần đưa ra đi 1 đơn vị
			so_tien_tra_lai +=5;
			tai_khoan -= 5;
			so_du_luc_sau = tai_khoan;
			EEPROM.write(ADDR_TAI_KHOAN[0], (unsigned char) tai_khoan); delay(5); // Chỉ lưu tài khoản khi sau khi nuốt tiền
			EEPROM.write(ADDR_TAI_KHOAN[1], (unsigned char)(tai_khoan>>8)); delay(5);
			if (Nv11.ERX[5]==0xF5)
			{
				Nv11.enable();
				Nv11.tra_lai_tien();
			}
			delay(500);
			do
			{
				Nv11.tham_do();
				delay(500);
			}
			while(Nv11.ERX[6]!=0xD2); 						// Chờ cho tới khi khách lấy tờ tiền đưa ra.
		}
		Nv11.enable();		 								// Kết nối lại Nv11 sau khi kết thúc quá trình trả lại
	}
	else if ((tong_so_tien_co_trong_bo_tra_lai!=0)&&(tong_so_tien_co_trong_bo_tra_lai < tai_khoan))	// Nếu số tiền có trong bộ trả lại không đủ
	{
		lcd_dang_tra_lai_tien();
		so_to_can_dua_ra = tong_so_tien_co_trong_bo_tra_lai/5;
		// Serial.print("Số tiền cần đưa ra là: ");
		// Serial.println(so_to_can_dua_ra);
		while (so_to_can_dua_ra!=0)
		{
			Nv11.tham_do();
			Nv11.tra_lai_tien();
			so_to_can_dua_ra --; 		// Giảm số tờ tiền cần đưa ra đi 1 đơn vị
			so_tien_tra_lai +=5;
			tai_khoan -= 5;
			so_du_luc_sau = tai_khoan;
			EEPROM.write(ADDR_TAI_KHOAN[0], (unsigned char) tai_khoan); delay(5); // Chỉ lưu tài khoản khi sau khi nuốt tiền
			EEPROM.write(ADDR_TAI_KHOAN[1], (unsigned char)(tai_khoan>>8)); delay(5);	
			if (Nv11.ERX[5]==0xF5)
			{
				Nv11.enable();
				Nv11.tra_lai_tien();
			}
			delay(500);
			do
			{
				Nv11.tham_do();
				delay(500);
			}
			while(Nv11.ERX[6]!=0xD2); 						// Chờ cho tới khi khách lấy tờ tiền đưa ra.		
		} 
		Nv11.enable();
		lcd_da_het_tien_tra_lai_xin_mua_hang_tiep();
		for (char i=0; i<3; i++) 	// Chờ màn hình trong 5s cho người mua hàng đọc
		{
			Nv11.tu_choi_tien();	// Trong lúc chờ thì không nhận tiền vào.
			delay(1000);
		}
	}
	else if(tong_so_tien_co_trong_bo_tra_lai==0)
	{
		so_du_luc_sau = tai_khoan;
		lcd_da_het_tien_tra_lai_xin_mua_hang_tiep();
		for (char i=0; i<3; i++) 	// Chờ màn hình trong 5s cho người mua hàng đọc
		{
			Nv11.tu_choi_tien();	// Trong lúc chờ thì không nhận tiền vào.
			delay(1000);
		}
	}
}


/* ================================================================================================== */
/* KẾT THÚC MỤC THANH TOÁN, CHUYỂN SANG TÍNH TOÁN DOANH THU ========================================= */


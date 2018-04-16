

#include <MBH.h>

unsigned int hanh_dong_tiep_theo;
unsigned char __giutien;

bool MAY_BAN_HANG::phan_tich_cau_tra_loi_tham_do_3() // Phân tích câu trả lời của lệnh 0x07
{
	if(Nv11.ERX[5]!=0xF0)
	{
		return false;
	}
	else
	{
		//Serial.println("Phân tích");
		for(unsigned char i=6; i<Nv11.ERX[0]+5; i++) // ERX[0] là độ dài gói câu trả lời nhận được
		{ // Dữ liệu gói tin bắt đầu được lưu từ byte thứ 6 trong mảng
			switch(Nv11.ERX[i]) // Nv11.ERX[5] = 0xF0, bắt đầu tính từ byte Nv11.ERX[6]
			{
/* 1 */			case 0xF1:	// NV11 đang khởi động
				{
					Serial.println("NV11 Reseting");
					break;
				}
/* 2 */			case 0xEF:	// NV11 đang đọc giá trị tiền
				{
					switch(Nv11.ERX[i+1]) // Phân tích byte tiếp theo
					{
						case 0: menh_gia_tien_dang_giu = 0; 
								Serial.println("Đang đọc tiền"); 	
								break;
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
						Serial.print("Tiền trong ngăn chứa: ");
						Serial.println(menh_gia_tien_dang_giu);	
						tai_khoan += menh_gia_tien_dang_giu;
						Serial.print("Tài khoản là: ");
						Serial.println(tai_khoan);
						hanh_dong_tiep_theo = __giutien;
					}
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
						Serial.print("Tiền đã nuốt: ");
						Serial.println(menh_gia_tien_da_nuot);								
					}
					i++;					
					break;
				}
/* 4 */			case 0xED:	// Đang từ chối
				{
					// tai_khoan -= menh_gia_tien_dang_giu;
					// menh_gia_tien_dang_giu = 0;
					Serial.print("Tài khoản là: ");
					Serial.println(tai_khoan);					
					// Không làm gì cả
					break;
				}
/* 5 */			case 0xEC:	// Đã từ chối
				{
					tai_khoan -= menh_gia_tien_dang_giu;
					menh_gia_tien_dang_giu = 0;				
					// Cập nhật lại dữ liệu
					Serial.print("Tài khoản là: ");
					Serial.println(tai_khoan);						
					break;
				}
/* 6 */			case 0xCC:	// Đang nuốt tiền
				{
					//tai_khoan -= menh_gia_tien_dang_giu;
					//menh_gia_tien_dang_giu = 0;	
					Serial.print("Tài khoản là: ");
					Serial.println(tai_khoan);						
					break;
				}
/* 7 */			case 0xEB:	// Đã đưa tiền xuống Stacker
				{
					//tai_khoan -= menh_gia_tien_dang_giu;
					menh_gia_tien_dang_giu = 0;	
					Serial.print("Tài khoản là: ");
					Serial.println(tai_khoan);						
					break;
				}
/* 8 */			case 0xEA:	// 
				{
					break;
				}
/* 9 */			case 0xE9:	//
				{
					break;
				}
/* 10 */		case 0xE8:	//
				{
					break;
				}
/* 11 */		case 0xE6:	//
				{
					break;
				}
/* 12 */		case 0xE7:	//
				{
					break;
				}
/* 13 */		case 0xE1:	//
				{
					break;
				}
/* 14 */		case 0xE2:	//
				{
					break;
				}
/* 15 */		case 0xE3:	//
				{
					break;
				}
/* 16 */		case 0xE4:	//
				{
					break;
				}
/* 17 */		case 0xDB:	//
				{
					break;
				}
/* 18 */		case 0xDA:	//
				{
					break;
				}
/* 19 */		case 0xD2:	//
				{
					break;
				}
/* 20 */		case 0xC9:	//
				{
					break;
				}
/* 21 */		case 0xC3:	//
				{
					break;
				}
/* 22 */		case 0xCA:	//
				{
					break;
				}
/* 23 */		case 0xCB:	//
				{
					break;
				}
/* 24 */		case 0xCD:	//
				{
					break;
				}
/* 25 */		case 0xC6:	//
				{
					break;
				}
/* 26 */		case 0xC7:	//
				{
					break;
				}
/* 27 */		case 0xC8:	//
				{
					break;
				}
/* 28 */		case 0xCE:	//
				{
					break;
				}
/* 29 */		case 0xCF:	//
				{
					break;
				}
/* 30 */		case 0xB5:	//
				{
					break;
				}
			}
			if(i>=15) break; // Không phân tích các byte lớn hơn 15
		}
	}
}

void MAY_BAN_HANG::giu_tien()
{
	if(menh_gia_tien_dang_giu!=0)
	{
		int cong = 0;
		while(1)
		{
			Nv11.gui_lenh_giu_tien();
			delay(300);
			Nv11.receive();
			
			if(Nv11.ERX[5]==0xF0)
			{
				// Nếu OK nghĩa là đang giữ tiền, không làm gì cả
			}
			else if(Nv11.ERX[5]==0xF5)
			{
				tai_khoan -= menh_gia_tien_dang_giu;
				menh_gia_tien_dang_giu = 0; // Tờ tiền đã bị lấy lại
				break;
			}
			cong++;
			if(cong==19) break;
		}
		while(1)
		{
			Nv11.gui_lenh_tham_do();
			delay(300);
			Nv11.receive();
			phan_tich_cau_tra_loi_tham_do_3();	
			if(menh_gia_tien_dang_giu==0) break;
		}
	}
}

// =========================================================


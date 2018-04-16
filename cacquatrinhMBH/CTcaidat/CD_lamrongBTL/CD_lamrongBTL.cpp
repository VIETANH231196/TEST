/*
	Cài đặt làm rỗng bộ trả lại
*/

#include <MBH.h>


		//----------------------------------------------------------------------
/* OK */void MAY_BAN_HANG::trang_cai_dat_lam_rong_bo_tra_lai()		// Trang 3-1
		{
			while (trang_cai_dat_duoc_lua_chon)
			{
				lcd_lam_rong_bo_tra_lai_1();
				// Đọc bàn phím để xử lý bước tiếp theo
				quet_ban_phim();
				// Phân tích phím đọc được sau khi quét bàn phím
				switch(key)
				{
					case 0x00: break; 	// Không đọc được phím nào cả
					case 0x30: break; 	// Phím số 0
					case 0x31: break;
					case 0x32: break;
					case 0x33: break;
					case 0x34: break;
					case 0x35: break;
					case 0x36: break;
					case 0x37:			// Nếu nhấn phím 7 nghĩa là đồng ý làm rỗng bộ trả lại 
					{
						while (1)
						{
							Nv11.empty_recycle();
							lcd_lam_rong_bo_tra_lai_2();
							if ((Nv11.ERX[0]==0x01)&&(Nv11.ERX[5]==0xF0)) // Nếu câu trả lời là OK thì nghĩa là đã bắt đầu làm rỗng bộ trả lại
							{
								while(1)
								{
									Nv11.tham_do(); // Gửi lệnh thăm dò xem khi nào làm rỗng xong bộ trả lại
									if ((Nv11.ERX[0]==0x03)&&(Nv11.ERX[5]==0xF0)&&(Nv11.ERX[6]==0xC2)&&(Nv11.ERX[7]==0xE8))
									{
										// Đang làm rỗng và đã ngắt kết nối => cần thăm dò tiếp
										delay(1000);// Chờ 1s rồi thăm dò tiếp
									}
									else if ((Nv11.ERX[0]==0x03)&&(Nv11.ERX[5]==0xF0)&&(Nv11.ERX[6]==0xE8)&&(Nv11.ERX[7]==0xC2))
									{
										// Đã ngắt kết nối và đang làm rỗng => cần thăm dò tiếp
										delay(1000);// Chờ 1s rồi thăm dò tiếp							
									}
									else if ((Nv11.ERX[0]==0x03)&&(Nv11.ERX[5]==0xF0)&&(Nv11.ERX[6]==0xC3)&&(Nv11.ERX[7]==0xE8))
									{
										// Đã LÀM RỖNG XONG và ngắt kết nối => kết nối lại đầu đọc tiền rồi thoát
										Nv11.enable();
										break;
									}
									else if ((Nv11.ERX[0]=2)&&(Nv11.ERX[5]==0xF0)&&(Nv11.ERX[6]==0xE8))
									{
										Nv11.enable();
									}
								}
							}
							Nv11.tra_loi_theo_kenh();
							Nv11.tra_cuu_so_tien_tra_lai();							// Hỏi Nv11 số tiền có trong bộ trả lại của nó
							so_to_tien_co_trong_bo_tra_lai = Nv11.ERX[6];			// Số tờ tiền trong bộ trả lại là ...
							Nv11.tra_loi_theo_gia_tri();
							//Serial.print("Số tờ tiền có trong BTL là: ");
							Serial.println(so_to_tien_co_trong_bo_tra_lai);
							if(so_to_tien_co_trong_bo_tra_lai==0) break; // Nếu số tiền có trong bộ trả lại đúng là 0 thì thoát khỏi chương trình làm rỗng
						}
						break;
					}
					case 0x38: break;
					case 0x39: 			// Nếu nhấn phím 9 nghĩa là không đồng ý làm rỗng bộ trả lại, tương tự nút CALCEL
					{
						trang_cai_dat_duoc_lua_chon = 0;
						break;
					}
					
					case 0x23: // Phím CANCEL
					{
						trang_cai_dat_duoc_lua_chon = 0; // Thoát khỏi vòng lặp trong trang cài đặt hiện tại, trở về menu chính
						break;
					}
					case 0x2A: break; // Phím ENTER
				}
			}
			thoat_cai_dat_lam_rong_BTL:
			{
				trang_cai_dat_duoc_lua_chon = 3;
			}
		}
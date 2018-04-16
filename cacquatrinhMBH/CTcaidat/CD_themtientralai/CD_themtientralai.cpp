/*
	Mục cài đặt thêm tiền trả lại
*/

#include <MBH.h>

		//----------------------------------------------------------------------
/* OK */void MAY_BAN_HANG::trang_cai_dat_them_tien_tra_lai()		// Trang 2-3
		{
			unsigned char nut_nhan_cho_duoc_xu_ly = 0; // Không có nút nhấn nào cần được xử lý
			while (trang_cai_dat_duoc_lua_chon)
			{
				lcd_them_tien_tra_lai();
				Nv11.gui_lenh_tham_do();
				// Đọc bàn phím để xử lý bước tiếp theo
				kiem_tra_nut_cancel(60, nut_nhan_cho_duoc_xu_ly);
				Nv11.receive();
				if ((Nv11.ERX[0]==0x01)&&(Nv11.ERX[5]==0xF0))
				{
					// Chưa có hiện tượng gì xảy ra, không làm gì cả
				}
				else if((Nv11.ERX[0]=2)&&(Nv11.ERX[5]==0xF0)&&(Nv11.ERX[6]==0xE8)) //Trường hợp ngắt kết nối Nv11
					Nv11.enable(); // Kết nối lại NV11 
					
				Nv11.clear(); mang[0]=0x45; mang[1]=0x01; length_tx = 2;
				Nv11.send(mang, length_tx);
				kiem_tra_nut_cancel(50, nut_nhan_cho_duoc_xu_ly);
				Nv11.receive();
				
				Nv11.clear(); mang[0]=0x41; length_tx = 1;
				Nv11.send(mang, length_tx);								// Hỏi Nv11 số tiền có trong bộ trả lại của nó
				kiem_tra_nut_cancel(180, nut_nhan_cho_duoc_xu_ly);	//
				Nv11.receive();
				so_to_tien_co_trong_bo_tra_lai = Nv11.ERX[6];			// Số tờ tiền trong bộ trả lại là ...
				
							
				Nv11.clear(); mang[0]=0x45; mang[1]=0x00; length_tx = 2;
				Nv11.send(mang, length_tx);
				kiem_tra_nut_cancel(50, nut_nhan_cho_duoc_xu_ly);
				Nv11.receive();
				switch(nut_nhan_cho_duoc_xu_ly)
				{
					case 0x00: break;
					case 0x23: goto thoat_cai_dat_them_tien;
				}
			}
			thoat_cai_dat_them_tien:
				trang_cai_dat_duoc_lua_chon = 2;
		}

		void MAY_BAN_HANG::kiem_tra_nut_cancel(unsigned char tg_doi, unsigned char &ret)
		{
				unsigned char dem = 0;
				key = 0;
				while(key==0)
				{
					key = keypad.getKey(); 
					dem++; delay(1);
					if(dem == tg_doi) break;
				}
				// Phân tích phím đọc được sau khi quét bàn phím
				switch(key)
				{
					case 0x00: break; // Không đọc được phím nào cả
					case 0x30: break; // Phím số 0
					case 0x31: break;
					case 0x32: break;
					case 0x33: break;
					case 0x34: break;
					case 0x35: break;
					case 0x36: break;
					case 0x37: break;
					case 0x38: break;
					case 0x39: break;
					
					case 0x23: // Phím CANCEL
						ret = '#'; break;
					case 0x2A: break; // Phím ENTER
				}
				delay(tg_doi - dem); // Chờ cho đủ thời gian
		}
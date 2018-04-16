/*
	Tổng hợp các quá trình giữa SIM, thanh toán và hiển thị
*/

#include <MBH.h>

bool MAY_BAN_HANG::kiem_tra_cam_bien_cua()
{
	return digitalRead(2); // Trả lại giá trị đọc được từ chân cảm biến 2
}

void MAY_BAN_HANG::qua_trinh_doc_EEPROM(void)
{
	kiem_tra_ket_noi_voi_EEPROM();
	doc_tai_khoan();
	doc_gia_tien();
	doc_so_hang();
	doc_o_hang_khoa();
}

/** ================================================================================================================ **/
/** ================================================================================================================ **/
void MAY_BAN_HANG::qua_trinh_mua_hang(void)
{
	Nhietdo.bat_tat_may_lanh();
	dem_thoi_gian_quet_phim = 0;
	qua_trinh_chon_hang();
	// ========================================
	// KẾT THÚC QUÁ TRÌNH CHỌN HÀNG
	Rtc.readDS1307();
	unsigned char Sim_s_year, Sim_s_month, Sim_s_day, Sim_s_hour, Sim_s_min, Sim_s_sec;
	Sim_s_year=char(Rtc.year-2000); Sim_s_month=Rtc.month; Sim_s_day=Rtc.day; Sim_s_hour=Rtc.hour; Sim_s_min=Rtc.minute; Sim_s_sec = Rtc.second;
	unsigned long long int Sim_thoi_gian_bat_dau;
	{
		Sim_thoi_gian_bat_dau = Sim_s_year;
		Sim_thoi_gian_bat_dau = (Sim_thoi_gian_bat_dau<<8)||Sim_s_month;
		Sim_thoi_gian_bat_dau = (Sim_thoi_gian_bat_dau<<8)||Sim_s_day;
		Sim_thoi_gian_bat_dau = (Sim_thoi_gian_bat_dau<<8)||Sim_s_hour;
		Sim_thoi_gian_bat_dau = (Sim_thoi_gian_bat_dau<<8)||Sim_s_min;
		Sim_thoi_gian_bat_dau = (Sim_thoi_gian_bat_dau<<8)||Sim_s_sec;
	}
	qua_trinh_xu_ly_tien_va_hang();
	qua_trinh_tra_lai();
	//----------------------
	Rtc.readDS1307();
	unsigned int Sim_so_du_trc, Sim_so_tien_nuot, Sim_so_du_sau;
	unsigned char Sim_o_duoc_chon, Sim_tien_tra_lai;
	Sim_so_du_trc = so_du_luc_truoc;
	Sim_so_tien_nuot = so_tien_nuot_vao;
	Sim_o_duoc_chon = phim;
	Sim_tien_tra_lai = so_tien_tra_lai;
	Sim_so_du_sau = so_du_luc_sau;
	unsigned char Sim_e_year, Sim_e_month, Sim_e_day, Sim_e_hour, Sim_e_min, Sim_e_sec;
	Sim_e_year=char(Rtc.year-2000); Sim_e_month=Rtc.month; Sim_e_day=Rtc.day; Sim_e_hour=Rtc.hour; Sim_e_min=Rtc.minute; Sim_e_sec = Rtc.second;
	unsigned long long int Sim_thoi_gian_ket_thuc;
	{
		Sim_thoi_gian_ket_thuc = Sim_e_year;
		Sim_thoi_gian_ket_thuc = (Sim_thoi_gian_ket_thuc<<8)||Sim_e_month;
		Sim_thoi_gian_ket_thuc = (Sim_thoi_gian_ket_thuc<<8)||Sim_e_day;
		Sim_thoi_gian_ket_thuc = (Sim_thoi_gian_ket_thuc<<8)||Sim_e_hour;
		Sim_thoi_gian_ket_thuc = (Sim_thoi_gian_ket_thuc<<8)||Sim_e_min;
		Sim_thoi_gian_ket_thuc = (Sim_thoi_gian_ket_thuc<<8)||Sim_e_sec;
	}
	luu_du_lieu_mua_hang_bt(Sim_so_du_trc, Sim_so_tien_nuot, Sim_o_duoc_chon, Sim_tien_tra_lai, Sim_so_du_sau, Sim_thoi_gian_bat_dau, Sim_thoi_gian_ket_thuc);
	Sim_Gui_Server(0x65);
}

/* ========================== CÁC QUÁ TRÌNH NHỎ CỦA QUÁ TRÌNH MUA HÀNG ======================= */
//-----------------------------------------------------------
void MAY_BAN_HANG::qua_trinh_chon_hang()
{
	TRANG_THAI_CHON_HANG = chua_chon; phim = 0;// Reset về trạng thái chưa chọn hàng
	// Trước khi chọn hàng thì đặt các giá trị cần thiết về 0, số dư lúc trước  = tài khoản ở thời điểm ngay trước khi chọn hàng
	so_tien_nuot_vao = 0; doanh_thu_1_lan_mua_hang = 0; so_tien_tra_lai = 0;
	so_du_luc_truoc = tai_khoan; 
	do
	{
		while ((tai_khoan==0)||(TRANG_THAI_CHON_HANG==chua_chon)||(TRANG_THAI_CHON_HANG==chon_sai)||(TRANG_THAI_CHON_HANG==chon_dung_nhung_chua_hop_le))
		{
			// doc_ban_phim_ngan();
			if(Nv11.LOI==1)
				gui_lenh_cho_nv11();
			doc_ban_phim();
			doc_ban_phim();
			if(Nv11.LOI==1)
				doc_tien();
			cap_nhat_lcd();
			// Serial.println("Trong vòng lặp");
			kiem_tra_tinh_hop_le_cua_o_hang();
			// Serial.print("Trạng thái chọn hàng là: ");
			// Serial.println(TRANG_THAI_CHON_HANG);
		}
		// Serial.println("Ô hàng chọn là hợp lệ");
		// Sau khi chọn đúng ô hàng và tài khoản có tiền thì thoát ra khỏi vòng lặp
		// ========================================================================
		// Ở đây có 2 trường hợp là đầu ngậm có tiền và đầu ngậm không có tiền
		// Nếu đầu ngậm có tiền và tài khoản < giá tiền thì nuốt tờ tiền đang ngậm và hiển thị LCD + yêu cầu đưa thêm tiền
		// Nếu đầu ngậm không có tiền và tài khoản < giá tiền thì chỉ hiển thị LCD yêu cầu đưa thêm tiền
	}
	while (tai_khoan>=gia_tien[phim]==false);
}

//-----------------------------------------------------------
void MAY_BAN_HANG::qua_trinh_xu_ly_tien_va_hang()
{
	dua_hang_ra();
	quay_dong_co();
	tru_hang_hoac_khoa_o_hang();
}

//-----------------------------------------------------------
void MAY_BAN_HANG::qua_trinh_tra_lai()
{
	if(tai_khoan==0)
	{
		so_tien_tra_lai = 0; so_du_luc_sau = 0;
		// Nếu tài khoản bằng = 0đ
		// Không làm gì cả, chỉ đơn giản kết thúc quá trình mua hàng
	}
	else if (tai_khoan>0) 
	{
		// Nếu tài khoản còn tiền
		lcd_mua_hang_tiep(); // Hiển thị màn hình hỏi khách hàng có muốn mua tiếp không?
		enter_hay_cancel();
		if (phim_xac_nhan == '#')
		{
			// Trả lại tiền cho khách hàng khi nhấn cancel
			tra_lai_tien();
		}
		else if (phim_xac_nhan == '*')
		{
			// Mua tiếp khi kết thúc nhấn enter hoặc không nhấn gì trong 1 thời gian
			// Chỉ đơn giản là kết thúc chương trình
			so_du_luc_sau = tai_khoan;
			so_tien_tra_lai = 0;
		}
		phim_xac_nhan = 0; // Trả về giá trị mặc định cho phím xác nhận
	}
}

/** ================================================================================================================ **/
/** ================================================================================================================ **/
void MAY_BAN_HANG::qua_trinh_tinh_va_luu_doanh_thu_EEPROM()
{
	tinh_va_luu_doanh_thu();
}

/** ================================================================================================================ **/
/** ================================================================================================================ **/
void MAY_BAN_HANG::qua_trinh_cai_dat(void)
{
	NHAP_PASSWORD();	// Hiển thị LCD và đọc password từ bàn phím và xử lý
}

/* ========================== CÁC QUÁ TRÌNH NHỎ CỦA QUÁ TRÌNH CÀI ĐẶT ======================= */

void MAY_BAN_HANG::luu_du_lieu_mua_hang_bt(unsigned int sdt, unsigned int stn, unsigned char o, unsigned char ttl, unsigned int sds, unsigned long long int tg1, unsigned long long int tg2)
{
	EEPROM.write(3500, sdt); delay(5);
	EEPROM.write(3501, sdt>>8); delay(5);
	EEPROM.write(3502, stn); delay(5);
	EEPROM.write(3503, stn>>8); delay(5);
	EEPROM.write(3504, o); delay(5);
	EEPROM.write(3505, EEPROM.read(ADDR_GIA_TIEN[o])); delay(5);
	EEPROM.write(3506, ttl); delay(5);
	EEPROM.write(3507, sds); delay(5);
	EEPROM.write(3508, sds>>8); delay(5);
	EEPROM.write(3509, tg1>>40); delay(5);
	EEPROM.write(3510, tg1>>32); delay(5);
	EEPROM.write(3511, tg1>>24); delay(5);
	EEPROM.write(3512, tg1>>16); delay(5);
	EEPROM.write(3513, tg1>>8); delay(5);
	EEPROM.write(3514, tg1); delay(5);
	EEPROM.write(3515, tg2>>40); delay(5);
	EEPROM.write(3516, tg2>>32); delay(5);
	EEPROM.write(3517, tg2>>24); delay(5);
	EEPROM.write(3518, tg2>>16); delay(5);
	EEPROM.write(3519, tg2>>8); delay(5);
	EEPROM.write(3520, tg2); delay(5);
}
/*
	Thư viện các hàm xử lý của chương trình chính máy bán hàng	
*/ 
//	File hàm chính này bao gồm:
/**	
	+, Các thư viện cơ bản: NV11, LCD, Bàn phím, Thời gian thực
	+, Danh sách các biến hệ thống 														(file: 		bien_he_thong.h)
	+, Cấu trúc địa chỉ bộ nhớ EEPROM và các giá trị được lưu trong các ô nhớ này 		(2 file: 	eeprom_addr.h và eeprom_value.h)
	+, Các hàm hiển thị 																(file: 		hienthi.h)
	+, Các hàm xử lý tình huống (chưa được tách ra)
*/

#ifndef MBH_H
#define MBH_H

#include <Arduino.h>
#include <SPI.h>
// ===============================================================================
// CÁC THƯ VIỆN CƠ BẢN ===========================================================
#define MEGA2560
#ifdef MEGA2560

#include <EEPROM.h>								// Thư viện EEPROM trong của 2560
#include <thuviencoban/rtc/RTC.h>				// Thư viện thời gian thực
#include "thuviencoban/NV11/NV11.h"				// Thư viện đầu đọc tiền NV11
#include <thuviencoban/lcd/U8glib.h> 			// Thư viện màn hình LCD
extern U8GLIB_ST7920_128X64_4X u8g;

#include <thuviencoban/keypad/Keypad.h>
extern Keypad keypad;
extern int sound;

#include <thuviencoban/dongco/dongco.h>			// Thư viện điều khiển động cơ
#include <thuviencoban/donhietdo/donhietdo.h>	// Thư viện đo nhiệt độ và đk máy lạnh
#include <thuviencoban/Sim/Sim.h>	           	// Thư viện khởi tạo cho Sim 
#include <thuviencoban/String/Str.h>			// Thư viện dùng để tạo String nhằm giảm bộ nhớ RAM

// ================================================================================
// THƯ VIỆN CÁC BIẾN HỆ THỐNG VÀ EEPROM ===========================================

#include <bien_he_thong/bien_he_thong.h>		// Các biến hệ thống
#include <bien_he_thong/eeprom_addr.h>	// Địa chỉ bộ nhớ EEPROM

class MAY_BAN_HANG
{
	public: 
	// CÁC THƯ VIỆN HÀM SỬ DỤNG TRONG CHƯƠNG TRÌNH HỆ THỐNG
	#include <cacquatrinhMBH/cacquatrinh.h>							// Tổng hợp các quá trình nhỏ lẻ

	#include <cacquatrinhMBH/CTkhoidong/khoidong.h>					// 
	#include <cacquatrinhMBH/CTkhoidong/hienthi_khoidong.h>			// 
	
	#include "cacquatrinhMBH/CTchinh/thanhtoan/thanhtoan.h"			// Các hàm xử lý thanh toán cơ bản
	#include <cacquatrinhMBH/CTchinh/doanhthu/tinhtoan_doanhthu.h>	// Tính toán và lưu vào EEPROM trong quá trình thanh toán
	#include <cacquatrinhMBH/CTchinh/hienthi/hienthi.h> 			// Các hàm hiển thị màn hình LCD
	
	#include <cacquatrinhMBH/CTcaidat/hienthicaidatchung.h>			// Các hàm hiển thị LCD trong phần cài đặt
	#include <cacquatrinhMBH/CTcaidat/caidatchung.h>				// Thư viện các hàm trong mục cài đặt
	#include <cacquatrinhMBH/CTcaidat/CD_doanhthu/CD_doanhthu.h>	// Phần riêng của tính toán và hiển thị doanh thu trong cài đặt

	#include <phantichlenhthamdo.h>									// Phân tích câu trả lời của lệnh thăm dò NV11
	
/*H*/#include <cacquatrinhMBH/cacCTkhac/SIM800C/SIM800C.h>			// Các hàm truyền thông với SIM800C

	void begin();
	void chuong_trinh_mua_hang();
	void chuong_trinh_cai_dat();
	
};

extern MAY_BAN_HANG Mbh;

#endif
#endif
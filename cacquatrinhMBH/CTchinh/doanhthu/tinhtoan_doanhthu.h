/*
	Phần tính toán và lưu doanh thu, tiền ra, tiền vào trong quá trình thanh toán
*/

#ifndef tinhtoan_doanhthu_h
#define tinhtoan_doanhthu_h

// Đầu vào: Số dư lúc trước, số tiền đưa vào, số tiền trả lại, số dư lúc sau - Thời gian: các ngày phân biệt nhau - thời gian thực
// Đầu ra: Tổng số tiền vào trong 1 ngày, tổng doanh thu trong 1 ngày, tổng số tiền trả lại trong 1 ngày lưu trong 1 ngăn bộ nhớ

void tinh_va_luu_doanh_thu();
void tinh_DT_ngay(unsigned int dia_chi_bat_dau); 	// Tính toán doanh thu ngày dựa trên 1 lần mua thành công
void tinh_DT_thang(unsigned int dia_chi_bat_dau);	// Tính toán doanh thu tháng
void tinh_DT_nam(unsigned int dia_chi_bat_dau);		// Tính toán doanh thu năm

void xoa_goi_tin_EEPROM(unsigned int dia_chi_bat_dau, unsigned char kich_thuoc);
void kiem_tra_bo_nho();

#endif
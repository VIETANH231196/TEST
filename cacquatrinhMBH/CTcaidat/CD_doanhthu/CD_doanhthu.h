/*
	Tính toán và hiển thị doanh thu trong mục cài đặt
*/

#ifndef _CD_doanhthu_h
#define _CD_doanhthu_h

public: 

	void trang_cai_dat_xem_doanh_thu();				// Trang 2-1
	
	void thong_ke_doanh_thu_ngay();
	void thong_ke_doanh_thu_thang();
	void thong_ke_doanh_thu_nam();
	
	void doc_doanh_thu_nam_tu_EEPROM(unsigned int dia_chi_bat_dau);
	void doc_doanh_thu_thang_tu_EEPROM(unsigned int dia_chi_bat_dau);
	void doc_doanh_thu_ngay_tu_EEPROM(unsigned int dia_chi_bat_dau);

#endif
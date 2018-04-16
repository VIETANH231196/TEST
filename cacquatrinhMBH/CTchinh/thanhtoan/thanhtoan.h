/*
	Các hàm xử lý thanh toán khi mua hàng
*/

#ifndef thanhtoan_h
#define thanhtoan_h

public: 
	void gui_lenh_cho_nv11();
	void doc_ban_phim();
	void doc_tien();
	void phan_tich_cau_tra_loi_giu_tien();
	void phan_tich_cau_tra_loi_tham_do();
	unsigned char trang_thai_ban_phim();
	bool dem_thoi_gian_khong_nhan_phim();
	bool kiem_tra_tinh_hop_le_cua_o_hang();
	void trang_thai_chon_hang(void);
	void thong_bao_lcd_neu_chon_o_hang_sai();
	
	void nuot_tien();
	void dua_hang_ra();
	void quay_dong_co();
	void tru_hang_hoac_khoa_o_hang();
	void enter_hay_cancel();
	
	void tra_lai_tien();
	
	
/* ================================================================================================== */
/* KẾT THÚC MỤC THANH TOÁN, CHUYỂN SANG TÍNH TOÁN DOANH THU ========================================= */	
	
	
	
	
#endif




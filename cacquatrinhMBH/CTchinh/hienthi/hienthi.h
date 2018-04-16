/*
	Chứa các hàm màn hình hiển thị LCD của máy bán hàng tự động

*/

#ifndef hienthi_h
#define hienthi_h

public: 

		void lcd_start1_tab1();												// Màn hình LCD kiểm tra lỗi đầu chương trình
		void lcd_start2_tab1();
		void lcd_start3_tab1();
		void lcd_start1_tab2();
		
		void lcd_khong_o_trong_thoi_gian_hoat_dong(); 						// Màn hình LCD thông báo máy không hoạt động
		void lcd_hay_chon_hang_can_mua();									//
		void hien_thi_so_nhap_tu_ban_phim();								//
		void lcd_mua_hang_thanh_cong();										//
		void lcd_huy_giao_dich();											//
		void lcd_balance_item();											//
		void lcd_xac_nhan_mua_hang();										//
		void lcd_ban_co_muon_dua_them_tien_vao_may();						//
		void lcd_mua_hang_tiep();											//
		void lcd_dang_tra_lai_tien();										//
		void lcd_da_het_tien_tra_lai_xin_mua_hang_tiep();					//
		void cap_nhat_lcd();												// Cập nhật LCD trong quá trình chọn hàng
		
		//==================================
		void lcd_quay_dong_co();
		void lcd_thong_bao_chon_hang_sai();
	
#endif
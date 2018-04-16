/*
	Các hàm sử dụng trong mục cài đặt
*/

#ifndef caidatchung_h
#define caidatchung_h


public: 

	#include <cacquatrinhMBH/CTcaidat/CD_doanhthu/CD_doanhthu.h>
	#include <cacquatrinhMBH/CTcaidat/CD_giatien/CD_giatien.h>
	#include <cacquatrinhMBH/CTcaidat/CD_khoaohang/CD_khoaohang.h>
	#include <cacquatrinhMBH/CTcaidat/CD_sohang/CD_sohang.h>
	#include <cacquatrinhMBH/CTcaidat/CD_nhatkyloi/CD_nhatkyloi.h>
	#include <cacquatrinhMBH/CTcaidat/CD_themtientralai/CD_themtientralai.h>
	#include <cacquatrinhMBH/CTcaidat/CD_lamrongBTL/CD_lamrongBTL.h>
	
	#include <cacquatrinhMBH/CTcaidat/CD_led/CD_led.h>
	#include <cacquatrinhMBH/CTcaidat/CD_maylanh/CD_maylanh.h>
	#include <cacquatrinhMBH/CTcaidat/CD_nhietdo/CD_nhietdo.h>
	
	unsigned char vi_tri_trang_duoc_chon = 1;
	
	void NHAP_PASSWORD();
	void lua_chon_trang_cai_dat_chinh();
	void trang_muc_luc_cai_dat_chung_1();
	void trang_muc_luc_cai_dat_chung_2();
	void trang_muc_luc_cai_dat_chung_3();
	void trang_muc_luc_cai_dat_chung_4();
	void trang_muc_luc_cai_dat_chung_5();

	//Nhập code ở đây
	

	/** CÁC HÀM BỔ TRỢ -----------------------------------------------------**/
	void quet_ban_phim();
	void lua_chon_o_bat_dau();
	void lua_chon_o_ket_thuc();
	void doc_ban_phim_cd();
	
	
	

#endif
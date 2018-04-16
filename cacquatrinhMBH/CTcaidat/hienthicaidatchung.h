/*
	Các hàm hiển thị màn hình LCD trong mục cài đặt
*/ 

#ifndef hienthicaidatchung_h
#define hienthicaidatchung_h

public:

	// Các màn hình mục lục cài đặt
	void lcd_PASSWORD();
	void lcd_PASSWORD_hien_so();
	void lcd_PASSWORD_sai();
	
	void lcd_cai_dat_chung(char string_1[], char string_2[], char string_3[], char string_4[]);
	void lcd_cai_dat_chung_2();
	void lcd_cai_dat_chung_3();
	void lcd_cai_dat_chung_4();
	void lcd_cai_dat_chung_5();
	
// -----------------------------------------------------------------------------------------------
	#include <cacquatrinhMBH/CTcaidat/CD_doanhthu/hienthi_doanhthu.h>
	#include <cacquatrinhMBH/CTcaidat/CD_giatien/hienthi_giatien.h>
	#include <cacquatrinhMBH/CTcaidat/CD_khoaohang/hienthi_khoaohang.h>
	#include <cacquatrinhMBH/CTcaidat/CD_sohang/hienthi_sohang.h>
	#include <cacquatrinhMBH/CTcaidat/CD_nhatkyloi/hienthi_nhatkyloi.h>
	#include <cacquatrinhMBH/CTcaidat/CD_themtientralai/hienthi_themtien.h>
	#include <cacquatrinhMBH/CTcaidat/CD_lamrongBTL/hienthi_lamrongBTL.h>
	
	#include <cacquatrinhMBH/CTcaidat/CD_led/hienthi_CDled.h>
	#include <cacquatrinhMBH/CTcaidat/CD_maylanh/hienthi_CD_maylanh.h>
	#include <cacquatrinhMBH/CTcaidat/CD_nhietdo/hienthi_CD_nhietdo.h>
	
// -----------------------------------------------------------------------------------------------
// Màn hình sử dụng chung của các mục cài đặt:

	void lcd_xong();
	
#endif
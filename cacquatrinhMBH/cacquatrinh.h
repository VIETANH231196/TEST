/*
	Tổng hợp các quá trình giữa SIM, thanh toán và hiển thị
*/

#ifndef cacquatrinh_h
#define cacquatrinh_h

bool kiem_tra_cam_bien_cua();
/* ======================================================== */
void qua_trinh_doc_EEPROM(void);
#include <cacquatrinhMBH/CTchinh/kiemtraEEPROM/kiemtraEEPROM.h>

/* ======================================================== */
void qua_trinh_mua_hang(void);
// =============================
	void qua_trinh_chon_hang();
	void qua_trinh_xu_ly_tien_va_hang();
	void qua_trinh_tra_lai();

/* ======================================================== */
void qua_trinh_tinh_va_luu_doanh_thu_EEPROM();

/* ======================================================== */
void qua_trinh_cai_dat(void);
// =============================
	void quet_ban_phim_cai_dat();
	void giu_ket_noi_voi_nv11();
	void lua_chon_trang_cai_dat_tren_tab_muc_luc();

void luu_du_lieu_mua_hang_bt(unsigned int sdt, unsigned int stn, unsigned char o, unsigned char ttl, unsigned int sds, unsigned long long int tg1, unsigned long long int tg2);
#endif
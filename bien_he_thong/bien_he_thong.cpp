/*
	Khai báo các biến hệ thống ở đây
*/
#include "bien_he_thong.h"

int trang_thai_cua_nv11;						// Biến trạng thái hành động của NV11 sau khi nhận được tiền: có 4 trạng thái như ở dưới
unsigned char hanh_dong_tiep_theo_cua_nv11;		// Yêu cầu hành động tiếp theo của NV11
unsigned char trang_thai_BTL;
unsigned char trang_thai_gui_goi_tin;

unsigned int tai_khoan = 0;								//Biến tài khoản của hệ thống

unsigned char gia_tien[100];
unsigned char so_hang[100];
unsigned char o_hang_loi[100]; 							// Các ô hàng hợp lệ:

// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH KIỂM TRA TÍNH PHÙ HỢP CỦA Ô HÀNG
const unsigned char loi = 0;
const unsigned char khong_khoa_khong_loi = 1;
const unsigned char khoa = 2;

unsigned char key = 0x00;								// Biến đọc trạng thái bàn phím

bool trang_thai_dau_ngam;								// Biến trạng thái của đầu ngậm tiền: 2 trạng thái: có và không có tiền
const bool khong_co_tien = 0;
const bool co_tien = 1;

// ========================================================

unsigned int dem_thoi_gian_quet_phim = 0; 				// Biến đếm thời gian dành cho vòng lặp quét bàn phím
unsigned long int dem_thoi_gian_chuyen_man_hinh = 0;
// ========================================================
// Các biến thông số máy

volatile unsigned char nhiet_do_hien_tai_cua_may;		// Biến nhiệt độ hiện tại của máy
unsigned char trang_thai_cua;

// ========================================================
// Các biến quét bàn phím
unsigned char phim_1, phim_2, phim;

// Các biến chuyển màn hình bàn phím
const bool trang_0 = 0;
const bool trang_1 = 1;
bool man_hinh;

unsigned char TRANG_THAI_CHON_HANG;						// Các trạng thái chọn hàng
const unsigned char chon_dung_hop_le = 3;				// Chọn đúng ô hàng
const unsigned char chon_dung_nhung_chua_hop_le = 2;	// Chọn đúng ô hàng không lỗi tuy nhiên giá tiền chưa hợp lệ
const unsigned char chon_sai = 1;						// Chọn sai ô hàng (ô hàng bị khóa hoặc không tồn tại)
const unsigned char chua_chon = 0;						// Chưa chọn ô hàng nào cả

bool TRANG_THAI_MUA_HANG;
const bool xong = 1;
const bool chua_xong = 0;

unsigned short int so_tien_trong_ngan_tra_lai;

// Biến trạng thái enter/cancel
unsigned char phim_xac_nhan = 0;

unsigned int menh_gia_tien_dang_giu = 0;
unsigned int menh_gia_tien_da_nuot = 0;

/* ==========================================================================================================*/
/* ===================================== CÁC BIẾN THÊM MỚI LONG =============================================*/

// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH TRẢ LẠI

unsigned char so_to_tien_co_trong_bo_tra_lai = 0;		// Số tờ tiền trong bộ trả lại
unsigned int tong_so_tien_co_trong_bo_tra_lai = 0;		// Tổng số tiền trong bộ trả lại
unsigned int so_tien_can_tra_lai = 0;					// Số tiền cần trả lại
unsigned char so_to_can_dua_ra;							// Số tờ tiền cần đưa ra

// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH CÀI ĐẶT

unsigned char trang_muc_luc_cai_dat = 1; 	// Đặt trang mục lục ban đầu mặc định là 1
unsigned char trang_cai_dat_duoc_lua_chon = 0;
// -------------------------------------------------------
// Mục cài đặt giá tiền
unsigned char o_bat_dau, o_ket_thuc;		// Chọn ô bắt đầu và ô kết thúc chung trong 3 mục cài đặt 1-1; 1-2; 1-3
unsigned int gia_cai_dat;					// Giá hàng cài đặt trong mục 1-1: cài đặt giá tiền
unsigned char so_hang_cai_dat;				// Cài đặt số hàng trong mục 1-2: cài đặt số hàng
unsigned char o_hang_khoa_cai_dat;			// Cài đặt ô hàng cần khóa trong mục 1-3: cài đặt ô hàng khóa
unsigned char vi_tri_con_tro_lcd = 1;		// Dùng ở 3 trang trong tab 1 mục cài đặt vì 3 trang này tương tự nhau (có 3 vị trí con trỏ)
unsigned char da_nhap = 0; 					// Số ô đã nhập, // Dùng ở 3 trang trong tab 1 mục cài đặt vì 3 trang này tương tự nhau 

// -------------------------------------------------------
// Mục nhật ký lỗi
unsigned char dong_1_lcd = 0;
unsigned char dong_2_lcd = 0;

// -------------------------------------------------------
// Mục doanh thu ngày, tháng, năm
//---------------------------------------------------------

unsigned int tien_vao_ngay, doanh_thu_ngay, tien_ra_ngay;			// Doanh thu theo ngày
unsigned long int tien_vao_thang, doanh_thu_thang, tien_ra_thang;	// Doanh thu theo tháng
unsigned long int tien_vao_nam, doanh_thu_nam, tien_ra_nam;			// Doanh thu theo năm

// Các biến sử dụng trong mục tính toán doanh thu sau 1 lần mua hàng
unsigned int so_tien_nuot_vao, so_du_luc_truoc, doanh_thu_1_lan_mua_hang, so_tien_tra_lai, so_du_luc_sau;

unsigned int nam_cua_o_nho, nam_nay;
unsigned char thang_cua_o_nho, ngay_cua_o_nho, thang_nay, ngay_hom_nay;

unsigned char dong_co_ok;

/* Hòa *************************************************************/
/**************Các biến sử dụng cho thông báo các trạng thái của SIM800C***********/
unsigned int TRANG_THAI_GUI_GOI_TIN=0;                                 //Biến báo gói tin cần gửi
unsigned int SEND_STATUS;                                              //Biến báo gửi Server thành công
unsigned int GPRS_STATUS;                                              //Trạng thái GPRS của sim =1 là đang có GPRS
unsigned int SONG_STATUS;                                              //Trạng thái sóng của sim
//unsigned int SIM_STATUS;                                                   //Trạng thái hoạt động của SIM

/* A.Ngọc *************************************************************/
char value_password[6] = {9, 9, 9, 9, 9, 9};
char value_password_admin[6] = {0, 0, 0, 0, 0, 0};
char password_nhap[6]={'*','*','*','*','*','*'};
char password_chu_so=0;
char value_ID[10]= {2, 0, 1, 8, 0, 0, 0, 0, 0, 0 };
char chu_so_ID=0;

unsigned char value_nhiet_do_cai_dat;
unsigned int thoi_gian_bat_do_nhiet;
unsigned char value_tt_ML=0;
unsigned char value_trang_thai_led=1;
unsigned char value_trang_thai_cbroi=0;
unsigned char value_ngon_ngu=0; 

//unsigned long int  value_ID= 201800000;
unsigned char value_time_on=7;
unsigned char value_time_off=20;

unsigned char value_tg_luu_so_tai_khoan=3;
unsigned char value_lien_ket_1=00;
unsigned char value_lien_ket_2=00;
//unsigned long int value_password=999999;
//unsigned long int password_nhap;
unsigned char  password_ok= 0;
unsigned char  password_ok_admin=0;
unsigned long int value_tghoatdong=900000000;
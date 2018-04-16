/*
	Khai báo các biến hệ thống ở đây
*/

#ifndef bien_he_thong_h
#define bien_he_thong_h

extern int trang_thai_cua_nv11;	//Biến trạng thái hành động của NV11 sau khi nhận được tiền: có 4 trạng thái như ở dưới
#define _trang_thai_cho 0 //Trạng thái khi đang nhận dạng tiền được coi như là trạng thái chưa nhận được tiền

#define _dang_nhan_dang_tien 1
#define _dang_giu_tien 2				
#define _dang_nuot_tien 3
#define _dang_tu_choi_tien 4
#define _dang_cho_tien_tra_lai_duoc_lay_ra 5

#define _da_nhan_dang_tien 10

#define _da_dua_tien_len_note_float 11		// Trạng thái mang tính kết thúc
#define _da_dua_tien_xuong_stack 12			// Trạng thái mang tính kết thúc
#define _da_day_tien_stack 13				// Ngăn chứa đã đầy tiền

#define _da_mat_ket_noi 14
#define _da_tu_choi_to_tien 15				// Trạng thái mang tính kết thúc
#define _da_credited 16

extern unsigned char trang_thai_BTL;
#define _chua_day_tien_note_float 0		// Note float đã đầy tiền trả lại
#define _da_day_tien_note_float 1		// Note float đã đầy tiền trả lại


extern unsigned char hanh_dong_tiep_theo_cua_nv11;
#define _tham_do_trang_thai_cua_nv11 0
#define _giu_tien 1
#define _nuot_tien 2
#define _tu_choi_tien 3
#define _tra_lai_tien 4
#define _lam_rong_BTL 5
#define _tra_cuu_so_tien_trong_BTL 6
#define _doc_lenh_theo_kenh 7
#define _doc_lenh_theo_gia_tri 8
#define _ket_noi_dau_doc_tien 9
#define _ngat_ket_noi_dau_doc 10

extern unsigned char trang_thai_gui_goi_tin;
#define chua_gui 0
#define da_gui 1

extern unsigned int tai_khoan;	//Biến tài khoản của hệ thống

extern unsigned char gia_tien [100];
extern unsigned char so_hang [100];
// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH KIỂM TRA TÍNH PHÙ HỢP CỦA Ô HÀNG
extern unsigned char o_hang_loi[100];
extern const unsigned char loi;
extern const unsigned char khong_khoa_khong_loi;
extern const unsigned char khoa;

extern unsigned char key;			// Biến quét bàn phím

extern bool trang_thai_dau_ngam;	//Biến trạng thái của đầu ngậm tiền: 2 trạng thái: có và không có tiền
extern const bool khong_co_tien;
extern const bool co_tien;

//==================================

extern unsigned int dem_thoi_gian_quet_phim; //Biến đếm thời gian dành cho vòng lặp quét bàn phím
extern unsigned long int dem_thoi_gian_chuyen_man_hinh;
//==================================
//Các biến thông số máy

extern volatile unsigned char nhiet_do_hien_tai_cua_may;//Biến nhiệt độ hiện tại của máy
extern unsigned char trang_thai_cua;


//Các biến quét bàn phím
extern unsigned char phim_1, phim_2, phim;

//Các biến chuyển màn hình bàn phím
extern const bool trang_0;
extern const bool trang_1;
extern bool man_hinh;

extern unsigned char TRANG_THAI_CHON_HANG;	// Các trạng thái chọn hàng
extern const unsigned char chon_dung_hop_le;		// Chọn đúng ô hàng
extern const unsigned char chon_dung_nhung_chua_hop_le;
extern const unsigned char chon_sai;		// Chọn sai ô hàng (ô hàng bị khóa hoặc không tồn tại)
extern const unsigned char chua_chon;		// Chưa chọn ô hàng nào cả

extern bool TRANG_THAI_MUA_HANG;
extern const bool xong;
extern const bool chua_xong;

//Biến trạng thái enter/cancel
extern unsigned char phim_xac_nhan; // Giá trị 0x23(CANCEL) hoặc 0x2A(ENTER)

extern unsigned int menh_gia_tien_dang_giu;
extern unsigned int menh_gia_tien_da_nuot;

/* ==========================================================================================================*/
/* ===================================== CÁC BIẾN THÊM MỚI LONG =============================================*/

// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH TRẢ LẠI
extern unsigned char so_to_tien_co_trong_bo_tra_lai;
extern unsigned int tong_so_tien_co_trong_bo_tra_lai;
extern unsigned int so_tien_can_tra_lai;
extern unsigned char so_to_can_dua_ra;

// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH GỬI DỮ LIỆU QUA SIM

extern unsigned char TRANG_THAI_GUI_DU_LIEU_QUA_SIM;
extern const unsigned char khoi_dong_may;
extern const unsigned char gui_lenh_theo_chu_ky;
extern const unsigned char mo_cua;
extern const unsigned char dong_cua;
extern const unsigned char mua_hang_binh_thuong;
extern const unsigned char mua_hang_loi;
extern const unsigned char loi_thiet_bi;

// ========================================================
// CÁC BIẾN SỬ DỤNG TRONG QUÁ TRÌNH CÀI ĐẶT

extern unsigned char trang_muc_luc_cai_dat;
extern unsigned char trang_cai_dat_duoc_lua_chon;
// -------------------------------------------------------
// Mục cài đặt giá tiền
extern unsigned char o_bat_dau, o_ket_thuc;
extern unsigned int gia_cai_dat;
extern unsigned char so_hang_cai_dat;
extern unsigned char o_hang_khoa_cai_dat;
extern unsigned char vi_tri_con_tro_lcd;
extern unsigned char da_nhap;
// -------------------------------------------------------
// Mục nhật ký lỗi
extern unsigned char dong_1_lcd, dong_2_lcd;

// -------------------------------------------------------
// Mục doanh thu ngày, tháng, năm
//---------------------------------------------------------

extern unsigned int tien_vao_ngay, doanh_thu_ngay, tien_ra_ngay;
extern unsigned long int tien_vao_nam, doanh_thu_nam, tien_ra_nam;
extern unsigned long int tien_vao_thang, doanh_thu_thang, tien_ra_thang;

// Các biến sủ dụng trong quá trình tính toán doanh thu sau 1 lần mua hàng
extern unsigned int so_tien_nuot_vao, so_du_luc_truoc, doanh_thu_1_lan_mua_hang, so_tien_tra_lai, so_du_luc_sau;

extern unsigned int nam_cua_o_nho, nam_nay;
extern unsigned char thang_cua_o_nho, ngay_cua_o_nho,thang_nay, ngay_hom_nay;

extern unsigned char dong_co_ok;
/**************Các biến sử dụng cho thông báo các trạng thái của SIM800C***********/
extern unsigned int TRANG_THAI_GUI_GOI_TIN;                                        //Biến báo gói tin cần gửi
extern unsigned int SEND_STATUS;                                              //Biến báo gửi Server thành công
extern unsigned int GPRS_STATUS;                                              //Trạng thái GPRS của sim
extern unsigned int SONG_STATUS;                                              //Trạng thái sóng của sim
//extern unsigned int SIM_STATUS;                                                   //Trạng thái hoạt động của SIM
/* A.Ngọc *************************************************************/
extern char value_password[6];
extern char value_password_admin[6];
extern char password_nhap[6];
extern char password_chu_so;
extern char value_ID[10];
extern char chu_so_ID;

extern unsigned char value_nhiet_do_cai_dat;
extern unsigned int thoi_gian_bat_do_nhiet;
extern unsigned char value_tt_ML;
extern unsigned char value_trang_thai_led;
extern unsigned char value_trang_thai_cbroi;
extern unsigned char value_ngon_ngu; 

//unsigned long int  value_ID= 201800000;
extern unsigned char value_time_on;
extern unsigned char value_time_off;

extern unsigned char value_tg_luu_so_tai_khoan;
extern unsigned char value_lien_ket_1;
extern unsigned char value_lien_ket_2;
//unsigned long int value_password=999999;
//unsigned long int password_nhap;
extern unsigned char  password_ok;
extern unsigned char  password_ok_admin;
extern unsigned long int value_tghoatdong;


#endif

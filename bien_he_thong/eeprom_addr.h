/*
	File phân vùng địa chỉ cho bộ nhớ EEPROM
*/

#ifndef eeprom_addr_h
#define eeprom_addr_h

extern unsigned char ADDR_GIA_TIEN [60];				// Địa chỉ các ô nhớ lưu giá tiền của mỗi ngăn chứa
extern unsigned char ADDR_SO_HANG [60];					// Địa chỉ các ô nhớ lưu trữ số hàng trên mỗi ngăn chứa hàng
extern unsigned char ADDR_LOI_DC [60];					// Địa chỉ các ô nhớ lưu trữ lỗi của các động cơ

extern unsigned char ADDR_TAI_KHOAN[2];					// Địa chỉ ô nhớ lưu tài khoản
	
#define ADDR_LOI_NV11 300								// Địa chỉ ô ghi lỗi NV11
#define ADDR_LOI_SIM 301								// Địa chỉ ô ghi lỗi SIM

#define ADDR_TRANG_THAI_LED 302							// Địa chỉ ô lưu trạng thái cài đặt led
#define ADDR_TRANG_THAI_CBROI 303						// Địa chỉ ô lưu trạng thái bật/tắt chế độ cảm biến rơi
#define ADDR_NGON_NGU 304								// Địa chỉ ô lưu ngôn ngữ đang bật/tắt
#define ADDR_NHIET_DO_CAI_DAT 305						// Địa chỉ ô lưu nhiệt độ cài đặt

#define ADDR_KIEM_TRA_KET_NOI 306						// Địa chỉ của ô nhớ nhằm kiểm tra kết nối EEPROM
	
/* =========================================================================================================== */
/* =========================================================================================================== */
// Địa chỉ biến lưu theo thuật toán mới: Bắt đầu từ ô nhớ số 500, lưu theo gói tin
//--------------------------------------------------------------------------------------------------------------
// 1. Đối với doanh thu lưu theo ngày: Hiển thị và lưu trữ doanh thu của 30 ngày gần nhất. 
// Đọc lại từ bộ nhớ mỗi khi chuyển ngày

extern unsigned int ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[2];
extern unsigned int ADDR_TONG_SO_GOI_TIN;
extern unsigned int ADDR_BAT_DAU_GOI_TIN_DT_NGAY[31]; // Ngày hôm nay
// 1 byte báo có dữ liệu/ 2 byte năm/ 1 byte tháng/ 1 byte ngày/ 2 byte tiền vào/ 2 byte doanh thu/ 2 byte tiền ra

// 1 byte báo có dữ liệu/ 2 byte năm/ 1 byte tháng/ 4 byte tiền vào/ 4 byte doanh thu/ 4 byte tiền ra
extern unsigned int ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[2];
extern unsigned int ADDR_TONG_SO_GOI_TIN_DT_THANG;
extern unsigned int ADDR_BAT_DAU_GOI_TIN_DT_THANG[13];

// 1 byte báo có dữ liệu/ 2 byte năm/ 1 byte tháng/ 4 byte tiền vào/ 4 byte doanh thu/ 4 byte tiền ra
extern unsigned int ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[2];
extern unsigned int ADDR_TONG_SO_GOI_TIN_DT_NAM;
extern unsigned int ADDR_BAT_DAU_GOI_TIN_DT_NAM[3];

/*******************************Vùng nhớ cho dữ liệu Sim800C**********************************************************/
extern unsigned int ADDR_SIM_ID_MBH[10];                               //Mã số của máy bán hàng
//1. ĐỊA CHỈ CHO SIM KHỞI ĐỘNG MÁY--------------------------------------------------
extern unsigned int ADDR_SIM_KHOI_DONG;                                //Báo máy đã khởi động: 0x31
//2. ĐỊA CHỈ CHO SIM GỬI CHU KÌ-----------------------------------------------------
extern unsigned int ADDR_SIM_TRANG_THAI_CUA;                           //Báo trạng thái cửa: 0x30 đóng, 0x31 mở
extern unsigned int ADDR_SIM_NHIET_DO;                                 //Nhiệt độ hiện tại của máy
extern unsigned int ADDR_SIM_LOI_DAU_DOC;                              //Báo lỗi đầu đọc: 0x30 lỗi, 0x31 không lỗi
extern unsigned int ADDR_SIM_SO_TIEN_NGAN_TRA_LAI;                     //Số tờ tiền trong ngăn trả lại: 0x0A, 10 tờ
extern unsigned int ADDR_SIM_MENH_GIA_TIEN_TRA_LAI;                    //Mệnh giá tiền trong ngăn trả lại: 0x05, 5 nghìn
extern unsigned int ADDR_SIM_TIME_HOAT_DONG[4];       //Tổng thời gian hoạt động cửa máy
extern unsigned int ADDR_SIM_HANG_TUNG_KHAY[60];                       //Số lượng hàng trên từng khay SIM_HANG_TUNG_KHAY[0]=0x05; 5 hàng trên khay 1
extern unsigned int ADDR_SIM_THOI_GIAN_KET_THUC[6];                    //Thời gian tại thời điểm gửi đi
//3. ĐỊC CHỈ SIM BÁO MỞ CỬA//ADDR_SIM_THOI_GIAN_KET_THUC[6]------------------------------
//4. ĐỊA CHỈ SIM BÁO ĐÓNG CỬA------------------------------------------------------------
extern unsigned int ADDR_SIM_TRANG_THAI_LED;                             //Trạng thái đèn led: 0x30 tắt, 0x31 bật
extern unsigned int ADDR_SIM_NHIET_DO_CAI_DAT;                           //Nhiệt độ cài đặt máy: 0x18, 24 độ
extern unsigned int ADDR_SIM_TRANG_THAI_CB_ROI;                          //Trạng thái cảm biến rơi: 0x30 tắt, 0x31 bật
//ADDR_SIM_SO_TIEN_NGAN_TRA_LAI
extern unsigned int ADDR_SIM_GIA_TIEN_KHAY[60];                               //Giá tiền trên từng khay SIM_GIA_TIEN_KHAY[0]=0x05; 5 nghìn hàng trên khay 1
//ADDR_SIM_HANG_TUNG_KHAY
//ADDR_SIM_THOI_GIAN_KET_THUC
//5. ĐỊA CHỈ SIM BÁO MUA HÀNG--------------------------------------------------------------
extern unsigned int ADDR_SIM_SO_TIEN_DU[2];                      //Báo số tiền dư
extern unsigned int ADDR_SIM_SO_TIEN_VAO_MAY[2] ;                //Báo số đưa vào máy
extern unsigned int ADDR_SIM_O_CHON;                                    //Ô hàng mà người mua lựa chọn 0x30 : ô hàng số 48
extern unsigned int ADDR_SIM_GIA_O_CHON;                                //Báo giá ô được chọn                                               
extern unsigned int ADDR_SIM_TIEN_TRA_LAI;                              //Số tiền trả lại khách : 0x0F trả lại 15 ngàn 
extern unsigned int ADDR_SIM_TIEN_CON_LAI[2];                     //Số tiền còn lại sau khi mua
extern unsigned int ADDR_SIM_THOI_GIAN_BAT_DAU[6];                          //Thời gian tại thời điểm gửi đi
//ADDR_SIM_THOI_GIAN_KET_THUC[6]
//6. ĐỊA CHỈ SIM BÁO MUA HÀNG LỖI----------------------------------------------------------
//ADDR_SIM_SO_TIEN_DU
//ADDR_SIM_SO_TIEN_VAO_MAY
extern unsigned int ADDR_SIM_O_CHON_LOI;                                     //Ô hàng lỗi mà người mua lựa chọn 0x30 : ô hàng số 48
extern unsigned int ADDR_SIM_GIA_O_CHON_LOI;                                 //Báo giá ô được chọn lỗi    
extern unsigned int ADDR_SIM_O_LAN_1;                                        //Ô người mua hàng chọn lần 1, 0x01 ô số 1
extern unsigned int ADDR_SIM_O_LAN_2;                                        //Ô người mua hàng chọn lần 2, 0x02 ô số 2
//ADDR_SIM_TIEN_TRA_LAI
//ADDR_SIM_THOI_GIAN_BAT_DAU
//ADDR_SIM_THOI_GIAN_KET_THUC[6]
//7. ĐỊA CHỈ SIM BÁO LỖI THIẾT BỊ----------------------------------------------------------
extern unsigned int ADDR_SIM_LOI_THIET_BI;                                   //Báo lỗi thiết bị
extern unsigned int ADDR_SIM_TRANG_THAI_LOI;                                 //Báo trạng thái lỗi của thiết bị
//8. ĐỊA CHỈ SIM BÁO DOANH THU--------------------------------------------------------------
extern unsigned int ADDR_SIM_DOANH_THU[4];                  //Báo tổng doanh thu trong ngày
extern unsigned int ADDR_SIM_TONG_SO_LOI;                                    //Tổng số lỗi trong ngày
extern unsigned int ADDR_SIM_NGAY_TINH_DOANH_THU[3];             //Ngày tính doanh thu
/***********************************************************************************************************/
extern unsigned int ADDR_TRANG_THAI_ML;




#endif
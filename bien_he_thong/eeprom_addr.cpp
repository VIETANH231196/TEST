/*
	File phân vùng địa chỉ cho bộ nhớ EEPROM
*/

#include "eeprom_addr.h"
#include <avr/pgmspace.h>

unsigned char ADDR_GIA_TIEN[60] = 						// Địa chỉ các ô nhớ lưu giá tiền của mỗi ngăn chứa
{
	0, 	1, 	2, 	3, 	4, 	5, 	6, 	7, 	8, 	9,
	10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
	20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
	30,	31,	32,	33,	34,	35,	36,	37,	38,	39,
	40,	41,	42,	43,	44,	45,	46,	47,	48,	49,
	50,	51,	52,	53,	54,	55,	56,	57,	58,	59
};

unsigned char ADDR_SO_HANG[60] =							// Địa chỉ các ô nhớ lưu trữ số hàng trên mỗi ngăn chứa hàng
{
	60,61,62,63,64,65,66,67,68,69,
	70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,
	90,91,92,93,94,95,96,97,98,99,
	100,101,102,103,104,105,106,107,108,109,
	110,111,112,113,114,115,116,117,118,119
};

unsigned char ADDR_LOI_DC[60] = 							// Địa chỉ các ô nhớ lưu trữ lỗi của các động cơ
{
	120,121,122,123,124,125,126,127,128,129,
	130,131,132,133,134,135,136,137,138,139,
	140,141,142,143,144,145,146,147,147,149,
	150,151,152,153,154,155,156,157,158,159,
	160,161,162,163,164,165,166,167,168,169,
	170,171,172,173,174,175,176,177,178,179
};

unsigned char ADDR_TAI_KHOAN[2] = {180, 181};					// Địa chỉ biến tài khoản
	
/* =========================================================================================================== */
/* =========================================================================================================== */
// Địa chỉ biến lưu theo thuật toán mới: Bắt đầu từ ô nhớ số 500, lưu theo gói tin
// --------------------------------------------------------------------------------------------------------------
// 1. Đối với doanh thu lưu theo ngày: Hiển thị và lưu trữ doanh thu của 30 ngày gần nhất. 
// Đọc lại từ bộ nhớ mỗi khi chuyển ngày
unsigned int ADDR_DC_GOI_TIN_DT_NGAY_HIEN_TAI[2] = {498, 499};	// Địa chỉ lưu giữ thông tin gói tin hiện tại
unsigned int ADDR_TONG_SO_GOI_TIN = 500;
unsigned int ADDR_BAT_DAU_GOI_TIN_DT_NGAY[31] = 
{
	501, 512, 523, 534, 545, 556, 567, 578, 589, 600,
	611, 622, 633, 644, 655, 666, 677, 688, 699, 710,
	721, 732, 743, 754, 765, 776, 787, 798, 809, 820,
	831
};

// 1 byte báo có dữ liệu/ 2 byte năm/ 1 byte tháng/ 4 byte tiền vào/ 4 byte doanh thu/ 4 byte tiền ra
unsigned int ADDR_DC_GOI_TIN_DT_THANG_HIEN_TAI[2] = {1198, 1199};
unsigned int ADDR_TONG_SO_GOI_TIN_DT_THANG = 1200;
unsigned int ADDR_BAT_DAU_GOI_TIN_DT_THANG[13] =
{
	1201, 1217, 1233, 1249, 1265, 1281, 1297, 1303, 1319, 1335, 1351, 1367, 1383
};

// 1 byte báo có dữ liệu/ 2 byte năm/ 1 byte tháng/ 4 byte tiền vào/ 4 byte doanh thu/ 4 byte tiền ra
unsigned int ADDR_DC_GOI_TIN_DT_NAM_HIEN_TAI[2] = {1598, 1599};
unsigned int ADDR_TONG_SO_GOI_TIN_DT_NAM = 1600;
unsigned int ADDR_BAT_DAU_GOI_TIN_DT_NAM[3] = {1601, 1616, 1631};
// 1 byte báo có dữ liệu/ 2 byte năm/ 4 byte tiền vào/ 4 byte doanh thu/ 4 byte tiền ra

/*******************************Vùng nhớ cho dữ liệu Sim800C**********************************************************/
unsigned int ADDR_SIM_ID_MBH[10]=                        //Mã số của máy bán hàng
{
	2000,2001,2002,2003,2004,2005,2006,2007,2008,2009
};
//1. ĐỊA CHỈ CHO SIM KHỞI ĐỘNG MÁY--------------------------------------------------
unsigned int ADDR_SIM_KHOI_DONG=2010;                                //Báo máy đã khởi động: 0x31
//2. ĐỊA CHỈ CHO SIM GỬI CHU KÌ-----------------------------------------------------
unsigned int ADDR_SIM_TRANG_THAI_CUA=2011;                           //Báo trạng thái cửa: 0x30 đóng, 0x31 mở
unsigned int ADDR_SIM_NHIET_DO=2012;                                 //Nhiệt độ hiện tại của máy
unsigned int ADDR_SIM_LOI_DAU_DOC=2013;                              //Báo lỗi đầu đọc: 0x30 lỗi, 0x31 không lỗi
unsigned int ADDR_SIM_SO_TIEN_NGAN_TRA_LAI=2014;                     //Số tờ tiền trong ngăn trả lại: 0x0A, 10 tờ
unsigned int ADDR_SIM_MENH_GIA_TIEN_TRA_LAI=2015;                    //Mệnh giá tiền trong ngăn trả lại: 0x05, 5 nghìn
unsigned int ADDR_SIM_TIME_HOAT_DONG[4]={2016,2017,2018,2019};       //Tổng thời gian hoạt động cửa máy
unsigned int ADDR_SIM_HANG_TUNG_KHAY[60]=                            //Số lượng hàng trên từng khay SIM_HANG_TUNG_KHAY[0]=0x05; 5 hàng trên khay 1
{
	2020,2021,2022,2023,2024,2025,2026,2027,2028,2029,
	2030,2031,2032,2033,2034,2035,2036,2037,2038,2039,
	2040,2041,2042,2043,2044,2045,2046,2047,2048,2049,
	2050,2051,2052,2053,2054,2055,2056,2057,2058,2059,
	2060,2061,2062,2063,2064,2065,2066,2067,2068,2069,
	2070,2071,2072,2073,2074,2075,2076,2077,2078,2079	
};
unsigned int ADDR_SIM_THOI_GIAN_KET_THUC[6]=                         //	Thời gian tại thời điểm gửi đi
{
	2080,2081,2082,2083,2084,2085
};
//3. ĐỊC CHỈ SIM BÁO MỞ CỬA//ADDR_SIM_THOI_GIAN_KET_THUC[6]------------------------------
//4. ĐỊA CHỈ SIM BÁO ĐÓNG CỬA------------------------------------------------------------
unsigned int ADDR_SIM_TRANG_THAI_LED=2086;                            // Trạng thái đèn led: 0x30 tắt, 0x31 bật
unsigned int ADDR_SIM_NHIET_DO_CAI_DAT=2087;                          // Nhiệt độ cài đặt máy: 0x18, 24 độ
unsigned int ADDR_SIM_TRANG_THAI_CB_ROI=2088;                         // Trạng thái cảm biến rơi: 0x30 tắt, 0x31 bật
//ADDR_SIM_SO_TIEN_NGAN_TRA_LAI
unsigned int ADDR_SIM_GIA_TIEN_KHAY[60]=                              // Giá tiền trên từng khay SIM_GIA_TIEN_KHAY[0]=0x05; 5 nghìn hàng trên khay 1
{
	2090,2091,2092,2093,2094,2095,2096,2097,2098,2099,
	2100,2101,2102,2103,2104,2105,2106,2107,2108,2109,
	2110,2111,2112,2113,2114,2115,2116,2117,2118,2119,
	2120,2121,2122,2123,2124,2125,2126,2127,2128,2129,
	2130,2131,2132,2133,2134,2135,2136,2137,2138,2139,
	2140,2141,2142,2143,2144,2145,2146,2147,2148,2149	
};
//ADDR_SIM_HANG_TUNG_KHAY
//ADDR_SIM_THOI_GIAN_KET_THUC
//5. ĐỊA CHỈ SIM BÁO MUA HÀNG--------------------------------------------------------------
unsigned int ADDR_SIM_SO_TIEN_DU[2]={2150,2151};                      //Báo số tiền dư
unsigned int ADDR_SIM_SO_TIEN_VAO_MAY[2]={2152,2153};                 //Báo số đưa vào máy
unsigned int ADDR_SIM_O_CHON=2154;                                    //Ô hàng mà người mua lựa chọn 0x30 : ô hàng số 48
unsigned int ADDR_SIM_GIA_O_CHON=2155;                                //Báo giá ô được chọn                                               
unsigned int ADDR_SIM_TIEN_TRA_LAI=2156;                              //Số tiền trả lại khách : 0x0F trả lại 15 ngàn 
unsigned int ADDR_SIM_TIEN_CON_LAI[2]={2157,2158};                    //Số tiền còn lại sau khi mua
unsigned int ADDR_SIM_THOI_GIAN_BAT_DAU[6]=                           //Thời gian tại thời điểm gửi đi
{
	2159,2160,2161,2162,2163,2164
};
//ADDR_SIM_THOI_GIAN_KET_THUC[6]
//6. ĐỊA CHỈ SIM BÁO MUA HÀNG LỖI----------------------------------------------------------
//ADDR_SIM_SO_TIEN_DU
//ADDR_SIM_SO_TIEN_VAO_MAY
unsigned int ADDR_SIM_O_CHON_LOI=2165;                                     //Ô hàng lỗi mà người mua lựa chọn 0x30 : ô hàng số 48
unsigned int ADDR_SIM_GIA_O_CHON_LOI=2166;                                 //Báo giá ô được chọn lỗi    
unsigned int ADDR_SIM_O_LAN_1=2167;                                        //Ô người mua hàng chọn lần 1, 0x01 ô số 1
unsigned int ADDR_SIM_O_LAN_2=2168;                                        //Ô người mua hàng chọn lần 2, 0x02 ô số 2
//ADDR_SIM_TIEN_TRA_LAI
//ADDR_SIM_TIEN_CON_LAI
//ADDR_SIM_THOI_GIAN_BAT_DAU
//ADDR_SIM_THOI_GIAN_KET_THUC[6]
//7. ĐỊA CHỈ SIM BÁO LỖI THIẾT BỊ----------------------------------------------------------
unsigned int ADDR_SIM_LOI_THIET_BI=2169;                                   //Báo lỗi thiết bị
unsigned int ADDR_SIM_TRANG_THAI_LOI=2170;                                 //Báo trạng thái lỗi của thiết bị
//8. ĐỊA CHỈ SIM BÁO DOANH THU--------------------------------------------------------------
unsigned int ADDR_SIM_DOANH_THU[4]={2171,2172,2173,2174};                  //Báo tổng doanh thu trong ngày
unsigned int ADDR_SIM_TONG_SO_LOI=2175;                                    //Tổng số lỗi trong ngày
unsigned int ADDR_SIM_NGAY_TINH_DOANH_THU[3]={2176,2177,2178};             //Ngày tính doanh thu
/***********************************************************************************************************/

unsigned int ADDR_TRANG_THAI_ML = 2800;


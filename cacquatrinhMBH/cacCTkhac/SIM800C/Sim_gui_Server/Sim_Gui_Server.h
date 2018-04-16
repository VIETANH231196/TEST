/*
	File lập trình các câu lệnh gửi đi của SIM800C
*/

/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */
#include <Arduino.h>
#ifndef Sim_Gui_Server_H
#define Sim_Gui_Server_H
public: 
unsigned int checkSimAT=0; 
unsigned int SERVER_CONNECT=0; 
unsigned int TRANG_THAI_GUI_GOI_TIN=0;                                 //Biến báo gói tin cần gửi
unsigned int SEND_STATUS;                                              //Biến báo gửi Server thành công
unsigned int GPRS_STATUS;                                              //Trạng thái GPRS của sim =1 là đang có GPRS
unsigned int SONG_STATUS;                                              //Trạng thái sóng của sim
String SERVER_IP="103.78.88.118";                      //CỔNG SERVER MÁY BÁN HÀNG
//String SERVER_IP="192.168.20.12";
String PORT="8281";
//String SERVER_IP="google.com.vn";  
//String PORT="80";  
    /**************************Các thư viện phục vụ kèm********************************/
void Gui_Server(unsigned char arr[], unsigned int kich_thuoc);

void Hien_Thi_Phan_Hoi();         //Hàm nhận phản hồi từ chân Serial2 với Moduln Sim
#endif
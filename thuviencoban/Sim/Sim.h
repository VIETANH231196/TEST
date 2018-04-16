/*
	File lập trình các thiết lập cơ bản cho SIM800C
*/
/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */
/**------------------------------------------------------------------------
Author  : Nguyen Van Hoa ************************************************
School  : Hanoi University of Science and Technology ********************
Dept    : School of Electrical Engineering  *****************************
Phone   : 0968638223*****************************************************
------------------------CÁC HÀM SỬ DỤNG CHÍNH CHO CHỨC NĂM SIM--------------------------------
/**
1.Khởi tạo                                 :Sim.begin();
2.Chức năng gọi điện                       :Sim.Goi_dien("sdt");
2.Chức năng gửi tin nhắn                   :Sim.Gui_SMS("nội dung tin nhắt","sdt");
3.Chức năng kiểm tra chất lượng sóng       :Sim.Kiem_tra_song();
4.Chức năng đọc thời gian thực             :Sim.Doc_rtc_sim();
5.Chức năng kiểm tra chất lượng GPRS       :Sim.Kiem_tra_GPRS();
6.Chức năng kiểm tra trạng thái hoạt động  :Sim.Kiem_tra_SIM();
**/

#ifndef Sim_H
#define Sim_H
class SIM
{
	public:
		unsigned int Do_song,checkSimAT=0,SERVER_CONNECT_STATUS=0,Check_Call=0;
		unsigned int SIM_SEND_STATUS=0;                                              //Biến báo gửi Server thành công
        unsigned int SIM_GPRS_STATUS=0;                                              //Trạng thái GPRS của sim =1 là đang có GPRS
        unsigned int SIM_SONG_STATUS=0;                                              //Trạng thái sóng của sim
        unsigned int SIM_STATUS=0;                                                   //Trạng thái hoạt động của SIM
		int second, minute, hour, day, wday, month, year;        //Biến lưu thời gian thực
		void Begin();                                            //Hàm khởi tạo cho sim800c
		int Kiem_tra_song();                                    //Hàm kiểm tra sóng cho sim800c
		void Doc_rtc_sim();                                      //Hàm đọc rtc cho sim800c
		bool  Kiem_tra_GPRS();                                    //Hàm kiểm tra sóng GPRS
		bool  Kiem_tra_SIM();                                     //Hàm kiểm sim có hoạt đọng không
		void Goi_dien(String sdt);                               //Chức năng gọi điện
		void Gui_SMS(String sms,String sdt);                     //Chức năng gửi tin nhắn
		void Hien_thi_phan_hoi();                                //Hiển thị phản hồi sim800c
};

extern SIM Sim;
#endif
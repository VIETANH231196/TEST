/*
	File lập trình các câu lệnh gửi đi của SIM800C
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

#include <MBH.h>
#include "Sim.h"
    /***************************Hàm khởi tạo GPRS,kết nối cho sim800c****************************/
    void SIM::Begin()                                     
    {
		    Serial2.begin(115200);                                               //Tốc độ truyền cho chân sim
			Serial.begin(115200);                                                //Tốc độ truyền Serial
			Serial2.println("AT+IPR=115200");checkSimAT=13;
            Hien_thi_phan_hoi();
            Serial2.println("AT");checkSimAT=6;
            Hien_thi_phan_hoi();
		    Serial2.println("ATE0");checkSimAT=6;                             //Tắt phản hồi về
            Hien_thi_phan_hoi();
            Serial2.println("AT+CPIN?");checkSimAT=10;                         // thiết lập mật khẩu của thiết bị
            Hien_thi_phan_hoi();
            //CHECK_SONG();                                                   //KIỂM TRA CHẤT LƯỢNG SÓNG                                   
            Serial2.println("AT+CREG?");checkSimAT=6;                          // thông tin về tình trạng đăng ký và khả năng truy cập của thiết bị
            Hien_thi_phan_hoi();
            Serial2.println("AT+CGATT?");checkSimAT=2;                         // kiểm tra trạng thái của gói dịch vụ đính kèm
            Hien_thi_phan_hoi();
			//Kiểm tra độ dài dữ liệu đã gửi
			Serial2.println("AT+CIPQSEND=1");checkSimAT=6;                      //PHẢN HỒI LẠI ĐỘ DÀI DỮ LIỆU ĐÃ GỬI
            Hien_thi_phan_hoi();
			//Bật gprs nếu chưa kết nối
			if(SIM_GPRS_STATUS==0)
			    {
					Serial2.println("AT+CGATT=1");
					checkSimAT=1; 
					Hien_thi_phan_hoi();
				}
            Serial2.println("AT+CIPSHUT");checkSimAT=3;                        // đóng PDP của GPRS
            Hien_thi_phan_hoi();
            Serial2.println("AT+CIPSTATUS");checkSimAT=6;                      // trả về trạng thái kết nối hiện tại
            Hien_thi_phan_hoi();
            Serial2.println("AT+CIPMUX=0");checkSimAT=6;                       // cấu hình kết nối IP đơn
            Hien_thi_phan_hoi();
            Serial2.println("AT+CSTT=\"internet\"");checkSimAT=11;             // thiết lập APN cho PDP
            Hien_thi_phan_hoi();
            Serial2.println("AT+CIICR");checkSimAT=6;                          // kết nối wireless                                                                                                                                                                         
            Hien_thi_phan_hoi();
            Serial2.println("AT+CIFSR"); checkSimAT=6;                        // trả về địa chỉ IP cục bộ
            Hien_thi_phan_hoi();
            Serial2.println("AT+CIPSPRT=0");checkSimAT=6;                      //=1 Để show '>'  sau khi gửi"AT+CIPSEND"
            Hien_thi_phan_hoi();
            Serial.println("Set up SIM800C completed!");
	}
	/***************************Hàm gọi điện cho sim800c****************************************/
	void SIM::Goi_dien(String sdt)                                    
	{
			    if(Check_Call==1)delay(1500);                        //Vừa mới gửi tin nhắn xong
				Check_Call=0;
			    Serial.println("Bắt đầu gọi điện đến số: ");
                Serial.println(sdt);				
                Serial2.println("ATD" + sdt + ";"); // Gọi điện
			    checkSimAT=17;
                Hien_thi_phan_hoi();
                if(Check_Call==1)
				    {     
				        checkSimAT=14;
                        Hien_thi_phan_hoi();
						Check_Call=0;
				    }
	}
	/***************************Hàm gửi tin nhắn cho sim800c************************************/
	void SIM::Gui_SMS(String sms,String sdt)
    {
		        Serial2.write("AT+CMGF=1\r\n");       //Cài đặt định dạng bản tin
                checkSimAT=6;
                Hien_thi_phan_hoi();
                Serial2.println("AT+CMGS=\"" + sdt + "\"\r\n");//Cài đặt số điện thoại
                checkSimAT=15;
                Hien_thi_phan_hoi();
                Serial2.println(sms);                    //Cài đặt nội dung s
                Serial2.write((char)26);                //Gửi kí hiệu kết thúc Ctrl+Z / ESC 
                checkSimAT=15;
                Hien_thi_phan_hoi();
				checkSimAT=16;
                Hien_thi_phan_hoi();
	}	
	/***************************Hàm kiểm tra sóng cho sim800c***********************************/
	//Do_song= :  1 (Sóng yếu), 2(Trung bình), 3(Tốt), 4(Cực tốt)         
	int SIM::Kiem_tra_song()                    
	{   
	    if(SIM_STATUS==1)
		{
			Serial2.println("AT+CSQ");checkSimAT=12;                         
            Hien_thi_phan_hoi();
            switch(Do_song)
			    {
					case 1:Serial.println("Tín hiệu sim yếu!");break;
					case 2:Serial.println("Tín hiệu sim bình thường!");break;
					case 3:Serial.println("Tín hiệu sim tốt!");break;
					case 4:Serial.println("Tín hiệu sim cực tốt!");break;
				}
        }
        else 
		{
			Serial.println("Lỗi thẻ sim!Không kiểm tra được chất lượng sóng");
            Do_song	=0;
        }
        return Do_song;		
	}
	/********************Hàm đọc rtc cho sim800c***********************************************/
	void SIM::Doc_rtc_sim()                       
	{
			
    }
	/********************Hàm kiểm tra GPRS sim800c*********************************************/
	bool SIM::Kiem_tra_GPRS()
	{
		
		            Serial2.println("AT+CGATT?");checkSimAT=2;                         // kiểm tra trạng thái của gói dịch vụ đính kèm
                    Hien_thi_phan_hoi();
			        //Bật gprs nếu chưa kết nối
			        if(SIM_GPRS_STATUS==0)
			        {
					    Serial2.println("AT+CGATT=1");
					    checkSimAT=1; 
					    Hien_thi_phan_hoi();
						//Serial2.println("AT+CIICR");checkSimAT=6;                          // kết nối wireless                                                                                                                                                                         
                        //Hien_thi_phan_hoi();
						//Serial2.println("AT+CIPSHUT");checkSimAT=3;                        // đóng PDP của GPRS
                        //ShowSerialData();
				    }
                    return SIM_GPRS_STATUS;					
	}
	/***********************Hàm kiểm sim có hoạt đọng không************************************/
	bool SIM::Kiem_tra_SIM()
    {
	    Serial2.println("AT+CPIN?");checkSimAT=10;                         
        Hien_thi_phan_hoi();
		return SIM_STATUS;
	}	
	/********************Hàm đọc phản hồi lệch cho sim800c*************************************/
	void SIM::Hien_thi_phan_hoi()                       
	{
		while (checkSimAT!=0)
            {   
				delay(5);	
                if( Serial2.available()!=0)
                { 
                    delay(10);
                    char c;
					String s;
                    int length = Serial2.available();
                    for(int i=0; i<length; i++) 
                        {
                            c=Serial2.read();
                            s+=c;
                        }
                    //Serial.println(s);
                    //Kiểm tra lệnh AT gửi về 
                    switch (checkSimAT)
                       {
                        case 1: // KÍCH HOẠT GPRS
                            {
                                if (s.indexOf("OK") >= 0){Serial.println("Đã kích hoạt GPRS!");SIM_GPRS_STATUS=1;}
								else {Serial.println("Lỗi kết nối GPRS!");SIM_GPRS_STATUS=0;}
							    checkSimAT = 0;
                                break;
                            }
                        case 2: // Check CGATT                               //KIỂM TRA GPRS
						    {
                               if (s.indexOf("1") >= 0){Serial.println("Kết nối GPRS OK!");SIM_GPRS_STATUS=1;}
							   else {Serial.println("Lỗi kết nối GPRS!");SIM_GPRS_STATUS=0;}
							   checkSimAT = 0;
                               break;
                            }
                        case 3: // Check SHUT                            //Kết nối đã được đóng
                            {
                                if (s.indexOf("SH") >= 0)Serial.println("Đã đóng kết nối TCP/IP!");
							    else Serial.println("Lỗi đóng kết nối!");
								checkSimAT = 0;
                                break;
                            }
                        case 4: // check Connect
                            {
                                if ((s.indexOf("CO") >= 0)||(s.indexOf("OK") >= 0))Serial.println("Mở kết nối SERVER!");
								else Serial.println("Lỗi kết nối SERVER!");
								checkSimAT = 0;
                                break;
                            }
                        case 5: // check Close
                            {
                                if (s.indexOf("CL") >= 0)Serial.println("Đóng tất cả các kết nối SERVER!");
								else Serial.println("Đóng kết nối không thành công!");
								checkSimAT = 0;
                                break;
                            }
						case 6: //Khởi tạo ok
                            {
                                if (s.indexOf("OK") >= 0) Serial.println("KHỞI TẠO OK!");
								else Serial.println("Lỗi khởi tạo!");
								checkSimAT = 0;
                                break;
                            }
						case 7: //Khởi tạo ok
                            {
                                if (s.indexOf("O") >= 0) Serial.println("KẾT NỐI SERVER THÀNH CÔNG!");
								else Serial.println("Lỗi kết nối!");
								checkSimAT = 0;
                                break;
                            }
						case 8: //Khởi tạo ok
                            {
                                if (s.indexOf("OK") >= 0){Serial.println("Gửi dữ liệu thành công!");SIM_SEND_STATUS=1;}
								else if(s.indexOf("DATA") >= 0){Serial.println("Gửi dữ liệu thành công!");SIM_SEND_STATUS=1;}
								else {Serial.println("Gửi dữ liệu lỗi!");SIM_SEND_STATUS=0;}
								checkSimAT = 0;
                                break;
                            }
						case 9: //KIỂM TRA KẾT NỐI VỚI SERVER
                            {
								if(s.indexOf("TCP CO") >= 0){ SERVER_CONNECT_STATUS=2;}  //Trạng thái đang thiết lập kết nối
                                else if (s.indexOf("CON") >= 0) {Serial.println("Đang kết nối với SERVER!");SERVER_CONNECT_STATUS=1;}
								else if(s.indexOf("PDP") >= 0){SERVER_CONNECT_STATUS=0;}                    
					            else if(s.indexOf("IP") >= 0){SERVER_CONNECT_STATUS=0;} 
								else {Serial.println("Yêu cầu thiết lập kết nối lại SERVER!");SERVER_CONNECT_STATUS=0;}
								checkSimAT = 0;
                                break;
                            }
						case 10: //KIỂM TRA KẾT NỐI SIM
                            {
                                if (s.indexOf("ERR") >= 0) {Serial.println("Lỗi kết nối thẻ Sim!");SIM_STATUS=0;}
								else {Serial.println("Thẻ SIM được kết nối!");SIM_STATUS=1;}
								checkSimAT = 0;
                                break;
                            }
						case 11: //KIỂM TRA KẾT NỐI SIM
                            {
                                if (s.indexOf("ERR") >= 0) {Serial.println("Lỗi truy cập Internet!");}
								else {Serial.println("Truy cập internet ok!");}
								checkSimAT = 0;
                                break;
                            }
						case 12: //KIỂM TRA CHẤT LƯỢNG SÓNG
                            {
                                if (s.indexOf("ERR") >= 0) {Serial.println("Lỗi SIM không kiểm tra được sóng!");}
								else 
								    {
										String chat_luong_song=s.substring(s.indexOf(":")+2,s.indexOf(","));
										//Serial.print("Chất lượng sóng:");
										//Serial.println(chat_luong_song);
										if(chat_luong_song=="2")Do_song=1;
										else if(chat_luong_song=="3")Do_song=1;
										else if(chat_luong_song=="4")Do_song=1;
										else if(chat_luong_song=="5")Do_song=1;
										else if(chat_luong_song=="6")Do_song=1;
										else if(chat_luong_song=="7")Do_song=1;
										else if(chat_luong_song=="8")Do_song=1;
										else if(chat_luong_song=="9")Do_song=1;
										else if(chat_luong_song=="10")Do_song=2;
										else if(chat_luong_song=="11")Do_song=2;
										else if(chat_luong_song=="12")Do_song=2;
										else if(chat_luong_song=="13")Do_song=2;
										else if(chat_luong_song=="14")Do_song=2;
										else if(chat_luong_song=="15")Do_song=3;
										else if(chat_luong_song=="16")Do_song=3;
										else if(chat_luong_song=="17")Do_song=3;
										else if(chat_luong_song=="18")Do_song=3;
										else if(chat_luong_song=="19")Do_song=3;
										else if(chat_luong_song=="20")Do_song=4;
										else if(chat_luong_song=="21")Do_song=4;
										else if(chat_luong_song=="22")Do_song=4;
										else if(chat_luong_song=="23")Do_song=4;
										else if(chat_luong_song=="25")Do_song=4;
										else if(chat_luong_song=="26")Do_song=4;
										else if(chat_luong_song=="27")Do_song=4;
										else if(chat_luong_song=="28")Do_song=4;
										else if(chat_luong_song=="29")Do_song=4;
										else if(chat_luong_song=="30")Do_song=4;
										else if(chat_luong_song=="31")Do_song=4;
										else if(chat_luong_song=="32")Do_song=4;
										else Do_song=0;
								    }
								checkSimAT = 0;
                                break;
							/* Bảng kiểm tra chất lượng tín hiệu sóng
                                2	-109	Marginal      
                                3	-107	Marginal         
                                4	-105	Marginal                Yếu
                                5	-103	Marginal
                                6	-101	Marginal
                                7	-99	Marginal
                                8	-97	Marginal
                                9	-95	Marginal
                                10	-93	OK
                                11	-91	OK                           Trung bình
                                12	-89	OK
                                13	-87	OK
                                14	-85	OK
                                15	-83	Good
                                16	-81	Good                          Tốt
                                17	-79	Good
                                18	-77	Good
                                19	-75	Good
                                20	-73	Excellent
                                21	-71	Excellent
                                22	-69	Excellent
                                23	-67	Excellent
                                24	-65	Excellent
                                25	-63	Excellent                     Cực tốt
                                26	-61	Excellent
                                27	-59	Excellent
                                28	-57	Excellent
                                29	-55	Excellent
                                30	-53	Excellent
								*/
                            }
						case 13: // Cài đặt baudrate
                            {
                                Serial.println("Cài đặt tốc độ truyền thành công!");
								checkSimAT = 0;
                                break;
                            }
						case 14: //KIỂM TRA CUỘC GỌI
                            {
                                if (s.indexOf("BUS") >= 0) {Serial.println("Số máy chăm sóc khách hàng bận!");checkSimAT = 0;}
								else if (s.indexOf("DIAL") >= 0) {Serial.println("Số máy gọi không đúng!");checkSimAT = 0;}
								else if (s.indexOf("NO CA") >= 0) {Serial.println("Đã tắt máy!");checkSimAT = 0;}
								else if (s.indexOf("BUS") >= 0) {Serial.println("Máy bận!");checkSimAT = 0;}
								else if (s.indexOf("ANS") >= 0) {Serial.println("Số máy chăm sóc khách hàng không trả lời!");checkSimAT = 0;}
								else {Serial.println("Cuộc gọi thành công!");checkSimAT = 0;}
                                break;
                            }
						case 15: //KIỂM GỬI TIN NHẮT
                            {
                                if (s.indexOf(">") >= 0) {Serial.println("ĐÃ GỬI TIN THÀNH CÔNG!");}
								else {Serial.println("LỖI GỬI TIN!");}
								checkSimAT = 0;
                                break;
                            }
						case 16: //KIỂM TRA GỬI TIN NHẮT
                            {
                                if (s.indexOf("+CM") >= 0) {Serial.println("KẾT THÚC QUÁ TRÌNH GỬI TIN!");Check_Call=1;}
								else {Serial.println("LỖI GỬI TIN!");Check_Call=0;}
								checkSimAT = 0;
                                break;
                            }
						case 17: //KIỂM TRA CUỘC GỌI
                            {
                                if (s.indexOf("OK") >= 0) {Serial.println("THIẾT LẬP CUỘC GỌI!");Check_Call=1;}
								else {Serial.println("LỖI CUỘC GỌI!");Check_Call=0;}
								checkSimAT = 0;
                                break;
                            }
                        default:checkSimAT = 0;
                        break;
                        } 
                    }   
				else
				{
					checkSimAT = 0;
				}			    
				}

    }
static SIM Sim;


/*
	File lập trình các câu lệnh gửi đi của SIM800C
*/

/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */
#include <MBH.h>
#include "Sim_Gui_Server.h"


 /***************************Gửi gói tin lên Server**********************************/        
//Hàm gửi dữ liệu lên SERVER sau khi lệnh đã được ghép và tính CRC

void MAY_BAN_HANG::Gui_Server(unsigned char arr[], unsigned int kich_thuoc)
{
	Serial2.println("AT+CIPSTATUS");
	Serial.println("AT+CIPSTATUS");
	checkSimAT=9;                                     //Kiểm tra trạng thái kết nối với Server của SIM
	Hien_Thi_Phan_Hoi();
	//SERVER_CONNECT = 0;
	if(SERVER_CONNECT==0)
	{
        String cmd = "AT+CIPSTART=\"TCP\",\"";                      // TCP connection
        cmd += SERVER_IP;                                          // SERVER MÁY BÁN HÀNG
        cmd += "\",";                                           
        cmd+=PORT;                                                 // PORT 
        Serial2.println(cmd);
		Serial.println(cmd);
		checkSimAT=4;                                               //Kiểm tra trạng thái kết nối                              
        Hien_Thi_Phan_Hoi();
		/*SERVER_CONNECT=2;
		while(SERVER_CONNECT==2)
		{
			Serial2.println("AT+CIPSTATUS");
			checkSimAT=9;                                     //Kiểm tra trạng thái kết nối với Server của SIM
			Hien_Thi_Phan_Hoi();
			//SERVER_CONNECT = 0;
		}*/
	}
    //========================================================== Gửi chuỗi
    Serial2.println("AT+CIPSEND");delay(20);                   //Bắt đầu gửi dữ liệu    
	Serial.println("AT+CIPSEND");delay(20);                      //Bắt đầu gửi dữ liệu 
	//Hien_Thi_Phan_Hoi();
	for(unsigned int i=0; i<kich_thuoc; i++)
	{
		Serial2.write(arr[i]);                                      //Gửi dữ liệu đã lấy 
		//Serial.println(arr[i], HEX);
	}

	Serial2.write(0x1A);
	checkSimAT=8;                                            //Kiểm tra gửi thành công hay không
	Hien_Thi_Phan_Hoi();
    Serial2.println("AT+CIPSHUT");                           //Kiểm tra đóng kết nối
    //  checkSimAT=3;    
    // Hien_Thi_Phan_Hoi();
}

//Hàm chuẩn hóa dữ liệu để gửi

//Hàm nhận phản hồi từ chân Serial2 với Moduln Sim		
		void MAY_BAN_HANG::Hien_Thi_Phan_Hoi()                 
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
                    Serial.println(s);
                    //Kiểm tra lệnh AT gửi về 
                    switch (checkSimAT)
                    {
                        case 1: // KÍCH HOẠT GPRS
                            {
                                if (s.indexOf("OK") >= 0)
								    {
										//Serial.println("Đã kích hoạt GPRS!");
							            GPRS_STATUS=1;
							        }
								else 
								    {
										//Serial.println("Lỗi kết nối GPRS!");
										GPRS_STATUS=0;
									}
							    checkSimAT = 0;
                                break;
                            }
                        case 2: // Check CGATT                               //KIỂM TRA GPRS
						    {
                               if (s.indexOf("1") >= 0)
							        {
										//Serial.println("Kết nối GPRS OK!");
										GPRS_STATUS=1;
									}
							   else 
							        {
										//Serial.println("Lỗi kết nối GPRS!");
										GPRS_STATUS=0;
									}
							   checkSimAT = 0;
                               break;
                            }
                        case 3: // Check SHUT                            //Kết nối đã được đóng
                            {
                                //if (s.indexOf("SH") >= 0)Serial.println("Đã đóng kết nối TCP/IP!");
							    //else Serial.println("Lỗi đóng kết nối!");
								checkSimAT = 0;
                                break;
                            }
                        case 4: // check Connect
                            {
                                //if ((s.indexOf("CO") >= 0)||(s.indexOf("OK") >= 0))Serial.println("Mở kết nối SERVER!");
								//else Serial.println("Lỗi kết nối SERVER!");
								checkSimAT = 0;
                                break;
                            }
                        case 5: // check Close
                            {
                                //if (s.indexOf("CL") >= 0)Serial.println("Đóng tất cả các kết nối SERVER!");
								//else Serial.println("Đóng kết nối không thành công!");
								checkSimAT = 0;
                                break;
                            }
						case 6: //Khởi tạo ok
                            {
                                //if (s.indexOf("OK") >= 0) Serial.println("KHỞI TẠO OK!");
								//else Serial.println("Lỗi khởi tạo!");
								checkSimAT = 0;
                                break;
                            }
						case 7: //Khởi tạo ok
                            {
                                //if (s.indexOf("O") >= 0) Serial.println("KẾT NỐI SERVER THÀNH CÔNG!");
								//else Serial.println("Lỗi kết nối!");
								checkSimAT = 0;
                                break;
                            }
						case 8: //Khởi tạo ok
                            {
                                if (s.indexOf("OK") >= 0)
								    {
										//Serial.println("Gửi dữ liệu thành công!");
										SEND_STATUS=1;
									}
								else if(s.indexOf("DATA") >= 0)
								    {
										//Serial.println("Gửi dữ liệu thành công!");
										SEND_STATUS=1;
									}
								else 
								    {
										//Serial.println("Gửi dữ liệu lỗi!");
										SEND_STATUS=0;
									}
								checkSimAT = 0;
                                break;
                            }
						case 9: //KIỂM TRA KẾT NỐI VỚI SERVER
                            {
								if(s.indexOf("TCP CO") >= 0)SERVER_CONNECT=2;  //Trạng thái đang thiết lập kết nối
                                else if (s.indexOf("CON") >= 0) 
								    {
										//Serial.println("Đang kết nối với SERVER!");
										SERVER_CONNECT=1;
									}
								else if(s.indexOf("PDP") >= 0)SERVER_CONNECT=0;                 
					            else if(s.indexOf("IP") >= 0)SERVER_CONNECT=0;
								else 
								    {
										//Serial.println("Yêu cầu thiết lập kết nối lại SERVER!");
										SERVER_CONNECT=0;
									}
								checkSimAT = 0;
                                break;
                            }
						case 10: //KIỂM TRA KẾT NỐI SIM
                            {
                                //if (s.indexOf("ERR") >= 0) Serial.println("Lỗi kết nối thẻ Sim!");
								//else {Serial.println("Thẻ SIM được kết nối!");}
								checkSimAT = 0;
                                break;
                            }
						case 11: //KIỂM TRA KẾT NỐI SIM
                            {
                                //if (s.indexOf("ERR") >= 0) Serial.println("Lỗi truy cập Internet!");
								//else Serial.println("Truy cập internet ok!");
								checkSimAT = 0;
                                break;
                            }
						case 12: //KIỂM TRA CHẤT LƯỢNG SÓNG
                            {
                                //if (s.indexOf("ERR") >= 0) Serial.println("Lỗi SIM không kiểm tra được sóng!");
								//else 
								    //{
								        //uint8_t k=s.indexOf(',')-s.indexOf(':')-1;
										//String chat_luong_song=s.substring(s.indexOf(":")+1,s.indexOf(","));
										//Serial.print("Chất lượng sóng:");
										//Serial.println(chat_luong_song);
								    //}
								checkSimAT = 0;
                                break;
                            }
						case 13: // Cài đặt baudrate
                            {
                                //Serial.println("Cài đặt tốc độ truyền thành công!");
								checkSimAT = 0;
                                break;
                            }
						case 14: //KIỂM TRA CUỘC GỌI
                            {
                                if (s.indexOf("BUS") >= 0) 
								    {
										//Serial.println("Số máy chăm sóc khách hàng bận!");
										checkSimAT = 0;
									}
								else if (s.indexOf("DIAL") >= 0) 
								    {
										//Serial.println("Số máy gọi không đúng!");
										checkSimAT = 0;
									}
								else if (s.indexOf("NO CA") >= 0) 
								    {
										//Serial.println("Đã tắt máy!");
										checkSimAT = 0;
									}
								else if (s.indexOf("BUS") >= 0) 
								    {
										//Serial.println("Máy bận!");
										checkSimAT = 0;
									}
								else if (s.indexOf("ANS") >= 0) 
								    {
										//Serial.println("Số máy chăm sóc khách hàng không trả lời!");
										checkSimAT = 0;
									}
								else 
								    {
										//Serial.println("Cuộc gọi thành công!");
										checkSimAT = 0;
									}
                                break;
                            }
						case 15: //KIỂM GỬI TIN NHẮT
                            {
                                //if (s.indexOf(">") >= 0) Serial.println("ĐÃ GỬI TIN THÀNH CÔNG!");
								//else Serial.println("LỖI GỬI TIN!");
								checkSimAT = 0;
                                break;
                            }
						case 16: //KIỂM TRA GỬI TIN NHẮT
                            {
                                //if (s.indexOf("+CM") >= 0) Serial.println("KẾT THÚC QUÁ TRÌNH GỬI TIN!");
								//else Serial.println("LỖI GỬI TIN!");
								checkSimAT = 0;
                                break;
                            }
						case 17: //KIỂM TRA CUỘC GỌI
                            {
                                //if (s.indexOf("OK") >= 0) Serial.println("THIẾT LẬP CUỘC GỌI!");
								//else Serial.println("LỖI CUỘC GỌI!");
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
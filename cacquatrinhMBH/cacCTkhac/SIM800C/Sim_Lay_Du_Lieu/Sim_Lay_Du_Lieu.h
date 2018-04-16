/*
	File lập trình các câu lệnh lấy dữ liệu gửi đi của SIM800C
*/

/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */

#ifndef Sim_Lay_Du_Lieu_H
#define Sim_Lay_Du_Lieu_H
public:
/**************************Các thư viện phục vụ kèm********************************/
void Sim_tao_goi_tin(char Lenh_gui, unsigned char &array, unsigned int data_addr[], unsigned int size[], unsigned char num_of_data_addr);
void Frame_overview(unsigned char &array, unsigned int size_of_data); // Địa chỉ đầu ra và kích thước thông số lệnh (size)
void Update_ID(unsigned char &array, unsigned int dia_chi_o_nho);
void Update_CMD(char Lenh_gui, unsigned char &array);
void Update_data_CMD(unsigned char &array, unsigned int data_addr[], unsigned int size[], unsigned char num_of_data_addr);
void Update_CRC(unsigned char &arr, unsigned int size_of_data, unsigned char &array); // Trỏ tới mảng nhập vào;

// void Sim_Khoi_Tao_Gia_tri();                            //Khởi tạo giá trị ban đầu cho Sim//Nếu có rồi thì không cần khởi tạo nữa
#endif
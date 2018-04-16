/*
	File lập trình các câu lệnh gửi đi của SIM800C
*/

/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */

#ifndef SIM800C_h
#define SIM800C_h
public:

 /***************************Gửi gói tin lên Server**********************************
    /**************************Các thư viện phục vụ kèm********************************/
	#include <cacquatrinhMBH/cacCTkhac/SIM800C/Sim_Lay_Du_Lieu/Sim_Lay_Du_Lieu.h>
	#include <cacquatrinhMBH/cacCTkhac/SIM800C/Sim_gui_Server/Sim_gui_Server.h>
	    /**************************Gửi dữ liệu lên SERVER**********************************/
	void Sim_Gui_Server(char Lenh_gui);
    void Sim_Gui_Server(char Lenh_gui, unsigned int data_addr[], unsigned int size[], unsigned char num_of_data_addr);    
	
#endif
/*
	File lập trình các câu lệnh gửi đi của SIM800C
*/

/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */

#include <MBH.h>

void MAY_BAN_HANG::Sim_Gui_Server(char Lenh_gui) // Dành cho các gói tin có bộ nhớ cố định (không đổi) // Lệnh 0x61,62
{
	// Đầu vào mặc định:
	unsigned int data_addr[10], size[10];
	unsigned char num_of_data_addr;
	switch(Lenh_gui)
	{
		case 0x61: // Mở máy
			data_addr[0]=3011; size[0]=0x01; num_of_data_addr=1; break;
		case 0x62: // Chu kỳ
			data_addr[0]=3030; 	size[0]=1; // Nên thay hết các tên địa chỉ bắt đầu bằng các MACRO
			data_addr[1]=3031; 	size[1]=1; 
			data_addr[2]=3032; 	size[2]=1; 
			data_addr[3]=3033; 	size[3]=1; 
			data_addr[4]=3034; 	size[4]=1; 
			data_addr[5]=60; 	size[5]=60; 
			data_addr[6]=3035; 	size[6]=4; 
			data_addr[7]=3039; 	size[7]=6; 
			num_of_data_addr = 8;
			break;
		case 0x63: // Mở cửa
			data_addr[0]=3020; size[0]=0x06; num_of_data_addr=1; break;
		case 0x64: // Đóng cửa
			data_addr[0]=3050; 	size[0]=1; // Nên thay hết các tên địa chỉ bắt đầu bằng các MACRO
			data_addr[1]=3051; 	size[1]=1; 
			data_addr[2]=3052; 	size[2]=1; 
			data_addr[3]=3033; 	size[3]=1; 
			data_addr[4]=0; 	size[4]=60; 
			data_addr[5]=60; 	size[5]=60; 
			data_addr[6]=3053; 	size[6]=6; 
			num_of_data_addr = 7;
			break; 
		case 0x65: 
		{
			data_addr[0]=3500; 	size[0]=21;
			num_of_data_addr = 1;
			break; // Dữ liệu động - Mua hàng bình thường
		}
		case 0x66: break; // Dữ liệu động - Mua hàng lỗi
		case 0x67: break; // Dữ liệu động - Lỗi thiết bị
		case 0x68: break; // Dữ liệu động - Doanh thu ngày
	}
	// Bắt đầu tạo Frame truyền
	Sim_Gui_Server(Lenh_gui, data_addr, size, num_of_data_addr);
}

/***************************Gửi gói tin lên Server**********************************/
// Hàm này cần module lại. Có thể giảm được tốc độ
void MAY_BAN_HANG::Sim_Gui_Server(char Lenh_gui, unsigned int data_addr[], unsigned int size[], unsigned char num_of_data_addr)
{
	/** Bước 1: Tạo 1 gói tin truyền đi ************************************/
	unsigned int size_of_data = 0;
	for (unsigned char i=0; i<num_of_data_addr; i++)
		size_of_data+=size[i]; // Tính toán kích thước của thông số lệnh
	unsigned char Frame_1[size_of_data+28]; // Cần xem lại kích cỡ mảng Frame - kích thước các phần tử
/* */Sim_tao_goi_tin(Lenh_gui, Frame_1[0], data_addr, size, num_of_data_addr);
	/** Bước 2: Nhồi byte **************************************************/
	for(unsigned int i=0; i<sizeof(Frame_1); i++)
		if(Frame_1[i]==0x1A) size_of_data+=2;
	unsigned char Frame_2[size_of_data+28];
	unsigned int j = 0;
	for(unsigned int i=0; i<sizeof(Frame_1); i++)
	{
		if(Frame_1[i]==0x1A) 
		{
			Frame_2[j] = 'L'; 
			Frame_2[j+1] = 'O';
			Frame_2[j+2] = 'I';
			j+=3;
		}
		else 
		{
			Frame_2[j] = Frame_1[i];
			j++;
		}
	}
	
	for(unsigned int i=0; i<sizeof(Frame_2); i++)
		if(Frame_2[i]==0x1B) size_of_data+=2;
	unsigned char Frame_3[size_of_data+28];
	unsigned int k = 0;
	for(unsigned int i=0; i<sizeof(Frame_2); i++)
	{
		if(Frame_2[i]==0x1B) 
		{
			Frame_3[k] = 'S'; 
			Frame_3[k+1] = 'A';
			Frame_3[k+2] = 'I';
			k+=3;
		}
		else 
		{
			Frame_3[k] = Frame_2[i];
			k++;
		}
	}
	
	/** Bước 3: Gửi gói tin sau khi nhồi byte tới Server ******************/
/* *///Gui_Server(Frame_3, sizeof(Frame_3));
	//for (int i=0; i<sizeof(Frame_2); i++)
		//Serial.print(Frame_2[i], HEX);
	Serial.println("Frame 3");
	for (int i=0; i<sizeof(Frame_3); i++)
	{
		Serial.print(Frame_3[i], HEX);
		Serial.print(" ");
	}
	Serial.println();
}


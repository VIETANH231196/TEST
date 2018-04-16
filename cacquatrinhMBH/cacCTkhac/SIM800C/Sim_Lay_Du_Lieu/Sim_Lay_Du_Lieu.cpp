/*
	File lập trình các câu lệnh lấy dữ liệu gửi đi của SIM800C
*/

/** Các biến hệ thống cần truyền đi được lưu trong file bienhethong.h */

#include <MBH.h>
#include <thuviencoban/Crc16/Crc16.h>	       // Thư viện khởi tạo cho tính CRC
Crc16 crc;
void MAY_BAN_HANG::Sim_tao_goi_tin(char Lenh_gui, unsigned char &array, unsigned int data_addr[], unsigned int size[], unsigned char num_of_data_addr)
{								// Mã lệnh		/Mảng trả về/  Địa chỉ EEPROM lưu DL		/ Kích cỡ ô nhớ trước/ Số phần tử ô nhớ
	unsigned int size_of_data = 0;
	for (unsigned char i=0; i<num_of_data_addr; i++)
		size_of_data+= size[i]; // Tính toán kích thước của thông số lệnh
	
	Frame_overview(array, size_of_data);
	// Các mảng nhỏ nằm trong Frame truyền tổng quan
	// ------------------------------------------------------------------------
	Update_CMD(Lenh_gui, *(&array+20));
	// Có 8 gói tin, và có 2 loại dữ liệu: 1 loại rời rạc và 1 loại là liên tục
	// + Rời rạc: Gói tin: DL theo chu kỳ (0x62); Sự kiện đóng của (0x64)
	// + Rời rạc 1 dữ liệu và liên tục: 61, 63, 67 và 65, 66, 68.
	Update_data_CMD(*(&array+22), data_addr, size, num_of_data_addr);
	Update_CRC(*(&array+3), size_of_data, *(&array+23+size_of_data)); // Đầu vào của hàm tính CRC là điểm bắt đầu của mảng và kích thước mảng - Đầu ra là địa chỉ kết thúc mảng
}

void MAY_BAN_HANG::Frame_overview(unsigned char &array, unsigned int size_of_data) // Địa chỉ đầu ra và kích thước thông số lệnh (size)
{
	array = '#';  
	*(&array+1) = '#';
	*(&array+2) = '#';
	*(&array+3) = '|';
	Update_ID(*(&array+4), 3000); // Nhập vào dấu .... địa chỉ ô nhớ lưu trữ ID
	*(&array+14) = '|';
	*(&array+15) = 'C';
	*(&array+16) = 'M';
	*(&array+17) = 'D';
	*(&array+18) = '=';
	*(&array+19) = '|';
	//*(&array+20) là mã lệnh
	/** Update_CMD(*(&array+20)); */
	*(&array+21) = '|';
	//*(&array+21+size) là mã lệnh
	/** Update_data_CMD(*(&array+22)); */
	*(&array+22+size_of_data) = '|';
	//*(&array+23;24+size_of_data) là CRC
	/** Update_CRC(*(&array+23+size_of_data)); */
	*(&array+25+size_of_data) = '&';
	*(&array+26+size_of_data) = '&';
	*(&array+27+size_of_data) = '&';
	// Kết thúc gói tin tổng quan, giờ điền các mảng tương ứng vào vị trí của nó
}

void MAY_BAN_HANG::Update_ID(unsigned char &array, unsigned int dia_chi_o_nho)
{
	for(unsigned char i=0; i<10; i++)
	{
		*(&array+i) = EEPROM.read(dia_chi_o_nho+i);
	}
}

void MAY_BAN_HANG::Update_CMD(char Lenh_gui, unsigned char &array)
{
	switch(Lenh_gui)
	{
		case 0x61: array=0x61; break;    
		case 0x62: array=0x62; break;
		case 0x63: array=0x63; break;
		case 0x64: array=0x64; break;
		case 0x65: array=0x65; break;
		case 0x66: array=0x66; break;
		case 0x67: array=0x67; break;
		case 0x68: array=0x68; break;
        default: break;	
	}	
}

void MAY_BAN_HANG::Update_data_CMD(unsigned char &array, unsigned int data_addr[], unsigned int size[], unsigned char num_of_data_addr)
{
	unsigned int size_of_data = 0;
	for(unsigned char i=0; i<num_of_data_addr; i++) // Địa chỉ 
	{
		for(unsigned int j=data_addr[i]; j<(data_addr[i]+size[i]); j++)
		{
			*(&array+size_of_data)=EEPROM.read(j);
			//Serial.println(j, HEX);
			size_of_data++;
		}
	}
}

void MAY_BAN_HANG::Update_CRC(unsigned char &arr, unsigned int size_of_data, unsigned char &array) // Trỏ tới mảng nhập vào
{
	crc.clearCrc();
	for(int i=0; i<size_of_data; i++)
	{
		crc.updateCrc(*(&arr+i));
	}
	unsigned int value = crc.getCrc();
	array = value;
	*(&array+1) = value>>8;
	// Serial.println(value, HEX);
}
	
//Khởi tạo giá trị ban đầu cho sim
/*void MAY_BAN_HANG::Sim_Khoi_Tao_Gia_tri()
    {
	//Cập nhập mã máy bán hàng
		for(int i=0;i<10;i++)
		{
			EEPROM.write(ADDR_SIM_ID_MBH[i],0x39);
			delay(5);
		}
	//Thông tin khởi động
		EEPROM.write(ADDR_SIM_KHOI_DONG,0x31);
		delay(5);
	//Thông tin sim gửi chu kì
		EEPROM.write(ADDR_SIM_TRANG_THAI_CUA,0x31);
		delay(5);
		EEPROM.write(ADDR_SIM_NHIET_DO,0x19);
		delay(5);
		EEPROM.write(ADDR_SIM_LOI_DAU_DOC,0x31);
		delay(5);
		EEPROM.write(ADDR_SIM_SO_TIEN_NGAN_TRA_LAI,0x1A);
		delay(5);
		EEPROM.write(ADDR_SIM_MENH_GIA_TIEN_TRA_LAI,0x05);
		delay(5);
		for(int i=0;i<4;i++)
		{
			EEPROM.write( ADDR_SIM_TIME_HOAT_DONG[i],0x10
			);
			delay(5);
		}
		for(int i=0;i<60;i++)
		{
			EEPROM.write(ADDR_SIM_HANG_TUNG_KHAY[i],0x0A);
			delay(5);
		}
		EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[0],0x1A);
		delay(5);
		EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[1],0x04);
		delay(5);
		EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[2],0x1A);
		delay(5);
		EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[3],0x00);
		delay(5);
		EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[4],0x1A);
		delay(5);
		EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[5],0x1A);
		delay(5);
		/*
		for(int i=0;i<5;i++)
		{
			EEPROM.write(ADDR_SIM_THOI_GIAN_KET_THUC[i+1],0x0A);
			delay(5);
		}
	//Thông tin báo đóng cửa
		EEPROM.write(ADDR_SIM_TRANG_THAI_LED,0x31);
		delay(5);
		EEPROM.write(ADDR_SIM_NHIET_DO_CAI_DAT,0x12);
		delay(5);
		EEPROM.write( ADDR_SIM_TRANG_THAI_CB_ROI,0x30);
		delay(5);
		for(int i=0;i<60;i++)
		{
			EEPROM.write(ADDR_SIM_GIA_TIEN_KHAY[i],0x1A);
			delay(5);
		}
	//Thông tin báo mua hàng
		EEPROM.write(ADDR_SIM_SO_TIEN_DU[0],0x0A);
		delay(5);
		EEPROM.write(ADDR_SIM_SO_TIEN_DU[1],0x00);
		delay(5);
		EEPROM.write(ADDR_SIM_SO_TIEN_VAO_MAY[0],0x14);
		delay(5);
		EEPROM.write(ADDR_SIM_SO_TIEN_VAO_MAY[1],0x00);
		delay(5);
		EEPROM.write(ADDR_SIM_O_CHON,0x0A);
		delay(5);
		EEPROM.write(ADDR_SIM_GIA_O_CHON,0x05);
		delay(5);
		EEPROM.write(ADDR_SIM_TIEN_TRA_LAI,0x05);
		delay(5);
		EEPROM.write(ADDR_SIM_TIEN_CON_LAI[0],0x05);
		delay(5);
		EEPROM.write(ADDR_SIM_TIEN_CON_LAI[1],0x00);
		delay(5);
		EEPROM.write(ADDR_SIM_THOI_GIAN_BAT_DAU[0],0x0A);
		delay(5);
		for(int i=0;i<5;i++)
		{
			EEPROM.write(ADDR_SIM_THOI_GIAN_BAT_DAU[i+1],0x0A);
			delay(5);
		}
	//Thông tin mua hàng lỗi
		EEPROM.write(ADDR_SIM_O_CHON_LOI,0x0A);
		delay(5);
		EEPROM.write(ADDR_SIM_GIA_O_CHON_LOI,0x0F);
		delay(5);
		EEPROM.write(ADDR_SIM_O_LAN_1,0x0B);
		delay(5);
		EEPROM.write(ADDR_SIM_O_LAN_2,0x0C);
		delay(5);
	//Thông tin báo lỗi máy bán hàng
	    EEPROM.write(ADDR_SIM_LOI_THIET_BI,0x61);
		delay(5);
		EEPROM.write(ADDR_SIM_TRANG_THAI_LOI,0x31);
		delay(5);
	//Thông tin báo doanh thu
	    for(int i=0;i<4;i++)
		{
			EEPROM.write(ADDR_SIM_DOANH_THU[i],0x00);
			delay(5);
		}
		EEPROM.write(ADDR_SIM_TONG_SO_LOI,0x00);
		delay(5);
		EEPROM.write(ADDR_SIM_NGAY_TINH_DOANH_THU[0],0x12);
	    delay(5);
		for(int i=0;i<2;i++)
		{
			EEPROM.write(ADDR_SIM_NGAY_TINH_DOANH_THU[i+1],0x0A);
			delay(5);
		}
		
		Serial.println("Khởi tạo giá trị cho Sim thành công!");
	}	

	*/
/*
File Nv11.h Version 1
*/

#ifndef NV11_H
#define NV11_H

#include "AESLib.h" //Thư viện mã hóa và giải mã AES128
#include "CRC.h"


static byte mang[32];//mảng chứa lệnh mà người dùng nhập vào (ở đây chỉ là người lập trình)
static unsigned char length_tx;//độ dài lệnh mà người dùng nhập vào
	
class NV11
{
	public:	
	
		bool LOI = 1;
		
		bool ENCRYPT_STATUS = 0; //Trạng thái mã hóa. Dùng sau này khi gộp hai hàm send_packet và send_epacket vào một hàm lớn
		static unsigned char seq; //Gán giá trị ban đầu cho SEQ
	
		struct PACKET//Cấu trúc gói tin gửi
		{
			const byte STX = 0x7F;
			byte SEQ; //byte SEQ = 0x00;
			unsigned char LENGTH;
			byte DATA[32]; //dữ liệu gửi đi không quá 32 byte
			byte CRCL;
			byte CRCH;
			/**---------------------------------------------------------------**/
			byte ARR_BEFOR_SUF[32];//Mảng chứa toàn bộ gói tin trước khi nhồi byte
			byte ARR_AFTER_SUF[32];//Mảng chứa toàn bộ gói tin sau khi nhồi byte
		}PACKET;
		
		void send_packet(byte data[], unsigned char length);// Nhập mảng lệnh cần gửi vào để gửi
		byte RX[128];//Lưu giá trị đọc được vào mảng RX[256]
		unsigned int length_rx; //Biến độ dài gói tin nhận được
		
		unsigned char receive_packet();
		void clear_RX();	// Hàm xóa dữ liệu vừa nhận
		
		struct FULL_KEY
		{
			unsigned long long FIXED = 0x0123456701234567;//Khóa cố định (có thể cài đặt được)
			unsigned long long NEGATIVE;// Khóa đồng bộ
			byte FULLKEY_ARR[16];//Khóa full
		} KEY;

		struct NEGATIVE_KEY
		{
			unsigned long long GENERATOR = 0x000000007B059425;
			unsigned long long MODULUS = 0x00000000068BFB6B;
			unsigned long long HOST_RANDOM = 0x0000000000000001;
			unsigned long long HOST_INTER_KEY;
			unsigned long long SLAVE_INTER_KEY;
			unsigned long long NEGATIVE_KEY;
		}NEGA;
		
		bool make_negative_key();
		void make_fullkey();//Kết thúc hàm thì full key được lưu trong KEY.ARR
		
		static unsigned long count;

		struct EPACKET
		{
				unsigned char LENGTH;
				unsigned long COUNT;
				byte DATA[9] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
				byte CRCL;
				byte CRCH;
				byte ARR[16];
				byte ARR_SEND[17] ={0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		}EPACKET;

		void make_epacket(byte data[], unsigned char length_data);
		void send_epacket(byte data[], unsigned char length_data);
		byte ERX[16];
		
		void clear_ERX();
		byte receive_epacket();

		/*******************************************************************************************************/
		/** Các hàm có thể sử dụng trong chương trình **********************************************************/

		void send(byte data[], unsigned char length_data);
		uint8_t receive();//Kết thúc hàm này thì mọi dữ liệu nhận được được lưu trong ERX, kể cả đã được giải mã.
		void clear();
		
		/**
		/*******************************************************************************************************/
		/**Các hàm rút gọn chạy trong chương trình chính */

		void hienthidulieu_gui();
		void begin();
		void kiemtrahienthi(); //Hiển thị dữ liệu nhận được
		void dong_bo();
		void gui_lenh_tham_do();
		void tham_do(); //0x07 lệnh thăm dò tiền
		void dua_tien_xuong_stacker();
		void dua_tien_len_note_float();
		void tu_choi_tien(); // từ chối tiền
		void giu_tien();
		void gui_lenh_giu_tien();
		void tra_loi_theo_kenh();
		void tra_loi_theo_gia_tri();
		void tra_cuu_so_tien_tra_lai();
		void tra_lai_tien();
		void empty_recycle();
		void enable();
		void disable();

};

extern Cyclic_Redundancy_Check Crc;
extern NV11 Nv11;


#endif

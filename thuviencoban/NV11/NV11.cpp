/*
File Nv11.cpp Version 1
*/

#include "NV11.h"

Cyclic_Redundancy_Check Crc;

	
		unsigned char NV11::seq = 0x00;
		unsigned long NV11::count = 0;
		
		void NV11::send_packet(byte data[], unsigned char length)// Nhập mảng lệnh cần gửi vào để gửi
		{
			/** BƯỚC 1: Đảo SEQ trước khi gửi mỗi gói tin giữa 2 giá trị 0x80 và 0x00*********************************/
			if (seq==0x80)
			{
				seq = 0x00;
			}
			else if(seq==0x00)
			{
				seq = 0x80;
			}
			/** BƯỚC 2: HOÀN THIỆN GÓI TIN PACKET ********************************************************************/
			PACKET.LENGTH = length; //độ dài gói tin = length đã nhập vào
			PACKET.SEQ = seq;	//SEQ = SEQ vừa đảo phía trên
			for (unsigned char index=0; index<PACKET.LENGTH; index++)
			{
				PACKET.DATA[index] = data[index];
			}
			//Tính CRC, hoàn thiện gói tin
			Crc.ResetCrc();
			Crc.UpdateCrc(PACKET.SEQ);
			Crc.UpdateCrc(PACKET.LENGTH);
			for (unsigned char index=0; index<PACKET.LENGTH; index++)
			{
				Crc.UpdateCrc(PACKET.DATA[index]);
			}
			PACKET.CRCL = Crc.L;
			PACKET.CRCH = Crc.H;
			/** BƯỚC 3: GÓI TIN ĐẦY ĐỦ TRƯỚC KHI NHỒI BYTE ************************************************************/
			PACKET.ARR_BEFOR_SUF[0] = PACKET.STX;//byte 0
			PACKET.ARR_BEFOR_SUF[1] = PACKET.SEQ;//byte 1
			PACKET.ARR_BEFOR_SUF[2] = PACKET.LENGTH;//byte 2
			for (unsigned char i=0; i<PACKET.LENGTH; i++)
			{
				PACKET.ARR_BEFOR_SUF[i+3] = PACKET.DATA[i];//byte 3 tới 2+LENGTH
			}
			PACKET.ARR_BEFOR_SUF[3+PACKET.LENGTH] = PACKET.CRCL;//byte 3+LENGTH
			PACKET.ARR_BEFOR_SUF[4+PACKET.LENGTH] = PACKET.CRCH;//byte 4+LENGTH
			/** BƯỚC 4: THỰC HIỆN NHỒI BYTE, CHUYỀN TỪ BEFORE_SUF SANG AFTER_SUF **************************************/
			PACKET.ARR_AFTER_SUF[0] = PACKET.ARR_BEFOR_SUF[0];
			unsigned short int j = 1; // Biến độ dài mảng PACKET.ARR_AFTER_SUF
			for (unsigned char i=1; i<(5+PACKET.LENGTH); i++)
			{
				if(PACKET.ARR_BEFOR_SUF[i]!=0x7F)
				{
					PACKET.ARR_AFTER_SUF[j] = PACKET.ARR_BEFOR_SUF[i];
					j++;
				}
				else if(PACKET.ARR_BEFOR_SUF[i]==0x7F)
				{
					PACKET.ARR_AFTER_SUF[j] = PACKET.ARR_BEFOR_SUF[i];
					PACKET.ARR_AFTER_SUF[j+1] = PACKET.ARR_BEFOR_SUF[i];
					j = j+2;
				}
			}
			/** BƯỚC 5: GỬI GÓI TIN CUỐI CÙNG ĐI***********************************************************************/
			//Serial.print("Gửi: ");
			for (unsigned char i=0; i<j; i++)
			{
				Serial1.write(PACKET.ARR_AFTER_SUF[i]);
				//Serial.print(PACKET.ARR_AFTER_SUF[i], HEX);
				//Serial.print(" ");
			}
			//Serial.println();
			/**********************************************************************************************************/
			//Sau khi gửi xong gói tin thì đặt lại PACKET.SEQ
		}
		
		unsigned char NV11::receive_packet()
		{
			/*if(Serial.available()==0)
			{
				unsigned int nv11_dem;
				while(1)
				{
					nv11_dem++;
					if(Serial.available()!=0) break;
					if(nv11_dem==20000) break;
				}
			}*/
			length_rx = 0;
			bool du_lieu = 0;
			//Serial.println("Đang chờ dữ liệu");
			//Serial.println(Serial1.available());
			//Serial.println(Serial1.peek(), HEX);
			while(Serial1.available()) // Nếu có dữ liệu trong bộ đệm thì bắt đầu đọc
			{
				// Serial.println("Đang đọc DL");					
				switch(du_lieu)	
				{
					case 0: // Trường hợp chưa nhận được gói tin thì thăm dò
					{
						if(Serial1.peek()!=0x7F)	//Nếu dữ liệu khác 0x7F thì xóa
						{		
							char x = Serial1.read();
							du_lieu = 0; // Chưa có dữ liệu nhận được
							//Serial.println("Không có dữ liệu");
							//goto thoat_nhan_du_lieu;
						}
						else if(Serial1.peek()==0x7F) // Còn nếu là 0x7F thì nghĩa là bắt đầu gói tin, bắt đầu đọc
						{
							du_lieu = 1; // Bắt đầu nhận được 1 gói tin
							//Serial.println("Có dữ liệu");
						}
						//Serial.println("Không có dữ liệu");
						break;
					}
					case 1: // Trường hợp có dữ liệu thì bắt đầu đọc
					{
						length_rx += Serial1.available(); // Xem độ dài gói tin đã nhận được
						RX[0] = Serial1.read();	// Đọc byte bắt đầu
						if(length_rx<3)			/** Trường hợp chưa đọc được byte độ dài => phải đọc byte độ dài */
						{
							delay(3);
							length_rx += Serial1.available();
							RX[1] = Serial1.read();// Đọc byte thứ 2
							RX[2] = Serial1.read();// Đọc byte độ dài gói tin
							/* So sánh byte độ dài với số gói tin đã nhận được */
							if(RX[2]<=Serial1.available()-2) // Nếu độ dài gói tin nhỏ hơn số byte còn lại trong bộ đệm (-2 byte CRC)
							// thì nghĩa là đã nhận đủ gói tin => đọc gói tin
							{
								for(unsigned char i=3; i<length_rx; i++)
								{
									RX[i] = Serial1.read();
								}
								length_rx = RX[2];
							}
							else // Chưa nhận đủ gói tin => đọc nốt
							{
								unsigned char t_cho = RX[2]+2 - Serial1.available();
								delay(t_cho+2);
								unsigned char i = 3;
								while(Serial1.available())
								{
									RX[i] = Serial1.read();
									i++;
								}
								length_rx = RX[2];
								Serial.println("Đọc xong gói tin 1");
							}
						}
						else if(length_rx>=3) 	/** Trường hợp đã đọc được byte độ dài gói tin */
						{
							RX[1] = Serial1.read();// Đọc byte thứ 2
							RX[2] = Serial1.read();// Đọc byte độ dài gói tin
							// Sau đó so sánh byte độ dài với gói tin nhận được
							if(RX[2]<=Serial1.available()-2) // Nếu độ dài gói tin bằng đúng số byte còn lại trong bộ đệm (-2 byte CRC)
							// thì nghĩa là đã nhận đủ gói tin => đọc gói tin
							{
								for(unsigned char i=3; i<length_rx; i++)
								{
									RX[i] = Serial1.read();
								}
								length_rx = RX[2];
							}
							else // Chưa nhận đủ gói tin => đọc nốt
							{
								unsigned char t_cho = RX[2]+2 - Serial1.available();
								delay(t_cho+2);
								unsigned char i = 3;
								while(Serial1.available())
								{
									RX[i] = Serial1.read();
									i++;
								}
								length_rx = RX[2];
								//Serial.println("Đọc xong gói tin 2");
							}
						}
												
						/** Bỏ byte nhồi và lưu vào RX ************************************/
						for (unsigned char i=3; i<21; i++) // Lưu ý: Nên thay 21 = biến độ dài gói tin thực
						{
							if((RX[i]==0x7F)&&(RX[i+1]==0x7F))
							{
								for(unsigned char j=i; j<21; j++)
								{
									RX[j] = RX[j+1];
								}
							}
						}
						/*Serial.print("Độ dài:");
						Serial.println(length_rx);
						Serial.print("Nhận được");
						for(unsigned char i=0; i<20; i++)
						{
							Serial.print(RX[i], HEX);
							Serial.print(" ");							
						}
						Serial.println();*/
						return RX[3];						
						break;
					}
				}
			}
			thoat_nhan_du_lieu:
			{
				// Không làm gì cả
			}
		}
		
		void NV11::clear_RX()	// Hàm xóa dữ liệu vừa nhận
		{
			for(unsigned char i=0; i<32; i++)
			{
				RX[i] = 0x00;
			}
		}
		
		bool NV11::make_negative_key()
		{
			byte arr[9];
			//Gửi lệnh send GENERATOR
			//========================================================================
			arr[0]=0x4A;
			for (unsigned char i=1; i<sizeof(arr); i++)
			{
				arr[i] = (NEGA.GENERATOR>>(8*(i-1)));
			}
			send_packet(arr, sizeof(arr));
			delay(50);
			//Hiển thị câu lệnh gửi đi
			//-----------------------
			//Serial.print("Gửi ");
			for (unsigned char i=0; i<sizeof(arr); i++)
			{
				Serial.print(arr[i], HEX);
				Serial.print(" ");
			}
			Serial.println();
			//-----------------------
			if(receive_packet()!=0xF0)
			{
				//Serial.println("Lỗi GENERATOR");
				return 0;
			}
			//Serial.print("Nhận: ");
			Serial.println(RX[3]);
			clear_RX();
			//Gửi lệnh send MODULUS
			//========================================================================
			arr[0]=0x4B;
			for (unsigned char i=1; i<sizeof(arr); i++)
			{
				arr[i] = (NEGA.MODULUS>>(8*(i-1)));
			}
			send_packet(arr, sizeof(arr));
			delay(50);
			//Hiển thị câu lệnh gửi đi
			//-----------------------
			//Serial.print("Gửi ");
			for (unsigned char i=0; i<sizeof(arr); i++)
			{
				Serial.print(arr[i], HEX);
				Serial.print(" ");
			}
			Serial.println();
			//-----------------------
			if(receive_packet()!=0xF0)
			{
				//Serial.println("Lỗi MODULUS");
				return 0;
			}
			//Serial.print("Nhận: ");
			Serial.println(RX[3]);
			clear_RX();
			//Tính HOST_INTER_KEY=(GENERATOR^HOST_RANDOM)%MODULUS
			//========================================================================
			unsigned long long H = 1;
			for (unsigned char i=0; i<NEGA.HOST_RANDOM; i++)
			{
				H = H*NEGA.GENERATOR;
			}
			NEGA.HOST_INTER_KEY = (H%NEGA.MODULUS);
			//Gửi HOST_INTER_KEY
			//========================================================================
			arr[0] = 0x4C;
			for (unsigned char i=1; i<sizeof(arr); i++)
			{
				arr[i] = (NEGA.HOST_INTER_KEY>>(8*(i-1)));
			}
			send_packet(arr, sizeof(arr));
			delay(50);
			//Hiển thị câu lệnh gửi đi
			//-----------------------
			//Serial.print("Gửi ");
			for (unsigned char i=0; i<sizeof(arr); i++)
			{
				Serial.print(arr[i], HEX);
				Serial.print(" ");
			}
			Serial.println();
			//-----------------------
			if(receive_packet()!=0xF0)
			{
				//Serial.println("Lỗi HOST_INTER_KEY");
				return 0;
			}
			//Serial.print("Nhận: ");
			for (unsigned char i=3; i<RX[2]+3; i++)
			{
				Serial.print(RX[i]);
				Serial.print(" ");
			}
			Serial.println();
			//Tính NEGATIVE_KEY (Đã nhận SLAVE_INTER_KEY sau khi so sánh receive!=0xF0
			//========================================================================
			//RX[] = 0x7F - 0x80 - 0x11 - 8byte SLAVE_INTER_KEY - CRCL - CRCH
			for (unsigned char i=4; i<12; i++)
			{
				unsigned long long SLAVE_INTER_KEY00 = RX[i];
				NEGA.SLAVE_INTER_KEY = (NEGA.SLAVE_INTER_KEY | (SLAVE_INTER_KEY00<<(8*(i-4))));
			}
			/*byte M[16];
			for(unsigned char i=0; i<8; i++)
			{
				M[i] = (NEGA.SLAVE_INTER_KEY>>(8*i));
				Serial.print(M[i], HEX);
				Serial.print(" ");
			}*/
			//Tính NEGATIVE_KEY
			unsigned long long NG = 1;
			for (unsigned char i=0; i<NEGA.HOST_RANDOM; i++)
			{
				NG = NG*NEGA.SLAVE_INTER_KEY;
			}
			NEGA.NEGATIVE_KEY = (NG%NEGA.MODULUS);
			KEY.NEGATIVE = NEGA.NEGATIVE_KEY;	
			ENCRYPT_STATUS = 1;
		}
		
		void NV11::make_fullkey()
		{
			for (unsigned char i=0; i<8; i++)
			{
				KEY.FULLKEY_ARR[i] = (KEY.FIXED>>(8*i));
			}
			for (unsigned char i=8; i<16; i++)
			{
				KEY.FULLKEY_ARR[i] = (KEY.NEGATIVE>>(8*(i-8)));
			}
			/*for (int i=0; i<16; i++)
			{
				Serial.print(KEY.FULLKEY_ARR[i], HEX);
				Serial.print(" ");
			}
			Serial.println();*/
		}//Kết thúc hàm thì full key được lưu trong KEY.ARR

		void NV11::make_epacket(byte data[], unsigned char length_data)
		{
			byte ARR_COUNT[4];
			EPACKET.COUNT = count;
			EPACKET.LENGTH = length_data;
			for (unsigned char i=0; i<4; i++)
			{
				ARR_COUNT[i] = (EPACKET.COUNT>>(8*i));
			}
			for (unsigned char i=0; i<EPACKET.LENGTH; i++)
			{
				EPACKET.DATA[i] = data[i];
			}
			//Tính CRC
			Crc.ResetCrc();
			Crc.UpdateCrc(EPACKET.LENGTH);
			for(unsigned char i=0; i<4; i++)
			{
				Crc.UpdateCrc(ARR_COUNT[i]);
			}
			for (unsigned char i=0; i<9; i++)
			{
				Crc.UpdateCrc(EPACKET.DATA[i]);
			}
			EPACKET.CRCL = Crc.L;
			EPACKET.CRCH = Crc.H;
			//Đặt tất cả các giá trị tính được vào 1 mảng EPACKET.ARR
			EPACKET.ARR[0] = EPACKET.LENGTH;
			for (unsigned char i=1; i<5; i++)
			{
				EPACKET.ARR[i] = ARR_COUNT[i-1];
			}
			for (unsigned char i=5; i<14; i++)
			{
				EPACKET.ARR[i] = EPACKET.DATA[i-5];
			}
			EPACKET.ARR[14] = EPACKET.CRCL;
			EPACKET.ARR[15] = EPACKET.CRCH;
		}

		void NV11::send_epacket(byte data[], unsigned char length_data)
		{
			make_epacket(data, length_data);//tạo gói tin đầy đủ để mã hóa, lưu trong EPACKET.ARR
			aes128_enc_single(KEY.FULLKEY_ARR, EPACKET.ARR);//Mã hóa gói tin EPACKET.ARR, lưu lại vào chính nó
			for (unsigned char i=0; i<16; i++)//kiểm tra 16 byte vừa mã hóa
			{
				EPACKET.ARR_SEND[i+1] = EPACKET.ARR[i];
			}
			send_packet(EPACKET.ARR_SEND, sizeof(EPACKET.ARR_SEND));//Gửi gói tin EPACKET.ARR vừa mã hóa đi
			count++;
		}

		void NV11::clear_ERX()
		{
			for(unsigned char i=0; i<16; i++)
			{
				ERX[i] = 0x00;
			}
		}

		byte NV11::receive_epacket()
		{
			receive_packet();
			if(RX[3]==0x7E)
			{
				//Serial.println("Gói tin trước mã hóa là: ");
				for (unsigned char i=0; i<16; i++)
				{
					ERX[i] = RX[i+4];
					//Serial.print(ERX[i], HEX);
					//Serial.print(" ");
				}
				//Serial.println();
				aes128_dec_single(KEY.FULLKEY_ARR, ERX);//Sau khi giải mã, dữ liệu được lưu vào mảng ERX
				/*Serial.println("Gói tin sau mã hóa là: ");
				for (int i=0; i<16; i++)
				{
					Serial.print(ERX[i], HEX);
					Serial.print(" ");
				}*/
				return ERX[5];
			}
		}

		/**
		int c = 0;
		byte receive_resend()
		{
			c = 0;
			while(Serial.available()==0)
			{
				delay(1);
				c++;
				if (c==1000)
				{
					count --;
					send_epacket(mang, length);
					c = 0;
				}
			}
			receive_epacket();
			return ERX[5];
		}

		/*******************************************************************************************************/
		/** Các hàm có thể sử dụng trong chương trình **********************************************************/

		void NV11::send(byte data[], unsigned char length_data)
		{
			if(ENCRYPT_STATUS==0)// Nếu không ở trong trạng thái mã hóa thì chỉ gửi gói tin đi
			{
				send_packet(data, length_data);
			}
			
			else if(ENCRYPT_STATUS==1)// Còn nếu ở trong trạng thái mã hóa thì phải mã hóa gói tin rồi mới gửi đi
			{
				make_epacket(data, length_data);//tạo gói tin đầy đủ để mã hóa, lưu trong EPACKET.ARR
				aes128_enc_single(KEY.FULLKEY_ARR, EPACKET.ARR);//Mã hóa gói tin EPACKET.ARR, lưu lại vào chính nó
				for (unsigned char i=0; i<16; i++)//kiểm tra 16 byte vừa mã hóa, thêm 0x7E
				{
					EPACKET.ARR_SEND[i+1] = EPACKET.ARR[i];
				}
				send_packet(EPACKET.ARR_SEND, sizeof(EPACKET.ARR_SEND));//Gửi gói tin EPACKET.ARR vừa mã hóa đi
				count++;
			}
		}

		uint8_t NV11::receive()	//Kết thúc hàm này thì mọi dữ liệu nhận được được lưu trong ERX, kể cả đã được giải mã.
		{
			if(ENCRYPT_STATUS==0)//Nếu không ở trong chế độ mã hóa thì chỉ nhận gói dữ liệu
			{
				receive_packet();
				for( unsigned char i=0; i<16; i++)
				{
					ERX[i] = RX[i+3];
				}
				Serial.print("Nhận: ");
				for (unsigned char i=0; i <RX[2]; i++)
				{
					Serial.print(RX[i+3], HEX);
					Serial.print(" ");
				}
				Serial.println();
				/*unsigned short int dodaigoitin = RX[2];
				for(int i=3; i<(dodaigoitin+3); i++)
				{
					Serial.print(RX[i]);
					Serial.print(" ");
				}
				Serial.println();*/
				return RX[3];
			}
			
			else if(ENCRYPT_STATUS==1)	//Nếu ở trong chế độ mã hóa thì nhận gói dữ liệu và giải mã
			{
				receive_epacket();
				/**for (int i=0; i<16; i++)
				{
					Serial.print(ERX[i], HEX);
					Serial.print(" ");
				}*/
				unsigned short int dodaigoitine = ERX[0];
				Serial.print("Nhận: ");
				for(unsigned char i=5; i<dodaigoitine+5; i++)
				{
					Serial.print(ERX[i], HEX);
					Serial.print(" ");			
				}
				Serial.println();
				return ERX[5];
			}
		}
		
		void NV11::clear()
		{
			clear_RX();
			clear_ERX();
		}
		
		/**
		/*******************************************************************************************************/
		/**Các hàm rút gọn chạy trong chương trình chính */

		void NV11::hienthidulieu_gui()
		{
			Serial.print("Gửi: ");
			for (unsigned char i=0; i<length_tx; i++)
			{
				Serial.print(mang[i], HEX);
				Serial.print(" ");
			}
			Serial.println(); 
		}

		void NV11::begin()
		{
			Serial1.begin(9600, SERIAL_8N2); //Cổng kết nối với NV11
			Serial.begin(115200);	//Cổng hiển thị dữ liệu
			//Gửi lệnh đồng bộ
			clear();
			mang[0] = 0x11;
			length_tx = 1;
			send(mang, length_tx);
			delay(50);
			hienthidulieu_gui();
			receive();
			//Tạo khóa
			make_negative_key();
			make_fullkey();
			//-------------------------------------------------------------
			clear();
			mang[0]=0x06; mang[1]=0x06;
			length_tx = 2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//--------------------------------------------------------------
			clear();
			mang[0]=0x06; mang[1]=0x07;
			length_tx = 2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x06; mang[1]=0x08;
			length_tx = 2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x06; mang[1]=0x07;
			length_tx = 2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			/*clear();
			mang[0]=0x05;
			length_tx = 1;
			send(mang, length_tx);
			hienthidulieu_gui();
			receive();
			*/
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x40; mang[2]=0x0D; mang[3]=0x03; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x20; mang[2]=0xA1; mang[3]=0x07; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x40; mang[2]=0x42; mang[3]=0x0F; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x80; mang[2]=0x84; mang[3]=0x1E; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x40; mang[2]=0x4B; mang[3]=0x4C; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x80; mang[2]=0x96; mang[3]=0x98; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x02; mang[1]=0xFF; mang[2]=0xFF; 
			length_tx = 3;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x0A;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x45; mang[1]=0x01;
			length_tx = 2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x41;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			clear();
			//---------------------------------------------------------------
			/*mang[0]=0x45; mang[1]=0x00;
			length_tx = 2;
			send(mang, length_tx);
			hienthidulieu_gui();
			receive();*/
			//---------------------------------------------------------------
			tu_choi_tien();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x07;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			if(ERX[5]==0xF0)
			{
				LOI = 1;
			}
			else LOI = 0;
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x40; mang[2]=0x0D; mang[3]=0x03; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x20; mang[2]=0xA1; mang[3]=0x07; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x40; mang[2]=0x42; mang[3]=0x0F; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x80; mang[2]=0x84; mang[3]=0x1E; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x40; mang[2]=0x4B; mang[3]=0x4C; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3C; mang[1]=0x80; mang[2]=0x96; mang[3]=0x98; mang[4]=0x00; mang[5]=0x56; mang[6]=0x4E; mang[7]=0x44;
			length_tx = 8;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			//Serial.println("OK 2");
			//---------------------------------------------------------------
			clear();
			mang[0]=0x5C; mang[1]=0x01;
			length_tx=2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear(); // 2000đ
			//mang[0]=0x3B; mang[1]=0x01; mang[2]=0x40; mang[3]=0x0D; mang[4]=0x03; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			//length_tx = 9;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear(); //5000đ - 3
			//mang[0]=0x3B; mang[1]=0x00; mang[2]=0x20; mang[3]=0xA1; mang[4]=0x07; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			//length_tx = 9;
			mang[0]=0x3B; mang[1]=0x00; mang[2]=0x03;mang[3]=0x56; mang[4]=0x4E; mang[5]=0x44;
			length_tx = 6;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3B; mang[1]=0x01; mang[2]=0x40; mang[3]=0x42; mang[4]=0x0F; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			length_tx = 9;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3B; mang[1]=0x01; mang[2]=0x80; mang[3]=0x84; mang[4]=0x1E; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			length_tx = 9;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3B; mang[1]=0x01; mang[2]=0x40; mang[3]=0x4B; mang[4]=0x4C; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			length_tx = 9;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------------------------------------------------
			clear();
			mang[0]=0x3B; mang[1]=0x01; mang[2]=0x80; mang[3]=0x96; mang[4]=0x98; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			length_tx = 9;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			//---------------------
			//tu_choi_tien();
			//tra_lai_tien();
			
		}

		void NV11::kiemtrahienthi() //Hiển thị dữ liệu nhận được
		{
			for (unsigned char i=0; i<16; i++)
			{
				Serial.print(ERX[i], HEX);
				Serial.print(" ");
			}
			Serial.println();
		}
		
		void NV11::dong_bo()
		{
			clear();
			mang[0]=0x11;
			length_tx = 1;
			send(mang, length_tx);
			delay(10);
			hienthidulieu_gui();
			receive();
		}
		
		void NV11::gui_lenh_tham_do()
		{
			clear();
			mang[0]=0x07; length_tx = 1;
			send(mang, length_tx);
			hienthidulieu_gui();
		}
		
		void NV11::tham_do() //0x07 lệnh thăm dò tiền
		{
			clear();
			mang[0]=0x07;
			length_tx = 1;
			send(mang, length_tx);
			hienthidulieu_gui();
			delay(150);
			receive();
		}
		
		void NV11::tu_choi_tien() // từ chối tiền
		{
			clear();
			mang[0]=0x08;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
		}
		
		void NV11::giu_tien()
		{
			clear();
			mang[0]=0x18;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
		}
		
		void NV11::gui_lenh_giu_tien()
		{
			clear();
			mang[0]=0x18;
			length_tx = 1;
			send(mang, length_tx);	
			hienthidulieu_gui();	
		}
		
		void NV11::tra_loi_theo_kenh()
		{
			clear();
			mang[0]=0x45; mang[1]=0x01;
			length_tx = 2;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
		}
		
		void NV11::tra_loi_theo_gia_tri()
		{
			clear();
			mang[0]=0x45; mang[1]=0x00;
			length_tx = 2;
			send(mang, length_tx);delay(50);
			hienthidulieu_gui();
			receive();
		}
		
		void NV11::tra_cuu_so_tien_tra_lai()
		{
			clear();
			mang[0]=0x41;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			delay(150);
			hienthidulieu_gui();
			receive();
		}
		
		void NV11::tra_lai_tien()
		{
			clear();
			mang[0]=0x42;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();			
		}
		
		void NV11::empty_recycle()
		{
			clear();
			mang[0]=0x3F;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
		}
	
		void NV11::enable()
		{
			clear();
			mang[0]=0x0A;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();	
		}
		
		void NV11::dua_tien_xuong_stacker()
		{
			tham_do();
		}
		
		void NV11::dua_tien_len_note_float()
		{
			clear();
			//mang[0]=0x3B; mang[1]=0x00; mang[2]=0x20; mang[3]=0xA1; mang[4]=0x07; mang[5]=0x00; mang[6]=0x56; mang[7]=0x4E; mang[8]=0x44;
			//length_tx = 9;
			mang[0]=0x3B; mang[1]=0x00; mang[2]=0x03;mang[3]=0x56; mang[4]=0x4E; mang[5]=0x44;
			length_tx = 6;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();
			tham_do();
		}
		
		void NV11::disable()
		{
			clear();
			mang[0]=0x09;
			length_tx = 1;
			send(mang, length_tx); delay(50);
			hienthidulieu_gui();
			receive();				
		}
		
		static NV11 Nv11;
		
/*
	Quá trình kiểm tra dữ liệu trong bộ nhớ EEPROM
*/

#include <MBH.h>

void MAY_BAN_HANG::kiem_tra_ket_noi_voi_EEPROM()
{
	if(EEPROM.read(2900)!=0x87) // Kiểm tra ô nhớ số 3000
	{
		EEPROM_LOI = 0; // Lỗi
		lcd_check_loi_2();
	}
	else
		EEPROM_LOI = 1; // Không lỗi
}

void MAY_BAN_HANG::doc_tai_khoan()
{
	tai_khoan = EEPROM.read(ADDR_TAI_KHOAN[1]);
	tai_khoan = (tai_khoan<<8)|(EEPROM.read(ADDR_TAI_KHOAN[0]));
	if(tai_khoan>1000)
	{
		// Serial.println(Tài khoản vượt quá mức 1triệu, có lỗi bộ nhớ - Reset);
		tai_khoan = 0;
		EEPROM.write(ADDR_TAI_KHOAN[0], 0x00);
		EEPROM.write(ADDR_TAI_KHOAN[1], 0x00);
	}
}

void MAY_BAN_HANG::doc_gia_tien()
{
	for(int i=1; i<60; i++)
		gia_tien[i] = EEPROM.read(ADDR_GIA_TIEN[i]); 
}

void MAY_BAN_HANG::doc_so_hang()
{
	for(int i=1; i<60; i++)
	{
		so_hang[i] = EEPROM.read(ADDR_SO_HANG[i]);
		if(so_hang[i]==0)
		{
			EEPROM.write(ADDR_LOI_DC[i], khoa);
			delay(5);
		}
	}
}

void MAY_BAN_HANG::doc_o_hang_khoa()
{
	for(int i=1; i<60; i++)
	{
		if((i%10==1)||(i%10==2)||(i%10==3)||(i%10==4)||(i%10==5)||(i%10==6))
		{
			o_hang_loi[i] = EEPROM.read(ADDR_LOI_DC[i]); 
			if((o_hang_loi[i]!=0)&&(o_hang_loi[i]!=1)&&(o_hang_loi[i]!=2))
			{
				o_hang_loi[i] = 0x00;
				EEPROM.write(ADDR_LOI_DC[i], 0x00); delay(5); // Nếu giá trị ô lỗi khác cả 0,1,2 thì ô đó đã bị lỗi (lỗi ô nhớ)
			}
		}
	}
}

/*
	Các hàm xử lý của thư viện MBH.
*/ 

#include <MBH.h>
U8GLIB_ST7920_128X64_4X u8g(58, 56, 57); // Định nghĩa chân kết nối LCD


// ===================================================
// Định nghĩa các chân kết nối bàn phím

char keys[4][3] = 
{										//	
	{'0','4','8'},						//	0x30 0x34 0x38
	{'1','5','9'},						//	0x31 0x35 0x39
	{'2','6','*'},						//	0x32 0x36 0x2A
	{'3','7','#'},						//	0x33 0x37 0x23
};

byte rowPins[4] = {25, 26, 27, 28}; 	//Ket noi voi dau ra cua arduino hang ngang
byte colPins[3] = {22, 23, 24}; 		//Ket noi voi dau ra cua arduino cot doc
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3 );//Gan bien
#define sound 50//Chân gắn loa


// ===================================================
void MAY_BAN_HANG::begin()
{
	khoi_dong();
	asm("cli");			// Tắt ngắt toàn cục của AVR
	asm("sei");
}

// ===================================================
void MAY_BAN_HANG::chuong_trinh_mua_hang()
{
	//Serial.println("Chương trình mua hàng");
	qua_trinh_doc_EEPROM();
	qua_trinh_mua_hang();
	qua_trinh_tinh_va_luu_doanh_thu_EEPROM();
}

// ===================================================
void MAY_BAN_HANG::chuong_trinh_cai_dat()
{
	//Serial.println("Chương trình cài đặt");
	qua_trinh_cai_dat();
}

static MAY_BAN_HANG Mbh;

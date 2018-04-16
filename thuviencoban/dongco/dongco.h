/*
	Các hàm điều khiển và dừng động cơ
*/

#ifndef dongco_h
#define dongco_h

#include <Arduino.h>

class DONG_CO
{
	public:
		
		void begin();
		void quay_1_vong(unsigned char o_hang);
		void quay_1_vong_khong_cam_bien_roi(unsigned char o_hang);
		void bat_diem_0();
		
};

extern DONG_CO Dongco;

#endif
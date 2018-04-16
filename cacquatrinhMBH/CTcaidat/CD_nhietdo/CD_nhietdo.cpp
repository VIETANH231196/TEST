/*
	Mục cài đặt nhiệt độ
*/

#include <MBH.h>

void MAY_BAN_HANG::trang_cai_dat_nhiet_do()					// Trang 1-1	
		{
			value_nhiet_do_cai_dat=EEPROM.read(ADDR_NHIET_DO_CAI_DAT);
			lcd_cai_dat_nhiet_do();
			while (trang_cai_dat_duoc_lua_chon)
			{  
				doc_ban_phim_cd();
				if(key=='8')
				{
					 value_nhiet_do_cai_dat++;
					 lcd_cai_dat_nhiet_do();
				}
				else if(key=='0')
				{
					 value_nhiet_do_cai_dat--;
					 lcd_cai_dat_nhiet_do();
				}
				
				else if(key=='#') 
				{
					goto thoat_cai_dat_nhiet_do;
				}
				else if(key=='*') 
				{   
                     doc_ban_phim_cd();
				     EEPROM.write(ADDR_NHIET_DO_CAI_DAT, value_nhiet_do_cai_dat); delay(5);
					goto thoat_cai_dat_nhiet_do;
				}
			}
			thoat_cai_dat_nhiet_do:
			{
				trang_cai_dat_duoc_lua_chon = 2;
			}
		}	
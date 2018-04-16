/*
	Mục cài đặt máy lạnh
*/

#include <MBH.h>

void MAY_BAN_HANG::trang_cai_dat_may_lanh()					// Trang 1-1	
		{
			value_tt_ML=EEPROM.read(ADDR_TRANG_THAI_ML);
			value_nhiet_do_cai_dat=EEPROM.read(ADDR_NHIET_DO_CAI_DAT);
			lcd_cai_dat_may_lanh();
			while (trang_cai_dat_duoc_lua_chon)
			{  
				doc_ban_phim_cd();
				if(key=='8')
				{
					value_tt_ML=1;
					lcd_cai_dat_may_lanh();
				}
				else if(key=='0')
				{
					value_tt_ML=0;
					lcd_cai_dat_may_lanh();
				}
				
				else if(key=='#') 
				{
					goto thoat_cai_dat_may_lanh;
				}
				else if(key=='*') 
				{   
   
					if(value_tt_ML==1)
					{
					 digitalWrite(5 , LOW);
                     digitalWrite(4 , LOW);	
					 trang_cai_dat_nhiet_do();	
					  
					}
					else if(value_tt_ML==0)
					{
					 digitalWrite(5 , HIGH);  //// Tat dieu hoa
                     digitalWrite(4 , HIGH);	
					}
					EEPROM.write(ADDR_TRANG_THAI_ML, value_tt_ML); delay(5);
					goto thoat_cai_dat_may_lanh;
				}
			}
			thoat_cai_dat_may_lanh:
			{
				trang_cai_dat_duoc_lua_chon = 1;
			}
			
		}	
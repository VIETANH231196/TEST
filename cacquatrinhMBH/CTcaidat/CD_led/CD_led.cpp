/*
	Cài đặt bật tắt đèn led
*/
#include <MBH.h>


void MAY_BAN_HANG::trang_cai_dat_led()					// Trang 1-1	
		{   
		    value_trang_thai_led=EEPROM.read(ADDR_TRANG_THAI_LED);
			lcd_cai_dat_led();
			while (trang_cai_dat_duoc_lua_chon)
			{
				doc_ban_phim_cd();
				if(key=='8')
				{
					value_trang_thai_led=1;
					lcd_cai_dat_led();
				}
				else if(key=='0')
				{
					value_trang_thai_led=0;
					lcd_cai_dat_led();
				}
				
				else if(key=='#') // Nhấn nút CANCEL
				{
					goto thoat_cai_dat_led;
				}
				else if(key=='*') 
				{   
   
					if(value_trang_thai_led==1)
					{
					     digitalWrite(A1,HIGH);
					}
					if(value_trang_thai_led==0)
					{
					     digitalWrite(A1,LOW);
					}
					EEPROM.write(ADDR_TRANG_THAI_LED, value_trang_thai_led); delay(5);
					goto thoat_cai_dat_led;
				}
			}
			thoat_cai_dat_led:
			{
				trang_cai_dat_duoc_lua_chon = 4;
			}
			
		}	
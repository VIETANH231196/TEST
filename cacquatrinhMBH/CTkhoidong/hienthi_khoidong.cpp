

#include <MBH.h>

void MAY_BAN_HANG::lcd_kd_may_36_ngan()
{
	u8g.firstPage(); 
	do
	{
		u8g.setFont(u8g_font_unifont);
		u8g.setPrintPos(20, 20);
		Str.str('M','A','Y',' ','B','A','N',' ','H','A','N','G', Str.max_128[0]);
		u8g.print(Str.max_128);
		u8g.setPrintPos(45, 37);
		Str.str('3','6',' ','N','G','A','N', Str.max_128[0]);
		u8g.print(Str.max_128);
	}
	while(u8g.nextPage());	
}

void MAY_BAN_HANG::lcd_check_loi_1()
{
	u8g.firstPage(); 
	do
	{
		u8g.setFont(u8g_font_unifont);
		u8g.setPrintPos(0, 20);
		Str.str('D','a','u',' ','d','o','c',' ','t','i','e','n', Str.max_128[0]);
		u8g.print(Str.max_128);
		u8g.setPrintPos(0, 45);
		switch(Nv11.LOI)
		{
			case 1:	
				Str.str('D','a',' ','k','e','t',' ','n','o','i', Str.max_128[0]);
				u8g.print(Str.max_128);
				break;
			case 0:
				Str.str('L','o','i', Str.max_128[0]);
				u8g.print(Str.max_128);
				break;
		}	
	}
	while(u8g.nextPage());	
}

void MAY_BAN_HANG::lcd_check_loi_2()
{
	u8g.firstPage(); 
	do
	{
		u8g.setFont(u8g_font_unifont);
		u8g.setPrintPos(0, 20);
		Str.str('B','o',' ','n','h','o', Str.max_128[0]);
		u8g.print(Str.max_128);		
		u8g.setPrintPos(0, 45);
		switch(EEPROM_LOI)
		{
			case 1:	
				Str.str('D','a',' ','k','e','t',' ','n','o','i', Str.max_128[0]);
				u8g.print(Str.max_128);		
				break;				
			case 0:
				Str.str('L','o','i',' ','h','o','a','c',' ','c','h','u','a',' ','C','D', Str.max_128[0]);
				u8g.print(Str.max_128);			
				break;
		}
	}
	while(u8g.nextPage());	
	switch(EEPROM_LOI)
	{
		case 0: while(1); break;
		case 1: break;
	}
}

void MAY_BAN_HANG::lcd_check_loi_3()
{
	u8g.firstPage(); 
	do
	{
		u8g.setFont(u8g_font_unifont);
		u8g.setPrintPos(0, 20);
		Str.str('M','o','d','u','l','e',' ','S','I','M','2','G',':', Str.max_128[0]);
		u8g.print(Str.max_128);		
		u8g.setPrintPos(0, 45);
		switch(Sim.SIM_STATUS)
		{
			case 1:	
				Str.str('O','N','L','I','N','E', Str.max_128[0]);
				u8g.print(Str.max_128);
				break;
			case 0:
				Str.str('O','F','F','L','I','N','E', Str.max_128[0]);
				u8g.print(Str.max_128);			
				break;
		}
	}
	while(u8g.nextPage());		
}

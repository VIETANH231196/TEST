

#include <thuviencoban/String/Str.h>


void STRING::str(ch s0, ch &ret)//1
{
	ret = s0;
	*(&ret+1) = 0x00;
}

void STRING::str(ch s0,ch s1,ch &ret)//2
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch &ret)//3
{
	ret = s0;
	*(&ret+1) = s1;
	*(&ret+2) = s2;	
	*(&ret+3) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch &ret)//4
{
	ret = s0;
	*(&ret+1) = s1;
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch &ret)//5
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch &ret)//6
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;	
	*(&ret+6) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch &ret)//7
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch &ret)//8
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;	
	*(&ret+6) = s6;	
	*(&ret+7) = s7;	
	*(&ret+8) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch &ret)//9
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;	
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch &ret)//10
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch &ret)//11
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;	
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;	
	*(&ret+11) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch &ret)//12
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch &ret)//13
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;	
	*(&ret+12) = s12;
	*(&ret+13) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch &ret)//14
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch &ret)//15
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;	
	*(&ret+15) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch &ret)//16
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch &ret)//17
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch &ret)//18
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;
	*(&ret+18) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch &ret)//19
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;
	*(&ret+19) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch &ret)//20
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;	
	*(&ret+20) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch &ret)//21
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch &ret)//22
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch &ret)//23
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = 0x00;	
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch &ret)//24
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;
	*(&ret+24) = 0x00;
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch &ret)//25
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;	
	*(&ret+24) = s24;
	*(&ret+25) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch &ret)//26
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;	
	*(&ret+24) = s24;
	*(&ret+25) = s25;	
	*(&ret+26) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch &ret)//27
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;	
	*(&ret+24) = s24;
	*(&ret+25) = s25;	
	*(&ret+26) = s26;
	*(&ret+27) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch &ret)//28
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;
	*(&ret+24) = s24;
	*(&ret+25) = s25;
	*(&ret+26) = s26;
	*(&ret+27) = s27;	
	*(&ret+28) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch &ret)//29
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;
	*(&ret+24) = s24;
	*(&ret+25) = s25;
	*(&ret+26) = s26;
	*(&ret+27) = s27;
	*(&ret+28) = s28;	
	*(&ret+29) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch s29,ch &ret)//30
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;
	*(&ret+24) = s24;
	*(&ret+25) = s25;
	*(&ret+26) = s26;
	*(&ret+27) = s27;
	*(&ret+28) = s28;	
	*(&ret+29) = s29;
	*(&ret+30) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch s29,ch s30,ch &ret)//31
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;
	*(&ret+24) = s24;
	*(&ret+25) = s25;
	*(&ret+26) = s26;
	*(&ret+27) = s27;
	*(&ret+28) = s28;
	*(&ret+29) = s29;
	*(&ret+30) = s30;
	*(&ret+31) = 0x00;		
}

void STRING::str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch s29,ch s30,ch s31,ch &ret)//32
{
	ret = s0;
	*(&ret+1) = s1;	
	*(&ret+2) = s2;
	*(&ret+3) = s3;
	*(&ret+4) = s4;
	*(&ret+5) = s5;
	*(&ret+6) = s6;	
	*(&ret+7) = s7;
	*(&ret+8) = s8;
	*(&ret+9) = s9;
	*(&ret+10) = s10;
	*(&ret+11) = s11;
	*(&ret+12) = s12;
	*(&ret+13) = s13;
	*(&ret+14) = s14;
	*(&ret+15) = s15;
	*(&ret+16) = s16;
	*(&ret+17) = s17;	
	*(&ret+18) = s18;	
	*(&ret+19) = s19;
	*(&ret+20) = s20;	
	*(&ret+21) = s21;
	*(&ret+22) = s22;
	*(&ret+23) = s23;
	*(&ret+24) = s24;
	*(&ret+25) = s25;
	*(&ret+26) = s26;
	*(&ret+27) = s27;
	*(&ret+28) = s28;	
	*(&ret+29) = s29;
	*(&ret+30) = s30;
	*(&ret+31) = s31;
	*(&ret+32) = 0x00;		
}

static STRING Str;


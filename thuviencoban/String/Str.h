/*
	Thư viện cho phép sử dụng chung 1 vùng bộ nhớ String
*/

#ifndef Str_h
#define Str_h

#define ch char // Dùng define cho tiết kiệm tốc độ xử lý so với typedef

class STRING
{
	public:
	
char max_128[128];
		
void str(ch s0,ch &ret);//1
void str(ch s0,ch s1,ch &ret);//2
void str(ch s0,ch s1,ch s2,ch &ret);//3
void str(ch s0,ch s1,ch s2,ch s3,ch &ret);//4
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch &ret);//5
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch &ret);//6
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch &ret);//7
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch &ret);//8
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch &ret);//9
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch &ret);//10
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch &ret);//11
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch &ret);//12
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch &ret);//13
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch &ret);//14
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch &ret);//15
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch &ret);//16
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch &ret);//17
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch &ret);//18
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch &ret);//19
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch &ret);//20
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch &ret);//21
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch &ret);//22
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch &ret);//23
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch &ret);//24
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch &ret);//25
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch &ret);//26
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch &ret);//27
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch &ret);//28
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch &ret);//29
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch s29,ch &ret);//30
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch s29,ch s30,ch &ret);//31
void str(ch s0,ch s1,ch s2,ch s3,ch s4,ch s5,ch s6,ch s7,ch s8,ch s9,ch s10,ch s11,ch s12,ch s13,ch s14,ch s15,ch s16,ch s17,ch s18,ch s19,ch s20,ch s21,ch s22,ch s23,ch s24,ch s25,ch s26,ch s27,ch s28,ch s29,ch s30,ch s31,ch &ret);//32

};

extern STRING Str;


#endif
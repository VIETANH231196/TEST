/*
	File CRC.cpp Ver1.0: Tạo mã Check sum 16 bit
*/

#include "CRC.h"

//------------------------------------------------------------------------
  void Cyclic_Redundancy_Check::UpdateCrc(const unsigned char num)
  {
    unsigned int table_addr;
    table_addr=(num ^ H);
    H=(CrcTable[table_addr] >> 8) ^ L;
    L=(CrcTable[table_addr] & 0x00FF);
  }
//------------------------------------------------------------------------
  void Cyclic_Redundancy_Check::ResetCrc(void) 
  {
  L=0xFF;
  H=0xFF;
  }

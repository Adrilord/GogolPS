#include "charmanagement.h"

//SUR AVR, ON N'A PAS BESOIN du \0
void strupdate(char* dest, unsigned int begin, char* src, unsigned int sizeSrc)
{
  int i=0;
  for(int i=0; i<sizeSrc; i++) {
    dest[begin+i] = src[i];
  }
}

void int2TabChar(char* dest, unsigned int sizeDest, int src)
{
  int i=0;
  for(i=sizeDest-1; i>=0; i--) {
    dest[i] = src % 10 + 48; // 48 <-> 0 en ASCII
    src/=10;
  }
}

void long2TabChar(char* dest, unsigned int sizeDest, long src)
{
  int i=0;
  for(i=sizeDest-1; i>=0; i--) {
    dest[i] = src % 10 + 48; // 48 <-> 0 en ASCII
    src/=10;
  }
}

void float2TabChar(char* dest, unsigned int sizeInt, unsigned int sizeDec, float src)
{
  int integerPart = (int) src;
  char dest1[sizeInt];
  int2TabChar(dest1, sizeInt, integerPart);
  float tempDecimalPart = (src - (float) integerPart);
  int i=0;
  for(int i=0; i<sizeDec; i++) {
    tempDecimalPart*=10;
  }
  int decimalPart = (int) tempDecimalPart;
  char dest2[sizeDec];
  int2TabChar(dest2, sizeDec, decimalPart);
  strupdate(dest, 0, dest1, sizeInt);
  strupdate(dest, sizeInt, ".", 1);
  strupdate(dest, sizeInt+1, dest2, sizeDec);
}

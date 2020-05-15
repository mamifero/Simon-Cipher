#ifndef NUMERICFUNCTION_H_INCLUDED
#define NUMERICFUNCTION_H_INCLUDED

#include <iostream>

#define u8 uint8_t
#define u32 uint32_t
#define u64 uint64_t

void Words32ToBytes(u32 words[],u8 bytes[],int numwords);
void Words64ToBytes(u64 words[],u8 bytes[],int numwords);
void BytesToWords32(u8 bytes[],u32 words[],int numbytes);
void BytesToWords64(u8 bytes[],u64 words[],int numbytes);


#endif // NUMERICFUNCTION_H_INCLUDED

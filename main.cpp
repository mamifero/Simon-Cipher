#include <iostream>

#include "Cipher.h"
#include "NumericFunction.h"
#include "BMPManager.h"

using namespace std;

int main()
{
    Cipher cipherObject;
    u8 plain[]= "und like";
    u8 key[] = { 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0a, 0x0b, 0x10, 0x11, 0x12, 0x13, 0x18, 0x19, 0x1a, 0x1b};
    u8 cipher[8];

    u32 plainBlocks[2];
    u32 ciperBlocks[2];
    u32 keyBlocks[4];
    u32 keyExpandedBlocks[44];

    BytesToWords32(plain,plainBlocks,8);
    BytesToWords32(key,keyBlocks,16);

    cipherObject.Simon64128KeySchedule(keyBlocks,keyExpandedBlocks);
    cipherObject.Simon64128Encrypt(plainBlocks,ciperBlocks,keyExpandedBlocks);

    Words32ToBytes(ciperBlocks,cipher,2);

    cout << "Plain Blocks" << endl;
    cout << std::hex << plainBlocks[0] << endl;
    cout << std::hex << plainBlocks[1] << endl;
    cout << "Cipher Blocks" << endl;
    cout << std::hex << ciperBlocks[0] << endl;
    cout << std::hex << ciperBlocks[1] << endl;
    cout << "Cipher String" << endl;
    cout << cipher << endl;



    cout << "KeySchedule" << endl;
    for(int i = 0; i<44; i++){
        cout << i << " - "<< std::hex << keyExpandedBlocks[i] << endl;
    }

    cout << "Key Blocks" << endl;
    cout << std::hex << keyBlocks[0] << endl;
    cout << std::hex << keyBlocks[1] << endl;
    cout << std::hex << keyBlocks[2] << endl;
    cout << std::hex << keyBlocks[3] << endl;

    return 0;
}

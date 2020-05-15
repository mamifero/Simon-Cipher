#include "Cipher.h"


Cipher::Cipher()
{
    //ctor
}

void Cipher::Simon64128KeySchedule(u32 K[],u32 rk[])
{
    u32 i,c=0xfffffffc;
    u64 z=0xfc2ce51207a635dbLL;
    rk[0]=K[0];
    rk[1]=K[1];
    rk[2]=K[2];
    rk[3]=K[3];
    u32 tmp;
    for(i=4; i<44; i++)
    {
        tmp = ROTR32(rk[i-1],3);
        tmp^= rk[i-3];
        tmp^= ROTR32(tmp,1);
        rk[i]=rk[i-4] ^ tmp ^ c^(z&1);
        rk[i]=c^(z&1)^rk[i-4]^ROTR32(rk[i-1],3)^rk[i-3]
              ^ROTR32(rk[i-1],4)^ROTR32(rk[i-3],1);
        z>>=1;
    }
}
void Cipher::Simon64128Encrypt(u32 Pt[],u32 Ct[],u32 rk[])
{
    u32 i;
    Ct[1]=Pt[1];
    Ct[0]=Pt[0];
    for(i=0; i<44;){
        R32x2(Ct[1],Ct[0],rk[i++],rk[i++]);
        //cout << std::hex << Ct[0] << " - " <<std::hex << Ct[1] << endl;
    };
}
void Cipher::Simon64128Decrypt(u32 Pt[],u32 Ct[],u32 rk[])
{
    int i;
    Pt[1]=Ct[1];
    Pt[0]=Ct[0];
    for(i=43; i>=0;) R32x2(Pt[0],Pt[1],rk[i--],rk[i--]);
}

void Cipher::encryptECB(){

};

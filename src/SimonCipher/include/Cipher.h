#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>

#define u8 uint8_t
#define u32 uint32_t
#define u64 uint64_t

#define ROTL32(x,r) (((x)<<(r)) | (x>>(32-(r))))
#define ROTR32(x,r) (((x)>>(r)) | ((x)<<(32-(r))))
#define ROTL64(x,r) (((x)<<(r)) | (x>>(64-(r))))
#define ROTR64(x,r) (((x)>>(r)) | ((x)<<(64-(r))))

#define f32(x) ((ROTL32(x,1) & ROTL32(x,8)) ^ ROTL32(x,2))
#define R32x2(x,y,k1,k2) (y^=f32(x), y^=k1, x^=f32(y), x^=k2)

class Cipher
{
    public:
        Cipher();

        u8* GetplainText() { return plainText; }
        u32* Getplain32Block() { return plain32Block; }
        u64* Getplain64Block() { return plain64Block; }
        u64* Getcipher64Block() { return cipher64Block; }
        u32* Getcipher32Block() { return cipher32Block; }
        u8* GetcipherText() { return cipherText; }

        void Simon64128KeySchedule(u32 K[],u32 rk[]);
        void Simon64128Encrypt(u32 Pt[],u32 Ct[],u32 rk[]);
        void Simon64128Decrypt(u32 Pt[],u32 Ct[],u32 rk[]);

        void encryptECB();

    protected:

    private:
        u8* plainText;
        u32* plain32Block;
        u64* plain64Block;
        u64* cipher64Block;
        u32* cipher32Block;
        u8* cipherText;
};

#endif // CIPHER_H

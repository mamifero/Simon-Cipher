#include "Cipher.h"
#include <new>
#include <iostream>


Cipher::Cipher(u8 key1[],u64 cantBytes1)
{
    cantBytes = cantBytes1;
    

    //Determino la cantidad de bloques
    cantBlocks = cantBytes/8;

    if(cantBytes % 8 != 0){
        cantBlocks++;
    }
    //Duplico la cantidad, porque corresonden a la cantidad de medios bloques de 64
    cantBlocks*= 2;

    //Creo un nuevo espacio para albergar el mensaje y la clave
    plainText = new u8[cantBlocks*4];
    cipherText = new u8[cantBlocks*4];

    key = new u8[16];

    //Copio todo el key
    for (u64 i = 0; i<16; i++){
        key[i] = key1[i];
    }



    //Expando el espacio de claves
    u32 keyBlocks[4];
    BytesToWords32(key,keyBlocks,16);
    Simon64128KeySchedule(keyBlocks);
    ///showKeyExpanded(); DESCOMENTAR



    //Creo el espacio en memoria para albergar los bloques
    plain32Block = new u32[cantBlocks];
    cipher32Block = new u32[cantBlocks];
    

    

}

void Cipher::setPlainText(u8 textPlain[]){
    //Copio todo el mensaje
    for (u64 i = 0; i<cantBytes; i++){
        plainText[i] = textPlain[i];
    }

    //Lleno el resto con 0
    for (u64 i = cantBytes; i<cantBlocks*4; i++){
        plainText[i] = 0;
    }

    BytesToWords32(plainText, plain32Block, cantBlocks*4);
}


void Cipher::setCipherText(u8 textChiper[]){
    //Copio todo el mensaje
    for (u64 i = 0; i<cantBytes; i++){
        cipherText[i] = textChiper[i];
    }

    //Lleno el resto con 0
    for (u64 i = cantBytes; i<cantBlocks*4; i++){
        cipherText[i] = 0;
    }

    BytesToWords32(cipherText, cipher32Block, cantBlocks*4);
}

void Cipher::Simon64128KeySchedule(u32 K[])
{
    u32* rk = expandKey;
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



u8* Cipher::desencryptECB(){

    std::cout << "CantBlock" << '\n';
    std::cout << cantBlocks/2 << '\n';

    u32* pointPlain = plain32Block;
    u32* pointCipher = cipher32Block;


    for(u64 i = 0; i < cantBlocks/2; i++){
        Simon64128Decrypt(pointPlain,pointCipher,expandKey);
        //muevo los punteros para la proxima ronda
        pointPlain += 2;
        pointCipher += 2;
    }

    Words32ToBytes(plain32Block,plainText,cantBlocks);
    return plainText;

}


u8* Cipher::encryptECB(){

    std::cout << "CantBlock" << '\n';
    std::cout << cantBlocks/2 << '\n';

    u32* pointPlain = plain32Block;
    u32* pointCipher = cipher32Block;


    for(u64 i = 0; i < cantBlocks/2; i++){
        Simon64128Encrypt(pointPlain,pointCipher,expandKey);
        //muevo los punteros para la proxima ronda
        pointPlain += 2;
        pointCipher += 2;
    }

    Words32ToBytes(cipher32Block,cipherText,cantBlocks);
    return cipherText;

}

void Cipher::Simon64128Encrypt(u32 Pt[],u32 Ct[],u32 rk[])
{
    u32 i;
    Ct[1]=Pt[1];
    Ct[0]=Pt[0];
    for(i=0; i<44;){
        R32x2(Ct[1],Ct[0],rk[i++],rk[i++]);
        //cout << std::hex << Ct[0] << " - " <<std::hex << Ct[1] << endl;
    }
}

void Cipher::Simon64128Decrypt(u32 Pt[],u32 Ct[],u32 rk[])
{
    int i;
    Pt[1]=Ct[1];
    Pt[0]=Ct[0];
    for(i=43; i>=0;) R32x2(Pt[0],Pt[1],rk[i--],rk[i--]);
}

u8* Cipher::encryptCBC(){

    std::cout << "CantBlock" << '\n';
    std::cout << cantBlocks/2 << '\n';
    u32 vectorInit = 1251663163;

    u32* pointPlain = plain32Block;
    u32* pointCipher = cipher32Block;
    //std::cout <<'\n'<< "no se che:"<<*pointPlain<<'\n';

    *pointPlain = (*pointPlain)^(vectorInit);
    *(pointPlain+1) = (*(pointPlain+1))^(vectorInit);

    for(u64 i = 0; i < cantBlocks/2; i++){
        Simon64128Encrypt(pointPlain,pointCipher,expandKey);
        //muevo los punteros para la proxima ronda
        pointPlain += 2;
        *pointPlain = (*pointPlain)^(*pointCipher);
        pointCipher++;
        *(pointPlain+1) = (*(pointPlain+1))^(*pointCipher);
        pointCipher++;
        
    }

    Words32ToBytes(cipher32Block,cipherText,cantBlocks);
    return cipherText;

}


u8* Cipher::desencryptCBC(){

    std::cout << "CantBlock" << '\n';
    std::cout << cantBlocks/2 << '\n';
    u32 vectorInit = 1251663163;

    u32* pointPlain = plain32Block;
    u32* pointCipher = cipher32Block;
    u32 auxCipher[2]; 
    //std::cout <<'\n'<< "no se che:"<<*pointPlain<<'\n';
    
    Simon64128Decrypt(pointPlain,pointCipher,expandKey);
    *pointPlain = (*pointPlain)^(vectorInit);
    pointPlain++;
    *pointPlain = (*pointPlain)^(vectorInit);
    pointPlain++;


    // pointPlain += 2;
    auxCipher[0] = *pointCipher; 
    auxCipher[1] = *(pointCipher+1); 
    pointCipher += 2;


    for(u64 i = 2; i < cantBlocks/2; i++){
        //muevo los punteros para la proxima ronda
        // pointPlain += 2;
        Simon64128Decrypt(pointPlain,pointCipher,expandKey);
        *pointPlain = (*pointPlain)^auxCipher[0];
        pointPlain++;
        *pointPlain = (*pointPlain)^auxCipher[1];
        pointPlain++;
        auxCipher[0] = *pointCipher; 
        auxCipher[1] = *(pointCipher+1); 
        pointCipher += 2;

    }

    Words32ToBytes(plain32Block,plainText,cantBlocks);
    return plainText;

}


void Cipher::showKeyExpanded(){
    for(int i = 0; i < 44; i ++){
        std::cout << std::hex << expandKey[i] << '\n';
    }
}


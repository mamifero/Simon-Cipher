#include <iostream>

#include "Cipher.h"
#include "NumericFunction.h"
#include "BMPManager.h"


using namespace std;

void printHelp(char * name);

void mainThread();

int main(int argc, char *argv[])
{

    if(argc != 4){
        printHelp(argv[0]);
        return 0;
    }
    std::string mode (argv[1]);
    std::string input (argv[2]);
    std::string output (argv[3]);


    BMPManager fm(input, output);

    //    u8 plain[]= "und likeund like";

    u8 key[] = { 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0a, 0x0b, 0x10, 0x11, 0x12, 0x13, 0x18, 0x19, 0x1a, 0x1b};
    u64 cantBytes = fm.getBodySize();
    //cout << "\ncant bytes:" << cantBytes << '\n';///183729
    //u8 plain[cantBytes];
    u8* outputBody;

    u8* inputBody = fm.getBodyBytes();
    // fm.clonebodyBytes(plain);
    // fm.getFileInfo();

    Cipher cipherObject = Cipher(key, cantBytes);






    if(mode.compare("-ecbc") == 0){
        cout << "Encriptando archivo en modo CBC..." << "\n\n";
        cipherObject.setPlainText(inputBody);
        outputBody = cipherObject.encryptCBC();

    }else if(mode.compare("-eecb") == 0){
        cout << "Encriptando archivo en modo ECB..." << "\n\n";
        cipherObject.setPlainText(inputBody);
        outputBody = cipherObject.encryptECB();

    }else if(mode.compare("-dcbc") == 0){
        cout << "Desencriptando archivo en modo CBC..." << "\n\n";
        cipherObject.setCipherText(inputBody);
        outputBody = cipherObject.desencryptCBC();
    }else if(mode.compare("-decb") == 0){
        cout << "Desencriptando archivo en modo ECB..." << "\n\n";
        cipherObject.setCipherText(inputBody);
        outputBody = cipherObject.desencryptECB();
    }else{
        printHelp(argv[0]);
        return 0;
    }

    fm.setbodyBytes(outputBody);
    fm.saveFileCopy();

    cout << "Fin" << endl;



}


void printHelp(char * name){

    cout << "Usage: "<< name <<" [OPTION] [INPUT] [OUTPUT]" << "\n";
    cout << "Encripta/descripta archivos utilizando el algoritmo Simon64128" << "\n\n";
    cout << "   -ecbc      Encripta un archivo utilizando el modo CBC" << "\n";
    cout << "   -eecb      Encripta un archivo utilizando el modo ECB" << "\n";
    cout << "   -dcbc      Desencripta un archivo utilizando el modo CBC" << "\n";
    cout << "   -decb      Desencripta un archivo utilizando el modo ECB" << "\n";
    cout << "   -h         Muestra esta ayuda" << "\n";

}

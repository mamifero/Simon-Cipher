#include <iostream>
#include <string>


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
    string mode (argv[1]);
    string input (argv[2]);
    string output (argv[3]);
    string inputKey;


    BMPManager fm(input, output);

    //    u8 plain[]= "und likeund like";
    cout << "Introduzca la clave por favor (Max 16 caracteres): \n";
    getline (cin, inputKey);
    while(inputKey.length() > 16 || inputKey.length() == 0){
        cout << "La clave no puede ser mayor a 16 carateres o estar vacia. \n";
        cout << "Introduzca la clave por favor (Max 16 caracteres): \n";
        getline (cin, inputKey);
    }
    u8 key[16] = {0};
    inputKey.copy((char*)key, inputKey.length());
    u64 cantBytes = fm.getBodySize();

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

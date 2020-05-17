#include "BMPManager.h"



BMPManager::BMPManager(){}

BMPManager::BMPManager(const char*file){

        ///Intenta abrirlo, sino se rompe todo
        archivo.open(file, ios::binary);
        if(archivo.fail())
            cerr << "Error al abrir el archivo" << endl;

        ///Seteo el file path, todavia no se para que
        strcpy(filePath, file);

        ///Guardo el header en un vector de bytes
        archivo.read((char*)headerbytes, sizeof(headerbytes));
        ///printeos rancios

        filetype[0] = *(uint8_t*)(headerbytes);
        filetype[1] = *(uint8_t*)(headerbytes+1);
        filetype[2] = '\0';

        if(strcmp((char*)filetype,"BM")!=0)
            cout << "solo manejo archivos de mapa de bits"<<endl;

        filesize = *(uint32_t*)(headerbytes+2);
        dibheadersize = *(uint32_t*)(headerbytes + 14);
        width = *(uint32_t*)(headerbytes + 18);
        height = *(uint32_t*)(headerbytes + 22);
        planes = *(uint16_t*)(headerbytes + 26);
        bitcount = *(uint16_t*)(headerbytes + 28);
        bodysize = filesize-54-dibheadersize+1;     ///NO TOCAR ESE +1 ES VITAL

        ///Ahora que conozco el bodysize, puedo almacenar espacio para el cuerpo de la imagen
        bodyBytes = new uint8_t[bodysize];

        headerinfobytes = new uint8_t[dibheadersize];
        ///Guardo el header con info opcional en otro vector
        archivo.read((char*)headerinfobytes, dibheadersize);
        ///Guardo el cuerpo de la imagen.
        archivo.read((char*)bodyBytes, bodysize);


}

int BMPManager::getFileSize(){

    streampos begin,end;
    ifstream myfile (filePath, ios::binary);
    if(myfile.fail())
            cerr << "Error al abrir el archivo" << endl;


    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    myfile.close();
    //cout << "size is: " << (end-begin) << " bytes.\n";
    return (end-begin);
}

void BMPManager::getFileInfo(){
        cout << "File type: "<< filetype <<endl;
        cout << "Filesize (bytes) " << filesize <<endl;
        cout << "dibheadersize " << dibheadersize <<endl;
        cout << "width " << width <<endl;
        cout << "height " << height <<endl;
        cout << "planes " << planes <<endl;
        cout << "bitcount " << bitcount <<endl;
        cout << "body size (bytes) " << bodysize <<endl;

    }

void BMPManager::saveFileCopy(){

    ofstream destino("copia.bmp", ios::binary);

    destino.write((char*)headerbytes, sizeof(headerbytes));
    destino.write((char*)headerinfobytes, dibheadersize);
    destino.write((char*)bodyBytes, bodysize);

    destino.close();


}


unsigned int BMPManager::getBodySize(){
        return bodysize;
}

void BMPManager::romperbody(){
        ///solamente para ver que pasa
        for(unsigned int i=0; i < bodysize; i++){
            //bodyBytes[i]+=15;
            bodyBytes[i]=bodyBytes[bodysize-i];
        }
}

void BMPManager::clonebodyBytes(uint8_t* arrayBytes){

    ///arrayBytes = new uint8_t [bodysize];

    for(unsigned int i=0; i<bodysize; i++){
        arrayBytes[i]=bodyBytes[i];
    }


}

void BMPManager::setbodyBytes(uint8_t* newArray){

    //bodyBytes = newArray;
    for(unsigned int i=0; i<bodysize; i++){
        bodyBytes[i]=newArray[i];
    }
}

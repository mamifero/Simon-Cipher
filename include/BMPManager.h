
#include <iostream>
#include "NumericFunction.h"
#include "Cipher.h"

#define u8 uint8_t
#define u32 uint32_t
#define u64 uint64_t

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class BMPManager
{
    public:
        BMPManager();
        BMPManager(string file,string output);
        uint64_t getFileSize();
        void getFileInfo();
        void saveFileCopy();
        void clonebodyBytes(uint8_t*); ///te copia el vector de bytes del cuerpo, no se si vale la pena
        uint64_t getBodySize();
        uint8_t* getBodyBytes();
        void setbodyBytes(uint8_t*);
        void romperbody();
    protected:

    private:
        char filePath[100];
        ifstream archivo;
        uint8_t headerbytes[54];///Variable experimental
        uint8_t *headerinfobytes;
        uint8_t *bodyBytes;

        string inputFile;
        string outputFile;
        uint8_t filetype[3];
        uint64_t filesize;
        uint32_t dibheadersize;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bitcount;
        uint64_t bodysize;
};

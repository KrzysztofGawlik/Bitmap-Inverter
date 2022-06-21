#include <iostream>
#include <fstream>
using namespace std;

struct FileHeader{
    char signature[2]; // File structure
    uint32_t size; // Size of file
    uint16_t reservedA; // Reserved data A
    uint16_t reservedB; // Reserved data B
    uint32_t dataOffset; // Location of the first pixel
} FH;

struct BitmapInformationHeader{
    // Size of self
    uint32_t size; 
    // Image dimension in pixels
    uint32_t width;
    uint32_t height;
    // Image settings
    uint16_t colorPlanes;
    uint16_t colorDepth;
    uint32_t compression;
    uint32_t rawSize;
    //Resolution in pixels per metre
    int32_t horizontalPpm;
    int32_t verticalPpm;
    // Other settings
    uint32_t colorTable;
    uint32_t importantColors;

} BIH;

struct Pixel{
    // Reversed order - little indian notation
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Px;

int main(void){

    // Application  

}
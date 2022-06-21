#include <iostream>
#include <fstream>
using namespace std;

struct FileHeader{ // 14 BYTES
    uint8_t signature; //2B 'BM'
    uint32_t file_size; //4B file size in bytes
    uint32_t reserved; //4B unused=0
    uint32_t file_offset_to_pixel_array; //4B offset from beginning of file to the beggining of the bitmap data
};

struct BitmapInformationHeader{ // 40 BYTES
    uint32_t dib_header_size; // size of info header
    uint32_t image_width;
    uint32_t image_height;
    uint16_t planes;
    uint16_t bits_per_pixel; // Depth
    /*
    BITS PER PIXEL possible values:
        1 = monochrome palette > NumColors = 1
        4 = 4bit palletized > NumColors = 16
        8 = 8bit palletized > NumColors = 256
        16 = 16bit RGB > NumColors = 65536
        24 = 24bit RGB > NumColors = 16M
    */
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter; // Horizontal
    uint32_t y_pixels_per_meter; // Vertical
    uint32_t colors_in_color_table;
    uint32_t important_color_count;
    // NEXT: ColorTable (4*NumColors bytes) --> bits_per_pixel (present only if bits_per_pixel < 8)
};

struct Pixel{
    // Pixel Data - got size BIH.image_size Bytes
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

int main(void){

    FILE* bmp = fopen("sources/test.bmp", "rb");
    FileHeader fh;
    BitmapInformationHeader bih;

    fread(&fh, 14, 1, bmp); // Read all from HEADER
    fread(&bih, 40, 1, bmp); // Read all from INFO_HEADER

    cout << "-------------------------------------" << endl;
    // INFO FROM FILE HEADER
    cout << "SIGNATURE: " << fh.signature << endl;
    cout << "SIZE: " << fh.file_size << endl;
    cout << "RESERVED A: " << fh.reserved << endl;
    cout << "OFFSET: " << fh.file_offset_to_pixel_array << endl;
    cout << "-------------------------------------" << endl;

    //INFO FROM INFORMATION HEADER
    cout << "BIH size: " << bih.dib_header_size << endl <<
            "Image width: " << bih.image_width << endl <<
            "Image height: " << bih.image_height << endl <<
            "Planes: " << bih.planes << endl <<
            "Depth: " << bih.bits_per_pixel << endl <<
            "Compression: " << bih.compression << endl <<
            "Image size: " << bih.image_size << endl <<
            "X pixels per meter: " << bih.x_pixels_per_meter << endl <<
            "Y pixels per meter: " << bih.y_pixels_per_meter << endl <<
            "Colors: " << bih.colors_in_color_table << endl <<
            "Important colors: " << bih.important_color_count << endl;

    cout << "-------------------------------------" << endl;
}
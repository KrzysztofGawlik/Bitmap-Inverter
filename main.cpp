#include <iostream>
#include <fstream>
using namespace std;

struct FileHeader{
    char signature[2];
    uint32_t file_size;
    uint16_t reserved_A;
    uint16_t reserved_B;
    uint32_t file_offset_to_pixel_array;
};

struct BitmapInformationHeader{
    uint32_t dib_header_size; 
    uint32_t image_width;
    uint32_t image_height;
    uint16_t planes;
    uint16_t bits_per_pixel; // Depth
    uint32_t compression;
    uint32_t imageSize;
    uint32_t x_pixels_per_meter; // Horizontal
    uint32_t x_pixels_per_meter; // Vertical
    uint32_t colors_in_color_table;
    uint32_t important_color_count;
    uint32_t red_channel_bitmask;
    uint32_t green_channel_bitmask;
    uint32_t blue_channel_bitmask;
    uint32_t alpha_channel_bitmask;
    uint32_t color_space_type;
    uint32_t color_space_endpoints;
    uint32_t gamma_for_red_channel;
    uint32_t gamma_for_green_channel;
    uint32_t gamma_for_blue_channel;
    uint32_t intent;
    uint32_t icc_profile_data;
    uint32_t icc_profile_size;
    uint32_t reserved;
};

struct Pixel{
    // Reversed order - little indian notation
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

int main(void){

    FILE* bmp = fopen("sources/test.bmp", "rb");
    FileHeader fh;
    BitmapInformationHeader bih;

    fread(&fh, 14, 1, bmp);
    fread(&bih, 40, 1, bmp);

    cout << "-------------------------------------" << endl;
    // INFO FROM FILE HEADER
    cout << "SIGNATURE: " << fh.signature << endl;
    cout << "SIZE: " << fh.file_size << endl;
    cout << "RESERVED A: " << fh.reserved_A << " & RESERVED B: " << fh.reserved_B << endl;
    cout << "OFFSET: " << fh.file_offset_to_pixel_array << endl;
    cout << "-------------------------------------" << endl;

    //INFO FROM INFORMATION HEADER
    cout << "BIH size: " << bih.dib_header_size << endl <<
            "Image width: " << bih.image_width << endl <<
            "Image height: " << bih.image_height << endl;

    cout << "-------------------------------------" << endl;
}
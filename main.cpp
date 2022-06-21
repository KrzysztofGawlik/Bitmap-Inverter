#include <iostream>
#include <fstream>
using namespace std;

struct FileHeader{ // 14 BYTES
    char signature[2]; //2B 'BM'
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

bool negateImage(const char* src, int headerSize){
    try{
        ifstream in;
        ofstream out;
        char* header[headerSize];
        Pixel px;

        in.open(src, ios::in | ios::binary);
        out.open(src, ios::in | ios::binary);

        // Copy header
        in.read((char*)(&header),headerSize);
        out.write((char*)(&header),headerSize);

        while(!in.eof()){
            in.read((char*) (&px), sizeof(px));
            px.red = 255 - px.red;
            px.green = 255 - px.green;
            px.blue = 255 - px.blue;
            out.write((char*) (&px), sizeof(px));
        }
        in.close();
        out.close();

    } catch (exception e){
        return 0;
    }
    return 1;
}

int main(void){

    const char* filePath = "sources/test.bmp";
    const char* negFilePath = "sources/test-neg.bmp";
    FILE* bmp = fopen(filePath, "rb");
    FileHeader fh;
    BitmapInformationHeader bih;

    //fread(&fh, 14, 1, bmp); // Read all from HEADER - incorrect values (why?)
    fread(&fh.signature,2,1,bmp);
    fread(&fh.file_size,4,1,bmp);
    fread(&fh.reserved,4,1,bmp);
    fread(&fh.file_offset_to_pixel_array,4,1,bmp);

    fread(&bih, 40, 1, bmp); // Read all from INFO_HEADER

    cout << "\nMETADATA FROM FILE" << endl;
    cout << "-------------------------------------" << endl;
    // INFO FROM FILE HEADER
    cout << "SIGNATURE: " << fh.signature << endl;
    cout << "SIZE: " << fh.file_size << " B" << endl;
    cout << "RESERVED A: " << fh.reserved << endl;
    cout << "OFFSET: " << fh.file_offset_to_pixel_array << " B"<< endl;
    cout << "-------------------------------------" << endl;

    //INFO FROM INFORMATION HEADER
    cout << "BIH size: " << bih.dib_header_size << " B" << endl <<
            "Image width: " << bih.image_width << " px" << endl <<
            "Image height: " << bih.image_height << " px" << endl <<
            "Planes: " << bih.planes << endl <<
            "Depth: " << bih.bits_per_pixel << endl <<
            "Compression: " << bih.compression << endl <<
            "Image size: " << bih.image_size << endl <<
            "X pixels per meter: " << bih.x_pixels_per_meter << endl <<
            "Y pixels per meter: " << bih.y_pixels_per_meter << endl <<
            "Colors: " << bih.colors_in_color_table << endl <<
            "Important colors: " << bih.important_color_count << endl;

    cout << "-------------------------------------" << endl;

    char convert;
    bool loop = true;
    cout << "Would you like to convert image to negative (y/n)? ";
    while(loop){
        cin >> convert;
        switch(convert){
            case 'y':{
                loop = false;
                continue;
            }
            case 'n':{
                return 0;
            }
            default:{
                cout << "Incorrect option, try again... (y/n) ";
            }
        }
    }
    cout << "> Converting image to negative..." << endl;
    bool succeed = negateImage(filePath, fh.file_offset_to_pixel_array);
    if(succeed){
        cout << "> Conversion completed!" << endl;
    } else {
        cout << "> Conversion failed!" << endl;
    }
    cout << "-------------------------------------" << endl;
    cout << "Press enter to close...";
    cin.sync(); cin.get();
}
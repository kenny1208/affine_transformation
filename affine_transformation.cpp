#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    FILE* fp_r;
    bool err_r = fopen_s(&fp_r, "AiPicG.bmp", "rb");
    if (err_r != 0) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    
    vector<unsigned char> header;
    header.resize(1078);
    for (int i = 0; i < 1078; i++) {
        header[i] = getc(fp_r);
    }

    int img_h = 1024;
    int img_w = 1024;

    
    vector<vector<unsigned char>> imgArr;
    imgArr.resize(img_h, vector<unsigned char>(img_w));
    for (int i = 0; i < img_h; i++) {
        for (int j = 0; j < img_w; j++) {
            imgArr[j][img_h - i - 1] = getc(fp_r);
        }
    }

    fclose(fp_r);

    
    vector<vector<unsigned char>> outArr;
    outArr.resize(img_w, vector<unsigned char>(img_h));

    
    for (int i = 0; i < img_h; i++) {
        for (int j = 0; j < img_w; j++) {
            int new_i = cos(10.0f * 3.1415926 / 180.0f) * i - sin(10.0f * 3.1415926 / 180.0f) * j + 0.5;
            int new_j = sin(10.0f * 3.1415926 / 180.0f) * i + cos(10.0f * 3.1415926 / 180.0f) * j + 0.5;

            new_i = (new_i > img_h - 1) ? img_h - 1 : (new_i < 0) ? 0 : new_i;
            new_j = (new_j > img_w - 1) ? img_w - 1 : (new_j < 0) ? 0 : new_j;

            outArr[new_j][new_i] = imgArr[j][i];
        }
    }

    
    FILE* fp_w;
    bool err_w = fopen_s(&fp_w, "xxx.bmp", "wb");

    
    for (int i = 0; i < 1078; i++) {
        putc(header[i], fp_w);
    }

    
    for (int i = img_h - 1; i >= 0; i--) {
        for (int j = 0; j < img_w; j++) {
            putc(outArr[j][i], fp_w);
        }
    }

    fclose(fp_w);
    cout << "Rotation completed and saved to xxx.bmp" << endl;

    return 0;
}
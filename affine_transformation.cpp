#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    FILE* fp_r;
    bool err_r = fopen_s(&fp_r, "AiPicG.bmp", "rb");


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
    outArr.resize(img_w, vector<unsigned char>(img_h, 0));  

    float angle = -10.0f * 3.1415926f / 180.0f;

    for (int i = 0; i < img_h; i++) {
        for (int j = 0; j < img_w; j++) {

            float src_i = cos(angle) * i - sin(angle) * j;
            float src_j = sin(angle) * i + cos(angle) * j;

            if (src_i >= 0 && src_i < img_h - 1 && src_j >= 0 && src_j < img_w - 1) {
                
                int i_floor = floor(src_i);
                int j_floor = floor(src_j);
                float i_frac = src_i - i_floor;
                float j_frac = src_j - j_floor;

                
                unsigned char p00 = imgArr[j_floor][i_floor];
                unsigned char p01 = imgArr[j_floor][i_floor + 1];
                unsigned char p10 = imgArr[j_floor + 1][i_floor];
                unsigned char p11 = imgArr[j_floor + 1][i_floor + 1];

                
                float value = (1 - i_frac) * (1 - j_frac) * p00 +
                    i_frac * (1 - j_frac) * p01 +
                    (1 - i_frac) * j_frac * p10 +
                    i_frac * j_frac * p11;

                outArr[j][i] = static_cast<unsigned char>(value + 0.5f);  
            }
            
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
    cout << "Rotation with bilinear interpolation completed and saved to xxx.bmp" << endl;

    return 0;
}
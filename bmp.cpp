#include "bmp.h"

void BMP::writeUC(unsigned char uc, int repeat){
    for(int i=0; i<repeat; i++){
        ofs.write((const char *)&uc, sizeof(uc));
    }
}

void BMP::writeInt(int src, int bytes){
    for(int i=0;i<bytes;i++){
        unsigned char uc = 0;
        for(int j=0;j<8;j++){
            if(src&(1L << (j+8*i))){
                uc |= (1L << j);
            }
        }
		writeUC(uc);
    }
}

void BMP::writeString(const std::string &src){
    for(auto uc = src.begin(); uc != src.end(); uc++){
        writeUC(*uc);
    }
}

BMP::BMP(
    unsigned int width,
    unsigned int height,
	unsigned char bg
){
    reset(width, height, bg);
}

void BMP::reset(
    unsigned int width,
    unsigned int height,
	unsigned char bg
){
    Height = height;
    Width = width;
    data.resize(Width*Height*3, bg);
}

void BMP::set(
        unsigned int x,
        unsigned int y,
        unsigned char r,
        unsigned char g,
        unsigned char b
){
    unsigned int idx = (x+Width*y)*3;
    data[idx]=r;
    data[idx+1]=g;
    data[idx+2]=b;
}

void BMP::get(
    unsigned int x,
    unsigned int y,
    unsigned char &r,
    unsigned char &g,
    unsigned char &b
){
    unsigned int idx = (x+Width*y)*3;
    r = data[idx];
    g = data[idx+1];
    b = data[idx+2];
}

void BMP::drawTriangle(
        int x1, int y1,
        int x2, int y2,
        int x3, int y3,
        int r,
        int g,
        int b
){
    for(int y=0, idx=0;y<Height;y++){
        for(int x=0;x<Width;x++,idx+=3){
			double x12 = x2 - x1;
			double y12 = y2 - y1;
			double x2p = x - x2;
			double y2p = y - y2;
			double x23 = x3 - x2;
			double y23 = y3 - y2;
			double x3p = x - x3;
			double y3p = y - y3;
			double x31 = x1 - x3;
			double y31 = y1 - y3;
			double x1p = x - x1;
			double y1p = y - y1;
			double c1 = x12*y2p - y12*x2p;
			double c2 = x23*y3p - y23*x3p;
			double c3 = x31*y1p - y31*x1p;
			if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)){
				data[idx] = r;
				data[idx + 1] = g;
				data[idx + 2] = b;
			}
        }
    }
}

void BMP::write(const std::string &filename){
    ofs.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	
	//File Header
	writeString("BM");//bfType
	writeInt(54 + Width*Height * 3, 4);//file size
	writeUC(0, 2);//Reserved1
	writeUC(0, 2);//Reserved2
	writeInt(54, 4);//offset

	//Bitmap Information Header
	writeInt(40, 4);//head size
	writeInt(Width, 4);//width
	writeInt(Height, 4);//height
	writeInt(1, 2);//planes
	writeInt(24, 2);//color bit
	writeUC(0, 4);//compression
	writeUC(0, 4);//size image
	writeUC(0, 4);//xppm
	writeUC(0, 4);//yppm
	writeUC(0, 4);//color used
	writeUC(0, 4);//color important

	//image
	for (int y = Height - 1; y >= 0; y--){
		for (int x = 0; x < Width; x++){
			unsigned int idx = (x + Width*y) * 3;
			writeUC(data[idx + 2]);
			writeUC(data[idx + 1]);
			writeUC(data[idx]);
		}
	}
}
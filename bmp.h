#pragma once
#include <vector>
#include <string>
#include <fstream>

class BMP{
    private:
    std::ofstream ofs;
    unsigned int Width;
    unsigned int Height;
    std::vector<unsigned char>data;
    void writeUC(unsigned char uc, int repeat = 1);
    void writeInt(int src, int bytes);
    void writeString(const std::string &src);

    public:
    BMP(
        unsigned int width = 640,
        unsigned int height = 480,
		unsigned char bg = 255
        );
    void reset(
        unsigned int width = 640,
        unsigned int height = 480,
		unsigned char bg = 255
    );
    void set(
        unsigned int x,
        unsigned int y,
        unsigned char r,
        unsigned char g,
        unsigned char b
    );
    void get(
        unsigned int x,
        unsigned int y,
        unsigned char &r,
        unsigned char &g,
        unsigned char &b
    );
    void drawTriangle(
        int x1, int y1,
        int x2, int y2,
        int x3, int y3,
        int r,
        int g,
        int b
    );
    void write(const std::string &filename = "out.bmp");
};
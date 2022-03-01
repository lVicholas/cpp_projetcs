#ifndef IMAGEPROCESSING_FILEDATA_H
#define IMAGEPROCESSING_FILEDATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cmath>

#define HEADEREND 18

struct Header {

public:
    char idlength;
    char map;
    char type;
    short mOrigin;
    short mLength;
    char mDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bpp;
    char descriptor;

    void headerData(const std::string& _file) {

        std::ifstream file(_file, std::ios_base::binary);

        char character;
        short shorty;

        file.read(&character, sizeof(character));
        idlength = character;

        file.read(&character, sizeof(character));
        map = character;

        file.read(&character, sizeof(character));
        type = character;

        file.read((char*)&shorty, sizeof(shorty));
        mOrigin = shorty;

        file.read((char*)&shorty, sizeof(shorty));
        mLength = shorty;

        file.read(&character, sizeof(character));
        mDepth = character;

        file.read((char*)&shorty, sizeof(shorty));
        xOrigin = shorty;

        file.read((char*)&shorty, sizeof(shorty));
        yOrigin = shorty;

        file.read((char*)&shorty, sizeof(shorty));
        width = shorty;

        file.read((char*)&shorty, sizeof(shorty));
        height = shorty;

        file.read(&character, sizeof(character));
        bpp = character;

        file.read(&character, sizeof(character));
        descriptor = character;

        file.close();

    }


    void Set(const Header& h) {

        idlength = h.idlength; map = h.map; type = h.type; mOrigin = h.mOrigin;
        mLength = h.mLength; mDepth = h.mDepth; xOrigin = h.xOrigin; yOrigin = h.yOrigin;
        width = h.width; height = h.height; bpp = h.bpp; descriptor = h.descriptor;
    }
    Header() {

        idlength = map = type = mDepth = bpp = descriptor = 0;
        mOrigin = mLength = xOrigin = yOrigin = width = height = 0;

    }
    explicit Header(std::string& file) { headerData(file); }
    Header(const Header& h) { Set(h); }
    ~Header() = default;
    bool operator==(const Header& header) const {

        return (idlength == header.idlength && map == header.map && type == header.type &&
            mOrigin == header.mOrigin && mLength == header.mLength && mDepth == header.mDepth &&
            xOrigin == header.xOrigin && yOrigin == header.yOrigin && width == header.width &&
            height == header.height && bpp == header.bpp && descriptor == header.descriptor);

    }

};
struct Pixel {

public:

    unsigned char B;
    unsigned char G;
    unsigned char R;

    void Set(const Pixel& p) { B = p.B; G = p.G; R = p.R; }

    Pixel() { G = B = R = 0; }
    Pixel(const Pixel& p) { Set(p); }
    Pixel(unsigned char b, unsigned char g, unsigned char r) { B = b; G = g; R = r; }
    Pixel& operator=(const Pixel& p) { Set(p); return *this; }
    ~Pixel() = default;
    bool operator==(const Pixel& pixel) const { return (B == pixel.B && G == pixel.G && R == pixel.R); }

};
struct Norm {

    float B;
    float G;
    float R;

    explicit Norm(Pixel pixel) { B = (float)pixel.B / 255; G = float(pixel.G) / 255; R = float(pixel.R) / 255; }
    Norm() { B = G = R = 0; }
    ~Norm() = default;

};
class FileData {

public:

    Header header;
    std::string fileName;
    short width, height;
    std::vector<Pixel> pixels;

    FileData() { header = Header(); fileName = ""; width = height = 0; }

    ~FileData() = default;

    explicit FileData(const std::string& _file) {

        fileName = _file;
        header = Header(fileName);
        width = header.width;
        height = header.height;
        load();

    }

    FileData(const FileData& org) {

        fileName = org.fileName;
        header = org.header;
        width = org.width;
        height = org.height;

        copy(org.pixels.begin(), org.pixels.end(), std::back_inserter(pixels));

    }

    void load() {

        std::ifstream file;
        file.open(fileName, std::ios_base::binary);

        file.seekg(HEADEREND);

        while (true) {

            unsigned char ch, ar, ac;

            file.read((char*)&ch, sizeof(ch));
            file.read((char*)&ar, sizeof(ar));
            file.read((char*)&ac, sizeof(ac));

            Pixel pixel = Pixel(ch, ar, ac);

            pixels.push_back(pixel);

            if (!file)
                break;

        }

        file.close();

    }

    bool operator==(const FileData& copy) const {

        if (!(header == copy.header)) {

            std::cout << "Header does not match\n";
            return false;

        }

        std::vector<Pixel> p = copy.pixels;

        for (unsigned int x = 0; x < pixels.size(); x++) {

            if (!(pixels[x] == p[x])) {

                std::cout << "Pixel " << x << " does not match\n";
                return false;

            }

        }

        return true;

    }
    std::vector<Norm> normalize() const {

        std::vector<Norm> norm;

        for (const Pixel& pix : pixels) {

            Norm norm1 = Norm(pix);
            norm.push_back(norm1);

        }

        return norm;

    }

};
#endif
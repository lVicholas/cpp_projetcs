#include <iostream>
#include <vector>
#include <algorithm>
#include "FileData.h"

/*

    The main function takes files from input and writes to output

    Each task performs some transformation onto some file(s) from input,
    writes the transformed version to output, compares the file written to output
    and its corresponding file in examples, and prints to the console whether the
    example file and output file are identical

*/

float min(float a, float b) { float c = (a < b) ? a : b; return c; }
float max(float a, float b) { float c = (a > b) ? a : b; return c; }
void multiply(const FileData&, const std::vector<int>&, FileData&);
void multiply(const FileData&, const FileData&, FileData&);
void subtract(const FileData&, const FileData&, FileData&);
void screen(const FileData&, const FileData&, FileData&);
void add(const FileData&, const std::vector<int>&, FileData&);
void overlay(const FileData&, const FileData&, FileData&);
void copyChannel(const FileData&, FileData&, int);
void flip(const FileData&, FileData&);
void transcribe(const FileData&, std::ofstream&);
void Task1();
void Task2();
void Task3();
void Task4();
void Task5();
void Task6();
void Task7();
void Task8();
void Task9();
void Task10();


int main() {

    Task1();
    Task2();
    Task3();
    Task4();
    Task5();
    Task6();
    Task7();
    Task8();
    Task9();
    Task10();

    return 0;

}

void multiply(FileData& file, std::vector<int> factors, FileData& out) {

    out.pixels.clear();

    out.header = file.header;
    out.height = file.height;
    out.width = file.width;

    const std::vector<Norm> norm = file.normalize();

    for (const Norm& x : norm) {

        float m, n, o;

        m = x.B * factors[0];
        n = x.G * factors[1];
        o = x.R * factors[2];

        m = min(max(m, 0), 1);
        n = min(max(n, 0), 1);
        o = min(max(o, 0), 1);

        Pixel pixel(m * 255 + .5f, n * 255 + .5f, o * 255 + .5f);
        out.pixels.push_back(pixel);

    }

}
void multiply(FileData& fileA, FileData& fileB, FileData& out) {

    out.pixels.clear();

    out.header = fileA.header;
    out.height = fileA.height;
    out.width = fileA.width;

    const std::vector<Norm> A = fileA.normalize();
    const std::vector<Norm> B = fileB.normalize();

    for (unsigned int x = 0; x < A.size(); x++) {

        float b, g, r;

        b = A[x].B * B[x].B;
        g = A[x].G * B[x].G;
        r = A[x].R * B[x].R;

        Pixel pixel(b * 255 + .5f, g * 255 + .5f, r * 255 + .5f);
        out.pixels.push_back(pixel);

    }

}
void subtract(FileData& top, FileData& bot, FileData& out) {

    out.pixels.clear();

    out.header = top.header;
    out.height = top.height;
    out.width = top.width;

    const std::vector<Pixel> T = top.pixels;
    const std::vector<Pixel> B = bot.pixels;

    for (unsigned int x = 0; x < T.size(); x++) {

        unsigned char b, g, r;
        int m, n, o;

        m = B[x].B - T[x].B;
        n = B[x].G - T[x].G;
        o = B[x].R - T[x].R;

        b = (unsigned char)min(max(m, 0), 255);
        g = (unsigned char)min(max(n, 0), 255);
        r = (unsigned char)min(max(o, 0), 255);

        Pixel pixel(b, g, r);
        out.pixels.push_back(pixel);

    }

}
void screen(FileData& im1, FileData& im2, FileData& out) {

    out.pixels.clear();

    const std::vector<Norm> a = im1.normalize();
    const std::vector<Norm> d = im2.normalize();

    out.header = im1.header;
    out.height = im1.height;
    out.width = im1.width;

    for (unsigned int x = 0; x < a.size(); x++) {

        unsigned char b, g, r;
        float m, n, o;

        m = (1 - (1 - a[x].B) * (1 - d[x].B));
        n = (1 - (1 - a[x].G) * (1 - d[x].G));
        o = (1 - (1 - a[x].R) * (1 - d[x].R));

        m = min(max(m, 0), 1);
        n = min(max(n, 0), 1);
        o = min(max(o, 0), 1);

        Pixel pixel = Pixel(m * 255 + .5f, n * 255 + .5f, o * 255 + .5f);
        out.pixels.push_back(pixel);

    }

}
void add(FileData& im, std::vector<int>& factors, FileData& out) {

    out.pixels.clear();

    out.header = im.header;
    out.height = im.height;
    out.width = im.width;

    for (const Pixel& p : im.pixels) {

        unsigned char b, g, r;
        int m, n, o;

        m = p.B + factors[0];
        n = p.G + factors[1];
        o = p.R + factors[2];

        b = (unsigned char)min(max(m, 0), 255);
        g = (unsigned char)min(max(n, 0), 255);
        r = (unsigned char)min(max(o, 0), 255);

        Pixel pix = Pixel(b, g, r);
        out.pixels.push_back(pix);

    }

}
void overlay(FileData& top, FileData& bot, FileData& out) {

    out.pixels.clear();

    std::vector<Norm> pixA = top.normalize();
    std::vector<Norm> pixB = bot.normalize();

    out.header = top.header;
    out.height = top.height;
    out.width = top.width;

    for (unsigned int x = 0; x < pixA.size(); x++) {

        float b, g, r;

        pixB[x].B <= 0.5 ? b = (2 * pixA[x].B * pixB[x].B) :
            b = (1 - (2 * (1 - pixA[x].B) * (1 - pixB[x].B)));

        pixB[x].G <= 0.5 ? g = (2 * pixA[x].G * pixB[x].G) :
            g = (1 - (2 * (1 - pixA[x].G) * (1 - pixB[x].G)));

        pixB[x].R <= 0.5 ? r = (2 * pixA[x].R * pixB[x].R) :
            r = (1 - (2 * (1 - pixA[x].R) * (1 - pixB[x].R)));

        Pixel p = Pixel(b * 255 + .5f, g * 255 + .5f, r * 255 + .5f);
        out.pixels.push_back(p);

    }

}
void copyChannel(FileData& ch, FileData& out, int t) {

    out.header = ch.header;
    out.height = ch.height;
    out.width = ch.width;

    out.pixels.clear();

    for (const Pixel& p : ch.pixels) {

        unsigned char b, g, r;
        b = g = r = 0;

        if (t < 0)
            b = g = r = p.B;

        else if (t == 0)
            b = g = r = p.G;

        else if (t > 0)
            b = g = r = p.R;

        Pixel pix = Pixel(b, g, r);
        out.pixels.push_back(pix);

    }

}
void flip(const FileData& data, FileData& out) {

    out.pixels.clear();

    out.header = data.header;
    out.height = data.height;
    out.width = data.width;

    const std::vector<Pixel> temp = data.pixels;
    std::vector<Pixel> o;

    for (unsigned int x = temp.size() - 1; x >= data.width; x = x - data.width) {

        auto f = temp.begin() + x - data.width;
        auto l = temp.begin() + x;

        std::vector<Pixel> t(f, l);
        std::vector<Pixel> rt(t.rbegin(), t.rend());

        copy(rt.begin(), rt.end(), std::back_inserter(o));

    }

    copy(o.begin(), o.end(), std::back_inserter(out.pixels));

}
void transcribe(const FileData& data, std::ofstream& output) {

    output.write(&data.header.idlength, sizeof(char));
    output.write(&data.header.map, sizeof(char));
    output.write(&data.header.type, sizeof(char));
    output.write((char*)&data.header.mOrigin, sizeof(short));
    output.write((char*)&data.header.mLength, sizeof(short));
    output.write(&data.header.mDepth, sizeof(char));
    output.write((char*)&data.header.xOrigin, sizeof(short));
    output.write((char*)&data.header.yOrigin, sizeof(short));
    output.write((char*)&data.header.width, sizeof(short));
    output.write((char*)&data.header.height, sizeof(short));
    output.write(&data.header.bpp, sizeof(char));
    output.write(&data.header.descriptor, sizeof(char));

    for (const Pixel& pix : data.pixels) {

        unsigned char col[] = { pix.B, pix.G, pix.R };

        output.write((char*)&col[0], sizeof(col[0]));
        output.write((char*)&col[1], sizeof(col[1]));
        output.write((char*)&col[2], sizeof(col[2]));

    }

    output.close();

}

void Task1() {

    FileData top("input/layer1.tga");
    FileData bot("input/pattern1.tga");

    FileData out;

    multiply(top, bot, out);
    std::ofstream file("output/part1.tga", std::ios::binary);

    transcribe(out, file);

    FileData output("examples/EXAMPLE_part1.tga");

    if (out == output)
        std::cout << "Task 1 success\n";
    else std::cout << "Task 1 failed\n";

}
void Task2() {

    FileData top("input/layer2.tga");
    FileData bot("input/car.tga");

    FileData out;
    std::ofstream file("output/part2.tga", std::ios::binary);

    subtract(top, bot, out);

    transcribe(out, file);

    FileData output("examples/EXAMPLE_part2.tga");

    if (out == output)
        std::cout << "Task 2 success\n";
    else std::cout << "Task 2 failed\n";

}
void Task3() {

    FileData layer1("input/layer1.tga");
    FileData pattern2("input/pattern2.tga");
    FileData text("input/text.tga");

    FileData temp;
    FileData out;

    multiply(layer1, pattern2, temp);
    screen(text, temp, out);

    std::ofstream file("output/part3.tga", std::ios::binary);

    transcribe(out, file);

    FileData output("examples/EXAMPLE_part3.tga");

    if (out == output)
        std::cout << "Task 3 success\n";
    else std::cout << "Task 3 failed\n";
}
void Task4() {

    FileData layer2("input/layer2.tga");
    FileData circles("input/circles.tga");
    FileData pattern2("input/pattern2.tga");

    FileData temp;
    FileData out;

    std::ofstream file("output/part4.tga", std::ios::binary);

    multiply(layer2, circles, temp);
    subtract(pattern2, temp, out);

    transcribe(out, file);

    FileData output("examples/EXAMPLE_part4.tga");

    if (out == output)
        std::cout << "Task 4 success\n";
    else std::cout << "Task 4 failed\n";
}
void Task5() {

    FileData layer1("input/layer1.tga");
    FileData pattern1("input/pattern1.tga");

    FileData out;

    overlay(layer1, pattern1, out);

    std::ofstream file("output/part5.tga", std::ios::binary);

    transcribe(out, file);

    FileData output("examples/EXAMPLE_part5.tga");

    if (out == output)
        std::cout << "Task 5 success\n";
    else std::cout << "Task 5 failed\n";

}
void Task6() {

    FileData car("input/car.tga");
    std::vector<int> fac = { 0, 200, 0 };
    FileData out;

    add(car, fac, out);

    std::ofstream file("output/part6.tga", std::ios::binary);
    transcribe(out, file);

    FileData output("examples/EXAMPLE_part6.tga");

    if (out == output)
        std::cout << "Task 6 success\n";
    else std::cout << "Task 6 failed\n";

}
void Task7() {

    FileData car("input/car.tga");
    std::vector<int> fac = { 0, 1, 4 };

    FileData out;

    multiply(car, fac, out);

    std::ofstream file("output/part7.tga", std::ios::binary);
    transcribe(out, file);

    FileData output("examples/EXAMPLE_part7.tga");

    if (out == output)
        std::cout << "Task 7 success\n";
    else std::cout << "Task 7 failed\n";

}
void Task8() {

    FileData car("input/car.tga");
    FileData red;
    FileData blue;
    FileData green;

    copyChannel(car, blue, -1);
    copyChannel(car, green, 0);
    copyChannel(car, red, 100);

    std::ofstream b("output/part8_b.tga", std::ios::binary);
    std::ofstream g("output/part8_g.tga", std::ios::binary);
    std::ofstream r("output/part8_r.tga", std::ios::binary);

    transcribe(blue, b);
    transcribe(green, g);
    transcribe(red, r);

    FileData outB("examples/EXAMPLE_part8_b.tga");
    FileData outR("examples/EXAMPLE_part8_r.tga");
    FileData outG("examples/EXAMPLE_part8_g.tga");

    std::cout << "Task 8:\n";
    blue == outB ? std::cout << "  Blue success\n" : std::cout << "  Blue failed\n";
    red == outR ? std::cout << "  Red success\n" : std::cout << "  Red failed\n";
    green == outG ? std::cout << "  Green success\n" : std::cout << "  Green failed\n";

}
void Task9() {

    FileData blue("input/layer_blue.tga");
    FileData green("input/layer_green.tga");
    FileData red("input/layer_red.tga");

    FileData out;
    out.header = blue.header;

    std::vector<Pixel> combo;

    for (unsigned int x = 0; x < blue.pixels.size(); x++) {

        unsigned char b, g, r;

        b = blue.pixels[x].B;
        g = green.pixels[x].G;
        r = red.pixels[x].R;

        Pixel p = Pixel(b, g, r);
        combo.push_back(p);

    }

    copy(combo.begin(), combo.end(), std::back_inserter(out.pixels));

    std::ofstream file("output/part9.tga", std::ios::binary);
    transcribe(out, file);

    FileData output("examples/EXAMPLE_part9.tga");

    if (out == output)
        std::cout << "Task 9 success\n";
    else std::cout << "Task 9 failed\n";

}
void Task10() {

    FileData text("input/text2.tga");
    FileData out;

    flip(text, out);

    std::ofstream file("output/part10.tga", std::ios::binary);
    transcribe(out, file);

    FileData output("examples/EXAMPLE_part10.tga");

    if (out == output)
        std::cout << "Task 10 success\n";
    else std::cout << "Task 10 failed\n";

}
#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>

using namespace std;

struct Pixel
{
    int* rgb = new int[3];
    int pos;
    float brig;
};

int getRowCount(string filename)
{
    fstream newfile;
    string tp;
    newfile.open(filename.c_str(),ios::in);
    int rowCount = 0;
    while(getline(newfile, tp))
    {
        rowCount++;
    }

    return rowCount;
}

Pixel strNumToInt(string num, int indexOrig)
{
    Pixel result;
    result.pos = indexOrig;
    int sum = 0;
    int m = 1;
    int index = 2;
    for(int i = num.length() - 1; i >= 0; i--)
    {
        if(int(num[i]) != 32)
        {
            sum += (int(num[i]) - 48) * m;
            m *= 10;
        }

        if(int(num[i]) == 32 || i == 0)
        {
            result.rgb[index] = sum;
            sum = 0;
            m = 1;
            index--;
        }
    }

    result.brig = (result.rgb[0] * 0.3) + (result.rgb[1] * 0.59) + (result.rgb[2] * 0.11);;

    return result;
}

Pixel* getPixelsFromImage(string filename, int rowCount)
{

    fstream newfile;
    string tp;
    newfile.open(filename.c_str(),ios::in);
    Pixel* pixels = new Pixel[rowCount];
    int index = 0;

    while(getline(newfile, tp))
    {
        pixels[index] = strNumToInt(tp, index);
        index++;
    }
    newfile.close();
    return pixels;

}


void getNewOrder(Pixel* pixels, Pixel* pixels2, int rowCount)
{
    for(int i = 0; i < rowCount; ++i)
    {
        float record = -1;
        float record2 = -1;
        int selectedPixel = i;
        int selectedPixel2 = i;
        for(int j = i; j < rowCount; ++j)
        {
            float b = pixels[j].brig;
            float b2 = pixels2[j].brig;
            if(b > record)
            {
                record = b;
                selectedPixel = j;
            }
            if(b2 > record2)
            {
                record2 = b2;
                selectedPixel2 = j;
            }

        }
        Pixel tmp = pixels[i];
        pixels[i] = pixels[selectedPixel];
        pixels[selectedPixel] = tmp;

        Pixel tmp2 = pixels2[i];
        pixels2[i] = pixels2[selectedPixel2];
        pixels2[selectedPixel2] = tmp2;

    }
}


void paintArray(Pixel* p1, Pixel* p2, int rowCount)
{
    for(int i = 0; i < rowCount; ++i)
    {
        p2[i].rgb[0] = p1[i].rgb[0];
        p2[i].rgb[1] = p1[i].rgb[1];
        p2[i].rgb[2] = p1[i].rgb[2];
    }
}


void sortImageBack(Pixel* p, int rowCount)
{
    for(int i = 0; i < rowCount; i++)
    {
        for(int j = i; j < rowCount; j++)
        {
            if(p[j].pos == i)
            {
                Pixel tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
                break;
            }
        }
    }
}


int main()
{

    string FILENAME = "..\\pixels\\img1.txt";
    string FILENAME_2 = "..\\imageBot\\pixels\\img2.txt";
    string FILENAME_RES = "..\\imageBot\\pixels\\img_res.txt";
    fstream newfile;
    fstream resfile;
    int rowCount = getRowCount(FILENAME);


    Pixel* pixels1 = getPixelsFromImage(FILENAME, rowCount);
    Pixel* pixels2 = getPixelsFromImage(FILENAME_2, rowCount);
    getNewOrder(pixels1, pixels2, rowCount);

    paintArray(pixels1, pixels2, rowCount);
    sortImageBack(pixels2, rowCount);

    resfile.open(FILENAME_RES.c_str(),ios::out);
    if(resfile.is_open())
    {
        for(int i = 0; i < rowCount; ++i)
        {
            Pixel p = pixels2[i];
            resfile << p.rgb[0] << " " << p.rgb[1] << " " << p.rgb[2] << "\n";
        }
        resfile.close();
    }

    return 0;
}

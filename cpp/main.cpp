#include <iostream>
#include <fstream>
#include <math.h>

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

void quickSortBrig(Pixel *pixels, int low, int high)
{
    int i = low;
    int j = high;
    float pivot = pixels[(i + j) / 2].brig;
    Pixel temp;

    while (i <= j)
    {
        while (pixels[i].brig < pivot)
            i++;
        while (pixels[j].brig > pivot)
            j--;
        if (i <= j)
        {
            Pixel tmp = pixels[i];
            pixels[i] = pixels[j];
            pixels[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSortBrig(pixels, low, j);
    if (i < high)
        quickSortBrig(pixels, i, high);
}


void quickSortPos(Pixel *pixels, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = pixels[(i + j) / 2].pos;
    Pixel temp;

    while (i <= j)
    {
        while (pixels[i].pos < pivot)
            i++;
        while (pixels[j].pos > pivot)
            j--;
        if (i <= j)
        {
            Pixel tmp = pixels[i];
            pixels[i] = pixels[j];
            pixels[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSortPos(pixels, low, j);
    if (i < high)
        quickSortPos(pixels, i, high);
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

int main()
{

    string FILENAME = "./pixels/img1.txt";
    string FILENAME_2 = "./pixels/img2.txt";
    string FILENAME_RES = "./pixels/img_res.txt";
    /*

    string FILENAME = "./pixels/img1.txt";
    string FILENAME_2 = "./pixels/img2.txt";
    string FILENAME_RES = "./pixels/img_res.txt";


    string FILENAME = "F:\\python\\imageBot\\pixels\\img1.txt";
    string FILENAME_2 = "F:\\python\\imageBot\\pixels\\img2.txt";
    string FILENAME_RES = "F:\\python\\imageBot\\pixels\\img_res.txt";

    */

    fstream newfile;
    fstream resfile;

    cout << "get row count" << endl;

    int rowCount = getRowCount(FILENAME);

    cout << "get pixels" << endl;

    Pixel* pixels1 = getPixelsFromImage(FILENAME, rowCount);

    cout << "get pixels" << endl;

    Pixel* pixels2 = getPixelsFromImage(FILENAME_2, rowCount);

    cout << "sort" << endl;

    quickSortBrig(pixels1, 0, rowCount-1);
    quickSortBrig(pixels2, 0, rowCount-1);

    cout << "paint" << endl;

    paintArray(pixels1, pixels2, rowCount);

    cout << "get result" << endl;

    quickSortPos(pixels2, 0, rowCount -1);

    resfile.open(FILENAME_RES.c_str(),ios::out);
    if(resfile.is_open())
    {

        for(int j = 0; j < rowCount; j++)
        {

            resfile << pixels2[j].rgb[0] << " " << pixels2[j].rgb[1] << " " << pixels2[j].rgb[2] << "\n";

        }

        cout << "done" << endl;
        resfile.close();
    }
    else
    {
        cout << "no res file" << endl;
    }


    return 0;
}

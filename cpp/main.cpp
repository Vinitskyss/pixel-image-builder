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

Pixel* getPixelsFromImage(int rowCount)
{

    Pixel* pixels = new Pixel[rowCount];


    for(int i = 0; i < rowCount; i++)
    {
        Pixel pixel;
        for(int j = 0; j < 3; j++)
        {
            cin >> pixel.rgb[j];
        }
        pixel.pos = i;
        pixel.brig = (pixel.rgb[0] * 0.3) + (pixel.rgb[1] * 0.59) + (pixel.rgb[2] * 0.11);
        pixels[i] = pixel;
    }
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

    fstream newfile;
    fstream resfile;


    int rowCount, width;

    cin >> rowCount;
    cin >> width;

    Pixel* pixels1 = getPixelsFromImage(rowCount);


    Pixel* pixels2 = getPixelsFromImage(rowCount);


    quickSortBrig(pixels1, 0, rowCount-1);
    quickSortBrig(pixels2, 0, rowCount-1);


    paintArray(pixels1, pixels2, rowCount);


    quickSortPos(pixels2, 0, rowCount -1);

    cout << rowCount << endl;
    cout << width << endl;
    for(int i = 0; i < rowCount; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << pixels2[i].rgb[j] << endl;
        }
    }

return 0;
}

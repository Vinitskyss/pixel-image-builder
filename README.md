# pixel-image-builder
This program will build one image from other image's pixels

Usage:
1. pip3 install -r requirements.txt
2. Place img1.png and img2.png in images folder
    * img1.png is used as a source of pixels
    * img2.png is painted with img1.png pixels

3. run sh run.sh
4. Result will be displayed in:
    * images/result.png (last image)
    * images/res (results history)

Max resolution of result image can be adjusted by editing
const.py file
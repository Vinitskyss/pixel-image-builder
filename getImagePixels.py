import os
from PIL import Image
import numpy as np
from numpy import asarray
import const

def printPixels(data):
    for l1 in data:
        for p in l1:
            for j in range(0, 3):
                print(p[j])

img1 = Image.open('images/img1.png')
img2 = Image.open('images/img2.png')


w = img2.size[0]
h = img2.size[1]

if(w > h):
    k2 = w / h
    if(w > const.SIZE):
        w = const.SIZE
        h = const.SIZE / k2
else:
    k2 = h / w
    if(h > const.SIZE):
        h = const.SIZE
        w = const.SIZE / k2 


img1 = Image.open('images/img1.png').resize((int(w), int(h)))
img2 = Image.open('images/img2.png').resize((int(w), int(h)))

print(int(w * h))
print(int(w))
data1 = np.array(img1)
data2 = np.array(img2)
printPixels(data1)
printPixels(data2)

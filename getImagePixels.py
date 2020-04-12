import os
from PIL import Image
import numpy as np
from numpy import asarray
import const

def saveImaeToTxt(name, data):
    f = open("pixels/" + name + ".txt", "w")
    for l1 in data:
        for p in l1:
            f.write(str(p[0]) + " " + str(p[1]) + " " + str(p[2]) + "\n") 

    f.close()

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
directory = "./pixels"
if not os.path.exists(directory):
    os.makedirs(directory)
cfg = open("pixels/cfg.txt", "w")
cfg.write(str(int(w)))

print(img1.size)
data1 = np.array(img1)
data2 = np.array(img2)


saveImaeToTxt("img1", data1)
saveImaeToTxt("img2", data2)

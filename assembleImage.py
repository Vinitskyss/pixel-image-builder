import os
from PIL import Image
import numpy as np
from numpy import asarray
import const
from datetime import datetime

total = int(input())
width = int(input())

directory = "./images/res"
if not os.path.exists(directory):
    os.makedirs(directory)

pixels = []
for i in range(0, total):
    sub = []
    for j in range(0, 3):
        sub.append(int(input()))
    pixels.append(sub)
   

matrix = np.array([pixels[i:i + width] for i in range(0, len(pixels), width)])
image2 = Image.fromarray(matrix.astype('uint8'), 'RGB')

image2.save("images/res/"+ str(datetime.now())  +".png")
image2.save("images/result.png")

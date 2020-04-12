FILE=cpp/a.out
g++ ./cpp/main.cpp
python3 getImagePixels.py | ./a.out | python3 assembleImage.py
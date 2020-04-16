pip3 install -r requirements.txt > /dev/null
FILE=cpp/a.out
g++ ./cpp/main.cpp
python3 getImagePixels.py | ./a.out | python3 assembleImage.py

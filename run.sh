#!/bin/bash
FILE=cpp/a.out
PILLOW=$(pip3 list --format columns | grep Pillow)
NUMPY=$(pip3 list --format columns | grep numpy)
if [[ ! "$PILLOW" ]] || [[ ! "$NUMPY" ]] ;
then
    pip3 install -r requirements.txt > /dev/null
fi
g++ ./cpp/main.cpp
python3 getImagePixels.py | ./a.out | python3 assembleImage.py

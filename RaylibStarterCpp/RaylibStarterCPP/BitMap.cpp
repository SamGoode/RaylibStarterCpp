#include "BitMap.h"

BitMap::BitMap() {
    bits = nullptr;
}

BitMap::BitMap(int _width, int _height) {
    width = _width;
    height = _height;
    bits = new bool[width * height];
    for (int i = 0; i < width * height; i++) {
        bits[i] = true;
    }
}

BitMap::BitMap(const BitMap& copy) {
    width = copy.width;
    height = copy.height;
    bits = new bool[width * height];
    for (int i = 0; i < width * height; i++) {
        bits[i] = copy.bits[i];
    }
}

BitMap::~BitMap() {
    delete[] bits;
}

BitMap& BitMap::operator=(const BitMap& copy) {
    delete[] bits;

    width = copy.width;
    height = copy.height;
    bits = new bool[width * height];
    for (int i = 0; i < width * height; i++) {
        bits[i] = copy.bits[i];
    }

    return *this;
}

bool& BitMap::getBit(int x, int y) {
    return bits[x + y * width - 1];
}
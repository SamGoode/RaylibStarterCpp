#pragma once

class BitMap {
private:
    int width;
    int height;
    bool* bits;

public:
    BitMap();

    BitMap(int _width, int _height);

    BitMap(const BitMap& copy);

    ~BitMap();

    BitMap& operator=(const BitMap& copy);

    bool& getBit(int x, int y);
};
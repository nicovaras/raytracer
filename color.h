#ifndef COLOR_H
#define COLOR_H

struct Color{
    Color(int r, int g, int b) : r(r), g(g), b(b) {
    }
    int r;
    int g;
    int b;
};

#endif
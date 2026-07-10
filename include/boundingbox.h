#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vector2d.h"

class BoundingBox {
public:
    Vector2D coord;
    int width, height;
    BoundingBox(): width{64}, height{64} {}
    BoundingBox(int x, int y, int w, int h): width{w}, height{h} {
        coord.x = x;
        coord.y = y;
    }
    bool overlaps(const BoundingBox& other) {
        if(*this == other) return true;
        auto [x1, y1] = coord;
        auto [x2, y2] = other.coord;
        auto overlap1 = (x1 <= x2 && x2 <= x1 + width) || (x1 > x2 && x1 <= x2 + other.width);
        auto overlap2 = (y1 <= y2 && y2 <= y1 + height) || (y1 > y2 && y1 <= y2 + other.height);
        return overlap1 && overlap2;
    }
    
    bool operator==(const BoundingBox& other) {
        auto [x1,y1] = other.coord;
        auto [x2, y2] = coord;
        return x2 == x1 && y2 == y1 && width == other.width && height == other.height;
    }
};

#endif

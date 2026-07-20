#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vector2d.h"
#include "global.h"

class BoundingBox {
public:
    Vector2D coord;
    int width, height;
    BoundingBox();
    BoundingBox(int x, int y, int w, int h);
    bool overlaps(const BoundingBox& other);
    bool operator==(const BoundingBox& other);
};

#endif

#include "viewport.h"
#include <gtest/gtest.h>
#include <iostream>
/*
 class Viewport {
    
public:
    Vector2D origin;
    static const int LL, UL, WINDOW_WIDTH, WINDOW_HEIGHT;
    Viewport();
    ~Viewport();
    void update_origin(const Vector2D coord);
    Vector2D translate(const Vector2D coord);
    bool is_visible(const BoundingBox& other);
};
*/

TEST(ViewportTests, defaultOrigin) {
    Viewport v;
    EXPECT_EQ(v.origin, Vector2D(0,0));
}



#include "viewport.h"
#include <gtest/gtest.h>
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
    Vector2D zero{0,0};
    EXPECT_EQ(v.origin.x, 0);
}



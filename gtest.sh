if [ -f gtest.out ]; then
  rm gtest.out
fi
 
clang++ src/*.cpp tests/*.cpp -o gtest.out -I include  --std=c++20 $(pkg-config --cflags --libs sdl2 sdl2_image sdl2_ttf gtest) -w -DTEST_MODE

if [ -f gtest.out ]; then
  ./gtest.out
  rm gtest.out
fi

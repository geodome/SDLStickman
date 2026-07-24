if [ -f gtest ]; then
  rm gtest
fi
 
clang++ src/*.cpp tests/*.cpp -o gtest -I include  --std=c++20 $(pkg-config --cflags --libs sdl2 sdl2_image sdl2_ttf gtest) -w -DTEST_MODE
./gtest

rm gtest

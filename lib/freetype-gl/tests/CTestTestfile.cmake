# CMake generated Testfile for 
# Source directory: /Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests
# Build directory: /Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ansi-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/ansi" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/ansi.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/ansi-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/ansi-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(ansi-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(benchmark-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/benchmark" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/benchmark.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/benchmark-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/benchmark-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(benchmark-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(cartoon-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/cartoon" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/cartoon.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/cartoon-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/cartoon-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(cartoon-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(console-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/console" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/console.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/console-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/console-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(console-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(cube-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/cube" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/cube.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/cube-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/cube-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(cube-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(distance-field-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/distance-field" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/distance-field.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/distance-field-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/distance-field-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(distance-field-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(distance-field-2-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/distance-field-2" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/distance-field-2.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/distance-field-2-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/distance-field-2-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(distance-field-2-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(distance-field-3-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/distance-field-3" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/distance-field-3.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/distance-field-3-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/distance-field-3-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(distance-field-3-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(embedded-font-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/embedded-font" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/embedded-font.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/embedded-font-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/embedded-font-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(embedded-font-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(font-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/font" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/font.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/font-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/font-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(font-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(gamma-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/gamma" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/gamma.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/gamma-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/gamma-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(gamma-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(glyph-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/glyph" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/glyph.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/glyph-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/glyph-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(glyph-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(lcd-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/lcd" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/lcd.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/lcd-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/lcd-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(lcd-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(outline-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/outline" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/outline.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/outline-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/outline-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(outline-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(subpixel-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/subpixel" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/subpixel.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/subpixel-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/subpixel-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(subpixel-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")
add_test(texture-cmp-test "/usr/local/Cellar/cmake/3.10.1/bin/cmake" "-DIM_COMPARE_EXECUTABLE=/usr/local/bin/compare" "-DTEST_EXECUTABLE=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos/texture" "-DTEST_OUTPUT_EXPECT=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/doc/images/texture.png" "-DTEST_OUTPUT_CURR=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/texture-current.tga" "-DTEST_OUTPUT_DIFF=/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/texture-diff.png" "-DTEST_DISTANCE=0.01" "-P" "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/tests/CompareOutput.cmake")
set_tests_properties(texture-cmp-test PROPERTIES  WORKING_DIRECTORY "/Users/hailong11/Documents/src/github.com/hailongz/game/lib/freetype-gl/demos")

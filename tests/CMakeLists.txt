create_executable_project(AllTests)

add_depend(Application EasyExample ${CMAKE_SOURCE_DIR}/libs/lib_circle)
add_depend(Application EasyExample ${CMAKE_SOURCE_DIR}/libs/lib_easy_example)
add_depend(Application EasyExample ${CMAKE_SOURCE_DIR}/libs/lib_intersection_utils)
add_depend(Application EasyExample ${CMAKE_SOURCE_DIR}/libs/lib_point2)
add_depend(Application EasyExample ${CMAKE_SOURCE_DIR}/libs/lib_point3)
add_depend(Application EasyExample ${CMAKE_SOURCE_DIR}/libs/lib_sphere)

target_link_libraries(AllTests gtest gtest_main)
add_test(NAME AllTests COMMAND AllTests)
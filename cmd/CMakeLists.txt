add_executable(membench src/main.cpp include/instances.h src/instances.cpp)

target_include_directories(membench PRIVATE include)
target_link_libraries(membench mbl)
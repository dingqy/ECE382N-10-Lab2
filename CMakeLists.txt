cmake_minimum_required(VERSION 3.16)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab2 ./sim/cache.cpp
                    ./sim/cache.h
                    ./sim/generic_error.h
                    ./sim/helpers.cpp
                    ./sim/helpers.cpp
                    ./sim/helpers.h
                    ./sim/iu.cpp
                    ./sim/iu.h
                    ./sim/main.cpp
                    ./sim/my_fifo.h
                    ./sim/network.cpp
                    ./sim/network.h
                    ./sim/proc_submission.cpp
                    ./sim/proc.h
                    ./sim/test_submission.cpp
                    ./sim/test.h
                    ./sim/types.h)

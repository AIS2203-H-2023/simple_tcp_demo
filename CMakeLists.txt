cmake_minimum_required(VERSION 3.26)
project(boost_networking)

set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(boost_networking main.cpp)
target_link_libraries(boost_networking
        PRIVATE
        Boost::system
        nlohmann_json::nlohmann_json
)
if (MINGW)
    target_link_libraries(boost_networking PRIVATE ws2_32)
endif ()

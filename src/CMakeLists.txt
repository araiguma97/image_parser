cmake_minimum_required(VERSION 2.6)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(image_parser
  main.cc
  image_parser_factory.cc
  image_parser.cc
  jpg_parser.cc
  image_info.cc
)


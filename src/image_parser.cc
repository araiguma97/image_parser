#include "image_parser.h"

#include <stdio.h>
#include <stdlib.h>

ImageParser::ImageParser(const char* path) {
  fp_ = fopen(path, "rb");
  if (fp_ == NULL) {
      fprintf(stderr, "Error: Failed to open.\n");
      exit(1);
  }
};

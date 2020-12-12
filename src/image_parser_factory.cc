#include "image_parser_factory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_parser.h"
#include "jpg_parser.h"

ImageParser* ImageParserFactory::create(const char* path) {
  const char* extention = strrchr(path, '.');
  if (strncmp(".jpg", extention, strlen(extention)) == 0) {
    return new JPGParser(path);
//  } else if (strncmp(".png", extention, strlen(extention)) == 0) {
//    return new PNGPraser(path);
  } else {
    fprintf(stderr, "Error: Not supported type.\n");
    exit(1);
  }
  
}


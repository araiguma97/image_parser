#include <stdio.h>
#include <stdlib.h>

#include "image_parser_factory.h"
#include "image_parser.h"
#include "image_info.h"

int main(const int argc, char const *argv[]) { 
  if (argc != 2) {
    fprintf(stderr, "Error: Invalid arguments.\n");
    exit(1);
  }

  ImageInfo* info = new ImageInfo;

  ImageParser* parser = ImageParserFactory::create(argv[1]);
  parser->parse(info);
  delete parser;

  info->printSize();  
  delete info;

  return 0;
}

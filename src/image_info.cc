#include "image_info.h"

#include <stdio.h>

void ImageInfo::setSize(int x, int y) {
  this->x  = x;
  this->y  = y;
}

void ImageInfo::printSize() {
  printf("%dx%d\n",x, y);
}

Orientation ImageInfo::getOrientation() {
  if (x > y) {
    return kPortrait;
  } else if (y > x) {
    return kLandscape;
  } else {
    return kSquare;
  }
}


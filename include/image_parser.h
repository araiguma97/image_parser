#pragma once

#include "stdio.h"

#include "image_info.h"

/**
 * 画像解析クラス
 */
class ImageParser {
public:
  ImageParser(const char* path);
  virtual ~ImageParser() {}

  /**
   *  画像を解析する
   *  @param [in] path JPGファイルのパス
   */
  virtual void parse(ImageInfo* info) = 0;

protected:
  FILE* fp_;

private:
  ImageParser() {}

};



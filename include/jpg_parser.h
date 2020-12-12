#pragma once

#include "image_parser.h"
#include "image_info.h"

/**
 * JPG解析クラス
 */
class JPGParser : public ImageParser {
public:
  JPGParser(const char* path) : ImageParser(path) {}

  /**
   *  JPGを解析する
   *  @param [out] info 解析された画像情報
   *
   */
  void parse(ImageInfo* info) override;

private:
  int toInt(unsigned char* bytes, int n);
};



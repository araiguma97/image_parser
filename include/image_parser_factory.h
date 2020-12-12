#pragma once

#include "image_parser.h"

class ImageParserFactory {
public:
  /**
   * 画像解析インスタンスを生成する。
   * @param [in] path 画像ファイルのパス
   */
  static ImageParser* create(const char* path);
};


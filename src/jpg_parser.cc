#include "jpg_parser.h"

#include <stdio.h>
#include <stdlib.h>

void JPGParser::parse(ImageInfo* info) {
  unsigned char marker_bytes[2]        = {};  // マーカーバイト列
  unsigned char flame_len_bytes[2]     = {};  // フレーム長バイト列
  unsigned char precision_bytes[1]     = {};  // サンプル精度バイト列
  unsigned char y_bytes[2]             = {};  // 高さバイト列
  unsigned char x_bytes[2]             = {};  // 幅バイト列
  unsigned char component_num_bytes[1] = {};  // 成分数バイト列

  while (fp_) {
    if (fread(marker_bytes, 1, 2, fp_) != 2) { // マーカーを読み込む
      fprintf(stderr, "Error: Failed to parse.\n");
      exit(1);
    }

    // フレームヘッダーを読み込む
    if ((marker_bytes[0] == 0xff && marker_bytes[1] == 0xc0) ||
        (marker_bytes[0] == 0xff && marker_bytes[1] == 0xc2)) {
      if (fread(flame_len_bytes,     1, 2, fp_) != 2 || 
          fread(precision_bytes,     1, 1, fp_) != 1 ||
          fread(y_bytes,             1, 2, fp_) != 2 ||
          fread(x_bytes,             1, 2, fp_) != 2 ||
          fread(component_num_bytes, 1, 1, fp_) != 1) {
          printf("Error: Failed to read.\n");
          exit(1);
      }

      // 整数型に変換して、画像情報としてセットする
      info->setSize(toInt(y_bytes, 2), toInt(x_bytes, 2));
      return;
    }
  }
}

int JPGParser::toInt(unsigned char* bytes, int n) {
  int num = -1;

  if (n == 1) {
    num = static_cast<int>(bytes[0]);
  } else if (n == 2) {
    num = static_cast<int>(bytes[0] << 8);
    num += static_cast<int>(bytes[1]);
  } else {
    printf("Error: Failed to convert to Integer.\n");
    exit(1);
  }

  return num;
}


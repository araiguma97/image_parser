#include <stdio.h>
#include <stdlib.h>

/**
 * 画像情報クラス
 */
class ImageInfo {
public:
  void set(int flame_len, int precision, int y, int x, int component_num);
  bool isPortrait();
  bool isLandscape();
  void print();

private:
  int flame_len;      // フレーム長
  int precision;      // サンプル精度
  int y;              // 高さ
  int x;              // 幅
  int component_num;  // 成分数
};

void ImageInfo::set(int flame_len, int precision, int y, int x, int component_num) {
  this->flame_len     = flame_len;
  this->precision     = precision;
  this->y             = y;
  this->x             = x;
  this->component_num = component_num;
}

bool ImageInfo::isLandscape() {
  return (x > y);
}

bool ImageInfo::isPortrait() {
  return (y > x);
}

void ImageInfo::print() {
  printf("フレーム長=%d\n",   flame_len);
  printf("サンプル精度=%d\n", precision);
  printf("大きさ=%dx%d\n",    x, y);
  printf("成分数=%d\n",       component_num);
}

/**
 * JPG解析クラス
 */
class JPGParser {
public:
  /**
   *  JPGを解析する
   *  @param [in] path JPGファイルのパス
   */
  void parse(const char* path, ImageInfo* info);

private:
  int toInt(unsigned char* bytes, int n);
};

void JPGParser::parse(const char* path, ImageInfo* info) {
  FILE* fp = fopen(path, "rb");

  unsigned char marker_bytes[2]        = {};  // マーカーバイト列
  unsigned char flame_len_bytes[2]     = {};  // フレーム長バイト列
  unsigned char precision_bytes[1]     = {};  // サンプル精度バイト列
  unsigned char y_bytes[2]             = {};  // 高さバイト列
  unsigned char x_bytes[2]             = {};  // 幅バイト列
  unsigned char component_num_bytes[1] = {};  // 成分数バイト列

  while (fp) {
    fread(marker_bytes, 1, 2, fp);  // マーカーを読み込む

    if ((marker_bytes[0] == 0xff) && 
        ((marker_bytes[1] == 0xc0) || (marker_bytes[1] == 0xc2))) {
      // フレームヘッダーを読み込む
      fread(flame_len_bytes,     1, 2, fp);
      fread(precision_bytes,     1, 1, fp);
      fread(y_bytes,             1, 2, fp);
      fread(x_bytes,             1, 2, fp);
      fread(component_num_bytes, 1, 1, fp);

      // 整数型に変換して、画像情報としてセットする
      info->set(toInt(flame_len_bytes,     2),
                toInt(precision_bytes,     1),
                toInt(y_bytes,             2),
                toInt(x_bytes,             2),
                toInt(component_num_bytes, 1));
      return;
    }
  }

  printf("Error: Failed to parse.\n");
  exit(1);
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

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Error: Invalid argument(s).\n");
    exit(1);
  }

  ImageInfo* info = new ImageInfo;

  // JPGを解析する
  JPGParser* parser = new JPGParser;
  parser->parse(argv[1], info);
  delete parser;

  // 画像向きを判定する
  info->print();
  if (info->isPortrait()) {
    printf("この画像は縦向きです\n");
  } else if (info->isLandscape()) {
    printf("この画像は横向きです\n");
  } else {
    printf("この画像は正方形です\n");
  }

  delete info;
}


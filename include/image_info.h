#pragma once

// 向き
enum Orientation {
  kPortrait,
  kLandscape,
  kSquare
};

/**
 * 画像情報クラス
 */
class ImageInfo {
public:
  void setSize(int x, int y);
  void printSize();
  Orientation getOrientation();

private:
  int x;  // 幅
  int y;  // 高さ
};


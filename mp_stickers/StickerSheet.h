/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include "Image.h"

#pragma once

class StickerSheet{
public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet& operator=(const StickerSheet &other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker,unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x,unsigned y);
  void removeSticker(unsigned index);
  Image * getSticker(unsigned index);
  Image render() const;

private:
  void clear();
  void copy(const StickerSheet &that);

  Image** scene;
  unsigned *index;
  unsigned *x_cor;
  unsigned *y_cor;
  Image base_image;
  unsigned max_num;
  unsigned cur_sticker;
};

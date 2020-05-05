#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

using cs225::HSLAPixel;

void Image::lighten(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if(pixel.l > 0.9){
        pixel.l =1;
      } else {
        pixel.l += 0.1;
      }
    }
  }
}
void Image::lighten(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if( (pixel.l+amount) > 1){
        pixel.l =1;
      } else {
        pixel.l += amount;
      }
    }
  }
}

void Image::darken(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel sinpixel.l -= amout;ce you're directly changing the memory of the Image.
      if(pixel.l < 0.1){
        pixel.l =0;
      } else {
        pixel.l -= 0.1;
      }
    }
  }
}
void Image::darken(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if((pixel.l-amount) < 0){
        pixel.l =0;
      } else {
        pixel.l -= amount;
      }
    }
  }
}

void Image::saturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if(pixel.s > 0.9){
        pixel.s =1;
      } else {
        pixel.s += 0.1;
      }
    }
  }
}
void Image::saturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if((pixel.s+amount) > 1){
        pixel.s =1;
      } else {
        pixel.s += amount;
      }
    }
  }
}
void Image::desaturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if(pixel.s < 0.1){
        pixel.s =0;
      } else {
        pixel.s -= 0.1;
      }
    }
  }
}
void Image::desaturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      if((pixel.s-amount) < 0){
        pixel.s =0;
      } else {
        pixel.s -= amount;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      // `pixel` is a pointer to the memory stored inside of the PNG `Image`,
      // which means you're changing the Image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the Image.
      pixel.s = 0;
    }
  }
}

void Image::illinify(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if ( (pixel.h < 113) || (pixel.h > 293)){
        pixel.h = 11;
      }else{
        pixel.h = 216;
      }
    }
  }
}
void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      int check = pixel.h +degrees;
      if(check > 360){
        while(check >360){
          check -=360;
        }
      }else if(check <0){
        while(check <0){
          check +=360;
        }
      }
      pixel.h=check;
    }
  }
}

void Image::scale(double factor){
  double new_width = this->width()*factor;
  double new_height = this->height()*factor;

  new_width = round(new_width);
  new_height = round(new_height);
  PNG *temp = new PNG(this->width(),this->height());

  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      HSLAPixel & temp_p1 = temp->getPixel(x, y);
      temp_p1 = pixel;
    }
  }

  this->resize(new_width,new_height);
  for (unsigned x = 0; x < new_width; x++) {
    for (unsigned y = 0; y < new_height; y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      HSLAPixel & temp_p2 = temp->getPixel(x/factor,y/factor);
      pixel = temp_p2;
    }
  }
  delete temp;
}


void Image::scale(unsigned w, unsigned h){
  double width_factor = double(w)/double(this->width());
  double height_factor = double(h)/double(this->height());
  this->scale(fmin(width_factor,height_factor));
}

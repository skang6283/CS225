#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG image;
  image.readFromFile(inputFile);
  cs225::HSLAPixel temp;

  int check= 0;

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      if(check == (image.width() * image.height())/2){
        break;
      }
      check++;
      cs225::HSLAPixel & pixel = image.getPixel(x, y);
      cs225::HSLAPixel & pixel2 = image.getPixel(image.width()-x-1,image.height()-y-1);

      temp = pixel;
      // temp.h = pixel.h;
      // temp.s = pixel.s;
      // temp.l = pixel.l;
      // temp.a = pixel.a;
      pixel = pixel2;
      // pixel.h = pixel2.h;
      // pixel.s = pixel2.s;
      // pixel.l = pixel2.l;
      // pixel.a = pixel2.a;
      pixel2 = temp;
      // pixel2.h = temp.h;
      // pixel2.s = temp.s;
      // pixel2.l = temp.l;
      // pixel2.a = temp.a;
      }
  }
  image.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);

  //240 180 300 120 60
  //double hue = 0;
  //double l_incr = 0;
  double a = 0;
  double hue  =0;
  for (unsigned x = 0; x < (png.height()); x++) {
    a +=0.00125;
    hue += 0.45;
    for (unsigned y = x; y < (png.height()); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
        pixel.h = hue;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = a;
    }
    for (unsigned y = x; y < (png.height()); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(y,x);
        pixel.h = hue;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = a;
    }
  }


  return png;
}

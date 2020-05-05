#include "Image.h"
#include "StickerSheet.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //	

	Image myimage;
	myimage.readFromFile("tests/code_image.png");

	Image error;
	Image message;
	error.readFromFile("tests/error.png");
	message.readFromFile("tests/segfault.png");


	StickerSheet sheet(myimage, 100);

	srand(time(0));

	for (unsigned i =0; i< 20;i++){
		unsigned x = (rand()%(myimage.width()));
		unsigned y = (rand()%(myimage.height()));
		std::cout<<x<<','<<y<<std::endl;
		sheet.addSticker(error,x,y);	
	}

	sheet.addSticker(message,(myimage.width()/2)-(message.width()/2),(myimage.height()/2)-(message.height()/2));
	Image result = sheet.render();
	result.writeToFile("myImage.png");


  return 0;
}

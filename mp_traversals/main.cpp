
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
    
  PNG house;
  house.readFromFile("pattern.png");

  FloodFilledImage image(house);
  DFS dfs1(house, Point(19, 8), 0.5);
  DFS dfs2(house, Point(38, 52), 0.03);
  BFS bfs1(house, Point(66, 99), 0.5);
  BFS bfs2(house, Point(107, 609), 0.5);
  BFS bfs3(house, Point(550, 144), 0.5);
  BFS bfs4(house, Point(270, 316), 0.5);



  RainbowColorPicker color(1);
  MyColorPicker color1(350);
  MyColorPicker color2(2);
  MyColorPicker color3(50);
  MyColorPicker color4(200);


  image.addFloodFill(dfs1,color4);
  image.addFloodFill(dfs2,color1);
  image.addFloodFill(bfs1,color2);
  image.addFloodFill(bfs2,color3);
  image.addFloodFill(bfs3,color4);
  image.addFloodFill(bfs4,color);


  Animation animation = image.animate(1000);


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");


  return 0;
}

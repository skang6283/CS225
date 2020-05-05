#include <cmath>
#include <iterator>
#include <iostream>
//#include <vector>


#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */


double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  curPoint = Point(-1,-1);

}


// 
// ImageTraversal::Iterator::~Iterator() {
//   if(traversal != NULL){
//     delete traversal;
//   }
// }

ImageTraversal::Iterator::Iterator(ImageTraversal* FS, Point pt) {
  /** @todo [Part 1] */
  traversal = FS;
  curPoint = pt;

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  curPoint = traversal->pop();
  traversal->visited_[curPoint.x][curPoint.y] = true;

  //right, below, left, above

  //bounds
  Point right (curPoint.x+1, curPoint.y);
  Point below (curPoint.x, curPoint.y+1);
  Point left  (curPoint.x-1, curPoint.y);
  Point above (curPoint.x ,curPoint.y-1);

  //std::cout<<curPoint<<std::endl;
  //std::cout<<right<<below<<left<<above<<std::endl;

  Point start(traversal->start_.x,traversal->start_.y);
  bool right_visited, below_visited, left_visited, above_visited;

  if(right.x <traversal->png_.width()){
    right_visited = traversal->visited_[right.x][right.y];
  }else {
    right_visited = true;
  }

  if(below.y <traversal->png_.height()){
    below_visited = traversal->visited_[below.x][below.y];
  }else {
    below_visited = true;
  }

  if(left.x <traversal->png_.width()){
    left_visited = traversal->visited_[left.x][left.y];
  }else {
    left_visited = true;
  }
  //std::cout<<left_visited<<std::endl;

  if(above.y < traversal->png_.height()){
    above_visited = traversal->visited_[above.x][above.y];
  }else{
    above_visited = true;
  }


   if(right.x < traversal->png_.width()){
     double t_right = calculateDelta(traversal->png_.getPixel(right.x,right.y),traversal->png_.getPixel(start.x,start.y) );
    if(check_visited(right_visited,t_right)){

      traversal->add(right);
      //std::cout<<"right"<<std::endl;
    }
  }

  //below
  if(below.y < traversal->png_.height()){
    double t_below = calculateDelta(traversal->png_.getPixel(below.x,below.y),traversal->png_.getPixel(start.x,start.y) );

    if(check_visited(below_visited,t_below)){
      traversal->add(below);
      //std::cout<<"below"<<std::endl;
    }
  }



  //left
  if(left.x >= 0 && left.x <traversal->png_.width()){
    double t_left  = calculateDelta(traversal->png_.getPixel(left.x, left.y),traversal->png_.getPixel(start.x,start.y) );
    //std::cout<<"left"<<left<<std::endl;
    //std::cout<<"visitied?"<<left_visited<<std::endl;
    // std::cout<<"tolerance?"<<t_left<<std::endl;


    if(check_visited(left_visited,t_left)){
      traversal->add(left);
     // std::cout<<"left"<<std::endl;
    }
  }

  //above
  if(above.y >= 0 && above.y < traversal->png_.height()){
    double t_above = calculateDelta(traversal->png_.getPixel(above.x,above.y),traversal->png_.getPixel(start.x,start.y) );
    //std::cout<<"above"<<above<<std::endl;
    //std::cout<<"visitied?"<<above_visited<<std::endl;
     //std::cout<<"tolerance?"<<t_above<<std::endl;


    if(check_visited(above_visited,t_above)){
      traversal->add(above);
      //std::cout<<"above"<<std::endl;
    }
  }



  curPoint = traversal->peek();
  //std::cout<<std::endl;

  while(!traversal->list.empty()){

    if(traversal->visited_[curPoint.x][curPoint.y] == true){
      curPoint = traversal->pop();
      curPoint = traversal->peek();
    }else
    break;
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */


bool ImageTraversal::Iterator::check_visited(bool check_visit, double check_tolerance){
  //std::cout<<"in check visitied"<<std::endl;
  if(check_tolerance > traversal->tolerance_){
    //std::cout<<"false tolerance"<<std::endl;

    return false;
  }
  // std::cout<<"in check mid point"<<std::endl;
  // std::cout<<check_visit<<std::endl;
  // std::cout<<traversal->visited_[check_visit.x][check_visit.y]<<std::endl;
  // std::cout<<check_visit<<std::endl;

  if(check_visit == true){
    //std::cout<<"false"<<std::endl;
   return false;
  }
  return true;


}

Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curPoint;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(curPoint == other.curPoint){
    return false;
  }
  return true;
}

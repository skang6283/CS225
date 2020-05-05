#include <iterator>
#include <cmath>
#include <iostream>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
// BFS::~BFS(){
//
// }
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */

  png_ = png;
  start_ = start;
  tolerance_ = tolerance;

  visited_.resize(png_.width());
  for(unsigned i = 0; i< png_.width() ; i++){
    visited_[i].resize(png_.height());
  }
  for(unsigned j =0; j < png_.width(); j++){
    for(unsigned k =0; k < png_.height(); k++){
      visited_[j][k] = false;
      //std::cout<<visited_[j][k];
    }
      //std::cout<<std::endl;

  }
  //std::cout<<std::endl;

  //for (auto it = visited_.begin(); it != visited_.end(); it++)
  //      std::cout << visited_[] << " ";


  list.push_back(start_);

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */

  ImageTraversal *tmp = new BFS(png_,start_, tolerance_);
  return ImageTraversal::Iterator(tmp, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  list.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point tmp(-1,-1);
  if(list.empty()){
    return tmp;
  }
  tmp = list.front();
  list.pop_front();
  return tmp;

}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  Point tmp(-1,-1);
  if(list.empty()){
    return tmp;
  }
  return list.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return list.empty();
}



// bool DFS::get_visit(unsigned x, unsigned y){
//   return visited_[x][y];
// }
// void DFS::set_visit(unsigned x, unsigned y){
//   visited_[x][y] = true;
// }

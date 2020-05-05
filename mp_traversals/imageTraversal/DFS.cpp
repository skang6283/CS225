#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The imagze this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */

// DFS::~DFS(){
//
// }


DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */

  png_ = png;
  start_ = start;
  tolerance_ = tolerance;

  visited_.resize(png_.width());
  for(unsigned i = 0; i < png_.width() ; i++){
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

  list.push_back(start);

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal *tmp = new DFS(png_,start_, tolerance_);
  return ImageTraversal::Iterator(tmp, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  list.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point tmp(-1,-1);
  if(list.empty()){
    return tmp;
  }

  tmp = list.back();
  list.pop_back();
  return tmp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  Point tmp(-1,-1);
  if(list.empty()){
    return tmp;
  }
  return list.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return list.empty();
}

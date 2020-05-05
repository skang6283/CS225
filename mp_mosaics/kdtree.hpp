/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
  if(first[curDim] < second[curDim]){
    return true;
  }else if(first[curDim] > second[curDim]){
    return false;
  } else {//if(first[curDim] == second[curDim]){
    return first < second;
  }
  //return false;

    
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    // double currentDistance = pow((currentBest[0]-target[0]),2) + pow((currentBest[1]-target[1]),2) + pow((currentBest[2]-target[2]),2) ;
    // double potentialDiasntace = pow((potential[0]-target[0]),2) + pow((potential[1]-target[1]),2) + pow((potential[2]-target[2]),2) ;
       double currentDistance = 0;
       double potentialDiasntace = 0;

    for(int i = 0; i < Dim; i++){
      currentDistance += pow((currentBest[i]-target[i]),2);
      potentialDiasntace += pow((potential[i]-target[i]),2);
    }


    if(potentialDiasntace < currentDistance){
      return true;
    }else if(potentialDiasntace > currentDistance){
      return false;
    }else {//if(potentialDiasntace == currentDistance){
      return potential < currentBest;
    }   
     //return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
  if(newPoints.empty()){
    root = NULL;
    size = 0;
  }else {
    vector<Point<Dim>> points_;
    points_.assign(newPoints.begin(), newPoints.end());
    size = 0;
    root = KDTree_helper(points_, 0, points_.size()-1, 0);
  }

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTree_helper(vector<Point<Dim>>& points_, int left, int right, int curDim){
  if(left > right){
    return NULL;
  }
  size_t m = (left+right)/2;
  KDTreeNode* subroot = new KDTreeNode(select(points_,left,right,m,curDim));
  
  size++;
  

  subroot->left = KDTree_helper(points_,left, m-1, (curDim+1) % Dim);
  subroot->right = KDTree_helper(points_, m+1, right, (curDim+1) % Dim);
  return subroot;
}





template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & list ,int left, int right, size_t pivotIndex, int curDim){
  Point<Dim> pivotValue = list[pivotIndex];
  swap(list[pivotIndex], list[right]);
  size_t storeIndex = left;
  for(int i = left ; i < right ; i++){
    if(smallerDimVal(list[i], pivotValue, curDim)){
      swap(list[storeIndex], list[i]);
      storeIndex++;
    }
  }
  swap(list[right], list[storeIndex]);
  return storeIndex;
}


// Returns the k-th smallest element of list within left..right inclusive
  // (i.e. left <= k <= right).

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>> & list ,int left, int right, size_t k, int curDim){
  if(left == right){
    return list[left];    
   }
   size_t pivotIndex = (left+right)/2;
   pivotIndex = partition(list, left, right, pivotIndex, curDim);
  if(k == pivotIndex){
    return list[k];
   }else if(k < pivotIndex){
     right = pivotIndex-1;
     return select(list,left,right,k,curDim);
   }else{
     left = pivotIndex+1;
    return select(list,left,right,k,curDim);
  }
}






template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy_helper(this->root, other.root);
}



template <int Dim>
void KDTree<Dim>::copy_helper(KDTreeNode * cur, KDTree* other){
  cur = new KDTreeNode();
  cur->point = other->point;
  copy_helper(cur->left, other->left);
  copy_helper(cur->left. other->left);
   
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  delete_helper(root);
  copy_helper(this->root, rhs.root);
  size = rhs.size;        
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  delete_helper(root);
}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const  //query == target
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> bestPoint= root->point;
    Point<Dim> target = query;
    find_helper(root, bestPoint, target, 0 ); // const error
    return bestPoint;
}

template <int Dim>
void KDTree<Dim>::find_helper(KDTreeNode* subroot, Point<Dim> & currentBest, Point<Dim> &target, int curDim) const{
  
  if(subroot == NULL){
    return;
  }

  int check = 0; // check left or right
  
  if(smallerDimVal(subroot->point, target, curDim)){ //&& subroot->left != NULL){
    //you go left
    find_helper(subroot->right, currentBest, target, (curDim + 1) % Dim);
    check = -1;
  }else{
    //you go right
    find_helper(subroot->left, currentBest, target, (curDim + 1) % Dim);    
    check = 1;
  }


  //compare curren point and current best 
  if(shouldReplace(target, currentBest, subroot->point)){
    currentBest = subroot->point;
  }



  double currentBest_radius = 0;
  
  for(int i = 0; i < Dim; i++){
      currentBest_radius += pow((currentBest[i]-target[i]),2);  
  }

  double distance = pow((subroot->point[curDim] - target[curDim]),2); 

  if(currentBest_radius >= distance){
    if(check == -1){
      find_helper(subroot->left, currentBest, target, (curDim+1)% Dim);
    }else if(check == 1){
      find_helper(subroot->right, currentBest, target, (curDim+1)% Dim);
    }
  }

}



  

//destructor
template <int Dim>
void KDTree<Dim>::delete_helper(KDTreeNode* cur) {
    if(cur == NULL){
      return;
    }

    if(cur->left != NULL){
      delete_helper(cur->left);
    }   

    if(cur->right != NULL){
      delete_helper(cur->right);
    }  

    delete cur; 
    cur = NULL;
}



/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <cmath>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot){
  if(subRoot == NULL || (subRoot->left == NULL && subRoot->right == NULL)){
    return;
  }

  Node* swap = subRoot->right;
  subRoot->right = subRoot->left;
  subRoot->left = swap;

  mirror(subRoot->left);
  mirror(subRoot->right);

}



/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    T before = 0;
    InorderTraversal<T> rooot(root);
    for (typename TreeTraversal<T>::Iterator it = rooot.begin() ; it != rooot.end() ; ++it){
        
        if((*it)->elem < before){
            return false;

        }   
        before = (*it)->elem; 
    }

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    if(root == NULL){
        return true;
    }              

    return isOrderedRecursive(root);


}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const {
    if(subRoot == NULL){
        return true;
    }

    if(subRoot->left == NULL && subRoot->right == NULL){
        return true;
    }
    int left_max = checkmax(subRoot->left);
    
    int right_min =  checkmin(subRoot->right);

    
    if(left_max > subRoot->elem){
        return false;
    } 

    if(right_min < subRoot->elem){
        return false;
    }

    bool check1 = isOrderedRecursive(subRoot->left);
    bool check2 = isOrderedRecursive(subRoot->right);


    if (check1 == false ||  check2 == false){
        return false;
    }

    return true;


}

template <typename T>
int BinaryTree<T>::checkmin(Node * subRoot) const {
    if(subRoot == NULL){
        return 1000000;
    }        

    int temp = subRoot->elem;
    int left_temp = checkmin(subRoot->left);
    int right_temp = checkmin(subRoot->right);


//    return fmin(left_temp,right_temp);

    if(left_temp < temp){
        return left_temp;
    }else if(right_temp < temp){
        return right_temp;
    }
    return temp;

}

template <typename T>
int BinaryTree<T>::checkmax(Node* subRoot) const {
    if(subRoot == NULL){
        return -1;
    }        

    int temp = subRoot->elem;
    int left_temp = checkmax(subRoot->left);
    int right_temp = checkmax(subRoot->right);

//    return fmax(left_temp,right_temp);
    if(left_temp > temp){
        return left_temp;
    }else if(right_temp > temp){
        return right_temp;
    }
    return temp;

}
    
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    std::vector<T> temp; 
    getPaths(paths, temp, root);
    
}


template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths,std::vector<T> &temp, Node* subRoot )const{
    temp.push_back(subRoot->elem);

    if(subRoot->left == NULL && subRoot->right == NULL){
        paths.push_back(temp);        
    }

    if(subRoot->left != NULL){
        getPaths(paths, temp, subRoot->left);
    }

    if(subRoot->right != NULL){
        getPaths(paths, temp ,subRoot->right);
    }
    
    temp.pop_back();

}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    int total=0;
    total = sumDistances(root,0);
    return total;
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* subRoot, int incr) const{
    if(subRoot->left == NULL & subRoot->right == NULL){
        //std::cout<<"leaf:"<<incr<<std::endl;

        return incr;
    }
    //std::cout<<incr<<std::endl;
    return incr + sumDistances(subRoot->left, incr + 1) + sumDistances(subRoot->right, incr + 1);
    

}

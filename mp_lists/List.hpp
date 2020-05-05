/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1


    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}



/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if(length_ ==0){
    return;
  } else if(length_ == 1){
    delete head_;
  } else{

    ListNode * tmp = head_;
    for(int i = 0;i<(length_-1);i++){
      tmp = tmp->next;
      delete tmp->prev;
    }
    delete tmp;

    head_ = NULL;
    tail_ = NULL;
    tmp = NULL;
    length_ =0;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;


  if (length_ != 0) { //head_ != NULL
    head_ -> prev = newNode;
  }

  if (length_ == 0) {    //tail_ == NULL
    tail_ = newNode;
  }
  head_= newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;

  if (length_ != 0) {   //tail_ != NULL
    tail_ -> next = newNode;
  }

  if (length_ == 0) {     //head_ == NULL
    head_ = newNode;
  }

  tail_= newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split()  function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * empty = NULL;
  if(splitPoint > length_){
    return empty;
  }

  ListNode * curr = start;

  if(splitPoint == 0){
    start = NULL;
    return curr;
  }


  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * cur = head_;
  ListNode * move = head_->next;
  while(move->next != NULL){
    cur->next = move->next;
    (cur->next)->prev = cur;

    move->next = NULL;
    move->prev = tail_;
    tail_->next = move;
    tail_ = move;

    cur = cur->next;
    move = cur->next;
  }

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  ListNode* start_tmp = startPoint;
  ListNode* tmp = NULL;
  ListNode* after_EP= NULL;
  ListNode* before_SP= NULL;
  ListNode* current = NULL;

  before_SP = startPoint->prev;
  after_EP = endPoint->next;
  current = startPoint;
  //new_next = startPoint->next;

  while(current != endPoint){
    tmp = current->next;
    current->next = current->prev;
    current->prev = tmp;
    current = tmp;
  }

  current->next = current->prev;
  current->prev = before_SP;
  startPoint->next = after_EP;

  //if the list is between values, connect them
  if(before_SP != nullptr){
    before_SP->next = endPoint;
  }else {
    //std::cout<<"before head is null"<<std::endl;
    head_ = endPoint;
  }

  if(after_EP != nullptr){
    after_EP->prev = startPoint;
  }else {
    tail_ = startPoint;
  }

  //swap startpoint and endpoint
  //ListNode* tmp_swap = start_tmp;  
  startPoint = endPoint;
  endPoint = start_tmp;

  //std::cout<<"check"<<std::endl;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  // @todo Graded in MP3.2
  if(n >= length_){
    reverse(head_,tail_);
    return;
  } else if(n <= 1 || head_== NULL){
    return;
  }

  int rmdr = length_% n;
  ListNode * head_tmp = head_;
  ListNode * tail_tmp = head_;
  //std::cout<<"rmdr:"<<rmdr<<std::endl;

 // std::cout<<"length_:"<<length_<<std::endl;
 // std::cout<<"N:"<<n<<std::endl;
 // std::cout<<length_/n<<std::endl;
  for(int i = 0; i < (length_/n);i++ ){
    for(int k = 0 ; k < n-1 ; k++){
      tail_tmp = tail_tmp->next;
    }

    reverse(head_tmp, tail_tmp);

    head_tmp = tail_tmp->next;
    tail_tmp = head_tmp;
    
  }

  if(rmdr > 1){
    //std::cout<<"begin rmdr"<<std::endl;
    tail_tmp = head_tmp;
    for(int j = 0 ; j < rmdr-1 ; j++){
      tail_tmp = tail_tmp->next;
    }
    reverse(head_tmp, tail_tmp);
    head_tmp = tail_tmp->next;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL && second == NULL){
    return NULL;
  }else if(first == NULL){
    return second;
  }else if(second == NULL){
    return first;
  }

  ListNode* newlist = NULL;
  ListNode* nltemp = NULL;
  ListNode* ftemp = first;
  ListNode* stemp = second;


  //set head
  if(ftemp->data < stemp->data){
    newlist = ftemp;
    ftemp = ftemp->next;
  }else{
    newlist = stemp;
    stemp = stemp->next;
  }

  nltemp = newlist;
  int i =0;
  while(ftemp != NULL && stemp != NULL){
    //std::cout<<"stemp:"<<stemp->data<<std::endl;
    //std::cout<<"ftemp:"<<ftemp->data<<std::endl;
    //std::cout<<"nltemp:"<<nltemp->data<<std::endl;
    //std::cout<<"nltemp->next->data:"<<nltemp->next->data<<std::endl;
    //std::cout<<""<<std::endl;

    if( ftemp->data < stemp->data && ftemp != NULL){
      //std::cout<<"ftemp is smaller"<<std::endl;

      nltemp->next = ftemp;
      ftemp->prev = nltemp;
      ftemp = ftemp->next;

    }else if(stemp->data < ftemp->data && stemp != NULL){
      //std::cout<<"stemp is smaller"<<std::endl;

      nltemp->next = stemp;
      stemp->prev = nltemp;
      stemp = stemp->next;

    }else{
      //std::cout<<"equal so doesn matter"<<std::endl;

      nltemp->next = stemp;
      stemp->prev = nltemp;
      stemp = stemp->next; 

    }
     //std::cout<<"check seg"<<std::endl;
    nltemp = nltemp->next;
  }
   //std::cout<<"nltemp:"<<nltemp->data<<std::endl;

   if(stemp != NULL){
    nltemp->next = stemp;
    stemp->prev = nltemp;
   }
   if(ftemp != NULL){
    nltemp->next = ftemp;
    ftemp->prev = nltemp;
   }



  return newlist;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start == NULL){
    return NULL;
  }

  if(chainLength == 1){
    return start;
  }

  
  int new_cl1 = chainLength / 2;
  int new_cl2 = chainLength - new_cl1;

  ListNode* new_start = split(start,new_cl1); 

  ListNode *newlist = merge(mergesort(start,new_cl1),mergesort(new_start,new_cl2));


  return newlist;
}



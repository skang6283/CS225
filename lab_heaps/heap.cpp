
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cmath>
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.

    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2 +1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(_elems.size() > currentIdx*2){
        return true;
    }
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(!hasAChild(currentIdx)){
        return 0;
    }else if(currentIdx*2 == _elems.size()-1){
        return currentIdx*2;
    }else if(higherPriority(_elems[currentIdx*2], _elems[currentIdx*2+1])){
        return currentIdx*2;
    }else{
        return currentIdx*2+1;
    }



}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)){
        size_t min = maxPriorityChild(currentIdx);
        if(higherPriority(_elems[min], _elems[currentIdx])){
            std::swap(_elems[currentIdx], _elems[min]);
            heapifyDown(min);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying

    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(size_t i = 0; i< elems.size(); i++){
        _elems.push_back(elems[i]);
    }
    for(size_t i = parent(_elems.size()-1); i > 0; i--){
        heapifyDown(i);
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    std::swap(_elems[1], _elems[_elems.size()-1]);
    T tmp = _elems[_elems.size()-1];
    _elems.pop_back();
    heapifyDown(1);
    return tmp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority

    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
    // @TODO Add elem to the heap
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    for(size_t i = idx; i > 0; i--){
      heapifyDown(i);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() == 1){
      return true;
    }
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}

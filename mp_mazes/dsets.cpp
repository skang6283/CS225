/* Your code here! */
#include "dsets.h"
#include <iostream>

//*****UNION BY SIZE*******

// Creates n unconnected root nodes at the end of the vector.

// Parameters
// num	The number of nodes to create

void DisjointSets::addelements(int num){
	for(int i =0; i < num; i++){
		s.push_back(-1);
	}
}

// This function should compress paths and works as described in lecture.

// Returns
// the index of the root of the up-tree in which the parameter element resides.	
int DisjointSets::find(int elem){
	if(s[elem] < 0 ) {return elem; }
	else{//return find(s[elem]); }
		int root = find(s[elem]); //compression
		s[elem] = root;
		return root;
	}
}

// This function should be implemented as union-by-size.

// That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.

// Your setunion function SHOULD find the roots of its arguments before combining the trees. If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)

// Parameters
// a	Index of the first element to union
// b	Index of the second element to union

void DisjointSets::setunion(int a, int b){
	int root1 = find(a);
	int root2 = find(b);
	
	int newSize = s[root1] + s[root2];



	if(s[root1] < s[root2]){
		s[root2] = root1;
		s[root1] = newSize;
	}else{
		s[root1] = root2;
		s[root2] = newSize;
	}



}



// This function should return the number of nodes in the up-tree containing the element.

// Returns
// number of nodes in the up-tree containing the element
int DisjointSets::size(int elem){
	if(s[elem] < 0){ return s[elem]*(-1); }
	else{ return size(s[elem]); }
}
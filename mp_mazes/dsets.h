/* Your code here! */
#pragma once 
#include<vector>


class DisjointSets{
public:
	void addelements(int);
	int find(int);
	void setunion(int,int);
	int size(int);

	std::vector<int> s;
};
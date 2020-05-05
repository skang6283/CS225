
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
//#include "../cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;


int main() {


  List<int> testlist1;
  List<int> testlist2;
  for(int i=0; i < 20;i+=2){
	 testlist1.insertBack(i);
  }

  std::cout<<testlist1<<std::endl;


  for(int i=0; i < 15;i+=3){
   testlist2.insertBack(i);
  }
  //std::cout<<testlist2<<std::endl;


  testlist1.reverse();

  std::cout<<testlist1<<std::endl;


  return 0;
 }

/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */

    string word1,word2;
    char tmp;
    ifstream wordsFile(word_list_fname);
    string word;
    if(wordsFile.is_open()){
    	while(getline(wordsFile, word)){
    		if(word.size() > 2){

    			

    			tmp = word[0];



    			word1 = tmp + word.substr(2, word.size()-1);

    			word2 = word.substr(1,word.size()-1);

    			//std::cout<<word<<" "<<word1<<" "<<word2<<std::endl;	

    			if(d.homophones(word1,word2)){
    				ret.push_back({word,word1,word2});
    			}

    			//std::cout<<word<<std::endl;
    		}	
    	}
    }

    return ret;
}

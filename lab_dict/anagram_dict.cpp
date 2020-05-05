/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream anagram_dict_file(filename);
    string line;
    if (anagram_dict_file.is_open()) {
        while (getline(anagram_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
        	string w = line;
        	sort(w.begin(), w.end());
        	dict[w].push_back(line);

        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{	
	for(size_t i =0; i< words.size(); i++){
		string w = words[i];
		sort(w.begin(), w.end());
		dict[w].push_back(words[i]);
	}

    /* Your code goes here! */
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */


	string sorted = word;
	sort(sorted.begin(), sorted.end());
	std::map<std::string, std::vector<std::string>>::const_iterator lookup = dict.find(sorted);
	if(lookup != dict.end()){
		return lookup->second;
	}

    return vector<string>(0);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	vector<vector<string>> out;

	for(std::map<string,vector<string>>::const_iterator it = dict.begin(); it != dict.end(); ++it){
		if(it->second.size() >1){
			out.push_back(it->second);
	
		}
	}


    return out;
}

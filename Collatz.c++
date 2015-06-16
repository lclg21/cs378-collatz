// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <map>      //map<int, int>
#include "Collatz.h"

using namespace std;

#ifdef CACHE
   #define typedef std::map<int, int> cache;
#endif


// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

//initializes my map (cache)
std::map<int, int> cache;
int collatz_eval (int i, int j) {
  int max = 0;
  //Checks to see if the range is in increasing order.
  if ( i < j){
    assert(i < j);
    //Loops through the range and find each element's length cycle.
    while (i < j + 1){
      assert(i < j+1);
      int n = i;
      int cycleLength = 1;
      assert(n > 0);
      while (n > 1){
	//checks if element n is in the cache
	if (cache.count(n) == 0){
	  assert(cache.count(n) == 0);
	  if ( n % 2 == 0){
	    n = n / 2;
	    ++cycleLength;
	  }   
	  else{
	    n = (3 * n) + 1;
	    ++cycleLength;
	  }
	}
	else{
	  //checks to see if element n is the cache(map).
	  cycleLength += ((cache.find(n) -> second)-1);
	  break;
	}
      }
      //inserts the cycle length of i in the cache(map)
      cache[i] = cycleLength;
      if (max < cycleLength){
	max = cycleLength;
	assert(max > 0);
      }
      ++i;
    }
  }
  //checks to see if range is in decreasing order.
  if ( i > j){
    assert(i > j);
    //Loops through the range and find each element's length cycle.
    while (j < i + 1){
      assert (j < i+1);
      int n = j;
      int cycleLength = 1;
      while (n > 1){
	//checks if element n is in the cache
	if (cache.count(n) == 0){
	  assert(cache.count(n) == 0);
	  if ( n % 2 == 0){
	    n = n / 2;
	    ++cycleLength;
	  }   
	  else{
	    n = (3 * n) + 1;
	    ++cycleLength;
	  }
	}
	else {
	  cycleLength += ((cache.find(n) -> second)-1);
	  break;
	}
      }
      //inserts the cycle length of i in the cache(map)
      cache[j] = cycleLength;
      if (max < cycleLength){
        max = cycleLength;
	assert(max > 0);
      }
      ++j;
    }
  }

  //checks for the cycle length when i == j.
  else {
    int n = i;
    int cycleLength = 1;
    while ( n > 1){
      if (cache.count(n) == 0) {
	if ((n % 2) == 0){
	  n = (n / 2);}
	else{
	  n = (3 * n) + 1;
	}
	++cycleLength;
      }
      else{
	cycleLength += ((cache.find(n) -> second)-1);
	break;
      }
    }
    cache[i] = cycleLength;
    if (cycleLength > max)
      max = cycleLength;
    max = cycleLength;
  }

  return max;}


// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

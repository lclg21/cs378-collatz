// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif


// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <map>


using namespace std;

#ifdef CACHE
typedef std::map<int, int> Map;
#endif


pair<int, int> collatz_read (const string& s);
int collatz_eval (int i, int j);
void collatz_print (ostream& w, int i, int j, int v);
void collatz_solve (istream& r, ostream& w);

// ----
// main
// ----

int main () {
  using namespace std;
  collatz_solve(cin, cout);
  return 0;}

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

//initializes the cache (map);
std::map<int, int> cache;
int collatz_eval (int i, int j) {
  int max = 0;
  //Checks to see if the range is in ascending order.
  if ( i < j){
    assert(i < j);
    while (i < j + 1){
      assert(i < j+1);
      int n = i;
      int cycleLength = 1;
      assert(n > 0);
      while (n > 1){
	//Looks to see if the n element is in the cache (map).
        if (cache.count(n) == 0){
          if ( n % 2 == 0){
            n = n / 2;
          }
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
      //inputs the cyclelength of i into the cache.
      //and checks to see if its max cycle length.
      cache[i] = cycleLength;
      if (max < cycleLength){
        max = cycleLength;
      }
      ++i;
    }
  }
  // chceks to see if the range given is in decresing order.
  if ( i > j){
    assert(i > j);
    while (j < i + 1){
      assert (j < i+1);
      int n = j;
      int cycleLength = 1;
      while (n > 1){
        if (cache.count(n) == 0){
          if ( n % 2 == 0){
            n = n / 2;
          }
          else{
            n = (3 * n) + 1;
          }
	  ++cycleLength;
        }
        else {
          cycleLength += ((cache.find(n) -> second)-1);
          break;
        }
      }
      cache[j] = cycleLength;
      if (max < cycleLength){
        max = cycleLength;
      }
      ++j;
    }
  }
  //if the elements given in the range are the same, it execcutes this else statement.
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
    //inputs the cycle length of i into the cache.
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

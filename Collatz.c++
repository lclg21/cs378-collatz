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

#include "Collatz.h"

using namespace std;

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

int collatz_eval (int i, int j) {
    int max = 0;
    if ( i < j){
        assert(i < j);
        while (i < j + 1){
            assert(i < j+1);
            int n = i;
            int cycleLength = 1;
            assert(n > 0);
            while (n > 1){
                if ( n % 2 == 0){
                    n = n / 2;
                }   
                else{
                    n = (3 * n) + 1;
		}
                ++cycleLength;
            }
            if (max < cycleLength){
                max = cycleLength;
            }
            ++i;
        }
    }

    if ( i > j){
        assert(i > j);
        while (j < i + 1){
            assert (j < i+1);
            int n = j;
            int cycleLength = 1;
            while (n > 1){
                assert (n > 1);
                if ( n % 2 == 0){
                    n = n / 2;
                }   
                else{
                    n = (3 * n) + 1;
                }
                ++cycleLength;
            }
            if (max < cycleLength){
                max = cycleLength;
            }
            ++j;
        }
    }

    else {
      int n = i;
      int c = 1;
      while ( n > 1){
	if ((n % 2) == 0){
	  n = (n / 2);}
        else{
	  n = (3 * n) + 1;}
        ++c;
      }
      max = c;
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

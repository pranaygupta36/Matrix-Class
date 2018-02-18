//////////////////
// Pranay Gupta //
//   IIIT HYD   //
//////////////////

// #ifndef MATRIX_H
// #define MATRIX_H

#include <vector>
#include <iostream>
//#include "matrix.h"
#include "expression_templates.h"
#include <cassert>

using namespace std;

int main(void) {
	Matrix<int> b(2,2,3);
	Matrix<int> c(2,2,1);
	Matrix<int> d(2,2,1);

	
	Matrix<int> a;
	// a = 0;
	a = (b+c+d);
	cout<<a(0,0)<<endl;
	return 0; 
}

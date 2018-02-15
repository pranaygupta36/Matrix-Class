//////////////////
// Pranay Gupta //
//   IIIT HYD   //
//////////////////

// #ifndef MATRIX_H
// #define MATRIX_H

#include <vector>
#include <iostream>
#include "matrix.h"
#include <cassert>

using namespace std;

int main(void) {
	Matrix<int> b(2,2,3);
	Matrix<int> c(2,1,1);

	// vector <vector<int> > temp;
	// vector<int> temp1;
	// temp1.push_back(1);
	// temp1.push_back(2);
	// temp.push_back(temp1);
	// temp.push_back(temp1);

	Matrix<int> a;
	// a = 0;
	a = (b*c);
	//cout<<"Yo"<<endl;
	const int i = 0;
	const int j = 1;
	cout<<(b*c)(0,0)<<endl;
	return 0; 
}

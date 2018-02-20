//////////////////
// Pranay Gupta //
//   IIIT HYD   //
//////////////////

#include <vector>
#include <iostream>
#include "../includes/expression_templates.h"
#include <cassert>

using namespace std;

int main(void) {
	Matrix<int> a(3,1,3);
	Matrix<int> b(1,3,1);
	Matrix<int> c(3,3,1);
	
	Matrix<int> d(3,3);
	d = (a*b*c);

	cout<<d(2,2)<<endl;
	return 0; 
}
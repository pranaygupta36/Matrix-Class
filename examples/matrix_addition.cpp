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
	Matrix<int> b(2,2,3);
	Matrix<int> c(2,2,1);
	Matrix<int> d(2,2,1);
	Matrix<int> e(2,2,1);

	cout<<b.r_size()<<endl;
	Matrix<int> a(2,2);
	a = (b+c+d+e);

	cout<<a(1,1)<<endl;
	return 0; 
}

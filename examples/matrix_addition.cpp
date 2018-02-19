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

	cout<<b.r_size()<<endl;
	Matrix<int> a;
	a = (b+c+d);

	cout<<a.r_size()<<endl;
	return 0; 
}

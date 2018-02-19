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
	
	Matrix<int> d;
	d = (a*b*c);

	cout<<d.r_size()<<endl;
	return 0; 
}
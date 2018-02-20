#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTests

#include <boost/test/unit_test.hpp> 
#include <iostream>
#include "../includes/expression_templates.h"
#include <typeinfo>
#include <string>
#include <complex.h>
#include <limits.h>
#include <cmath>

// consructor tests
BOOST_AUTO_TEST_SUITE(Constructor)
BOOST_AUTO_TEST_CASE (constructors_working) {

	// void matrix declaration
	Matrix<int> TestMatrix1;
	BOOST_CHECK(TestMatrix1.r_size() == 0);
	BOOST_CHECK(TestMatrix1.c_size() == 0);
	
	//matrix definition with initial size of 3,2
	Matrix<int> TestMatrix2(3,2);
	BOOST_CHECK(TestMatrix2.r_size() == 3);
	BOOST_CHECK(TestMatrix2.c_size() == 2);

	//matrix definition with initial size and value
	Matrix<int> TestMatrix3(4,4,1);
	BOOST_CHECK(TestMatrix3.r_size() == 4);
	BOOST_CHECK(TestMatrix3.c_size() == 4);
	for(int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			BOOST_CHECK(TestMatrix3(i,j) == 1);
		}
	}

}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(VariableType)
BOOST_AUTO_TEST_CASE (type_check) {
	
	//unsigned int is accepted
	Matrix<int> M(1,1,1);
	std::string type = typeid(M(0, 0)).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");
	
	//char is rejected
	Matrix<char> M1(1,1,'a');
	type = typeid(M1(0, 0)).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");	
	
	//string is rejected
	Matrix<std::string> M2(1,1,"foo");
	type = typeid(M2(0,0)).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");

}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Matrix_addition)
BOOST_AUTO_TEST_CASE(Matrix_addition_int) {
	
	Matrix<int> TestMatrix1(3, 3), TestMatrix2(3, 3), TestMatrix3(3,3), TestMatrix4(3, 3);
	TestMatrix1.setVal(0, 0, 1);
	TestMatrix1.setVal(0, 1, 2);
	TestMatrix1.setVal(0, 2, 7);
	TestMatrix1.setVal(1, 0, 3);
	TestMatrix1.setVal(1, 1, 4);
	TestMatrix1.setVal(1, 2, 8);
	TestMatrix1.setVal(2, 0, 5);
	TestMatrix1.setVal(2, 1, 6);
	TestMatrix1.setVal(2, 2, 9);
	
	TestMatrix2.setVal(0, 0, 2);
	TestMatrix2.setVal(0, 1, -4);
	TestMatrix2.setVal(0, 2, 5);
	TestMatrix2.setVal(1, 0, -3);
	TestMatrix2.setVal(1, 1, -5);
	TestMatrix2.setVal(1, 2, 2);
	TestMatrix2.setVal(2, 0, 7);
	TestMatrix2.setVal(2, 1, 1000);
	TestMatrix2.setVal(2, 2, 2);

	TestMatrix3.setVal(0, 0, 3);
	TestMatrix3.setVal(0, 1, -2);
	TestMatrix3.setVal(0, 2, 12);
	TestMatrix3.setVal(1, 0, 0);
	TestMatrix3.setVal(1, 1, -1);
	TestMatrix3.setVal(1, 2, 10);
	TestMatrix3.setVal(2, 0, 12);
	TestMatrix3.setVal(2, 1, 1006);
	TestMatrix3.setVal(2, 2, 11);

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.r_size(); i++) {
		for(int j = 0; j < TestMatrix4.c_size(); j++) {
			//checking overflow
			BOOST_CHECK( (double) (fabs( ( double ) TestMatrix1(i, j) + (double)TestMatrix2(i, j))) <= INT_MAX);
			//addition result checking
			BOOST_CHECK(TestMatrix4(i, j) == TestMatrix3(i, j));
		}
	}
}

BOOST_AUTO_TEST_CASE(Matrix_addition_long_long_int) {
	
	Matrix<long long> TestMatrix1(2, 2), TestMatrix2(2, 2), TestMatrix3(2, 2), TestMatrix4(2, 2);
	TestMatrix1.setVal(0, 0, (long long)1e18);
	TestMatrix1.setVal(0, 1, (long long)2e7);
	TestMatrix1.setVal(1, 0, 3);
	TestMatrix1.setVal(1, 1, -(long long)5e13);
	
	TestMatrix2.setVal(0, 0, (long long)1e18);
	TestMatrix2.setVal(0, 1, -(long long)4e7);
	TestMatrix2.setVal(1, 0, -3);
	TestMatrix2.setVal(1, 1, (long long)5e13);
	
	TestMatrix3.setVal(0, 0, (long long)2e18);
	TestMatrix3.setVal(0, 1, -(long long)2e7);
	TestMatrix3.setVal(1, 0, 0);
	TestMatrix3.setVal(1, 1, 0);
	
	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.r_size(); i++) {
		for(int j = 0; j < TestMatrix4.c_size(); j++) {
			//checking overflow
			BOOST_CHECK( (unsigned long long) (fabs( ( double ) TestMatrix1(i, j) + (double)TestMatrix2(i, j))) <= LLONG_MAX);
			//addition result checking
			BOOST_CHECK(TestMatrix4(i, j) == TestMatrix3(i, j));
		}
	}
}

BOOST_AUTO_TEST_CASE(Matrix_addition_float) {
	
	Matrix<float> TestMatrix1(2, 2), TestMatrix2(2, 2), TestMatrix3(2, 2), TestMatrix4(2, 2);
	TestMatrix1.setVal(0, 0, 1.3);
	TestMatrix1.setVal(0, 1, 2.567);
	TestMatrix1.setVal(1, 0, 3);
	TestMatrix1.setVal(1, 1, -4.789);
	
	TestMatrix2.setVal(0, 0, 2.56);
	TestMatrix2.setVal(0, 1, 3.678);
	TestMatrix2.setVal(1, 0, -3);
	TestMatrix2.setVal(1, 1, -2.211);
	
	TestMatrix3.setVal(0, 0, 3.86);
	TestMatrix3.setVal(0, 1, 6.245);
	TestMatrix3.setVal(1, 0, 0);
	TestMatrix3.setVal(1, 1, -7);
	
	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.r_size(); i++) {
		for(int j = 0; j < TestMatrix4.c_size(); j++) {
			//checking overflow
			BOOST_CHECK( (float) (fabs( ( double ) TestMatrix1(i, j) + (double)TestMatrix2(i, j))) <= (3.40282347e+38F));
			//addition result checking
			BOOST_CHECK(TestMatrix4(i, j) == TestMatrix3(i, j));
		}
	}
}

BOOST_AUTO_TEST_CASE (Matrix_addition_complex) {

	Matrix<std::complex<double> > TestMatrix1(1, 2), TestMatrix2(1, 2), TestMatrix3(1, 2), TestMatrix4(1, 2);
	
	TestMatrix1.setVal(0, 0, std::complex<double>(1.2, 1));
	TestMatrix1.setVal(0, 1, std::complex<double>(1.3, 1));
	
	TestMatrix2.setVal(0, 0, std::complex<double>(9.2, -1));
	TestMatrix2.setVal(0, 1, std::complex<double>(1.1, 2.9));

	TestMatrix3.setVal(0, 0, std::complex<double>(10.4, 0));
	TestMatrix3.setVal(0, 1, std::complex<double>(2.4, 3.9));

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.r_size(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.c_size(); j++) {
			//taking a precision error of 1e-13
			BOOST_CHECK(fabs(TestMatrix4(i, j).real() - TestMatrix3(i, j).real()) <= 1e-13);
			BOOST_CHECK(fabs(TestMatrix4(i, j).imag() - TestMatrix3(i, j).imag()) <= 1e-13);
		}
	}	
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_multiplication)
BOOST_AUTO_TEST_CASE(Matrix_multiplication_int) {
	
	Matrix<int> TestMatrix1(2, 2), TestMatrix2(2, 3), TestMatrix3(2, 3), TestMatrix4(2, 3);
	TestMatrix1.setVal(0, 0, 1);
	TestMatrix1.setVal(0, 1, 3);
	TestMatrix1.setVal(1, 0, 1);
	TestMatrix1.setVal(1, 1, -1);
	
	TestMatrix2.setVal(0, 0, 1);
	TestMatrix2.setVal(0, 1, 0);
	TestMatrix2.setVal(0, 2,-7);
	TestMatrix2.setVal(1, 0, 1);
	TestMatrix2.setVal(1, 1, 0);
	TestMatrix2.setVal(1, 2,-7);

	TestMatrix3.setVal(0, 0, 4);
	TestMatrix3.setVal(0, 1, 0);
	TestMatrix3.setVal(0, 2, -28);
	TestMatrix3.setVal(1, 0, 0);
	TestMatrix3.setVal(1, 1, 0);
	TestMatrix3.setVal(1, 2, 0);

	TestMatrix4 = TestMatrix1 * TestMatrix2;
	
	for(unsigned int i = 0; i < TestMatrix4.r_size(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.c_size(); j++) {
			//computed value check
			BOOST_CHECK(TestMatrix4(i, j) == TestMatrix3(i, j));
		}
	}
}

BOOST_AUTO_TEST_CASE (Matrix_Multiplication_complex) {

	Matrix< std::complex<unsigned int > > TestMatrix1(2, 2), TestMatrix2(2, 2), TestMatrix3(2, 2), TestMatrix4(2, 2);
	TestMatrix1.setVal(0, 0, std::complex<int>(1, 1));
	TestMatrix1.setVal(0, 1, std::complex<int>(2, 3));
	TestMatrix1.setVal(1, 0, std::complex<int>(1, -1));
	TestMatrix1.setVal(1, 1, std::complex<int>(2, -4));
	
	TestMatrix2.setVal(0, 0, std::complex<int>(0, 1));
	TestMatrix2.setVal(0, 1, std::complex<int>(0, -7));
	TestMatrix2.setVal(1, 0, std::complex<int>(0, 8));
	TestMatrix2.setVal(1, 1, std::complex<int>(9, 3));

	TestMatrix3.setVal(0, 0, std::complex<int>(-25, 17));
	TestMatrix3.setVal(0, 1, std::complex<int>(16, 26));
	TestMatrix3.setVal(1, 0, std::complex<int>(33, 17));
	TestMatrix3.setVal(1, 1, std::complex<int>(23, -37));

	
	TestMatrix4 = TestMatrix1 * TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.r_size(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.c_size(); j++) {
			//computed value check
			BOOST_CHECK(TestMatrix4(i, j) == TestMatrix3(i, j));
		}
	}
}
BOOST_AUTO_TEST_SUITE_END()

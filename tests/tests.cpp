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

BOOST_AUTO_TEST_SUITE(Constructor)
BOOST_AUTO_TEST_CASE (constructors_working) {
	Matrix<int> TestMatrix1;
	BOOST_CHECK(TestMatrix1.r_size == 0);
}
BOOST_AUTO_TEST_SUITE_END()

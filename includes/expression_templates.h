//////////////////
// Pranay Gupta //
//   IIIT HYD   //
//////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cassert>

//expression class definition
template<typename E>
class MatExp {
	public:
		double operator()(size_t i, size_t j) const{
			return static_cast<E const&>(*this)(i, j);
		} 
		size_t r_size() const {
			return static_cast<E const&>(*this).r_size;
		}
		size_t c_size() const {
			return static_cast<E const&>(*this).c_size;
		}

		operator E& () { return static_cast<E&>(*this); }
		operator const E& () const { return static_cast<E&>(*this); }
};

//matrix class definition
template<typename T>
class Matrix : public MatExp<Matrix<T> > {
	
	public:
		std::vector<std::vector<T> > mat;
		size_t r_size;
		size_t c_size;

		T operator()(size_t i, size_t j) const{ 
			return mat[i][j];
		}

		T &operator()(size_t i, size_t j) {
			return mat[i][j];
		}

		std::vector<T> operator[](size_t i) {
			return mat[i];
		}

		Matrix(void) {}
 	
 		// matrix defn with size
	 	Matrix(std::size_t r, std::size_t c) : r_size(r), c_size(c) {
			mat.resize(r_size);
	 		for(std::size_t i = 0; i<r_size; i++) {
	 			mat[i].resize(c_size);
	 		}	
	 	}
	 	
	 	//matrix defn with size and initia value
	 	Matrix(std::size_t r, std::size_t c, T val) : r_size(r), c_size(c) {
	 		mat.resize(r_size);
	 		for(std::size_t i = 0; i<r_size; i++) {
	 			mat[i].resize(c_size);
	 			for (std::size_t j = 0; j<c_size; j++) {
	 				mat[i][j] = val;
	 			}
	 		}
		}

		Matrix(std::vector< std::vector<T> > mat) : r_size(mat.r_size), c_size(mat.c_size), mat(mat) {}

		template<typename E>
		Matrix(MatExp<E> const& matexp) : r_size(matexp.r_size()), c_size(matexp.c_size()) {
			mat.resize(r_size);
			for(size_t i = 0; i<r_size; i++) {
				mat[i].resize(c_size);
				for(size_t j = 0; j<c_size; j++) {
					mat[i][j] = matexp(i, j);
				}
			}
		}

		template<typename E>
		Matrix operator = (MatExp<E> const& matexp) {
			size_t r_size = matexp.r_size();
			size_t c_size = matexp.c_size();
			mat.resize(r_size);
			for(size_t i = 0; i<r_size; i++) {
				mat[i].resize(c_size);
				for(size_t j = 0; j<c_size; j++) {
					mat[i][j] = matexp(i, j);
				}
			}
			return *(this);
		}
};

// matrix sum class definition
template<typename E1, typename E2> 	
class MatSum : public MatExp<MatSum<E1, E2> > {
	E1 const& _u;
	E2 const& _v;
public:
	MatSum(E1 const& u, E2 const& v) : _u(u) , _v(v) {
		assert(u.r_size == v.r_size && u.c_size == v.c_size);
	} 
	
	double operator()(size_t i, size_t j) const{
			return _u(i, j) + _v(i, j);
	}
	
	size_t r_size = _u.r_size;
	size_t c_size = _u.c_size;
};

//matrix mult class definition
template<typename E1, typename E2> 	
class MatMult : public MatExp<MatMult<E1, E2> > {
	E1 const& _u;
	E2 const& _v;
public:
	MatMult(E1 const& u, E2 const& v) : _u(u) , _v(v) {
		assert(u.c_size == v.r_size);
	} 
	
	double operator()(size_t idx1, size_t idx2) const{
		double sum = 0;
		for (int i = 0; i<_u.c_size; i++) {
			sum += _u(idx1, i)*_v(i, idx2);
		}
		return sum; 
	}
	
	size_t r_size = _u.r_size;
	size_t c_size = _v.c_size;
};


template <typename E1, typename E2>
MatSum<E1,E2> const operator+(E1 const& u, E2 const& v) {
	return MatSum<E1, E2>(u, v);
}


template <typename E1, typename E2>
MatMult<E1,E2> const operator*(E1 const& u, E2 const& v) {
	return MatMult<E1, E2>(u, v);
}


#endif
//////////////////
// Pranay Gupta //
//   IIIT HYD   //
//////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cassert>
#include <typeinfo>
//expression class definition

template<typename E>
class MatExp {
	public:
		
		inline E &self(void) { return static_cast<E*>(this); }
		inline const E &self(void) const { return *static_cast<const E*>(this); }
};

template<typename E1, typename E2> 	
class MatSum : public MatExp<MatSum<E1, E2> > {
	E1 const& _u;
	E2 const& _v;

public:
	MatSum(E1 const& u, E2 const& v) : _u(u) , _v(v) {
		assert(u.r_size() == v.r_size() && u.c_size() == v.c_size());
	} 
	
	typeof(_u(0,0)) operator()(size_t i, size_t j) const{
		return _u(i, j) + _v(i, j);
	}
	
	size_t r_size() const{ 
		return _u.r_size();
	}

	size_t c_size() const{ 
		return _u.c_size();
	}	

};

//matrix mult class definition
template<typename E1, typename E2> 	
class MatMult : public MatExp<MatMult<E1, E2> > {
	E1 const& _u;
	E2 const& _v;

public:
	MatMult(E1 const& u, E2 const& v) : _u(u) , _v(v) {
		assert(u.c_size() == v.r_size());
	} 
	
	typeof(_u(0, 0)) operator()(size_t idx1, size_t idx2) const{
		typeof(_u(0, 0)) sum = 0;
		for (int i = 0; i<_u.c_size(); i++) {
			sum += _u(idx1, i)*_v(i, idx2);
		}
		return sum; 
	}
	
	size_t r_size() const{ 
		return _u.r_size();
	}

	size_t c_size() const{ 
		return _v.c_size();
	}

};

//matrix class definition
template<typename T>
class Matrix : public MatExp<Matrix<T> > {
	
	size_t row_size;
	size_t col_size;

	public:
		std::vector<std::vector<T> > mat;
		
		T operator()(size_t i, size_t j) const{ 
			return mat[i][j];
		}

		T &operator()(size_t i, size_t j) {
			return mat[i][j];
		}

		size_t r_size() const {
			return row_size;
		}

		size_t c_size() const {
			return col_size;
		}

		void setR_size(size_t rowsize) {
			row_size = rowsize;
		}

		void setC_size(size_t colsize) {
			col_size = colsize;
		}
		
		void setVal(size_t i, size_t j, T val) {
			assert(i <= row_size-1 && i>=0);
			assert(j <= col_size-1 && j>=0);
			mat[i][j] = val;
		}

		std::vector<T> operator[](size_t i) {
			return mat[i];
		}

		Matrix(void) : row_size(0), col_size(0) {}
 	
 		// matrix defn with size
	 	Matrix(std::size_t r, std::size_t c) : row_size(r), col_size(c) {
			mat.resize(row_size);
	 		for(std::size_t i = 0; i<row_size; i++) {
	 			mat[i].resize(col_size);
	 		}	
	 	}
	 	
	 	//matrix defn with size and initia value
	 	Matrix(std::size_t r, std::size_t c, T val) : row_size(r), col_size(c) {
	 		mat.resize(row_size);
	 		for(std::size_t i = 0; i<row_size; i++) {
	 			mat[i].resize(col_size);
	 			for (std::size_t j = 0; j<col_size; j++) {
	 				mat[i][j] = val;
	 			}
	 		}
		}

		Matrix(std::vector< std::vector<T> > mat) : row_size(mat.r_size), col_size(mat.c_size), mat(mat) {}

		template<typename E1, typename E2>
		Matrix(MatSum<E1, E2> const& matsum) : row_size(matsum.r_size()), col_size(matsum.c_size()) {
			mat.resize(row_size);
			for(size_t i = 0; i<row_size; i++) {
				mat[i].resize(col_size);
				for(size_t j = 0; j<col_size; j++) {
					mat[i][j] = matsum(i, j);
				}
			}
		}

		template<typename E1, typename E2>
		Matrix(MatMult<E1, E2> const& matmult) : row_size(matmult.r_size()), col_size(matmult.c_size()) {
			mat.resize(row_size);
			for(size_t i = 0; i<row_size; i++) {
				mat[i].resize(col_size);
				for(size_t j = 0; j<col_size; j++) {
					mat[i][j] = matmult(i, j);
				}
			}
		}

		template<typename E1, typename E2>
		Matrix operator = (MatSum<E1, E2> const& matadd) {
			size_t rsize = matadd.r_size();
			size_t csize = matadd.c_size();
			
			assert(rsize == this->r_size());
			assert(csize == this->c_size());
			
			for(size_t i = 0; i<rsize; i++) {
				for(size_t j = 0; j<csize; j++) {
					mat[i][j] = (T) matadd(i, j);
				}
			}
			return *(this);
		}

		template<typename E1, typename E2>
		Matrix operator = (MatMult<E1, E2> const& matmult) {
			size_t rsize = matmult.r_size();
			size_t csize = matmult.c_size();
			
			assert(rsize == this->r_size());
			assert(csize == this->c_size());
			
			for(size_t i = 0; i<rsize; i++) {
				for(size_t j = 0; j<csize; j++) {
					mat[i][j] = (T) matmult(i, j);
				}
			}
			return *(this);
		}

		template<typename E1>
		Matrix operator += (MatExp<E1> const& matadd) {
			
			const E1& x = matadd.self();
			assert(x.r_size() == this->r_size());
			assert(x.c_size() == this->c_size());
			
			for(size_t i = 0; i<this->r_size() ;i++) {
				for(size_t j = 0; j<this->c_size() ;j++) {
					mat[i][j] += x.mat[i][j];
				} 
			}
			return *(this);
		}

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
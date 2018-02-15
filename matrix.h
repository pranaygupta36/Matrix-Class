//////////////////
// Pranay Gupta //
//   IIIT HYD   //
//////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

template< class T>
class Matrix;

template< class T> 
class MatrixAdd {
	public:	
		const Matrix<T> &mat1;
		const Matrix<T> &mat2;
		MatrixAdd(const Matrix<T> &mat1, const Matrix<T> &mat2) : mat1(mat1), mat2(mat2) {}	

	T operator()(size_t idx1, size_t idx2) const{
		return mat1.mat[idx1][idx2] + mat2.mat[idx1][idx2]; 
	}
};

template< class T> 
class MatrixMult {
	public:	
		const Matrix<T> &mat1;
		const Matrix<T> &mat2;
		MatrixMult(const Matrix<T> &mat1, const Matrix<T> &mat2) : mat1(mat1), mat2(mat2) {}	

	// to be changed.
	T operator()(size_t idx1, size_t idx2) const{
		T sum;
		for (int i=0;i<mat1.r_size;i++) {
			sum += mat1.mat[idx1][i]*mat2.mat[i][idx2];
		}		
		return sum; 
	}
};

template< class T> 
class Matrix {
 public:
 	int r_size, c_size;
 	std::vector< std::vector <T> > mat;
 	// matrix defn
 	Matrix(void) {}
 	
 	// matrix defn with size
 	Matrix(std::size_t r, std::size_t c) : r_size(r), c_size(c) {
		mat.resize(r_size);
 		for(std::size_t i = 0; i<r_size; i++) {
 			mat[i].resize(c_size);
 		}	
 	}
 	
 	//matrix defn with size and initia value
 	Matrix(std::size_t r, std::size_t c, double val) : r_size(r), c_size(c) {
 		mat.resize(r_size);
 		for(std::size_t i = 0; i<r_size; i++) {
 			mat[i].resize(c_size);
 			for (std::size_t j = 0; j<c_size; j++) {
 				mat[i][j] = val;
 			}
 		}
	}

	Matrix(std::vector< std::vector<T> > mat) : r_size(mat.r_size), c_size(mat.c_size), mat(mat) {}

 	// size of matrix
 	std::vector<int> size() const{
 		std::vector<int> ans;
 		ans.push_back(r_size);
 		ans.push_back(c_size);
 		return ans;
 	} 

 	//index operators
	T operator()(const int i, const int j) {
		return mat[i][j];	
	}

	inline Matrix &operator=(const MatrixAdd<T> ans) {
		r_size = ans.mat1.r_size;
		c_size = ans.mat2.c_size;

		for(int i = 0; i<r_size; i++) {
			for(int j = 0; j<c_size; j++) {
				mat[i][j] = ans.mat1.mat[i][j] + ans.mat2.mat[i][j];
			}
		} 
		return *this;
	}

	//chnages to be done
	inline Matrix &operator=(const MatrixMult<T> ans) {
		r_size = ans.mat1.r_size;
		c_size = ans.mat2.c_size;

		for(int i = 0; i<r_size; i++) {
			for(int j = 0; j<c_size; j++) {
				mat[i][j] = ans.mat1.mat[i][j] + ans.mat2.mat[i][j];
			}
		} 
		return *this;
	}

};

template< class T> 
inline MatrixAdd<T> operator+(const Matrix<T> &mat1, const Matrix<T> &mat2) {
	return MatrixAdd<T>(mat1,mat2);
}

template< class T> 
inline MatrixMult<T> operator*(const Matrix<T> &mat1, const Matrix<T> &mat2) {
	if (mat1.r_size == mat2.c_size) return MatrixMult<T>(mat1,mat2);
	else std::cout<<"Multiplication is not posiible"<<std::endl;
}




#endif
#pragma once
template<class T>
class DiagonalMatrix {
public:
	DiagonalMatrix(int size = 10)
	{
		n = size; d = new T[n];
	}
	~DiagonalMatrix() { delete[] d; } // 析构函数
	DiagonalMatrix< T > &
		Store(const T& x, int i, int j);
	T Retrieve(int i, int j) const;
private:
	int n; //矩阵维数
	T *d; // 存储对角元素的一维数组
};

template<class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::Store(const T& x, int i, int j)
{
	// 把x存为D ( i , j ) .
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	if (i != j && x != 0) throw MustBeZero();
	if (i == j) d[i - 1] = x;
	return *this;
};

template <class T>
T DiagonalMatrix<T>::Retrieve(int i, int j)  const
{
	// 返回D ( i , j ) .
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	if (i == j) return d[i - 1];
	else return 0;
}
#pragma once

//下三角矩阵
template<class T>
class LowerMatrix {
public:
	LowerMatrix(int size = 10)
	{
		n = size; t = new T[n*(n + 1) / 2];
	}
	~LowerMatrix() { delete[] t; }
	LowerMatrix<T>& Store(const T& x, int i, int j);
	T Retrieve(int i, int j) const;
private:
	int n; //矩阵维数
	T *t; //存储下三角矩阵的一维数组
};

template<class T>
LowerMatrix<T>& LowerMatrix<T>::Store(const T& x, int i, int j)
{
	//把x存为L ( i , j ) .
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	//当且仅当i ≥ j 时(i,j) 位于下三角
	if (i >= j) t[i*(i - 1) / 2 + j - 1] = x;
	else if (x != 0) throw MustBeZero();
	return *this;
};

template <class T>
T LowerMatrix<T>::Retrieve(int i, int j) const
{
	//返回L(i, j) .
		if (i < 1 || j < 1 || i > n || j > n)
			throw OutOfBounds();
	//当且仅当i ≥   j 时(i,j) 位于下三角
	if (i >= j) return t[i*(i - 1) / 2 + j - 1];
	else return 0;
};
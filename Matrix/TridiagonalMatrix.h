#pragma once
template<class T>
class TridiagonalMatrix {
public:
	TridiagonalMatrix(int size = 10)
	{
		n = size; t = new T[3 * n - 2];
	}
	~TridiagonalMatrix() { delete[] t; }
	TridiagonalMatrix<T>& Store(const T& x, int i, int j);
	T Retrieve(int i, int j) const;
private:
	int n; //矩阵维数
	T *t; //存储三对角矩阵的一维数组
};

template<class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::Store(const T& x, int i, int j)
{
	// 把x存为T ( i , j )
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	switch (i - j)
	{
	case 1: //低对角线
		t[i - 2] = x; break;  //减去2是考虑到这里是用数组来表示，数组下标从0开始。而i、j从1开始。
	case 0: //主对角线
		t[n + i - 2] = x; break;
	case -1: //高对角线
		t[2 * n + i - 2] = x; break;
	default: if (x != 0) throw MustBeZero();
	}
	return *this;
};

template <class T>
T TridiagonalMatrix<T>::Retrieve(int i, int j) const
{
	// 返回T ( i , j )
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	switch (i - j)
	{
	case 1: //低对角线
		return t[i - 2];
	case 0: //主对角线
		return t[n + i - 2];
	case -1: //高对角线
		return t[2 * n + i - 2];
	default: return 0;
	}
}
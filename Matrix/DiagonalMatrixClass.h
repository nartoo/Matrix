#pragma once
template<class T>
class DiagonalMatrix {
public:
	DiagonalMatrix(int size = 10)
	{
		n = size; d = new T[n];
	}
	~DiagonalMatrix() { delete[] d; } // ��������
	DiagonalMatrix< T > &
		Store(const T& x, int i, int j);
	T Retrieve(int i, int j) const;
private:
	int n; //����ά��
	T *d; // �洢�Խ�Ԫ�ص�һά����
};

template<class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::Store(const T& x, int i, int j)
{
	// ��x��ΪD ( i , j ) .
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	if (i != j && x != 0) throw MustBeZero();
	if (i == j) d[i - 1] = x;
	return *this;
};

template <class T>
T DiagonalMatrix<T>::Retrieve(int i, int j)  const
{
	// ����D ( i , j ) .
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	if (i == j) return d[i - 1];
	else return 0;
}
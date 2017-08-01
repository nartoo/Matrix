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
	int n; //����ά��
	T *t; //�洢���ԽǾ����һά����
};

template<class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::Store(const T& x, int i, int j)
{
	// ��x��ΪT ( i , j )
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	switch (i - j)
	{
	case 1: //�ͶԽ���
		t[i - 2] = x; break;  //��ȥ2�ǿ��ǵ�����������������ʾ�������±��0��ʼ����i��j��1��ʼ��
	case 0: //���Խ���
		t[n + i - 2] = x; break;
	case -1: //�߶Խ���
		t[2 * n + i - 2] = x; break;
	default: if (x != 0) throw MustBeZero();
	}
	return *this;
};

template <class T>
T TridiagonalMatrix<T>::Retrieve(int i, int j) const
{
	// ����T ( i , j )
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	switch (i - j)
	{
	case 1: //�ͶԽ���
		return t[i - 2];
	case 0: //���Խ���
		return t[n + i - 2];
	case -1: //�߶Խ���
		return t[2 * n + i - 2];
	default: return 0;
	}
}
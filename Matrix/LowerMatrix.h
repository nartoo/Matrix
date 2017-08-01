#pragma once

//�����Ǿ���
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
	int n; //����ά��
	T *t; //�洢�����Ǿ����һά����
};

template<class T>
LowerMatrix<T>& LowerMatrix<T>::Store(const T& x, int i, int j)
{
	//��x��ΪL ( i , j ) .
	if (i < 1 || j < 1 || i > n || j > n)
		throw OutOfBounds();
	//���ҽ���i �� j ʱ(i,j) λ��������
	if (i >= j) t[i*(i - 1) / 2 + j - 1] = x;
	else if (x != 0) throw MustBeZero();
	return *this;
};

template <class T>
T LowerMatrix<T>::Retrieve(int i, int j) const
{
	//����L(i, j) .
		if (i < 1 || j < 1 || i > n || j > n)
			throw OutOfBounds();
	//���ҽ���i ��   j ʱ(i,j) λ��������
	if (i >= j) return t[i*(i - 1) / 2 + j - 1];
	else return 0;
};
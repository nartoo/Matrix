#pragma once
template <class T>
class Term
{
	friend class SparseMatrix<T>;
private:
	int row, col;
	T value;
};

template<class T>
class SparseMatrix
{
	friend ostream& operator<< (ostream&, const SparseMatrix<T>&);
	friend istream& operator>> (istream&, SparseMatrix<T>&);
public:
	SparseMatrix(int maxTerms = 10);
	~SparseMatrix() { delete[] a; }
	void Transpose(SparseMatrix<T> &b) const;
	void Add(const SparseMatrix<T> &b, SparseMatrix<T> &c) const;
private:
	void Append(const Term<T>& t);
	int rows, cols; //����ά��
	int terms; // ��0Ԫ����Ŀ
	Term<T> *a; // �洢��0Ԫ�ص�����
	int MaxTerms; // ����a�Ĵ�С;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
	// ϡ�����Ĺ��캯��
	if (maxTerms < 1) throw BadInitializers();
	M a x Terms = maxTerms;
	a = new Term<T>[MaxTerms];
	terms = rows = cols = 0;
};

// ����<<
template <class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& x)
{
	// ��*this ���������
	// ������������
	out << "rows = " << x.rows << " columns = " << x.cols << endl;
	out << "nonzero terms = " << x.terms << endl;
	// �����0Ԫ�أ�ÿ��1��
	for (int i = 0; i < x.terms; i++)
		out << "a(" << x.a[i].row << ',' << x.a[i].col << ") = " << x.a[i].value << endl;
	return out;
};

// ����>>
template<class T>
istream& operator >> (istream& in, SparseMatrix<T>& x)
{
	// ����һ��ϡ�����
	// ������������
	cout << "Enter number of rows, columns, and terms" << endl;
	in >> x.rows >> x.cols >> x.terms;
	if (x.terms > x.MaxTerms) throw NoMem();
	// �������Ԫ��
	for (int i = 0; i < x.terms; i++) {
		cout << "Enter row, column, and value of term " << (i + 1) << endl; //(i+1)��ǵڼ���Ԫ�أ���1��ʼ
		in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
	}
	return in;
};

//ת��һ��ϡ�����
template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T> &b) const
{
	// ��*this��ת�ý������b
	// ȷ��b���㹻�Ŀռ�
	if (terms > b.MaxTerms) throw NoMem();
	// ����ת������
	b.cols = rows;
	b.rows = cols;
	b.terms = terms;
	// ��ʼ��
	int *ColSize, *RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[cols + 1];  //��Ϊת�þ�����У�Ҳ����ԭ������У�Ӧ����cols
	// ����*thisÿһ�еķ�0Ԫ����
	for (int i = 1; i <= cols; i++) // ��ʼ��
		ColSize[i] = 0;  //ԭ�����е�i�У�ת�þ���ĵ�i�У��еķ�0Ԫ��������ʼ��.row���У�col���С�
	for (int i = 0; i < terms; i++)
		ColSize[a[i].col]++; //ͳ�����о�����ͬcol��ԭ�������λ�ã���Ԫ��
	// ����b��ÿһ�е���ʼ�㣨b��ÿһ���׸���0Ԫ�ص���������λ�ã���0��ʼ��
	RowNext[1] = 0;//��ת�þ����һ��û�з�0Ԫ�أ���Rownext[2]=0
	for (int i = 2; i <= cols; i++)
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	// ִ��ת�ò���
	for (int i = 0; i < terms; i++) //����i���������������
	{
		int j = RowNext[a[i].col]++; // ��b�е�λ�ã������һ��������ԭ����ͬһ���еĵڶ�����0Ԫ�أ���
									 //RowNext[a[i].col]���Ѿ�����һ������1�˵ġ���++��
		b.a[j].row = a[i].col;
		b.a[j].col = a[i].row;
		b.a[j].value = a[i].value;
	}
}

//���һ����0Ԫ��
template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)
{
	// ��һ����0Ԫ��t��ӵ�*this֮��
	if (terms >= MaxTerms) throw NoMem();
	a[terms] = t;
	terms++;
}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &b, SparseMatrix<T> &c) const
{
	// ����c = (*this) + b.
	// ��֤������
	if (rows != b.rows || cols != b.cols)
		throw SizeMismatch(); // �������
							  // ���ý������c������
	c.rows = rows;
	c.cols = cols;
	c.terms = 0; // ��ֵ
				 // ����*this ��b���α�
	int ct = 0, cb = 0;
	// ��*this ��b �б���
	while (ct < terms && cb < b.terms)
	{
		// ÿһ��Ԫ�ص���������
		int indt = a[ct].(row - 1) * cols + a[ct].col;
		int indb = b.a[cb].(row - 1) * cols + b.a[cb].col;
		if (indt < indb) 
		{
			// b ��Ԫ���ں�
			c.Append(a[ct]);
			ct++;
		} // *this����һ��Ԫ��
		else 
		{
			if (indt == indb) 
			{
				// λ����ͬ
				// �����Ͳ�Ϊ0ʱ����ӵ�c��
					if (a[ct].value + b.a[cb].value) 
					{
						Term<T> t;
						t.row = a[ct].row;
						t.col = a[ct].col;
						t.value = a[ct].value + b.a[cb].value;
						c.Append(t);
					}
				ct++; cb++;
			} // *this ��b����һ��Ԫ��
			else { c.Append(b.a[cb]); cb++; } // b����һ��Ԫ��
		}
	}
	// ����ʣ��Ԫ�أ������������ֻ��һ���ܹ�ִ�С�
	for (; ct < terms; ct++)
		c.Append(a[ct]);
	for (; cb < b.terms; cb++)
		c.Append(b.a[cb]);
}
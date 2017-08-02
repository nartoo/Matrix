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
	int rows, cols; //矩阵维数
	int terms; // 非0元素数目
	Term<T> *a; // 存储非0元素的数组
	int MaxTerms; // 数组a的大小;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
	// 稀疏矩阵的构造函数
	if (maxTerms < 1) throw BadInitializers();
	M a x Terms = maxTerms;
	a = new Term<T>[MaxTerms];
	terms = rows = cols = 0;
};

// 重载<<
template <class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& x)
{
	// 把*this 送至输出流
	// 输出矩阵的特征
	out << "rows = " << x.rows << " columns = " << x.cols << endl;
	out << "nonzero terms = " << x.terms << endl;
	// 输出非0元素，每行1个
	for (int i = 0; i < x.terms; i++)
		out << "a(" << x.a[i].row << ',' << x.a[i].col << ") = " << x.a[i].value << endl;
	return out;
};

// 重载>>
template<class T>
istream& operator >> (istream& in, SparseMatrix<T>& x)
{
	// 输入一个稀疏矩阵
	// 输入矩阵的特征
	cout << "Enter number of rows, columns, and terms" << endl;
	in >> x.rows >> x.cols >> x.terms;
	if (x.terms > x.MaxTerms) throw NoMem();
	// 输入矩阵元素
	for (int i = 0; i < x.terms; i++) {
		cout << "Enter row, column, and value of term " << (i + 1) << endl; //(i+1)标记第几个元素，从1开始
		in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
	}
	return in;
};

//转置一个稀疏矩阵
template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T> &b) const
{
	// 把*this的转置结果送入b
	// 确信b有足够的空间
	if (terms > b.MaxTerms) throw NoMem();
	// 设置转置特征
	b.cols = rows;
	b.rows = cols;
	b.terms = terms;
	// 初始化
	int *ColSize, *RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[cols + 1];  //此为转置矩阵的行，也就是原矩阵的列，应该是cols
	// 计算*this每一列的非0元素数
	for (int i = 1; i <= cols; i++) // 初始化
		ColSize[i] = 0;  //原矩阵中第i列（转置矩阵的第i行）中的非0元素数，初始化.row是行，col是列。
	for (int i = 0; i < terms; i++)
		ColSize[a[i].col]++; //统计所有具有相同col（原矩阵的列位置）的元素
	// 给出b中每一行的起始点（b中每一行首个非0元素的行主次序位置，从0开始）
	RowNext[1] = 0;//若转置矩阵第一行没有非0元素，则Rownext[2]=0
	for (int i = 2; i <= cols; i++)
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	// 执行转置操作
	for (int i = 0; i < terms; i++) //这里i按行主次序递增。
	{
		int j = RowNext[a[i].col]++; // 在b中的位置，如果下一次遇到（原矩阵）同一列中的第二个非0元素，其
									 //RowNext[a[i].col]是已经在上一次中增1了的。（++）
		b.a[j].row = a[i].col;
		b.a[j].col = a[i].row;
		b.a[j].value = a[i].value;
	}
}

//添加一个非0元素
template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)
{
	// 把一个非0元素t添加到*this之中
	if (terms >= MaxTerms) throw NoMem();
	a[terms] = t;
	terms++;
}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &b, SparseMatrix<T> &c) const
{
	// 计算c = (*this) + b.
	// 验证可行性
	if (rows != b.rows || cols != b.cols)
		throw SizeMismatch(); // 不能相加
							  // 设置结果矩阵c的特征
	c.rows = rows;
	c.cols = cols;
	c.terms = 0; // 初值
				 // 定义*this 和b的游标
	int ct = 0, cb = 0;
	// 在*this 和b 中遍历
	while (ct < terms && cb < b.terms)
	{
		// 每一个元素的行主索引
		int indt = a[ct].(row - 1) * cols + a[ct].col;
		int indb = b.a[cb].(row - 1) * cols + b.a[cb].col;
		if (indt < indb) 
		{
			// b 的元素在后
			c.Append(a[ct]);
			ct++;
		} // *this的下一个元素
		else 
		{
			if (indt == indb) 
			{
				// 位置相同
				// 仅当和不为0时才添加到c中
					if (a[ct].value + b.a[cb].value) 
					{
						Term<T> t;
						t.row = a[ct].row;
						t.col = a[ct].col;
						t.value = a[ct].value + b.a[cb].value;
						c.Append(t);
					}
				ct++; cb++;
			} // *this 和b的下一个元素
			else { c.Append(b.a[cb]); cb++; } // b的下一个元素
		}
	}
	// 复制剩余元素，以下两种情况只有一种能够执行。
	for (; ct < terms; ct++)
		c.Append(a[ct]);
	for (; cb < b.terms; cb++)
		c.Append(b.a[cb]);
}
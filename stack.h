#pragma once
template <class T>
class stack
{
private:
	T * A;
	size_t s;
	size_t n;
	void resize(size_t);
public:
	stack();
	stack(size_t);
	stack(T *, size_t);
	stack(const stack &);
	stack(stack &&);
	void push(const T &);
	void pop();
	T top();
	void swap(stack &);
	size_t size();
	bool is_empty();
	~stack();
};


template <class T>
stack<T>::stack()
{
	A = new T[16];
	s = 16;
	n = 0;
}


template <class T>
stack<T>::stack(size_t s)
{
	A = new T[s];
	this->s = s;
	n = 0;
}


template <class T>
stack<T>::stack(T * B, size_t s)
{
	A = new T[s];
	this->s = s;
	n = s;
	for (size_t i = 0; i < n; i++)
	{
		A[i] = B[i];
	}
}


template <class T>
stack<T>::stack(const stack &b)
{
	A = new T[b.size];
	s = b.s;
	n = b.n
	for (size_t i = 0; i < n; i++)
	{
		A[i] = b.A[i];
	}
}


template <class T>
stack<T>::stack(stack &&b)
{
	A = b.A;
	s = b.s;
	n = b.n;
	b.A = new T[16];
	b.s = 16;
	b.n = 0;
}


template <class T>
void stack<T>::resize(size_t newsize)
{
	T * B = new T[newsize];
	for (size_t i = 0; i < n; i++)
	{
		B[i] = A[i];
	}
	s = newsize;
	A = B;
}


template <class T>
void stack<T>::push(const T &b)
{
	if (n == s)
	{
		resize(2 * s);
	}
	A[n] = b;
	n++;
}


template <class T>
void stack<T>::pop()
{
	n--;
}


template <class T>
T stack<T>::top()
{
	return A[n - 1];
}


template <class T>
size_t stack<T>::size()
{
	return n;
}


template <class T>
bool stack<T>::is_empty()
{
	return n == 0;
}


template <class T>
stack<T>::~stack()
{
	delete A;
}


template <class T>
void stack<T>::swap(stack<T> &b)
{
	swap(A, b.A);
	swap(s, b.s);
	swap(n, b.n);
}
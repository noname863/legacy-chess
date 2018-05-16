#pragma once//#include <algorithm>
#define NULL 0
//red-black tree
template <class T,bool comp(const T &, const T &)>
class set  
{
private:
	struct node
	{
		node * parent;
		node * left;
		node * right;
		bool is_red;
		T value;

		node();
		node(const node &, node *);
		node(const T &, node *);
		~node();
		node * brother();
	};

	node * root;

	friend bool colour(node *b)
	{
		if (!b)
			return false;
		else
			b->is_red;
	}


	void chcolouradd(node *)
	{
		if (colour(b->left) == colour(b->right) == true)
		{
			b->left->is_red = b->right->is_red = false;
			b->is_red = true;
			if (b->parent->is_red)
				chcolour(b->parent->parent);
		}
		if (colour(b->left))
		{
			b->left->is_red = false;
			b->is_red = true;
			rotateright(b);
		}
		if (colour(b->right))
		{
			b->right->is_red = false;
			b->is_red = true;
			rotateleft(b);
		}
	}
	void chcolourdel(node *)
	{
		if (it->parent->right->is_red)
		{
			it->parent->right->is_red = false;
			it->parent->is_red = true;
			rotateleft(it->parent);
		}
		if (it->parent->left->is_red)
		{
			it->parent->left->is_red = false;
			it->parent->is_red = true;
			rotateright(it->parent);
		}
		node * brother = it->brother();
		if ((!brother->left->colour()) && (!brother->right->colour()))
		{
			if (it->parent->colour() = true)
			{
				it->parent->is_red = false;
				brother->is_red = true;
				return;
			}
			else
			{
				brother->is_red = true;
				chcolourdel(it->parent);
			}
		}
		if (brother == it->parent->right)
		{
			if ((brother->left->colour()) && (!brother->right->colour()))
			{
				brother->left->is_red = false;
				brother->is_red = true;
				rotateright(brother);
				brother = brother->parent;
			}
			if (brother->right->colour())
			{
				brother->right->is_red = false;
				brother->is_red = brother->parent->is_red;
				brother->parent->is_red = false;
				rotateleft(brother->parent);
			}
			return;
		}
		if (brother == it->parent->left)
		{
			if ((!brother->left->colour()) && (brother->right->colour()))
			{
				brother->right->is_red = false;
				brother->is_red = true;
				rotateleft(brother);
				brother = brother->parent;
			}
			if (brother->left->colour())
			{
				brother->left->is_red = false;
				brother->is_red = brother->parent->is_red;
				brother->parent->is_red = false;
				rotateright(brother->parent);
			}
			return;
		}
	}

	node * rotateleft(node *)
	{
		if (!b->parent)
		{
			set<T, comp>::node temp = root->right->left;
			root->right->left = root;
			root->parent = root->right;
			root->right = temp;
			temp->parent = root;
			root = root->parent;
			root->parent = NULL;
			return root;
		}
		set<T, comp>::node p = b->parent;
		if (b == p->left)
		{
			p->left = b->left;
			b->left->parent = p;
		}
		else
		{
			p->right = b->left;
			b->left->parent = p;
		}
		set<T, comp>::node temp = b->right->left;
		b->right->left = b;
		b->parent = b->right;
		b->right = temp;
		temp->parent = b;
		return b->parent;
	}


	node * rotateright(node *)
	{
		if (!b->parent)
		{
			set<T, comp>::node temp = root->left->right;
			root->left->right = root;
			root->parent = root->left;
			root->left = temp;
			temp->parent = root;
			root = root->parent;
			root->parent = NULL;
			return root;
		}
		set<T, comp>::node p = b->parent;
		if (b == p->left)
		{
			p->left = b->right;
			b->right->parent = p;
		}
		else
		{
			p->right = b->right;
			b->right->parent = p;
		}
		set<T, comp>::node temp = b->left->right;
		b->left->right = b;
		b->parent = b->left;
		b->left = temp;
		temp->parent = b;
		return b->parent;
	}
public:
	set();
	set(const T &);
	//set(const T *, size_t);
	set(const set<T, comp> &);
	~set();
	bool is_empty();
	bool add(const T &); //true ���� ��������. false ���� ������� ��� ����
	bool del(const T &); //true ���� ������. false ���� ������ ���
	bool is_in(const T &);
	friend set<T, comp> operator|(const set<T, comp> &, const set<T, comp> &);  //����������� ��������
	friend set<T, comp> operator/(const set<T, comp> &, const set<T, comp> &);  //�������� ��������
	friend set<T, comp> operator^(const set<T, comp> &, const set<T, comp> &);  //�������������� �������� ���������
	friend set<T, comp> operator&(const set<T, comp> &, const set<T, comp> &);  //����������� ��������
	set<T, comp> & operator|=(const set<T, comp> &);
	set<T, comp> & operator/=(const set<T, comp> &);
	set<T, comp> & operator^=(const set<T, comp> &);
	set<T, comp> & operator&=(const set<T, comp> &);
	class iterator
	{
		node * cur;
	public:
		iterator() {}
		iterator(const iterator & b) { cur = b.cur; }
		bool operator==(iterator b) { return cur == b.cur; }
		bool operator!=(iterator b) { return cur != b.cur; }
		iterator & operator++();
		iterator & operator++(int);
		iterator & operator--();
		iterator & operator--(int);
		iterator & operator=(iterator b) { cur = b.cur; return *this; }
		T operator*() { return cur->value }
	};
	friend class set<T,comp>::iterator;
	iterator begin();
	iterator end();
};

template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::node()
{
	parent = left = right = is_red = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::node(const node &b, node * par = NULL)
{
	value = b.value;
	parent = par;
	is_red = b.is_red;
	if (left)
		left = new node(*b.left, this);
	else
		left = NULL;
	if (right)
		right = new node(*b.right, this);
	else
		right = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::node(const T &b, node * par = NULL)
{
	value = b;
	parent = par;
	if (par)
		is_red = true;
	else
		is_red = false;
	right = NULL;
	left = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::~node()
{
	delete right;
	delete left;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::node * set<T, comp>::node::brother()
{
	if (!this->parent)
		return NULL;
	if (this->parent->left = this)
		return this->parent->right;
	else
		return this->parent->left;
}

template <class T, bool comp(const T &, const T &)>
set<T,comp>::set()
{
	root = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(const T &b)
{
	root = new node(b);
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(const set<T, comp> &b)
{
	root = new node(b);
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::~set()
{
	delete root;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::is_empty()
{
	return root = NULL;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::add(const T &b)
{
	if (is_empty())
	{
		root = new node(b);
		return true;
	}
	node * it = root;
	node * p;
	while (it)
	{
		p = it;
		if (it->value == b)
			return false;
		if (comp(it->value, b))
			it = it->left;
		else
			it = it->right;
	}
	it = new node(b, p);
	if (p->is_red)
		chcolouradd(p->parent);
	return true;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::del(const T &b)
{
	node * it = root;
	while (it)
	{
		if (it->value == b)
			break;
		if (comp(it->value, b))
			it = it->left;
		else
			it = it->right;
	}
	if (!it)
		return false;
	node * it2 = it;
	if ((it->right) && (it->left))
	{
		it = it->right;
		while (it = it->left);
		swap(it2->value, it->value);
	}
	if (it->right == it->left)
	{
		if (it->parent->left == it)
			it->parent->left = NULL;
		if (it->parent->right == it)
			it->parent->right = NULL;
		delete it;
		return true;
	}
	if (it->right)
	{
		it2 = it->right;
		it->right->parent = it->parent;
		if (it->parent->right == it)
			it->parent->right = it->right;
		if (it->parent->left == it)
			it->parent->left = it->right;
	}
	if (it->left)
	{
		it2 = it->left;
		it->left->parent = it->parent;
		if (it->parent->right == it)
			it->parent->right = it->left;
		if (it->parent->left == it)
			it->parent->left = it->left;
	}
	if (it->is_red)
	{
		delete it;
		return true;
	}
	delete it;
	it = it2;
	if (it->is_red)
	{
		it->is_red = false;
		return true;
	}
	chcolourdel(it);
	return true;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::is_in(const T &b)
{
	node * it = root;
	while (it)
	{
		if (it->value == b)
			return true;
		if (it->value > b)
			it = it->left;
		else
			it = it->right;
	}
	return false;
}

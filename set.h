#pragma once
#define NULL 0
#include <algorithm>
//red-black tree
//todo операторы с пустыми множествами
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
		node(const node &b, node * par = NULL);
		node(const T b, node * par = NULL)
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
		~node();
		node * brother()
		{
			if (!this->parent)
				return NULL;
			if (this->parent->left == this)
				return this->parent->right;
			else
				return this->parent->left;
		}
	};

	node * root;

	friend bool colour(node *b)
	{
		if (!b)
			return false;
		else
			return b->is_red;
	}
	void chcolouradd(node *b)
	{
		if (!b)
		{
			root->is_red = false;
			return;
		}
		if ((colour(b->left)) && (colour(b->right)))
		{
			b->left->is_red = b->right->is_red = false;
			b->is_red = true;
			if (!b->parent)
			{
				b->is_red = false;
				return;
			}
			if (b->parent->is_red)
				chcolouradd(b->parent->parent);
			return;
		}
		if (colour(b->left))
		{
			if (colour(b->left->right))
				rotateleft(b->left);
			b->left->is_red = false;
			b->is_red = true;
			rotateright(b);
			return;
		}
		if (colour(b->right))
		{
			if (colour(b->right->left))
				rotateright(b->right);
			b->right->is_red = false;
			b->is_red = true;
			rotateleft(b);
			return;
		}
	}
	void chcolourdel(node *it)
	{
		if (!it)
			return;
		if (colour(it->parent->right))
		{
			it->parent->right->is_red = false;
			it->parent->is_red = true;
			rotateleft(it->parent);
			it = it->left->right;
		}
		if (colour(it->parent->left))
		{
			it->parent->left->is_red = false;
			it->parent->is_red = true;
			rotateright(it->parent);
			it = it->right->left;
		}
		//node * brother = it->brother();
		if ((!colour(it->left)) && (!colour(it->right)))
		{
			if (colour(it->parent))
			{
				it->parent->is_red = false;
				it->is_red = true;
				return;
			}
			else
			{
				it->is_red = true;
				chcolourdel(it->parent);
			}
		}
		if (it == it->parent->right)
		{
			if ((colour(it->left)) && (!colour(it->right)))
			{
				it->left->is_red = false;
				it->is_red = true;
				rotateright(it);
				it = it->parent;
			}
			if (colour(it->right))
			{
				it->right->is_red = false;
				it->is_red = it->parent->is_red;
				it->parent->is_red = false;
				rotateleft(it->parent);
			}
			return;
		}
		if (it == it->parent->left)
		{
			if ((!colour(it->left)) && (colour(it->right)))
			{
				it->right->is_red = false;
				it->is_red = true;
				rotateleft(it);
				it = it->parent;
			}
			if (colour(it->left))
			{
				it->left->is_red = false;
				it->is_red = it->parent->is_red;
				it->parent->is_red = false;
				rotateright(it->parent);
			}
			return;
		}
	}
	node * rotateleft(node *b)
	{
		if (!b->parent)
		{
			set<T, comp>::node * temp = root->right->left;
			root->right->left = root;
			root->parent = root->right;
			root->right = temp;
			if (temp)
				temp->parent = root;
			root = root->parent;
			root->parent = NULL;
			return root;
		}
		set<T, comp>::node * p = b->parent;
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
		set<T, comp>::node * temp = b->right->left;
		b->right->left = b;
		b->parent = b->right;
		b->right = temp;
		if (temp)
			temp->parent = b;
		return b->parent;
	}
	node * rotateright(node *b)
	{
		if (!b->parent)
		{
			set<T, comp>::node * temp = root->left->right;
			root->left->right = root;
			root->parent = root->left;
			root->left = temp;
			if (temp)
				temp->parent = root;
			root = root->parent;
			root->parent = NULL;
			return root;
		}
		set<T, comp>::node * p = b->parent;
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
		set<T, comp>::node * temp = b->left->right;
		b->left->right = b;
		b->parent = b->left;
		b->left = temp;
		if (temp)
			temp->parent = b;
		return b->parent;
	}
public:
	set();
	set(const T);
	//set(const T *, size_t);
	set(const set<T, comp> &);
	set(set<T, comp> &&);
	~set();
	bool is_empty();
	bool is_empty() const;
	bool add(const T &); //true если добавлен. false если элемент уже есть
	bool del(const T &); //true если удален. false если такого нет
	bool is_in(const T &);
	friend set<T, comp> operator|(const set<T, comp> &a, const set<T, comp> &b)  //Объединение множеств
	{
		return (set<T, comp>(a) |= b);
	}
	friend set<T, comp> operator/(const set<T, comp> &a, const set<T, comp> &b)  //Разность множеств
	{
		set<T, comp> res;
		iterator it = a.begin();
		for (; it != a.end(); ++it)
		{
			if (!b.is_in(*it))
				res.add(*it);
		}
		if (!b.is_in(*it))
			res.add(*it);
	}
	friend set<T, comp> operator^(const set<T, comp> &a, const set<T, comp> &b)  //Симметрическая разность множества
	{
		return (set<T, comp>(a) ^= b);
	}
	friend set<T, comp> operator&(const set<T, comp> &a, const set<T, comp> &b)  //Пересечение множеств
	{
		iterator it = b.begin();
		set<T, comp> res;
		for (; it != b.end(); ++it)
		{
			if (a.is_in(*it))
				res.add(*it);
		}
		if (a.is_in(*it))
			res.add(*it);
		return res;
	}
	set<T, comp> & operator=(const set<T, comp> &b)
	{
		delete root;
		if (b.root == NULL)
		{
			root = NULL;
			return *this;
		}
		root = new node(*b.root);
		return *this;
	}
	set<T, comp> & operator|=(const set<T, comp> &b)
	{
		if (b.is_empty())
			return *this;
		iterator it = b.begin();
		for (; it != b.end(); ++it)
		{
			add(*it);
		}
		add(*it);
		return *this;
	}
	set<T, comp> & operator/=(const set<T, comp> &b)
	{
		iterator it = b.begin();
		for (; it != b.end(); ++it)
		{
			del(*it);
		}
		del(*it);
		return *this;
	}
	set<T, comp> & operator^=(const set<T, comp> &b)
	{
		iterator it = b.begin();
		for (; it != b.end(); ++it)
		{
			if (!add(*it))
				del(*it);
		}
		if (!add(*it))
			del(*it);
		return *this;
	}
	set<T, comp> & operator&=(const set<T, comp> &b)
	{
		iterator it = b.begin();
		for (; it != b.end(); ++it)
		{
			if (!is_in(*it))
				del(*it);
		}
		if (!is_in(*it))
			del(*it);
		return *this;
	}
	class iterator
	{
		node * cur;
	public:
		iterator() {}
		iterator(const node *b) { cur = (node *)b; }
		iterator(const iterator & b) { cur = b.cur; }
		bool operator==(iterator b) { return cur == b.cur; }
		bool operator!=(iterator b) { return cur != b.cur; }
		iterator & operator++()
		{
			if (cur->right)
			{
				cur = cur->right;
				while (cur->left)
					cur = cur->left;
				return *this;
			}
			while (cur == cur->parent->right)
			{
				cur = cur->parent;
			}
			cur = cur->parent;
			return *this;
		}
		iterator operator++(int)
		{
			node * res = cur;
			if (cur->right)
			{
				cur = cur->right;
				while (cur->left)
					cur = cur->left;
				return *this;
			}
			while (cur == cur->parent->right)
			{
				cur = cur->parent;
			}
			cur = cur->parent;
			return iterator(res);
		}
		iterator & operator--()
		{
			if (cur->left)
			{
				cur = cur->left;
				while (cur->right)
					cur = cur->right;
				return *this;
			}
			while (cur == cur->parent->left)
			{
				cur = cur->parent;
			}
			cur = cur->parent;
			return *this;
		}
		iterator operator--(int)
		{
			node * res = cur;
			if (cur->left)
			{
				cur = cur->left;
				while (cur->right)
					cur = cur->right;
				return *this;
			}
			while (cur == cur->parent->left)
			{
				cur = cur->parent;
			}
			cur = cur->parent;
			return iterator(res);
		}
		iterator & operator=(iterator b) { cur = b.cur; return *this; }
		T operator*() { return cur->value; }
	};
	friend class set<T,comp>::iterator;
	iterator begin() const
	{
		node * it = root;
		while (it->left)
		{
			it = it->left;
		}
		return iterator(it);
	}
	iterator end() const
	{
		node * it = root;
		while (it->right)
		{
			it = it->right;
		}
		return iterator(it);
	}
	iterator begin()
	{
		node * it = root;
		while (it->left)
		{
			it = it->left;
		}
		return iterator(it);
	}
	iterator end()
	{
		node * it = root;
		while (it->right)
		{
			it = it->right;
		}
		return iterator(it);
	}
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
	if (b.left)
		left = new node(*b.left, this);
	else
		left = NULL;
	if (b.right)
		right = new node(*b.right, this);
	else
		right = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::~node()
{
	delete right;
	delete left;
}


template <class T, bool comp(const T &, const T &)>
set<T,comp>::set()
{
	root = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(const T b)
{
	root = new node(b);
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(const set<T, comp> &b)
{
	if (b.root == NULL)
	{
		root = NULL;
		return;
	}
	root = new node(*b.root);
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(set<T, comp> &&b)
{
	root = b.root;
	b.root = NULL;
}

template <class T, bool comp(const T &, const T &)>
set<T, comp>::~set()
{
	delete root;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::is_empty()
{
	return root == NULL;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::is_empty() const
{
	return root == NULL;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::add(const T &b)
{
	if (root == NULL)
	{
		root = new node(b);
		return true;
	}
	node * it = root;
	node * p = root;
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
	if (comp(p->value,b))
		p->left = new node(b, p);
	else
		p->right = new node(b, p);
	if (p->is_red)
		chcolouradd(p->parent);
	return true;
}

template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::del(const T &b)
{
	if (root == NULL)
		return false;
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
	node * brother = it->brother();
	if ((it->right) && (it->left))
	{
		it = it->right;
		while (it->left)
			it = it->left;
		std::swap(it2->value, it->value);
	}
	if (it->right == it->left)
	{
		if (it->parent->left == it)
			it->parent->left = NULL;
		if (it->parent->right == it)
			it->parent->right = NULL;
		if (!colour(it))
			chcolourdel(brother);
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
	it->right = NULL;
	it->left = NULL;
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
	chcolourdel(brother);
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
		if (comp(it->value, b))
			it = it->left;
		else
			it = it->right;
	}
	return false;
}
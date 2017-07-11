//Binary serach tree
#include<iostream>
#include<cstddef>
#include<stdexcept>
#include<functional>

#ifndef RNBST_H
#define RNBST_H
#define rnnull nullptr

template<typename T> class BST;
template<typename T>
class node
{
	friend class BST<T>;
public:
	node(const T& rnval): value(rnval){}
	node(const node<T>& rncopy): value(rncopy.value), p(rnnull), left(rnnull), right(rnnull){}
	bool valid() const
	{return p == rnnull&&left == rnnull&&right == rnnull?false:true;}
private:
	T value;
	node<T>* p = rnnull;
	node<T>* left = rnnull;
	node<T>* right = rnnull;
};
template<typename T>
class BST
{
	typedef std::size_t size_type;
public:
	BST() = default;
	BST(const std::function<bool(const T&, const T&)> rncomp): root(), size(), comp(rncomp){}
	template<typename T1>
	BST(const T1&, const std::function<bool(const T&, const T&)> = std::less<const T&>());
	~BST()
	{
		doDeconstruct(root);
		root = rnnull;
		size = 0;
	}
//structure method
	size_type Size() const
	{return size;}
	node<T> Max() const;
	node<T> Min() const;
	node<T> Predecessor(const node<T>&) const;
	node<T> Successor(const node<T>&) const;
	void Insert(const node<T>&);
	void Delete(const node<T>&);
	void Delete(const T& rnval)
	{Delete(node<T>(rnval));}
//traverse method	
	void MiddleTrav(std::ostream& rnos, const char rnblank = '\n') const
	{doMiddleTrav(rnos, root, rnblank);}
	bool Search(const T& rnval)
	{return (rnsearch(node<T>(rnval)) == rnnull)?false:true;}
private:
	node<T> rncompare(const node<T>*, bool) const;
	node<T>* rnsearch(const node<T>& rnnode);
	void doMiddleTrav(std::ostream&, node<T>*, const char) const;
	void doDeconstruct(node<T>*);

	node<T>* root = rnnull;
	size_type size = 0;
	std::function<bool(const T&, const T&)> comp = std::less<const T&>();
};
template<typename T>
template<typename T1>
BST<T>::BST(const T1& rncontainer, const std::function<bool(const T&, const T&)> rncomp): root(rnnull), size(0), comp(rncomp)
{
	for(auto rnindex: rncontainer)
		Insert(node<T>(rnindex));
}
template<typename T>
node<T> BST<T>::rncompare(const node<T>* rnroot, const bool rnsign) const
{
	if(rnroot == rnnull)
		return node<T>();
	node<T>* rntemp_ptr = rnroot;
	if(rnsign)
	{
		if(rntemp_ptr->right == rnnull)
			return *root;
		do{ 
			rntemp_ptr = rntemp_ptr->right;
		}while(rntemp_ptr->right != rnnull);
	}
	else
	{
		if(rntemp_ptr->left == rnnull)
			return *root;
		do{ 
			rntemp_ptr = rntemp_ptr->left;
		}while(rntemp_ptr->left != rnnull);
	}
	return *rntemp_ptr;
}
template<typename T>
node<T>* BST<T>::rnsearch(const node<T>& rnnode)
{
	node<T>* rntemp_ptr = root;
	while(rntemp_ptr != rnnull)
	{
		if(rntemp_ptr->value == rnnode.value)
			return rntemp_ptr;
		else if(comp(rnnode.value, rntemp_ptr->value))
		{
			rntemp_ptr = rntemp_ptr->left;
		}else
		{
			rntemp_ptr = rntemp_ptr->right;
		}
	}
	return rnnull;
}
template<typename T>
node<T> BST<T>::Max() const
{
	return rncompare(root, true);
}
template<typename T>
node<T> BST<T>::Min() const
{
	return rncompare(root, false);
}

template<typename T>
node<T> BST<T>::Successor(const node<T>& rnnode) const
{
	if(rnnode.right != rnnull)
		return rncompare(rnnode.right, false);
	const node<T>* rncurr_ptr = &rnnode;
	node<T>* rntemp_ptr = rnnode.p;
	while(rntemp_ptr != rnnull && rntemp_ptr->right == rncurr_ptr)
	{
		rncurr_ptr = rntemp_ptr;
		rntemp_ptr = rntemp_ptr->p;
	}
	return (rntemp_ptr == rnnull)?node<T>():*rntemp_ptr;
}
template<typename T>
node<T> BST<T>::Predecessor(const node<T>& rnnode) const
{
	if(rnnode.left != rnnull)
		return rncompare(rnnode.left, true);
	const node<T>* rncurr_ptr = &rnnode;
	node<T>* rntemp_ptr = rnnode.p;
	while(rntemp_ptr != rnnull && rntemp_ptr->left == rncurr_ptr)
	{
		rncurr_ptr = rntemp_ptr;
		rntemp_ptr = rntemp_ptr->p;
	}
	return (rntemp_ptr == rnnull)?node<T>():*rntemp_ptr;
}
template<typename T>
void BST<T>::Insert(const node<T>& rnnode)
{
	if(root == rnnull)
	{
		root = new node<T>(rnnode);
		++size;
		return;
	}
	node<T>* rntemp_ptr = root;
	while(1)
	{
		if(comp(rnnode.value, rntemp_ptr->value))
		{
			if(rntemp_ptr->left == rnnull)
			{
				rntemp_ptr->left = new node<T>(rnnode);
				rntemp_ptr->left->p = rntemp_ptr;
				++size;
				return;
			}else
			{
				rntemp_ptr = rntemp_ptr->left;
			}
		}else
		{
			if(rntemp_ptr->right == rnnull)
			{
				rntemp_ptr->right = new node<T>(rnnode);
				rntemp_ptr->right->p = rntemp_ptr;
				++size;
				return;
			}else
			{
				rntemp_ptr = rntemp_ptr->right;
			}
		}
	}
}
template<typename T>
void BST<T>::Delete(const node<T>& rnnode)
{
	node<T>* rnnode_ptr = rnsearch(rnnode);
	if(rnnode_ptr == rnnull)
		throw std::runtime_error("object never exist!\n");
	if(rnnode_ptr->left == rnnull)
	{
		if(rnnode_ptr->p == rnnull)
		{
			root = rnnode_ptr->right;
			root->p = rnnull;
		}else if(rnnode_ptr->p->left == rnnode_ptr)
		{
			rnnode_ptr->p->left = rnnode_ptr->right;
			rnnode_ptr->p->left->p = rnnode_ptr->p;
		}else
		{
			rnnode_ptr->p->right = rnnode_ptr->right;
			rnnode_ptr->p->right->p = rnnode_ptr->p;
		}
	}else
	{
		node<T>* rntemp_ptr = rnnode_ptr->left;
		if(rntemp_ptr->right != rnnull)
		{
			do{
				rntemp_ptr = rntemp_ptr->right;
			}while(rntemp_ptr->right != rnnull);
		}
		rntemp_ptr->p->right = rntemp_ptr->left;
		rntemp_ptr->left->p = rntemp_ptr->p;

		rntemp_ptr->left = rnnode_ptr->left;
		rntemp_ptr->right = rnnode_ptr->right;
		
		if(rnnode_ptr->p == rnnull)
		{
			root = rntemp_ptr;
			root->p = rnnull;
		}else if(rnnode_ptr->p->left == rnnode_ptr)
		{
			rnnode_ptr->p->left = rntemp_ptr;
			rntemp_ptr->p = rnnode_ptr->p;
		}else
		{
			rnnode_ptr->p->right = rntemp_ptr;
			rntemp_ptr->p = rnnode_ptr->p;
		}
	}
	delete rnnode_ptr;
	--size;
}
template<typename T>
void BST<T>::doMiddleTrav(std::ostream& rnos, node<T>* rnnode_ptr, const char rnblank) const
{
	if(rnnode_ptr == rnnull)
		return;
	doMiddleTrav(rnos, rnnode_ptr->left, rnblank);
	rnos<<rnnode_ptr->value<<rnblank;
	doMiddleTrav(rnos, rnnode_ptr->right, rnblank);
}
template<typename T>
void BST<T>::doDeconstruct(node<T>* rnnode_ptr)
{
	if(rnnode_ptr == rnnull)
		return;
	doDeconstruct(rnnode_ptr->left);
	doDeconstruct(rnnode_ptr->right);
	delete rnnode_ptr;
#ifndef DEBUG
	std::cout<<"delete node"<<std::endl;
#endif
}  
#endif

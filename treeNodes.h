#ifndef TREES_H
#define TREES_H

#include <map>
#include <array>
#include <utility>


using namespace ::std;

class TreeNode
{

};

template <class T>
class TreeNode_Data
{
private:
	T data_;
	// array<TreeNode*, N> children_;
public:
	TreeNode_Data() { }
	TreeNode_Data(const T& data) : data_(data) { }
	inline T& getData() {
		return data_;
	}

	//virtual inline TreeNode*& operator[] (unsigned int i) = 0;

};


template <size_t N>
class TreeNode_Children_Array
{
private:
	array<TreeNode*, N> children_;
public:
	TreeNode_Children_Array() : children_() {
		//children_.fill(0);
	}

	inline TreeNode*& operator[] (unsigned int i) {
		return children_[i];
	}

	/*
	void doNothing()
	{
		cout << "do nothing";
	}
	*/


};

template <class K>
class TreeNode_Children_Map
{
private:
	map<K, TreeNode*> children_;
public:
	TreeNode_Children_Map() : children_(map<K, TreeNode*>()) { }

	TreeNode*& find(K key)
	{
		TreeNode* tempPtr = children_.find(key);
		if(tempPtr != children_.end())
			return tempPtr;
		else
			return 0;
	}
	bool addChild(const K& key, TreeNode*& ptr) {
		return children_.insert(pair<K, TreeNode*>(key, ptr)).second;
	}

};

class TreeNode_Parent
{
private:
	TreeNode* parent_;
public:
	TreeNode_Parent() : parent_(0) { }

	inline TreeNode*& getParent() {
		return parent_;
	}

};



template <class T, class K>
class TreeNode_Data_Map_Parent : public TreeNode_Data<T>,
								 public TreeNode_Children_Map<K>,
								 public TreeNode_Parent
{
public:
	TreeNode_Data_Map_Parent() : TreeNode_Data<T>(), TreeNode_Children_Map<K>(), TreeNode_Parent() {	}
	TreeNode_Data_Map_Parent(const T& data) : TreeNode_Data<T>(data),
													TreeNode_Children_Map<K>(),
													TreeNode_Parent() {	}
};




#endif // TREES_H

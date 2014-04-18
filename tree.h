#ifndef TREE_H
#define TREE_H

#include "treeNodes.h"

template <class T, class K>
class Tree_Map_Parent
{
private:
	TreeNode_Data_Map_Parent<T, K> ptrToRoot_;
	TreeNode_Data_Map_Parent<T, K>* ptrToCurrentNode_;
	//T data;
	//U<Y, Tree*> children;

public:
	Tree_Map_Parent() :  ptrToRoot_(TreeNode_Data_Map_Parent<T, K>()), ptrToCurrentNode_(&ptrToRoot_) {	}
	void addNode(const K& key, const T& data) {
		ptrToCurrentNode_->addChild(key, new TreeNode_Data_Map_Parent<T, K>(data));
	}
};

#endif // TREE_H

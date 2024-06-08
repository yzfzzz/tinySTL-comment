#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace mystl{

enum class Color{Red, Black};
enum class err_case{ll, rr, lr, rl};

template<class T>
class Node{
	T value;
	Node* left;
	Node* right;
	Node* parent;
	Color color;

	// 构造函数
	Node(T value, Node* parent):value(0), son(nullptr), parent(nullptr), color(Color::Red){}
};

template<class T>
class RedBlackTree
{
public:
	size_t size;
	void invColor(Node* cur)
	{
		Color color = cur->color;
		switch (color) 
		{  
			case Color::Red:  
				return Color::Black;  
			case Color::Black:  
				return Color::Red;  
			// 默认情况, 一般不用
			default:  
				throw std::invalid_argument("Invalid color");  
    	}  
	}

	Node* LL(Node* cur)
	{
		Node* father = cur->parent;
		Node* gfather = father->parent;

		gfather->left = nullptr;
		father->parent = nullptr;

		father->right = gfather;
		gfather->parent = father;

		father->Color = invColor(father);
		gfather->Color = invColor(gfather);
		return father;
	}

	Node* RR(Node* cur)
	{
		Node* father = cur->parent;
		Node* gfather = father->parent;

		gfather->right = nullptr;
		father->parent = nullptr;

		father->left = gfather;
		gfather->parent = father;

		father->Color = invColor(father);
		gfather->Color = invColor(gfather);
		return father;
	}

	Node* LR(Node* cur)
	{
		Node* father = cur->parent;
		Node* gfather = father->parent;

		father->parent = cur;
		cur->left = father;

		cur->right = gfather;
		gfather->parent = cur;

		gfather = invColor(gfather);
		cur = invColor(father);
		return cur;
	}

	Node* RL(Node* cur)
	{
		Node* father = cur->parent;
		Node* gfather = father->parent;

		father->parent = cur;
		cur->right = father;

		cur->left = gfather;
		gfather->parent = cur;

		gfather = invColor(gfather);
		cur = invColor(cur);
		return cur;	
	}

	Node* changeColor(Node* cur)
	{
		Node* gfather =  cur->parent->parent;
		if(gfather->left != nullptr)
			invColor(gfather->left);
		if(gfather->right != nullptr)
			invColor(gfather->right);
		invColor(gfather);
		return gfather;
	}

	void fixup(Node* cur)
	{
		Node* father = nullptr;
		Node* gfather = nullptr;
		Node* uncle = nullptr;
		if(cur->parent != nullptr)
			father = cur->parent;
		if(father->parent != nullptr)
			gfather = father->parent;
		if(father != nullptr && gfather != nullptr)
		{
			if(father->value < gfather->value)
				uncle = gfather->right;
			if(father->value > gfather->value)
				uncle = gfather->right;

			if(uncle != nullptr && uncle->color == Color::Red)
			{
				Node* cur = changeColor(cur);
				check(cur);// 深度遍历
			}
			if(uncle == nullptr || uncle->color == Color::Black)
			{
				// LL
				if(father->value < gfather->value && cur->value < gfather->value)
				{
					Node* head = gfather->parent;
					cur = LL(cur);
					head->left = cur;
					cur->parent = head;
				}
				// RR
				if(father->value > gfather->value && cur->value > gfather->value)
				{
					Node* head = gfather->parent;
					cur = RR(cur);
					head->left = cur;
					cur->parent = head;
				}
				// LR
				if(father->value < gfather->value && cur->value > gfather->value)
				{
					Node* head = gfather->parent;
					cur = LR(cur);
					head->left = cur;
					cur->parent = head;
				}
				// RL
				if(father->value > gfather->value && cur->value < gfather->value)
				{
					Node* head = gfather->parent;
					cur = RL(cur);
					head->left = cur;
					cur->parent = head;
				}
			}
		}
	}

	Node* insert(Node* root, T input)
	{
		if(root == nullptr)
		{
			Node* cur = new Node(input, root->parent);
			if(root->parent->value > input)
				root->parent->left = cur;
			if(root->parent->value < input)
				root->parent->right = cur;
			return cur;
		}
		if(root->value > input)
			root = root->left;
		if(root->value < input)
			root = root->right;

		size++;
		fixup(root);
	}
};

}
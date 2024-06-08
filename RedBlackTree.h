#include <iostream>
#include <sstream>
#include <string>

enum class Color{RED, BLACK, DoubleBLACK};
namespace mystl
{

template <class Value> 
class RedBlackTree{
public:
	class Node
	{
	public:
		Value value;	// 数值
		Color color;	// 颜色
		Node* left;		// 左孩子
		Node* right;	// 右孩子
		Node* parent;	// 父节点

		// 有参构造
		Node(const Value& v, Color& c, Node* p = nullptr):value(v),color(c),left(nullptr),right(nullptr),parent(p){}
		Node(const Value& v, Color c = Color::RED, Node* p = nullptr):value(v),color(c),left(nullptr),right(nullptr),parent(p){}
		// 默认构造:
		Node():color(Color::RED),left(nullptr),right(nullptr),parent(nullptr){}
	};

	Node* root;		// 根节点
	size_t size;	// 树的大小

	RedBlackTree(const Value& v)
	{
		root = new Node(v, Color::BLACK);
		size++;
	}

	// 查找某节点,返回该节点的指针
	Node* lookUp(Value v)
	{
		Node* cur = root;
		while(cur != nullptr)
		{
			if(v < cur->value)
			{
				cur = cur->left;
			}
			else if(v > cur->value)
			{
				cur = cur->right;
			}
			else
			{
				return cur;
			}
		}
		return cur;
	}

	// 右旋函数,返回旋转后的父结点
	/*
		    O	<= node(将要旋转的点)
		   /
		  O 
		 /
		O
	*/
	Node* rightRotate(Node* node)
	{
		// node为失衡节点
		Node* l_son = node->left;

		// 不管是否会发生冲突，都把冲突的右孩变左孩
		node->left = l_son->right;
		// 右孩变左孩后，更新父节点（前提它不是空节点）
		if(node->left)
		{
			node->left->parent = node;
		}

		// 更新旋转中心的父节点指向
		l_son->parent = node->parent;
		// 如果当前节点（node）是根节点，则更新根节点为 l_son
		if(l_son->parent == nullptr)
		{
			root = l_son;
		}
		// 如果node是父结点的左子节点
		else if(node->parent->left == node)
		{
			node->parent->left = l_son;
		}
		else
		{
			// 如果node是父结点的右子节点
			node->parent->right = l_son;
		}

		// 把node结点接在l_son右边
		node->parent = l_son;
		l_son->right = node;

		return l_son;
	}

	Node* leftRotate(Node* node)
	{
		Node* r_son = node->right;
		// 提前断掉右结点
		node->right = r_son->left;
		if(r_son->left)
		{
			node->right = r_son->left;
			r_son->left->parent = node;
		}

		r_son->parent = node->parent;
		if(r_son->parent == nullptr)
		{
			root = r_son;
		}
		else if(node->parent->left == node)
		{
			node->parent->left = r_son;
		}
		else
		{
			node->parent->right = r_son;
		}

		r_son->left = node;
		node->parent = r_son;

		return r_son;
	}
	/*
		    O
		   /
		  O 
		 /
		O	<= target
	*/
	void insertFixup(Node* target) // target是当前插入的结点
	{
		// 父结点存在，且出现红红
		while(target->parent && target->parent->color == Color::RED)
		{
			Node* father = target->parent;
			Node* g_father;
			if(father)
				g_father = father->parent;
			
			// 父是爷的左孩子
			if(g_father && g_father->left == father)
			{
				Node* uncle = g_father->right;
				// 如果叔结点存在，且颜色为红色
				if(uncle && uncle->color == Color::RED)
				{
					// 叔父爷变色
					uncle->color = Color::BLACK;
					father->color = Color::BLACK;
					g_father->color = Color::RED;
					// 将当前指针指向爷结点
					target = g_father;
				}
				// 叔结点不存在或者颜色为黑色(LL/LR)
				else
				{
					// LR
					if(target == g_father->left->right)
					{
						// 先左旋，旋转函数的输入结点是失衡点
						leftRotate(father);
					}
					// RR和LR后面的步骤都是一样的
					Node* t = rightRotate(g_father);
					// 变色
					t->color = Color::BLACK;
					t->right->color = Color::RED;
					t->left->color = Color::RED;
					return;
				}
			}

			if(g_father && g_father->right == father)
			{
				Node* uncle = g_father->left;
				if(uncle && uncle->color == Color::RED)
				{
					g_father->color = Color::RED;
					father->color = Color::BLACK;
					uncle->color = Color::BLACK;
					target = g_father;
				}
				else
				{
					// RL
					if(target == g_father->right->left)
					{
						// !不是旋转父结点
						rightRotate(father);
					}
					// LL和RL后续都一样
					Node* t = leftRotate(g_father);
					t->color = Color::BLACK;
					t->left->color = Color::RED;
					t->right->color = Color::RED;
					return;
				}
			}
			root->color = Color::BLACK;
		}
	}

	void insert(Value v)
	{
		Node* node = new Node(v);
		Node* p = nullptr;
		Node* cur = root;

		while(cur)
		{
			p = cur;
			if(v > cur->value)
			{
				cur = cur->right;
			}
			else if(v < cur->value)
			{
				cur = cur->left;
			}
			else
			{
				std::cout << "the value was in the tree" << std::endl;
				delete node;
        		return;
			}
		}
		size++;
		if(v > p->value)
		{
			p->right = node;
		}
		else
		{
			p->left = node;
		}

		node->parent = p;
		if(!p)
		{
			root = node;
		}
		insertFixup(node);
	}

	  // 中序遍历
	void inorderTraversal(Node *node) const
	{
		if(node)
		{
			inorderTraversal(node->left);
			std::cout << node->value << std::endl;
			inorderTraversal(node->right);
		}
	}

	// 删除指定结点
	void deleteNode(Value v)
	{
		Node* cur = lookUp(v);
		deleteFixup(cur);
	}

	// 寻找以某个节点为根节点的右子树中的最小节点
	Node* findMinNode(Node* cur)
	{
		cur = cur->right;
		while(cur->left)
		{
			cur = cur->left;
		}
		return cur;
	}

	// 删除结点后，修复红黑树
	void deleteFixup(Node* cur)
	{
		// 当前要删除的结点颜色变成双黑
		Value v = cur->value;
		cur->color = Color::DoubleBLACK;
		while(cur->color == Color::DoubleBLACK)
		{	
			// 没有左右孩子
			if(!cur->left && !cur->right)
			{
				cur->color = Color::DoubleBLACK;
				// 当前结点为红
				if(cur->color == Color::RED)
				{
					delete cur;
					return;
				}
				// 当前结点为黑
				else
				{
					// 找兄弟结点
					Node* sibling;
					Node* p = cur->parent;
					if(p->left == cur)
					{
						sibling = p->right;
					}
					else
					{
						sibling = p->left;
					}
					if(sibling)
					{
						// 如果结点存在，且是黑色的
						if(sibling->color == Color::BLACK)
						{
							// 兄弟至少有一个红孩子
							if( (sibling->left && sibling->left->color == Color::RED) || (sibling->right && sibling->right->color == Color::RED))
							{
								// LL
								if(sibling == p->left && sibling->left)
								{
									Node* r = sibling->left;
									r->color = sibling->color;
									sibling->color = p->color;
									p->color = Color::BLACK;
									rightRotate(sibling);
									p->right = nullptr;
									delete cur;
									return;
								}
								// RR
								else if(sibling->right && sibling == p->right)
								{
									Node* r = sibling->right;
									r->color = sibling->color;
									sibling->color = p->color;
									p->color = Color::BLACK;
									leftRotate(sibling);
									p->left = nullptr;
									delete cur;
									return;
								}
								// LR
								else if(sibling == p->left && !sibling->left && sibling->right)
								{
									Node* r = sibling->right;
									r->color = p->color;
									p->color = Color::BLACK;
									leftRotate(r);
									rightRotate(p->left);
									p->right = nullptr;
									delete cur;
									return;
								}
								// RL
								else
								{
									Node* r = sibling->left;
									r->color = p->color;
									p->color = Color::BLACK;
									rightRotate(r);
									leftRotate(p->right);
									p->left = nullptr;
									delete cur;
									return;
								}
							}
							// 兄弟孩子都是黑的
							else
							{
								sibling->color = Color::RED;
								if(p->left == cur)
									p->left = nullptr;
								if(p->right == cur)
									p->right = nullptr;
								// 删除这个值所在的结点
								if(cur->value == v)
								{
									Node* temp = cur;
									cur = p;
									delete temp;
								}
								if(cur == root || cur->color == Color::RED)
								{
									cur->color = Color::BLACK;
									return;
								}
								else
								{
									cur->color = Color::DoubleBLACK;
								}
							}
						}
						// 兄弟结点是红色的
						else
						{
							sibling->color = Color::BLACK;
							p->color = Color::RED;
							if(cur->parent->left == cur)
							{
								leftRotate(sibling);
							}
							else
							{
								rightRotate(sibling);
							}
						}
					}
					
				}	
			}
			// 有左右子树
			else
			{
				// 有左右子树
				if(cur->left && cur->right)
				{
					Node* minNode = findMinNode(cur);
					cur->value = minNode->value;
					cur->color = Color::BLACK;
					cur = minNode;
					cur->color = Color::DoubleBLACK;
				}
				else
				{
					// 只有左子树
					if(cur->left)
					{
						cur->value = cur->left->value;
						cur->color = Color::BLACK;
						delete cur->left;
						cur->left = nullptr;
					}
					// 只有右子树
					else
					{
						cur->value = cur->right->value;
						cur->color = Color::BLACK;
						delete cur->right;
						cur->right = nullptr;
					}
				}
			}
		}
	}

	int getSize()
	{
		return size;
	}

	bool empty() { return size == 0; }

	void printTree()
	{
		inorderTraversal(root);
		std::cout << std::endl;
	}

	void clear()
	{
		deleteTree(root);
	}
	// 红黑树的析构
	~RedBlackTree()
	{
		clear();
	}

private:
	void deleteTree(Node* cur)
	{
		if(cur->left)
			deleteNode(cur->left->value);
		if(cur->right)
			deleteNode(cur->right->value);
		delete cur;
	}

};

}
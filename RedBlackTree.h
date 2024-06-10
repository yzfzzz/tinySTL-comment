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

	// 辅助函数，用新的结点替代目标结点
	void replaceNode(Node* targetNode, Node* newNode)
	{
		// 如果目标结点没有父结点，说明它是根结点
		if(targetNode->parent == nullptr)
		{
			root = newNode;
		}
		// 目标结点是左子结点
		else if(targetNode == targetNode->parent->left)
		{
			targetNode->parent->left = newNode;
		}
		// 目标结点是右子结点
		else
		{
			targetNode->parent->right = newNode;
		}

		if(newNode)
		{
			newNode->parent = targetNode->parent;
		}
	}

	// 删除后修复红黑树，保持红黑树的性质
	void removeFixup(Node* node)
	{
		// 如果没有移到根结点，就一直循环
		while(node != root)
		{
			// 结点是左子树
			if(node == node->parent->left)
			{
				Node* sibling = node->parent->right;
				// case1:兄弟结点是红色
				if(getColor(sibling) == Color::RED)
				{
					// 兄父变色
					setColor(sibling, Color::BLACK);
					setColor(node->parent, Color::RED);
					// 朝双黑方向旋转(双黑在哪就往哪转)
					leftRotate(node->parent);
					// 保持双黑继续调整
					sibling = node->parent->right;
				}
				// case2:兄弟结点是黑色,且兄弟的孩子都是黑的
				if(getColor(sibling->left) == Color::BLACK && getColor(sibling->right) == Color::BLACK)
				{
					// 兄弟变红
					setColor(sibling, Color::RED);
					// 双黑上移
					node = node ->parent;
					if(node->color == Color::RED)
					{
						// 上移是红，变单黑
						node->color = Color::BLACK;
						// 结束循环
						node = root;
					}
				}
				// 兄弟结点是黑色,兄弟至少有一个红孩子
				else
				{
					// 兄弟结点右孩子是黑的，所以左孩子一定是红的
					if(getColor(sibling->right) == Color::BLACK)
					{
						// RL类型
						// ! 变色
						setColor(sibling->left, Color::BLACK);
            			setColor(sibling, Color::RED);
						// 兄弟结点右旋
						rightRotate(sibling);
						// 旋转后更正兄弟结点
						sibling = node->parent->right;
					}
					// RR类型
					setColor(sibling->right, getColor(sibling));
					setColor(sibling, getColor(node->parent));
					setColor(node->parent, Color::BLACK);
					// 左旋结点
					leftRotate(node->parent);
					node = root;
				}
			}
			// 删除结点是右子树
			else
			{
				Node* sibling = node->parent->left;
				// case1:兄弟结点是红色
				if(getColor(sibling) == Color::RED)
				{
					// 兄父变色
					setColor(sibling, Color::BLACK);
					setColor(node->parent, Color::RED);
					// 朝双黑方向旋转(双黑在哪就往哪转)
					rightRotate(node->parent);
					// 保持双黑继续调整
					sibling = node->parent->left;
				}
				// case2:兄弟结点是黑色,且兄弟的孩子都是黑的
				if(getColor(sibling->left) == Color::BLACK && getColor(sibling->right) == Color::BLACK)
				{
					// 兄弟变红
					setColor(sibling, Color::RED);
					// 双黑上移
					node = node ->parent;
					if(node->color == Color::RED)
					{
						// 上移是红，变单黑
						node->color = Color::BLACK;
						// 结束循环
						node = root;
					}
				}
				// 兄弟结点是黑色,兄弟至少有一个红孩子
				else
				{
					// 结点左孩子是黑的，所以右孩子一定是红的
					if(getColor(sibling->left) == Color::BLACK)
					{
						// LR类型
						// ! 变色
						setColor(sibling->right, Color::BLACK);
            			setColor(sibling, Color::RED);
						// 兄弟结点左旋
						leftRotate(sibling);
						// 旋转后更正兄弟结点
						sibling = node->parent->left;
					}
					// LL类型
					setColor(sibling->left, getColor(sibling));
					setColor(sibling, getColor(node->parent));
					setColor(node->parent, Color::BLACK);
					// 右旋结点
					rightRotate(node->parent);
					node = root;
				}
			}
		}
	}

	// 删除指定结点
	void deleteNode(Value v)
	{
		Node* cur = lookUp(v);
		deleteFixup(cur);
	}

	// 寻找以某个节点为根节点的右子树中的最小节点, cur是删除结点的右子树
	Node* findMinNode(Node* cur)
	{
		while(cur->left)
		{
			cur = cur->left;
		}
		return cur;
	}

	// 获取颜色，空指针为黑色
	Color getColor(Node* node)
	{
		if(node == nullptr)
		{
			return Color::BLACK;
		}
		return node->color;
	}

	// 获取颜色，空指针为黑色
	void setColor(Node* node, Color color)
	{
		if(node == nullptr)
		{
			return;
		}
		node->color = color;
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
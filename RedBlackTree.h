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
		Value value;	// ��ֵ
		Color color;	// ��ɫ
		Node* left;		// ����
		Node* right;	// �Һ���
		Node* parent;	// ���ڵ�

		// �вι���
		Node(const Value& v, Color& c, Node* p = nullptr):value(v),color(c),left(nullptr),right(nullptr),parent(p){}
		Node(const Value& v, Color c = Color::RED, Node* p = nullptr):value(v),color(c),left(nullptr),right(nullptr),parent(p){}
		// Ĭ�Ϲ���:
		Node():color(Color::RED),left(nullptr),right(nullptr),parent(nullptr){}
	};

	Node* root;		// ���ڵ�
	size_t size;	// ���Ĵ�С

	RedBlackTree(const Value& v)
	{
		root = new Node(v, Color::BLACK);
		size++;
	}

	// ����ĳ�ڵ�,���ظýڵ��ָ��
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

	// ��������,������ת��ĸ����
	/*
		    O	<= node(��Ҫ��ת�ĵ�)
		   /
		  O 
		 /
		O
	*/
	Node* rightRotate(Node* node)
	{
		// nodeΪʧ��ڵ�
		Node* l_son = node->left;

		// �����Ƿ�ᷢ����ͻ�����ѳ�ͻ���Һ�����
		node->left = l_son->right;
		// �Һ����󺢺󣬸��¸��ڵ㣨ǰ�������ǿսڵ㣩
		if(node->left)
		{
			node->left->parent = node;
		}

		// ������ת���ĵĸ��ڵ�ָ��
		l_son->parent = node->parent;
		// �����ǰ�ڵ㣨node���Ǹ��ڵ㣬����¸��ڵ�Ϊ l_son
		if(l_son->parent == nullptr)
		{
			root = l_son;
		}
		// ���node�Ǹ��������ӽڵ�
		else if(node->parent->left == node)
		{
			node->parent->left = l_son;
		}
		else
		{
			// ���node�Ǹ��������ӽڵ�
			node->parent->right = l_son;
		}

		// ��node������l_son�ұ�
		node->parent = l_son;
		l_son->right = node;

		return l_son;
	}

	Node* leftRotate(Node* node)
	{
		Node* r_son = node->right;
		// ��ǰ�ϵ��ҽ��
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
	void insertFixup(Node* target) // target�ǵ�ǰ����Ľ��
	{
		// �������ڣ��ҳ��ֺ��
		while(target->parent && target->parent->color == Color::RED)
		{
			Node* father = target->parent;
			Node* g_father;
			if(father)
				g_father = father->parent;
			
			// ����ү������
			if(g_father && g_father->left == father)
			{
				Node* uncle = g_father->right;
				// ���������ڣ�����ɫΪ��ɫ
				if(uncle && uncle->color == Color::RED)
				{
					// �常ү��ɫ
					uncle->color = Color::BLACK;
					father->color = Color::BLACK;
					g_father->color = Color::RED;
					// ����ǰָ��ָ��ү���
					target = g_father;
				}
				// ���㲻���ڻ�����ɫΪ��ɫ(LL/LR)
				else
				{
					// LR
					if(target == g_father->left->right)
					{
						// ����������ת��������������ʧ���
						leftRotate(father);
					}
					// RR��LR����Ĳ��趼��һ����
					Node* t = rightRotate(g_father);
					// ��ɫ
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
						// !������ת�����
						rightRotate(father);
					}
					// LL��RL������һ��
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

	  // �������
	void inorderTraversal(Node *node) const
	{
		if(node)
		{
			inorderTraversal(node->left);
			std::cout << node->value << std::endl;
			inorderTraversal(node->right);
		}
	}

	// ɾ��ָ�����
	void deleteNode(Value v)
	{
		Node* cur = lookUp(v);
		deleteFixup(cur);
	}

	// Ѱ����ĳ���ڵ�Ϊ���ڵ���������е���С�ڵ�
	Node* findMinNode(Node* cur)
	{
		cur = cur->right;
		while(cur->left)
		{
			cur = cur->left;
		}
		return cur;
	}

	// ɾ�������޸������
	void deleteFixup(Node* cur)
	{
		// ��ǰҪɾ���Ľ����ɫ���˫��
		Value v = cur->value;
		cur->color = Color::DoubleBLACK;
		while(cur->color == Color::DoubleBLACK)
		{	
			// û�����Һ���
			if(!cur->left && !cur->right)
			{
				cur->color = Color::DoubleBLACK;
				// ��ǰ���Ϊ��
				if(cur->color == Color::RED)
				{
					delete cur;
					return;
				}
				// ��ǰ���Ϊ��
				else
				{
					// ���ֵܽ��
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
						// ��������ڣ����Ǻ�ɫ��
						if(sibling->color == Color::BLACK)
						{
							// �ֵ�������һ���캢��
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
							// �ֵܺ��Ӷ��Ǻڵ�
							else
							{
								sibling->color = Color::RED;
								if(p->left == cur)
									p->left = nullptr;
								if(p->right == cur)
									p->right = nullptr;
								// ɾ�����ֵ���ڵĽ��
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
						// �ֵܽ���Ǻ�ɫ��
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
			// ����������
			else
			{
				// ����������
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
					// ֻ��������
					if(cur->left)
					{
						cur->value = cur->left->value;
						cur->color = Color::BLACK;
						delete cur->left;
						cur->left = nullptr;
					}
					// ֻ��������
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
	// �����������
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
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
	Node* Nil;

	RedBlackTree(const Value& v)
	{
		root = new Node(v, Color::BLACK);
		Nil = new Node();
		Nil->color = Color::BLACK;
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

	// �������������µĽ�����Ŀ����
	void replaceNode(Node* targetNode, Node* newNode)
	{
		// ���Ŀ����û�и���㣬˵�����Ǹ����
		if(targetNode->parent == nullptr)
		{
			root = newNode;
		}
		// Ŀ���������ӽ��
		else if(targetNode == targetNode->parent->left)
		{
			targetNode->parent->left = newNode;
		}
		// Ŀ���������ӽ��
		else
		{
			targetNode->parent->right = newNode;
		}

		if(newNode)
		{
			newNode->parent = targetNode->parent;
		}
	}

	// ɾ�����޸�����������ֺ����������, node��˫�ڽ��
	void removeFixup(Node* node)
	{
		// ��ʱnode��Ψһһ�����
		if(node == Nil && node->parent == nullptr)
			return;
		// ���û���Ƶ�����㣬��һֱѭ��
		while(node != root)
		{
			// ɾ�������������,�ֵܽ����������
			if(node == node->parent->left)
			{
				Node* sibling = node->parent->right;
				// case1:�ֵܽ���Ǻ�ɫ
				if(getColor(sibling) == Color::RED)
				{
					// �ָ���ɫ
					setColor(sibling, Color::BLACK);
					setColor(node->parent, Color::RED);
					// ��˫�ڷ�����ת(˫�����ľ�����ת)
					leftRotate(node->parent);
					// ����˫�ڼ�������
					sibling = node->parent->right;
				}
				// case2:�ֵܽ���Ǻ�ɫ,���ֵܵĺ��Ӷ��Ǻڵ�
				if(getColor(sibling->left) == Color::BLACK && getColor(sibling->right) == Color::BLACK)
				{
					// �ֵܱ��
					setColor(sibling, Color::RED);
					// ˫������
					node = node ->parent;
					if(node->color == Color::RED)
					{
						// �����Ǻ죬�䵥��
						node->color = Color::BLACK;
						// ����ѭ��
						node = root;
					}
				}
				// �ֵܽ���Ǻ�ɫ,�ֵ�������һ���캢��
				else
				{
					// �ֵܽ���Һ����Ǻڵģ���������һ���Ǻ��
					if(getColor(sibling->right) == Color::BLACK)
					{
						// RL���ͣ�ֻҪ�漰��ת����Ҫ��ɫ
						// !
						setColor(sibling->left, Color::BLACK);
            			setColor(sibling, Color::RED);
						// �ֵܽ������
						rightRotate(sibling);
						// ��ת������ֵܽ��ָ��
						sibling = node->parent->right;
					}
					// RR����
					setColor(sibling->right, getColor(sibling));
					setColor(sibling, getColor(node->parent));
					setColor(node->parent, Color::BLACK);
					// �������
					leftRotate(node->parent);
					node = root;
				}
			}
			// ɾ�������������,�ֵܽ����������
			else
			{
				Node* sibling = node->parent->left;
				// case1:�ֵܽ���Ǻ�ɫ
				if(getColor(sibling) == Color::RED)
				{
					// �ָ���ɫ
					setColor(sibling, Color::BLACK);
					setColor(node->parent, Color::RED);
					// ��˫�ڷ�����ת(˫�����ľ�����ת)
					rightRotate(node->parent);
					// ����˫�ڼ�������
					sibling = node->parent->left;
				}
				// case2:�ֵܽ���Ǻ�ɫ,���ֵܵĺ��Ӷ��Ǻڵ�
				if(getColor(sibling->left) == Color::BLACK && getColor(sibling->right) == Color::BLACK)
				{
					// �ֵܱ��
					setColor(sibling, Color::RED);
					// ˫������
					node = node ->parent;
					if(node->color == Color::RED)
					{
						// �����Ǻ죬�䵥��
						node->color = Color::BLACK;
						// ����ѭ��
						node = root;
					}
				}
				// �ֵܽ���Ǻ�ɫ,�ֵ�������һ���캢��
				else
				{
					// ��������Ǻڵģ������Һ���һ���Ǻ��
					if(getColor(sibling->left) == Color::BLACK)
					{
						// LR����
						setColor(sibling->right, Color::BLACK);
            			setColor(sibling, Color::RED);
						// �ֵܽ������
						leftRotate(sibling);
						// ��ת������ֵܽ��
						sibling = node->parent->left;
					}
					// LL����
					setColor(sibling->left, getColor(sibling));
					setColor(sibling, getColor(node->parent));
					setColor(node->parent, Color::BLACK);
					// �������
					rightRotate(node->parent);
					node = root;
				}
			}
		}
		setColor(node, Color::BLACK);
	}

	// ȡ��Nil�ڱ�������
	void dieConnectNil() 
	{
		if (Nil == nullptr) {
		return;
		}
		if (Nil->parent != nullptr) {
		if (Nil == Nil->parent->left) {
			Nil->parent->left = nullptr;
		} else {
			Nil->parent->right = nullptr;
		}
		}
	}

	// ɾ����ֵ
	void deleteValue(Value v)
	{
		deleteNode(lookUp(v));
	}

	// ɾ��ָ�����
	void deleteNode(Node* del)
	{
		Node* rep = del;				// rep������ڵ㣩��ʼָ��Ҫɾ���Ľڵ�
		Node* child = nullptr;			// Ҫɾ�����ĺ��ӽ��
		Node* parentRP;					// ������ĸ��ڵ�
		Color origCol = rep->color;		// Ҫɾ������ԭʼ���

		// ���ɾ�����û������
		if(!del->left)
		{
			rep = del->right;
			parentRP = del->parent;
			origCol = getColor(rep);
			replaceNode(del, rep);
		}
		// ���ɾ�����û���Һ���
		else if(!del->right)
		{
			rep = del->left;
			parentRP = del->parent;
			origCol = getColor(rep);
			replaceNode(del, rep);
		}
		// ���ɾ���������������
		else
		{
			rep = findMinNode(del->right);
			origCol = rep->color;
			// ��������㲻��ɾ������ֱ���Һ���
			if(rep != del->right)
			{
				parentRP = rep->parent;
				child = rep->right;	//rep�Ѿ������������С�ģ�������������
				parentRP->left = child;	// �ø����ֱ����Ҫɾ����������
				// �ĺ��ӽ���ָ��
				if(child != nullptr)
				{
					child->parent = parentRP;
					setColor(child, getColor(parentRP->right));
				}
				// �����������ɾ�������,�����Һ��ӵ�ָ��
				del->left->parent = rep;
				del->right->parent = rep;
				rep->left = del->left;
				rep->right = del->right;
				// ���ɾ���ڵ��и��ڵ㣬���¸��ڵ�ĺ���ָ��
				if(del->parent != nullptr)
				{
					if(del == del->parent->left)
					{
						del->parent->left = rep;
						rep->parent = del->parent;
					}
					else
					{
						del->parent->right = rep;
						rep->parent = del->parent;
					}
				}
				// ���ɾ���ڵ�û�и��ڵ㣬˵�����Ǹ��ڵ�
				else
				{
					root = rep;
					root->parent = nullptr;
				}
			}
			// �������ڵ���ɾ���ڵ��ֱ���Һ���,˵������ڵ�û������
			else
			{
				child = rep->right; // ���ӽڵ�ָ������ڵ���Һ���
				rep->left = del->left; // ����ڵ������ָ��ɾ���ڵ������
				del->left->parent = rep; // �������ӵĸ��ڵ�
				// ����ɾ���ڵ㸸�ڵ�ĺ���ָ��
				if (del->parent != nullptr) 
				{
					if (del == del->parent->left) 
					{
						del->parent->left = rep;
						rep->parent = del->parent;
					} 
					else
					{
						del->parent->right = rep;
						rep->parent = del->parent;
					}
				}
				// ���ɾ���ڵ��Ǹ��ڵ�
				else 
				{
					root = rep;
					root->parent = nullptr;
				}
			}
		}
		// �������ڵ���ڣ���������ɫΪɾ���ڵ����ɫ,��������
		if(rep != nullptr)
		{
			rep->color = del->color;
		}
		// �������ڵ㲻���ڣ�˵��ɾ������һ��ʼ��Ŀ����(node)
		else
		{
			origCol = del->color;	// origColʼ��������ɾ��������ɫ
		}

		// ���ԭʼ��ɫ�Ǻ�ɫ����Ҫ���ж�����޸���������Ϊ��ɫ�ڵ��ɾ�����ܻ��ƻ������������
		if(origCol == Color::BLACK)
		{
			// ���ɾ�����û�к��ӽ��
			if (child == nullptr)
			{
				// ����ɾ���Ľ���Ǹ��ط����и����
				Nil->parent = parentRP;
				// �������ڵ�ĸ��ڵ���ڣ��������Ӧ�ĺ���ָ��ΪNil�ڵ�
				if(parentRP != nullptr)
				{
					if(parentRP->left == nullptr)
					{
						parentRP->left = Nil;
					}
					else
					{
						parentRP->right = Nil;
					}
				}
				// �޸�����ٽ��
				removeFixup(Nil);
				// �Ͽ�Nil�ڵ�����������
				dieConnectNil();
			}
			else
			{
				// removeFixup(child);
			}
		}
		delete del;
		
	}

	// Ѱ����ĳ���ڵ�Ϊ���ڵ���������е���С�ڵ�, cur��ɾ������������
	Node* findMinNode(Node* cur)
	{
		while(cur->left)
		{
			cur = cur->left;
		}
		return cur;
	}

	// ��ȡ��ɫ����ָ��Ϊ��ɫ
	Color getColor(Node* node)
	{
		if(node == nullptr)
		{
			return Color::BLACK;
		}
		return node->color;
	}

	// ��ȡ��ɫ����ָ��Ϊ��ɫ
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



};

}
#include<iostream>
using namespace std;




template <typename key, typename value>
class avl
{
	struct om
	{
		key data;
		struct om* left;
		struct om* right;
		int height;
		value val;
	};
	unsigned long int mapSize = 0;
	struct om* root=NULL;
	value def;

public:
	int height(om* n)
	{
		if (n == NULL)
			return 0;
		return n->height;
	}
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	om* newnode(key data, value val)
	{
		om* p = new om();
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		p->val = val;
		p->height = 1;
		def = val;
		mapSize++;
		return p;
	}
	om* rotateRight(om* p)
	{
		om* q = p->left;
		om* r = q->right;
		q->right = p;
		p->left = r;
		p->height = max(height(p->left), height(p->right)) + 1;
		q->height = max(height(q->left), height(q->right)) + 1;
		return q;
	}
	om* rotateLeft(om* p)
	{
		om* q = p->right;
		om* r = q->left;
		q->left = p;
		p->right = r;
		p->height = max(height(p->left), height(p->right)) + 1;
		q->height = max(height(q->left), height(q->right)) + 1;
		return q;
	}
	int getBalance(om* n)
	{
		if (n == NULL)
			return 0;
		return height(n->left) - height(n->right);
	}
	om* insertNode(om* node, key data,value val) 
	{
		if (node == NULL)
			return newnode(data,val);
		if (data < node->data)
			node->left = insertNode(node->left, data,val);
		else if (data > node->data)
			node->right = insertNode(node->right, data,val);
		
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);
		if (balance > 1 && data < node->left->data)
			return rotateRight(node);
		if (balance < -1 && data > node->right->data)
			return rotateLeft(node);
		if (balance > 1 && data > node->left->data)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		if (balance < -1 && data < node->right->data)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
		return node;
	}

	void insert(key k, value val)
	{
		root = insertNode(root, k, val);
	}

	void InOrder(om* root)
	{
		if (root != NULL)
		{
			int x = root->duplicate;
			InOrder(root->left);
			while (x--) {
				cout << root->data << " ";
			}
			InOrder(root->right);
		}
	}
	om* minValueNode(om* node)
	{
		om* p = node;
		while (p->left != NULL)
			p = p->left;
		return p;
	}
	om* deleteNode(om* root, key data)
	{
		if (root == NULL)
			return root;
		if (data < root->data)
			root->left = deleteNode(root->left, data);
		else if (data > root->data)
			root->right = deleteNode(root->right, data);
		else
		{
				if ((root->left == NULL) || (root->right == NULL))
				{
					om* temp;
					if (root->left != NULL)
						temp = root->left;
					else
						temp = root->right;
					if (temp == NULL){					{
						temp = root;
						root = NULL;
					}
					else
						*root = *temp;
					mapSize--;
					free(temp);
					
				}
				else
				{
					om* temp = minValueNode(root->right);
					root->data = temp->data;
					root->val = temp->val;	
					root->right = deleteNode(root->right, temp->data);
				}
		}
		if (root == NULL)
			return root;
		root->height = 1 + max(height(root->left), height(root->right));
		int balance = getBalance(root);
		if (balance > 1 && getBalance(root->left) >= 0)
			return rotateRight(root);
		if (balance < -1 && getBalance(root->right) <= 0)
			return rotateLeft(root);
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
		return root;
	}
	void erase(key data)
	{
		root = deleteNode(root, data);
	}
	bool search(om* root, key data) 
	{
		if (root == NULL)
			return false;
		if (data == root->data)
			return true;
		else if (data < root->data)
			return search(root->left, data);
		else
			return search(root->right, data);
	}
	bool find(key data)
	{
		return search(root, data);
	}
	int size() {
		return mapSize;
	}
	void clear()
	{
		mapSize = 0;
		om *temp= root;
		free(temp);
		root = NULL;
	}
	struct om* proxy(struct om* node, key data)
	{
		if (node->data == data)
		{
			return node;
		}
		else if (data > node->data)
			return proxy(node->right, data);
		else if (data < node->data)
			return proxy(node->left, data);
	}


	value& findValueCorrespondingToKey(struct om* node, key data)
	{
		if (node == NULL)
		{
			
			(*this).root = insertNode((*this).root, data, def);
			struct om* temp = proxy((*this).root, data);
			return temp->val;
		}
		if (node->data == data)
			return node->val;
		else if (data > node->data)
			return findValueCorrespondingToKey(node->right, data);
		else if (data < node->data)
			return findValueCorrespondingToKey(node->left, data);

	}

	value& operator [](key data)
	{
		return findValueCorrespondingToKey(root, data);
	}

		
	
};
int main()
{avl<int,int>* root = NULL;
	//avl<int> a;

	avl<int,int> a;


	 a.insert( 1,4);
	 a.insert( 3,8);
	 a.insert( 5,12);
	 a.insert( 8,20);
	 a.insert( 11,24);
	 cout << a.find(1) << endl;
	 cout << a.find(3) << endl;
	 cout << a.find(5) << endl;
	 cout << a.find(8) << endl;
	 cout << a.find(11) << endl;
	 cout << a.find(12) << endl;
	 cout <<"mapSize : "<<a.size() << endl;
	 cout << a[1] << endl;
	 cout << a[3] << endl;
	 cout << a[5] << endl;
	 cout << a[8] << endl;
	 cout << a[11] << endl;
	 cout << "mapSize : " << a.size() << endl;
	 cout << a[100] << endl;
	 cout << a[111] << endl;
	 cout << "mapSize : " << a.size() << endl;
	 cout << a[100] << endl;
	 cout << a[111] << endl;
	 cout << "mapSize : " << a.size() << endl;
	 a[111] = 17;
	 a[112] = 18;
	 cout << a[111] << endl;
	 cout << a[112] << endl;
	 cout << "mapSize : " << a.size() << endl;
	 a.erase(3);
	 a.erase(8);
	 cout << a.find(1) << endl;
	 cout << a.find(3) << endl;
	 cout << a.find(5) << endl;
	 cout << a.find(8) << endl;
	 cout << a.find(11) << endl;
	 cout << a.find(12) << endl;
	 cout << "mapSize : " << a.size() << endl;
	 a.clear();
	 cout << "mapSize : " << a.size() << endl;
	cout << endl;

	
}

/*by Zhaobo Ding*/

class RB_Tree
{
private:
	struct node
	{
		int key;
		node *left, *right, *parent;
		bool color; // we denote red as true and black as false
	}*root, *nil;

	node *new_node(int k = 0) // create a new node in RB tree
	{
		node *ans = new node;
		ans->left = ans->right = ans->parent = NULL;
		ans->key = k;
		ans->color = true; // set red as the default color for a new node
	}

	void left_rotate(node *root)
	{
		node *r = root->right;

	}
public:
	RB_Tree()
	{
		nil = new_node();
		nil->color = false; // the color of nil should be black
		root = nil;
	}
};
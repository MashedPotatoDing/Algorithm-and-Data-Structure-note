/*by Zhaobo Ding*/
// user should call clean() finally to avoid memory leak
class AVL
{
	private:
		struct node
		{
			node *left, *right;
			int key, height;
			// height stores the largest distance from current node down to a leaf node
		}*avl; // avl is the pointer to the root of AVL tree

		struct node *newnode(int k) // create a new pre-configured node for AVL tree
		{
			node *ans = new struct node;
			ans->left = ans->right = NULL;
			ans->key = k;
			ans->height = 1; // the height of a leaf node is 1
			return ans;
		}

		void update_height(struct node *root)
		{
			if (root->left == NULL)
				if (root->right == NULL)
					root->height = 1;
				else
					root->height = root->right->height + 1;
			else
				if (root->right == NULL)
					root->height = root->left->height + 1;
				else
					root->height = max(root->right->height, root->left->height) + 1;
		}

		struct node *left_rotate(struct node *root)
		{
			struct node *r = root->right;
			struct node *rl = r->left;

			r->left = root;
			root->right = rl;

			update_height(root);
			update_height(r);

			return r;
		}

		struct node *right_rotate(struct node *root)
		{
			struct node *l = root->left;
			struct node *lr = l->right;

			l->right = root;
			root->left = lr;

			update_height(root);
			update_height(l);

			return l;
		}

		int get_height(struct node *root)
		{
			if (root == NULL)
				return 0;
			else
				return root->height;
		}

		struct node *insert_process(int k, struct node *root)
		{
			if (root == NULL)
				return newnode(k);

			if (root->key == k)
				return root;

			if (root->key > k)
				root->left = insert_process(k, root->left);
			else
				root->right = insert_process(k, root->right);

			// after inserting the node, we will then make sure the BST is balanced
			update_height(root);
			int diff = get_height(root->left) - get_height(root->right);

			if (diff > 1) // the left subtree is "heavier"
				if (k < root->left->key)
					return right_rotate(root);
				else
				{
					root->left = left_rotate(root->left);
					return right_rotate(root);
				}

			if (diff < -1) // the right subtree is "heavier"
				if (k > root->right->key)
					return left_rotate(root);
				else
				{
					root->right = right_rotate(root->right);
					return left_rotate(root);
				}

			return root;
		}

		bool search(int k, struct node *root)
		{
			if (root == NULL) return false;

			if (root->key == k) return true;

			if (root->key > k)
				return search(k, root->left);
			else
				return search(k, root->right);
		}

		void discard(struct node *root)
		{
			if (root == NULL) return;

			discard(root->left);
			discard(root->right);
			delete root;
		}

		struct node *erase(int k, struct node *root)
		{
			if (root == NULL) return NULL;

			if (k < root->key)
				root->left = erase(k, root->left);
			else if (k > root->key)
				root->right = erase(k, root->right);
			else
			{
				if (root->left == NULL)
				{
					struct node *p = root->right;
					delete root;
					return p;
				}
				else if (root->right == NULL)
				{
					struct node *p = root->left;
					delete root;
					return p;
				}
				else
				{
					/* if neither left nor right child is empty, we find the leftmost node in
					right subtree to swap with the current node, which brings no conflict in
					AVL tree, but will make it easier for us to delete */
					struct node *p = root->right;
					while (p->left)
						p = p->left;
					root->key = p->key;
					root->right = erase(p->key, root->right);
				}
			}

			update_height(root);
			int diff = get_height(root->left) - get_height(root->right);

			if (diff > 1)
			{
				int sub_diff = get_height(root->left->left) - get_height(root->left->right);
				if (sub_diff < 0)
					root->left = left_rotate(root->left);

				return right_rotate(root);
			}

			if (diff < -1)
			{
				int sub_diff = get_height(root->right->left) - get_height(root->right->right);
				if (sub_diff > 0)
					root->right = right_rotate(root->right);

				return left_rotate(root);
			}

			return root;
		}

	public :
		AVL()
		{
			avl = NULL;
		}

		void insert(int k)
		{
			avl = insert_process(k, avl);
		}

		bool find(int k)
		{
			return search(k, avl);
		}

		void clean()
		{
			discard(avl);
		}

		void remove(int k)
		{
			avl = erase(k, avl);
		}
};

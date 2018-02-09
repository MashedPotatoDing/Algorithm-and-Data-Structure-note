class AVL
{
	private:
		struct node
		{
			node *left, *right;
			int key, height;
		}*avl;

		struct node *newnode(int k)
		{
			node *ans = new struct node;
			ans->left = ans->right = NULL;
			ans->key = k;
			ans->height = 1;
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

			update_height(root);
			int diff = get_height(root->left) - get_height(root->right);

			if (diff > 1)
				if (k < root->left->key)
					return right_rotate(root);
				else
				{
					root->left = left_rotate(root->left);
					return right_rotate(root);
				}

			if (diff < -1)
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
};

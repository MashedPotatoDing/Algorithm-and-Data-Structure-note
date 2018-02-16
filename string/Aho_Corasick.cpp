const int CharSize = 26;
const char CharBase = 'a';

struct trie_node
{
	int count;
	trie_node *fail;
	trie_node *children[CharSize];
	bool EOW;
};

struct trie_node *new_node()
{
	struct trie_node *ans = new struct trie_node;
	ans->count = ans->EOW = 0;
	ans->fail = NULL;
	for (int i = 0; i < CharSize; i++)
		ans->children[i] = NULL;

	return ans;
}

struct trie_node *root = new_node();

void insert_dict(string str)
{
	int l = str.length();
	trie_node *p = root;

	for (int i = 0; i < l; i++)
	{
		int x = str[i] - CharBase;
		if (p->children[x] == NULL)
			p->children[x] = new_node();
		p = p->children[x];
	}

	p->EOW = true;
}

void free(trie_node *x)
{
	if (x == NULL) return;
	for (int i = 0; i < CharSize; i++)
		delete x->children[i];

	delete x->fail;
	delete x;
}

void fail_pointer()
{
	queue <trie_node *> q;
	while (!q.empty()) q.pop();

	q.push(root);
	while (!q.empty())
	{
		trie_node *t = q.front();
		for (int i = 0; i < CharSize; i++)
		{
			if (t->children[i] == NULL)
				continue;

			if (t == root)
				t->children[i]->fail = root;
			else
			{
				trie_node *p = t->fail;
				while (p)
				{
					if (p->children[i])
					{
						t->children[i]->fail = p->children[i];
						break;
					}
					p = p->fail;
				}

				t->children[i]->fail = root;
			}

			q.push(t->children[i]);
		}
	}
}

void aho_corasick(string text)
{
	trie_node *p = root;
	int l = text.length();

	for (int i = 0; i < l; i++)
	{
		int x = text[i] - CharBase;

		if (p->children[x])
			p = p->children[x];
		else
			while (p != root)
			{
				p = p->fail;
				if (p->children[x])
				{
					p = p->children[x];
					break;
				}
			}

		if (p->EOW) p->count++;
	}
}
/*by Zhaobo Ding*/

/* We should call insert_dict(word) first to add words to the "dictionary", and then call fail_pointer() to
	build the fail pointer for initialization. Then, we call aho_corasick(text) to count the number of times
	every word appears in text. The result of function aho_corasick(text) will be stored in the trie. When
	we done the work, call free() for the avoidance of memory leak. */
const int CharSize = 26;
const char CharBase = 'a';

struct trie_node
{
	int count; // we store the number of times a word appears here
	trie_node *fail;
	trie_node *children[CharSize];
	bool EOW; // record if the node here in trie is the end of a word
};

trie_node *new_node() // create a new node
{
	trie_node *ans = new trie_node;
	ans->count = ans->EOW = 0;
	ans->fail = NULL;
	for (int i = 0; i < CharSize; i++)
		ans->children[i] = NULL;

	return ans;
}

trie_node *root = new_node();

void insert_dict(string str)
{
	int l = str.length();
	trie_node *p = root;

	for (int i = 0; i < l; i++)
	{
		int x = str[i] - CharBase;
		if (p->children[x] == NULL) // create new node for new word
			p->children[x] = new_node();
		p = p->children[x];
	}

	p->EOW = true;
}

void free(trie_node *x)
{
	if (x == NULL) return;
	for (int i = 0; i < CharSize; i++)
		free(x->children[i]);

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
		q.pop();
		for (int i = 0; i < CharSize; i++)
		{
			if (t->children[i] == NULL)
				continue;

			t->children[i]->fail = root;
			if (t != root)
			{
				trie_node *p = t->fail;
				while (p)
				{
					if (p->children[i]) // try to find a matched suffix
					{
						t->children[i]->fail = p->children[i];
						break;
					}
					p = p->fail;
				}
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
		if (x < 0 || x >= CharSize) // deal with word not in trie
		{
			p = root;
			continue;
		}

		if (p->children[x])
			p = p->children[x];
		else
			while (p != root) // when fail to match, try to find a shorter match with fail pointer
			{
				p = p->fail;
				if (p->children[x])
				{
					p = p->children[x];
					break;
				}
			}

		trie_node *q = p; // update word number recursively
		while (q != root)
		{
			if (q->EOW) q->count++;
			q = q->fail;
		}
	}
}
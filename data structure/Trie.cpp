/*by Zhaobo Ding*/
const int CharSize = 26, CharBase = 'a';

class Trie
{
	private :
		vector <int> children[26];
		vector <bool> EOW; // EOW(End of Word) stores if a node is the last letter of a word
		int root,size;

	public :
		Trie() // initialization
		{
			for (int i = 0; i < CharSize; i++)
				children[i].push_back(0);
			EOW.push_back(false);
			root = 0;
			size = 1;
		}

		void insert(string str) // insert a new word into trie
		{
			int cur = root, l = str.length();
			for (int i = 0; i < l; i++)
			{
				if (children[str[i] - CharBase][cur] == 0) 
				{
					children[str[i] - CharBase][cur] = size;
					for (int j = 0; j < CharSize; j++)
						children[j].push_back(0);
					EOW.push_back(false);
					size++;
					// create a new node for the new word
				}

				cur = children[str[i] - CharBase][cur];
			}

			EOW[cur] = true;
		}

		bool find(string str) // find if str is in recorded in trie
		{
			int cur = root, l = str.length();
			for (int i = 0; i < l; i++)
				if (children[str[i] - CharBase][cur])
					cur = children[str[i] - CharBase][cur];
				else
					return false;

			return EOW[cur];
		}
};

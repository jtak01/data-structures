// Node.h
// Small struct that is part of the trie


	
	struct Node {
		char data;
		Node *child[4];
		bool end;
	};

#include <bits/stdc++.h>
using namespace std;
class tree{
	public:
		tree(tree* right,tree* left,unsigned int val,int num);
		tree* getleft();
		tree* getright();
		unsigned int getval();
		int getnum();
	private:
		int num;
		unsigned int val;
		tree* right;
		tree* left;
};
struct cmp{
	bool operator()(tree *t1,tree *t2) const
	{
		return t1->getnum()>t2->getnum();
	}
};
class huffman{
	public:
		int buildtree(string s);
		void zip(string s,string s2);
		void unzip(string s,string to);
		int code(string s,tree *now);
		void url(string &s); 
		void my_print(int len,int now);
	private:
		tree* head;
		vector<tree> v;
		map<unsigned int,int> m;
		map<unsigned int,string> m2;
		priority_queue<tree*,vector<tree*>,cmp> q;
};

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
using namespace std;
struct node
{
	string nodeword;//单词
	char head;//首字母
	char tail;//尾字母
	vector<int> next;//能在末尾连接的下一个单词序号
	int wordlen;//单词长度
};
void readfile(string filepath);
void newnode(string word);
void addtomap(node newword);
void printmap();
void printnode(node n);
void toforest();
void totree(int root);
vector<vector<int>> next(int root);
void printforest();
void findlongest();
void printdetail(int index);
void wordlist();
vector<node> map;//有向图
vector<vector<int>> forest;
/*----------------------------------------------------------------*/
int main()
{	
	wordlist();
	return 0;
}
void wordlist()
{
	string filepath;
	cin >> filepath;
	readfile(filepath);
	toforest();
	findlongest();
}
void findlongest()//找出最长链
{
	int i = 0;
	int tempmax = 0;
	int tempindex = -1;
	for (i = 0; i < forest.size(); i++) 
	{
		if (forest[i].size() > tempmax)
		{
			tempmax = forest[i].size();
			tempindex = i;
		}
	}
	if (tempindex >= 0)
	{
		printdetail(tempindex);
	}
}
void printdetail(int index)
{
	int i = 0;
	for (i = 0; i < forest[index].size(); i++) 
	{
		cout << map[forest[index][i]].nodeword << endl;
	}
}
void toforest()//把有向图分解成各种链
{
	int wordnum = map.size();
	int i = 0;
	for (i = 0; i < wordnum; i++)
	{
		totree(i);
	}
}
void totree(int root)
{
	vector<vector<int>> tempnodes;
	tempnodes = next(root);
	forest.insert(forest.end(), tempnodes.begin(), tempnodes.end());
}

vector<vector<int>> next(int root)
{
	vector<vector<int>> nodes;
	int i = 0;
	if (map[root].next.size() == 0)
	{
		vector<int> singlenode;
		singlenode.push_back(root);
		nodes.push_back(singlenode);
		return nodes;
	}
	else {
		for (i = 0; i < map[root].next.size(); i++)
		{
			vector<vector<int>> tempnodes;
			tempnodes = next(map[root].next[i]);
			int j = 0;
			for (j = 0; j < tempnodes.size(); j++)
			{
				tempnodes[j].insert(tempnodes[j].begin(), root);
			}
			nodes.insert(nodes.end(), tempnodes.begin(), tempnodes.end());
		}
		return nodes;
	}
}
void newnode(string word)//添加新单词
{
	node newword;
	newword.nodeword = word;
	newword.head = word[0];
	newword.tail = word.back();
	newword.wordlen = word.length();
	//把单词加入图
	addtomap(newword);
}
void addtomap(node newword) 
{
	int i = 0;
	int index = map.size();
	for (i = 0; i < index; i++)
	{
		if (map[i].nodeword == newword.nodeword)
		{
			return;
		}
	}
	for (i = 0 ; i < index; i++)
	{
		if (map[i].tail == newword.head)
		{
			map[i].next.push_back(index);
		}
		if (map[i].head == newword.tail)
		{
			newword.next.push_back(i);
		}
	}
	map.push_back(newword);
}
void printmap() 
{
	cout << "------------Map Detail------------" << endl;
	int i = 0;
	for (i = 0; i < map.size(); i++)
	{
		cout << i << "  ";
		printnode(map[i]);
	}
}
void printnode(node n) {
	cout << n.nodeword << "  ";
	int i = 0;
	for (i = 0; i < n.next.size(); i++)
	{
		cout << n.next[i] << "  ";
	}
	cout << endl;
}
void printforest()
{
	cout << "----------All List---------" << endl;
	int i = 0;
	int j = 0;
	cout << "forest_size = " << forest.size() << endl;
	for (i = 0; i < forest.size(); i++)
	{
		for (j = 0; j < forest[i].size(); j++)
		{
			cout << forest[i][j] << " --> ";
		}
		cout << endl;
	}
}
void readfile(string filepath)
{
	ifstream infile;
	infile.open(filepath);
	char ch;
	string word;
	while (!infile.eof())
	{
		ch = infile.get();
		if (isalpha(ch))
		{
			if (isupper(ch))//大写转换为小写
			{
				ch = tolower(ch);
			}
			word += ch;
		}
		else{
			if (word.length() > 0)
			{
				//cout << word << endl;
				//读到单词后的操作，把单词填入有向图中
				newnode(word);

				word.erase();
			}
		}
	}
}

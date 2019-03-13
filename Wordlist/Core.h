#pragma once
#include <string>
#include <string.h>
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
class Core
{
public:
	Core();
	~Core();
	int gen_chain_word(char* words[], int len, char* result[],char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
private:

	void newnode(string word);
	void addtomap(node newword);
	void toforest();
	void next1(vector<int> forward, int root);
	void next2(vector<int> forward, int root);
	int findmostwords(char head, char tail);
	int findlongest(char head, char tail);
	int listlength(int index);
	vector<node> map;//有向图
	vector<vector<int>> forest;
	bool if_w = false;
	bool if_c = false;
	bool if_h = false;
	bool if_t = false;
	bool if_r = false;
	char head_alpha = ' ';
	char tail_alpha = ' ';
};
#pragma once
#include <string>
#include <string.h>
#include <vector>

using namespace std;
struct node
{
	string nodeword;//����
	char head;//����ĸ
	char tail;//β��ĸ
	vector<int> next;//����ĩβ���ӵ���һ���������
	int wordlen;//���ʳ���
};
class Core
{
public:
	Core();
	~Core();
	int gen_chain_word(char* words[], int len, char* result[],char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

	void testprint(int x);
private:

	void newnode(string word);
	void addtomap(node newword);
	void toforest();
	void next1(vector<int> forward, int root);
	void next2(vector<int> forward, int root);
	int findmostwords(char head, char tail);
	int findlongest(char head, char tail);
	int listlength(int index);
	vector<node> map;//����ͼ
	vector<vector<int>> forest;
	bool if_w = false;
	bool if_c = false;
	bool if_h = false;
	bool if_t = false;
	bool if_r = false;
	char head_alpha = ' ';
	char tail_alpha = ' ';
};
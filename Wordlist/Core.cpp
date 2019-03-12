#include"Core.h"
#include<iostream>
#include<string>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::endl;



Core::Core(){}
Core::~Core() {}
void Core::testprint(int x)
{
	std::cout << x << std::endl;
}
int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	int i = 0;
	if_r = enable_loop;
	if_w = true;
	if_h = isalpha(head);
	if_t = isalpha(tail);
	int resultindex = -1;
	for (i = 0; i < len; i++)
	{
		string word = words[i];
		newnode(word);
	}
	toforest();
	resultindex = findmostwords(head, tail);
	for (i = 0; i < forest[resultindex].size(); i++)
	{
		result[i] = const_cast<char*>(map[forest[resultindex][i]].nodeword.c_str());
	}
	return forest[resultindex].size();
}
int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) 
{
	int i = 0;
	if_r = enable_loop;
	if_c = true;
	if_h = isalpha(head);
	if_t = isalpha(tail);
	int resultindex = -1;
	for (i = 0; i < len; i++)
	{
		string word = words[i];
		newnode(word);
	}
	toforest();
	resultindex = findlongest(head, tail);
	for (i = 0; i < forest[resultindex].size(); i++)
	{
		result[i] = const_cast<char*>(map[forest[resultindex][i]].nodeword.c_str());
	}
	return forest[resultindex].size();
}

void Core::newnode(string word)
{
	node newword;
	newword.nodeword = word;
	newword.head = word[0];
	newword.tail = word.back();
	newword.wordlen = word.length();
	//�ѵ��ʼ���ͼ
	addtomap(newword);
}

void Core::addtomap(node newword)
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
	for (i = 0; i < index; i++)
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
void Core::toforest()
{
	int i = 0;
	if (if_t)
	{
		for (i = 0; i < map.size(); i++)
		{
			vector<int> forward;
			next2(forward, i);
		}
	}
	else {
		for (i = 0; i < map.size(); i++)
		{
			vector<int> forward;
			next1(forward, i);
		}
	}
}
void Core::next1(vector<int> forward, int root)
{
	int i = 0;
	for (i = 0; i < forward.size(); i++) {
		if (forward[i] == root)//�л�
		{
			if (!if_r)
			{
				cout << "���� ���е��ʻ�" << endl;

			}
			else {
				if (forward.size() > 1)
				{
					forest.push_back(forward);
				}
			}
			return;
		}
	}
	forward.push_back(root);
	if (map[root].next.size() == 0 && forward.size() > 1)
	{
		forest.push_back(forward);
		return;
	}
	else {
		int j = 0;
		for (j = 0; j < map[root].next.size(); j++)
		{
			next1(forward, map[root].next[j]);
		}
	}
}
void Core::next2(vector<int> forward, int root)
{
	int i = 0;
	for (i = 0; i < forward.size(); i++) {
		if (forward[i] == root)//�л�
		{
			if (!if_r)
			{
				cout << "���� ���е��ʻ�" << endl;

			}
			else {
				if (forward.size() > 1)
				{
					forest.push_back(forward);
				}
			}
			return;
		}
	}
	forward.push_back(root);
	if (forward.size() > 1)
	{
		forest.push_back(forward);
	}
	if (map[root].next.size() == 0)
	{
		return;
	}
	else {
		int j = 0;
		for (j = 0; j < map[root].next.size(); j++)
		{
			next2(forward, map[root].next[j]);
		}
	}
}
int Core::findmostwords(char head, char tail)
{
	int i = 0;
	int tempmax = 0;
	int tempindex = -1;
	if (isalpha(head) && !isalpha(tail))//ֻ�涨����������ĸ
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i][0]].head == head)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else if (!isalpha(head) && isalpha(tail))//ֻ�涨������β��ĸ
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i].back()].tail == tail)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else if (isalpha(head) && isalpha(tail)) {//�涨����ĸ��β��ĸ
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax && map[forest[i][0]].head == head && map[forest[i].back()].tail == tail)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	else {//û�й涨
		for (i = 0; i < forest.size(); i++)
		{
			if (forest[i].size() > tempmax)
			{
				tempmax = forest[i].size();
				tempindex = i;
			}
		}
	}
	if (tempindex >= 0)
	{
		return tempindex;
	}
}
int Core::findlongest(char head, char tail)
{
	int i = 0;
	int templong = 0;
	int tempindex = -1;
	int length = 0;
	if (if_h && !if_t)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i][0]].head == head_alpha)
			{
				length = listlength(i);
				if (length > templong)
				{
					templong = length;
					tempindex = i;
				}
			}
		}
	}
	else if (if_t && !if_h)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i].back()].tail == tail_alpha)
			{
				length = listlength(i);
				if (length > templong)
				{
					templong = length;
					tempindex = i;
				}
			}
		}
	}
	else if (if_h && if_t)
	{
		for (i = 0; i < forest.size(); i++)
		{
			if (map[forest[i][0]].head == head_alpha && map[forest[i].back()].tail == tail_alpha)
			{
				length = listlength(i);
				if (length > templong)
				{
					templong = length;
					tempindex = i;
				}
			}
		}
	}
	else {
		for (i = 0; i < forest.size(); i++)
		{
			length = listlength(i);
			if (length > templong)
			{
				templong = length;
				tempindex = i;
			}
		}
	}
	if (tempindex>=0 && forest[tempindex].size() > 1)
	{
		return tempindex;
	}
}
int Core::listlength(int index)
{
	int sum = 0;
	int i = 0;
	for (i = 0; i < forest[index].size(); i++)
	{
		sum += map[forest[index][i]].wordlen;
	}
	return sum;
}
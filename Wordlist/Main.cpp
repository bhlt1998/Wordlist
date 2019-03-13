#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Core.h"
using namespace std;
/*
struct node
{
	string nodeword;//单词
	char head;//首字母
	char tail;//尾字母
	vector<int> next;//能在末尾连接的下一个单词序号
	int wordlen;//单词长度
};
*/
int readfile(string filepath,char* words[]);
void printdetail(char* result[], int resultlen);
void printtofile(char* result[], int resultlen);
//void printmap();
//void printnode(node n);
//void printforest();
vector<string> readword; 
/*----------------------------------------------------------------*/
int main(int argc, char* argv[])
{	
	try {
		char* result[10001];
		char* words[10001];
		int wordslen = 0;
		string filepath;
		char* parameter;
		int i = 0;
		int resultlen = 0;
		bool if_head = false;
		bool if_tail = false;
		bool if_word = false;
		bool if_char = false;
		bool if_roun = false;
		char head_alpha = 0;
		char tail_alpha = 0;
		Core* core = new Core();

		/*----------------------命令行参数处理---------------------------*/
		if (argc > 1)
		{
			for (i = 1; i < argc; i++)
			{
				parameter = argv[i];
				if (strcmp(parameter, "-h") == 0)
				{
					if (if_head)
					{
						cout << "错误：-h参数重复" << endl;
						exit(0);
					}
					if_head = true;
					i++;
					parameter = argv[i];
					if (strlen(parameter) == 1 && isalpha(parameter[0]))
					{
						head_alpha = parameter[0];
					}
					else
					{
						cout << "错误：-h后没有字母" << endl;
						exit(0);
					}
				}
				else if (strcmp(parameter, "-t") == 0)
				{
					if (if_tail)
					{
						cout << "错误：-t参数重复" << endl;
						exit(0);
					}
					if_tail = true;
					i++;
					parameter = argv[i];
					if (strlen(parameter) == 1 && isalpha(parameter[0]))
					{
						tail_alpha = parameter[0];
					}
					else
					{
						cout << "错误：-t后没有字母" << endl;
						exit(0);
					}
				}
				else if (strcmp(parameter, "-r") == 0)
				{
					if (if_roun)
					{
						cout << "错误：-r参数重复" << endl;
						exit(0);
					}
					if_roun = true;
				}
				else if (strcmp(parameter, "-w") == 0)
				{
					if (if_word || if_char)
					{
						cout << "错误：-w\-c参数重复" << endl;
						exit(0);
					}
					if_word = true;
					i++;
					filepath = argv[i];
					//				readfile(filepath);				
				}
				else if (strcmp(parameter, "-c") == 0)
				{
					if (if_word || if_char)
					{
						cout << "错误：-w\-c参数重复" << endl;
						exit(0);
					}
					if_char = true;
					i++;
					filepath = argv[i];
					//				readfile(filepath);
				}
				else {
					cout << "错误：参数错误" << endl;
					exit(0);
				}
			}
		}
		else {
			cout << "参数错误" << endl;
			exit(0);
		}
		wordslen = readfile(filepath, words);
		if (if_word)
		{
			resultlen = core->gen_chain_word(words, wordslen, result, head_alpha, tail_alpha, if_roun);
		}
		else if (if_char)
		{
			resultlen = core->gen_chain_char(words, wordslen, result, head_alpha, tail_alpha, if_roun);
		}
		if (resultlen > 1) {
			printdetail(result, resultlen);
			printtofile(result, resultlen);
		}
	}
	catch (exception e) {
		cout <<"错误： " << e.what() << endl;
	}
	return 0;
}

void printdetail(char* result[],int resultlen)
{
	int i = 0;
	for (i = 0; i < resultlen; i++) 
	{
		cout << result[i] << endl;
	}
}
int readfile(string filepath, char* words[])
{
	ifstream infile;
	infile.open(filepath);

	int i = 0;
	if (!infile)
	{
		cout << "文件不存在" << endl;
		exit(0);
	}
	char ch;
	string word;
	while (!infile.eof())
	{
		ch = infile.get();
		if (isalpha(ch))
		{
			word += ch;
		}
		else {
			if (word.length() > 0)
			{
				//读到单词后的操作，把单词加入单词表
				readword.push_back(word);
				word.erase();
			}
		}
	}
	infile.close();
	for (i = 0; i < readword.size(); i++)
	{
		words[i] = const_cast<char*>(readword[i].c_str());
	}
	return readword.size();
}

void printtofile(char* result[], int resultlen)
{
	ofstream outfile;
	outfile.open("solution.txt");
	int i = 0;
	for (i = 0; i < resultlen; i++)
	{
		outfile << result[i] << endl;
	}
	outfile.close();
}

//void printmap() 
//{
//	cout << "------------Map Detail------------" << endl;
//	int i = 0;
//	for (i = 0; i < map.size(); i++)
//	{
//		cout << i << "  ";
//		printnode(map[i]);
//	}
//}
//void printnode(node n) {
//	cout << n.nodeword << "  ";
//	int i = 0;
//	for (i = 0; i < n.next.size(); i++)
//	{
//		cout << n.next[i] << "  ";
//	}
//	cout << endl;
//}
//void printforest()
//{
//	cout << "----------All List---------" << endl;
//	int i = 0;
//	int j = 0;
//	cout << "forest_size = " << forest.size() << endl;
//	for (i = 0; i < forest.size(); i++)
//	{
//		for (j = 0; j < forest[i].size(); j++)
//		{
//			cout << forest[i][j] << " --> ";
//		}
//		cout << endl;
//	}
//}

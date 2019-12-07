#pragma once
#include<string>
using namespace std;
enum Nodekind{
	ELEMENT, //字符
	CONCAT,  //连接
	ALT,     // 或
	CLOSURE, //闭包
	ZORONE   //？
}; 
const int EPS = -2;
struct ReTreeNode {
	Nodekind kind;
	char c;
	ReTreeNode* childs[2];
	ReTreeNode(Nodekind kind, char c, ReTreeNode* lch, ReTreeNode* rch) {
		this->kind = kind;
		this->c = c;
		childs[0] = lch, childs[1] = rch;
	}
};

class ReTree {

	string reg;
	ReTreeNode* root;
	int pos;
	char curc;
	char getnext();
	ReTreeNode* parse(); //处理|
	ReTreeNode* parse_A(); //处理与
	ReTreeNode* parse_B(); //处理*或者？
	ReTreeNode* parse_C(); //处理元素
	bool iselement();

public:
	ReTree(const string &s);
	ReTreeNode* getroot();
};
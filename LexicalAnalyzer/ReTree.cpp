#include "ReTree.h"
#include<iostream>
char ReTree::getnextChar()
{
	//cout << reg[pos];
	return pos < reg.size() ? reg[pos++] : '\0';
}
/* 处理语法糖[] */
void ReTree::update()
{
	std::string rv;
	int it = 0, it2 = -1;
	it = reg.find('[', it2 + 1);
	while (it > 0 && reg[it - 1] == '\\') it = reg.find('[', it + 1);
	while (it != reg.npos) {
		rv += reg.substr(it2 + 1, it - it2 - 1);
		it2 = reg.find(']', it);
		while (it2 > 0 && reg[it2 - 1] == '\\') it2 = reg.find(']', it2 + 1);
		if (it2 == reg.npos) {
			std::cout << "Lexical Analyzation Errinfo: " << "can't find matching ] in " << std::endl;
			std::cout << reg << "  pos:" << it << std::endl;
			//exit(0);
		}
		std::string temp, sub;
		sub = reg.substr(it + 1, it2 - it - 1);
		temp.push_back('(');
		for (int i = 0; i < sub.size() / 3; ++i) {
			for (char c = sub[i * 3]; c <= sub[i * 3 + 2]; ++c) {
				temp.push_back(c);
				temp.push_back('|');
			}
		}
		temp.pop_back();
		temp.push_back(')');
		rv += temp;
		it = reg.find('[', it2);
		while (it > 0 && reg[it - 1] == '\\') it = reg.find('[', it + 1);
	}
	rv += reg.substr(it2 + 1);
	reg = rv;
}
/*处理整个正则表达式*/
ReTreeNode * ReTree::parse()
{
	ReTreeNode* t = parse_A();
	while (currentChar == '|') {
		currentChar = getnextChar();
		ReTreeNode *p = parse_A();
		ReTreeNode *alt = new ReTreeNode(ALT, '|', t, p);
		t = alt;
	}
	return t;
}
/*处理正则表达式中的与部分*/
ReTreeNode * ReTree::parse_A()
{
	ReTreeNode* t = parse_B();
	while (currentChar != '|' && currentChar!=')' && currentChar != '\0') {
		ReTreeNode *p = parse_B();
		ReTreeNode *concat = new ReTreeNode(CONCAT, '&', t, p);
		t = concat;
	}
	return t;
}
/*处理正则表达式中*和？部分*/
ReTreeNode * ReTree::parse_B() {
	ReTreeNode *t = parse_C();
	while (currentChar == '*'||currentChar == '?') {
		if (currentChar == '*') t = new ReTreeNode(CLOSURE, '*', t, nullptr);
		else t = new ReTreeNode(ZORONE, '?', t, nullptr);
		currentChar = getnextChar();
	}
	return t;
}
/*处理正则表示的最小单元*/
ReTreeNode * ReTree::parse_C() {
	ReTreeNode* t = nullptr;
	if (currentChar == '(') {
		currentChar = getnextChar();
		t = parse();
		currentChar = getnextChar();
	}
	else {
		if (currentChar == '\\') currentChar = getnextChar();
		t = new ReTreeNode(ELEMENT, currentChar, nullptr, nullptr);
		alphabets.insert(currentChar);
		currentChar = getnextChar();
	}
	return t;
}

void ReTree::RE2tree()
{
	update();
	currentChar = getnextChar();
	if (currentChar != '\0')
		root = parse();
}

ReTree::ReTree(const std::string & s)
{
	root = nullptr;
	pos = 0;
	currentChar = '\0';
	reg = s;
	RE2tree();
}

ReTree::ReTree()
{
}

ReTreeNode * ReTree::getroot()
{
	return root;
}

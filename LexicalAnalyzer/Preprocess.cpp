#include "Preprocess.h"

#include <fstream>
#include<iostream>

Preprocess::Preprocess()
{
	is_block_comment = false;
}
void Preprocess::trim(std::string & s)
{
	int it, it2;
	if (is_block_comment) {
		it = s.find("*/", 0);
		if (it == s.npos) s.clear();
		else {
			s.erase(s.begin(), s.begin() + it + 2);
			is_block_comment = false;
		}
	}
	it = s.find("////", 0);
	if (it != s.npos) s.erase(s.begin() + it, s.end());
	it = s.find("//*", 0);
	if (it != s.npos) {
		it2 = s.find("*/", 0);
		if (it2 != s.npos) {
			s.erase(s.begin() + it, s.begin() + it + 2);
		}
		else {
			s.erase(s.begin() + it, s.end());
			is_block_comment = true;
		}
	}
}
void Preprocess::read_codefile(std::string filename)
{
	std::string temp;
	code_filename = filename;
	ifstream in(code_filename);
	if (!in.is_open()) {
		cout << "未成功打开code文件" << endl;
		return;
	}
	while (getline(in, temp)) {
		trim(temp);
		lines.push_back(temp);
	}
}

void Preprocess::read_regsfile(std::string filename)
{
	std::string temp;
	std::string curkind;
	std::string name, reg;
	regs_filename = filename;
	ifstream in(regs_filename);
	if (!in.is_open()){
		cout << "未成功打开regs文件" << endl;
		return;
	}
	while (getline(in, temp)) {
		if (temp[0] == '`') {
			curkind = temp.substr(1);
			continue;
		}
		int it = temp.find(':');
		name = temp.substr(0, it);
		reg = temp.substr(it + 1);
		if (curkind[0] == 'S')opes[name] = reg;
		else if (curkind[0] == 'R')reserved_words[name] = reg;
		else regs[name] = reg;
	}
	in.close();
}

void Preprocess::buildLA(LexicalAnalyzer & LA)
{
	LA.build(regs, opes, reserved_words);
}

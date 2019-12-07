#pragma once
#include<map>
#include"MDFA.h"
enum codekind{IDENT, NUM, OPRT, STRING, CHAR, RESERVE};
string kindexp[6] = { "IDENT", "NUM", "OPRT", "STRING","CHAR", "RESERVE" };
const int ERROR = -1;
struct code2kind {
	std::string code;
	codekind kind;
};
class LexicalAnalyzer {
	std::map<enum codekind, MDFA> MDFAs;
	std::map<std::string, int> reserved_words;
	std::map<std::string, int> opes;
	std::map<int, std::string> id2reserved_sig;
	std::map<int, std::string> id2opes_sig;
	std::vector<std::vector<code2kind>> outputs;
	std::string test_str;
	int pos;
	int line;
	char currentChar;
	char getnextChar();
	int nextstate(MDFANode &mdfanode, int c);
	std::vector<code2kind> match(const std::string &text);
	bool match_single_mdfa(MDFA &mdfa, code2kind &cdkd);
	bool match_string(code2kind &cdkd);
	bool match_char(code2kind &cdkd);
	bool match_ope(code2kind &cdkd);
	void print(std::string out_filename);
	void rollback();
	void RaiseExption(string errinfo);
	void reset();
	void NextUnspace();
	void print_(ostream &o);
public:
	LexicalAnalyzer();
	void parse(std::vector<std::string> &lines, std::string out_filename = "");
	void build(const std::map<std::string, std::string> &regs,
		const std::map<std::string, std::string> opes,
		const std::map<std::string, std::string> reserved_words);
	
};
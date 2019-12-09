#include "LexicalAnalyzer.h"
#include<iostream>
#include<stack>
#include<fstream>

char LexicalAnalyzer::getnextChar()
{
	return test_str[pos++];
}

int LexicalAnalyzer::nextstate(MDFANode &mdfanode, int c)
{
	auto edges = mdfanode.edges;
	for (auto &e : edges) {
		if (e.c == c) return e.to;
	}
	return -1;
}

std::vector<code2kind> LexicalAnalyzer::match(const std::string & text)
{
	code2kind cdkd;
	std::vector<code2kind> rv;
	test_str = text;
	bool ismatched = false;
	reset();
	while (pos != test_str.size()) {
		NextUnspace();
		//匹配保留字，标识符，数字
		for (auto &mdfapairs : MDFAs) {
			auto &mdfa = mdfapairs.second;
			codekind kind = mdfapairs.first;
			if (match_single_mdfa(mdfa, cdkd)) {
				if (kind == IDENT && reserved_words.find(cdkd.code) != reserved_words.end()) {
					cdkd.code = id2reserved_sig[reserved_words[cdkd.code]];
					kind = RESERVE;
				}
				cdkd.kind = kind;
				ismatched = true;
				break;
			}
		}
		if (ismatched) {
			rv.push_back(cdkd);
			ismatched = false;
			continue;
		}
		if (match_string(cdkd)) {
			cdkd.kind = STRING;
			rv.push_back(cdkd);
		}
		else if (match_char(cdkd)) {
			cdkd.kind = CHAR;
			rv.push_back(cdkd);
		}
		else if (match_ope(cdkd)) {
			cdkd.kind = OPRT;
			cdkd.code = id2opes_sig[opes[cdkd.code]];
			rv.push_back(cdkd);
		}
		else {
			rv.clear();
			return rv;
		}
	}
	return rv;
}

bool LexicalAnalyzer::match_single_mdfa(MDFA & mdfa, code2kind & cdkd)
{
	bool ismatched;
	int state = mdfa.getstart();
	int lastpos = pos;
	std::vector<int> s;
	auto &nodes = mdfa.get_nodes();
	while (state != ERROR && pos<test_str.size()) {
		currentChar = getnextChar();
		if (nodes[state].accept)
			s.clear();
		s.push_back(state);
		state = nextstate(nodes[state], currentChar);
	}
	while (!s.empty() && (state == ERROR || !nodes[state].accept)) {
		state = *(s.end()-1);
		s.pop_back();
		rollback();
	}
	ismatched = state!=ERROR && nodes[state].accept;
	if (ismatched) cdkd.code = test_str.substr(lastpos, pos - lastpos);
	return ismatched;
}

bool LexicalAnalyzer::match_string(code2kind & cdkd)
{
	if (currentChar == '"') {
		int it = test_str.find('"', pos + 1);
		if (it == test_str.npos) {
			RaiseExption("no matching right Double_Quotation_Marks");
		}
		cdkd.code = test_str.substr(pos, it - pos + 1);
		pos = it + 1;
		return true;
	}
	return false;
}

bool LexicalAnalyzer::match_char(code2kind & cdkd)
{
	if (currentChar == '\'') {
		int it = test_str.find('\'', pos + 1);
		if (it == test_str.npos) {
			RaiseExption("no matching right Single_Quotation_Marks");
		}
		cdkd.code = test_str.substr(pos, it + 1 - pos);
		pos = it + 1;
		return true;
	}
	return false;
}

bool LexicalAnalyzer::match_ope(code2kind & cdkd)
{
	bool ismatched = false;
	if (pos+1 < test_str.size() && opes.find(test_str.substr(pos, 2)) != opes.end()) {
		cdkd.code = test_str.substr(pos, 2);
		ismatched = true;
		pos += 2;
	}
	else if(opes.find(test_str.substr(pos, 1)) != opes.end()){
		cdkd.code = test_str.substr(pos, 1);
		ismatched = true;
		++pos;
	}
	return ismatched;
}
void LexicalAnalyzer::print(std::string out_filename)
{
	if (!out_filename.empty()) {
		std::ofstream of;
		of.open(out_filename, std::ios::out);
		if (!of.is_open()) {
			RaiseExption("Can not open output file.");
		}
		print_(of);
	}
	else print_(std::cout);
}

void LexicalAnalyzer::rollback()
{
	--pos;
}

void LexicalAnalyzer::RaiseExption(std::string errinfo)
{
	std::cout << "Lexical Analyzation Errinfo: " << errinfo << std::endl;
	std::cout<<"Line: " << line << "  pos: " << pos << "  character: " << currentChar << std::endl;
	//exit(0);
}

void LexicalAnalyzer::reset()
{
	pos = 0;
}

void LexicalAnalyzer::NextUnspace()
{
	while (pos < test_str.size() && (test_str[pos] == ' '|| test_str[pos]=='\t')) ++pos;
}

void LexicalAnalyzer::print_(std::ostream & o)
{
	for (auto &line : outputs) {
		for (auto &cdkd : line) {
			o << cdkd.code << "   ";
		}
		o << std::endl;
	}
	o << "----------------------------" << std::endl;
	for (auto &line : outputs) {
		for (auto &cdkd : line) {
			o << kindexp[cdkd.kind] << "   ";
		}
		o << std::endl;
	}
}

LexicalAnalyzer::LexicalAnalyzer()
{
	pos = 0; currentChar = '\0';
}

void LexicalAnalyzer::parse(std::vector<std::string>& lines, std::string out_filename)
{
	for (int i = 0; i < lines.size();++i) {
		pos = 0;
		line = i;
		outputs.push_back(match(lines[i]));
		if ((*outputs.rbegin()).empty()) {
			RaiseExption("Illegal character :");
		}
	}
	print(out_filename);
}



void LexicalAnalyzer::build(const std::map<std::string, std::string>& regs, const std::map<std::string, std::string> opes, const std::map<std::string, std::string> reserved_words)
{
	int i = 257;
	for (auto &e : opes) {
		id2opes_sig[i] = e.first;
		this->opes[e.second] = i;
		++i;
	}
	for (auto &e : reserved_words) {
		id2reserved_sig[i] = e.first;
		this->reserved_words[e.second] = i;
		++i;
	}
	for (auto &e : regs) {
		if(e.first=="id") MDFAs[IDENT] = MDFA(e.second);
		else MDFAs[NUM] = MDFA(e.second);
	}
}


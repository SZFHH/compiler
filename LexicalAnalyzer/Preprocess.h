#pragma once
#include"LexicalAnalyzer.h"
class Preprocess {
	std::string regs_filename;
	std::string code_filename;
	std::map<std::string, std::string> regs;
	std::map<std::string, std::string> opes;
	std::map<std::string, std::string> reserved_words;
	std::vector<std::string> lines;
	void trim(std::string & s);
	bool is_block_comment;
public:
	Preprocess();
	void read_codefile(std::string filename);
	void read_regsfile(std::string filename);
	void buildLA(LexicalAnalyzer &LA);

};
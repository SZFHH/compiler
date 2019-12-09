#include"Preprocess.h"
#include"LexicalAnalyzer.h"
#include<iostream>

void test(Preprocess &ppr, LexicalAnalyzer &la) {
	ppr.read_codefile("input.cpp");
	la.parse(ppr.get_code_file(), "");
}

int main(int argc, char *argv[]) {
	Preprocess ppr;
	LexicalAnalyzer LA;
	ppr.read_regsfile("regs.txt");
	ppr.buildLA(LA);
	if (argc > 1) {
		ppr.read_codefile(argv[1]);
		LA.parse(ppr.get_code_file(), "");
	}
	else test(ppr, LA);
	return 0;
}
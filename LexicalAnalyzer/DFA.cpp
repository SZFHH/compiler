#include "DFA.h"
#include<queue>
std::set<int> DFA::delta(const std::set<int>& st, char c)
{
	auto &allnfaedges = nfa.getalledges();
	std::set<int> rv;
	auto itpairs = allnfaedges.equal_range(c);
	auto startit = itpairs.first;
	auto endit = itpairs.second;
	for (auto it = startit; it != endit; ++it) {
		if (st.find(it->second->from) != st.end()) rv.insert(it->second->to);
	}
	return rv;
}
std::set<int> DFA::closure(const std::set<int>& st)
{
	std::set<int> rv;
	std::queue<int> q;
	auto &allnfanodes = nfa.getallnodes();
	for (auto &e : st) {
		q.push(e);
		allnfanodes[e].visit = true;
	}
	while (!q.empty()) {
		int id = q.front();
		rv.insert(id);
		q.pop();
		for (auto &edge : allnfanodes[id].edges) {
			if (edge.c == EPS) {
				if (!allnfanodes[edge.to].visit) {
					allnfanodes[edge.to].visit = true;
					q.push(allnfanodes[edge.to].num);
				}
			}
		}
	}
	nfa.resetvisit();
	return rv;
}
int DFA::InsertOrFind(const std::set<int>& st)
{
	for (int i = 0; i < allnodes.size(); ++i) {
		if (allnodes[i].vertex == st) return i;
	}
	addnewnode = true;
	allnodes.push_back(DFANode(st, st.find(nfa.getAccept()) != st.end(), allnodes.size()));
	return allnodes.size() - 1;
}
void DFA::addedge(const std::set<int>& from, const std::set<int>& to, char c)
{
	int from_ = InsertOrFind(from);
	int to_ = InsertOrFind(to);
	allnodes[from_].edges.push_back(DFAedge(from_, to_, c));
}
void DFA::SubsetConstruct()
{
	std::set<int> from, to;
	std::queue<std::set<int>> worklist; //工作区，存储第一次出现的点集
	worklist.push(closure({ nfa.getStart() }));
	while (!worklist.empty()) {
		from = worklist.front();
		worklist.pop();
		for (auto &c : alphabets) {
			to = delta(from, c);
			if (to.empty()) continue;
			to = closure(to);
			addedge(from, to, c);
			//如果加入了新的点，把新的点加入worklist（除了第一次会新建from，之后只可能新建to）
			if (addnewnode) {
				worklist.push(to);
				addnewnode = false;
			}
		}
	}
}

void DFA::NFA_to_DFA()
{
	SubsetConstruct();
	//存边，供MDFA使用
	for (auto &node : allnodes) {
		for (auto &edge : node.edges) {
			alledges.insert({ edge.c, &edge });
		}
	}
}

DFA::DFA(const std::string & reg):nfa(reg)
{
	addnewnode = false;
	alphabets = nfa.getalphabets();
	NFA_to_DFA();
}

DFA::DFA()
{
}

std::vector<DFANode>& DFA::getallnodes()
{
	return allnodes;
}

std::multimap<char, DFAedge*>& DFA::getalledges()
{
	return alledges;
}

#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

vector<string> parts;
map<string, long> memo;

long combinations(string word)
{
	long result = 0;
	if(word.size() == 0) {
		//cout<<" (end)"<<endl;
		return 1;
	}
	for(auto part : parts) {
		if(part == word.substr(0, part.size())) {
			//cout<<part<<",";
			string next = word.substr(part.size(), word.npos);
			if(memo.count(next)) { 
				result += memo[next];
			} else {
				long combos = combinations(next);
				result += combos;
				memo[next] = combos;
			}
		}
	}
	return result;
}

int main()
{
	vector<string> words;
	char prev = -1;
	char c = -1;
	string s1 = "";
	while(1) {
		c = cin.get();
		if(prev == '\n' && c == '\n')
			break;
		if(c == ',') {
			parts.push_back(s1);
			s1 = "";
		} else if (isalpha(c))
			s1 += c;
		prev = c;
	}
	parts.push_back(s1);
	s1 = "";
	while(!cin.eof()) {
		c = cin.get();
		if(c != '\n')
			s1+=c;
		else {
			words.push_back(s1);
			s1 = "";
		}
	}
	for(auto p : parts)
		cout<<p<<',';
	cout<<endl;
	for(auto w : words)
		cout<<w<<endl;
	long result = 0;
	for(int i = 0; i < words.size(); i++) {
		auto w = words[i];
		cout<<i*100 / words.size()<<'%'<<endl;
		result += combinations(w);
	}
	cout<<"The result: "<<result<<endl;
	return 0;
}

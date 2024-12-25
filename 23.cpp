#include<iostream>
#include<map>
#include<set>

using namespace std;

pair<string,string> mkp(string a, string b)
{
	return make_pair(a,b);
}

map<string,set<string>> graph;

int main()
{
	while(!cin.eof()) {
		string s1 = "";
		string s2 = "";
		cin>>s1;
		if(cin.eof())
			break;
		cin>>s2;
		graph[s1].insert(s2);
		graph[s2].insert(s1);
	}
	for(auto cons : graph) {
		for(auto node : cons.second) {
			cout<<"("<<cons.first<<","<<node<<")"<<endl;
		}
	}
	set<set<string>> friends;
	for(auto his : graph) {
		if(his.first[0] != 't')
			continue;
		for(string pal1 : his.second) {
			for(string pal2 : graph[pal1]) {
				if(graph[pal2].count(his.first)) {
					cout<<his.first<<","
					    <<pal1<<","
					    <<pal2<<endl;
					set<string> pals;
					pals.clear();
					pals.insert(his.first);
					pals.insert(pal1);
					pals.insert(pal2);
					friends.insert(pals);
				}
			}
		}
	}
	cout<<"Rsuelt: "<<friends.size()<<endl;
	return 0;
}

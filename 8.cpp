#include<iostream>
#include<map>
#include<vector>

using namespace std;

pair<int, int> mkp(int a, int b) {
	return make_pair(a, b);
}

pair<int, int> adp(pair<int,int> a, pair<int, int> b) {
	return mkp(a.first+b.first, a.second+b.second);
}

pair<int, int> subp(pair<int, int> a, pair<int, int> b) {
	return mkp(a.first-b.first, a.second-b.second);
}

pair<int, int> p2x(pair<int, int> a) {
	return mkp(a.first*2, a.second*2);
}

int main()
{
	map<pair<int, int>, bool> antinodes;
	map<char, vector<pair<int,int>>> antennae;
	int width = 0;
	int height = 0;
	int x = 0;
	int y = 0;
	while(!cin.eof()) {
		char c = cin.get();
		if(c == '\n' || c == '\r') {
			y++;
			if(!width)
				width = x;
			x=0;
			continue;
		} else if(c == '.') {
			x++;
			continue;
		} else {
			if(!antennae.count(c)) {
				antennae[c] = vector<pair<int,int>>();
				antennae[c].push_back(mkp(x, y));
			} else {
				pair<int, int> here = mkp(x, y);
				for(auto a : antennae[c]) {
					antinodes[subp(p2x(a), here)] = true;
					antinodes[subp(p2x(here), a)] = true;
				}
				antennae[c].push_back(here);
			}
			x++;
		}
	}
	height = y;
	int result = 0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(antinodes[mkp(j,i)] == true) {
				cout<<'#';
				result++;
			} else {
				cout<<'.';
			}
		}
		cout<<endl;
	}
	cout<<"result: "<<result<<endl;
	return 0;
}

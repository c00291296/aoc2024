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

bool pair_oob(pair<int, int> a, int w, int h) {
	return a.first < 0 || a.second < 0 ||
		a.first >= w || a.second >= h;
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
				antinodes[here] = true;
				antinodes[antennae[c][0]] = true;
				
				for(auto a : antennae[c]) {
					auto step = subp(a, here);
					//to there
					int c=0;
					for(auto p = adp(here, step);
							c<100;
							p=adp(p, step), c++)
						antinodes[p] = true;
					//to here
					c=0;
					auto unstep = subp(mkp(0,0), step);
					for(auto p = adp(a, unstep);
							c<100;
							p=adp(p, unstep), c++)
						antinodes[p] = true;

				}
				antennae[c].push_back(here);
			}
			x++;
		}
	}
	height = y-1;
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

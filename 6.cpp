#include<iostream>
#include<map>
#include<vector>

using namespace std;

pair<int, int> rot(pair<int, int> dir) {
	map<pair<int, int>, pair<int,int>> rots;
	rots[make_pair(1, 0)] = make_pair(0, 1);
	rots[make_pair(0, 1)] = make_pair(-1, 0);
	rots[make_pair(-1, 0)] = make_pair(0, -1);
	rots[make_pair(0, -1)] = make_pair(1, 0);
	return rots[dir];
}

pair<int, int> addp(pair<int, int> a, pair<int, int> b) {
	return make_pair<int,int>(a.first+b.first, a.second+b.second);
}

bool is_guard(char c)
{
	return c == '^' || c == 'v' || c=='<' || c=='>';
}

int main()
{
	vector<vector<char>> area;
	vector<char> row;
	map<pair<int, int>, bool> visited;
	int x = 0, y = 0;
	int gx = 0, gy = 0;
	while(!cin.eof()) {
		char c = cin.get();
		if(c!='\r' && c!='\n') {
			row.push_back(c);
			if(is_guard(c)) {
				gx = x;
				gy = y;
			}
			x++;
		} else {
			area.push_back(row);
			row = vector<char>();
			x = 0;
			y++;
		}
	}
	row.pop_back(); //remove EOF
	area.push_back(row);
	for(auto r : area) {
		for (char c : r) {
			cout<<c;
		}
		cout<<endl;
	}
	cout << gx << " " << gy << endl;
	return 0;
}

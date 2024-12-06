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

pair<int, int> guard_dir(char g)
{
	switch (g) {
		case '^':
			return make_pair(0, -1);
		case 'v':
			return make_pair(0, 1);
		case '<':
			return make_pair(-1, 0);
		case '>':
			return make_pair(1, 0);
	}
	return make_pair(0xdead, 0xbeef);
}

int main()
{
	vector<vector<char>> area;
	vector<char> row;
	map<pair<int, int>, bool> visited;
	pair<int, int> dir = make_pair(0, -1); //hardcoded for now
	int width = 0;
	int height = 0;
	int x = 0, y = 0;
	int gx = 0, gy = 0;
	while(!cin.eof()) {
		char c = cin.get();
		if(c!='\r' && c!='\n') {
			if(is_guard(c)) {
				gx = x;
				gy = y;
				c = '.';
				visited[make_pair(gx, gy)] = true;
			}
			row.push_back(c);
			x++;
		} else {
			area.push_back(row);
			row = vector<char>();
			x = 0;
			y++;
		}
	}
	width = area[0].size();
	height = area.size();
	//traversal
	while(!(gx + dir.first >= width || gx + dir.first<0)
			&& !(gy+dir.second >= height || gy+ dir.second <0)) {
		int newx = gx + dir.first;
		int newy = gy + dir.second;
		if(area[newy][newx] == '.') {
			gx = newx;
			gy = newy;
			visited[make_pair(gx, gy)] = true;
		} else {
			dir = rot(dir);
		}
	}

	y = 0;
	x = 0;
	for(auto r : area) {
		for (char c : r) {
			if(!visited[make_pair(x,y)])
				cout<<c;
			else
				cout<<"X";
			x++;
		}
		x = 0;
		y++;
		cout<<endl;
	}
	cout << gx << " " << gy << endl;
	int result = 0;
	for (auto p : visited) {
		if(p.second) {
			cout<<"("<<p.first.first<<","<<p.first.second<<")"<<endl;
			result++;
		}
	}
	cout << "unique locations: " << result << endl;
	return 0;
}

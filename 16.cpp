#include<iostream>
#include<vector>
#include<map>
#include<climits>
#include<set>

using namespace std;

pair<int, int> mkp(int a, int b) {
	return make_pair(a, b);
}

pair<int, int> adp(pair<int,int> a, pair<int, int> b) 
{
	return mkp(a.first+b.first, a.second+b.second);
}

vector<vector<char>> maze;

char gt(pair<int, int> pos)
{
//	cout<<"getting x: "<<pos.first<<endl;
//	cout<<"getting y: "<<pos.second<<endl;
	return maze[pos.second][pos.first];
}

pair<int, int> rot(pair<int, int> dir) {
	map<pair<int, int>, pair<int,int>> rots;
	rots[make_pair(1, 0)] = make_pair(0, 1);
	rots[make_pair(0, 1)] = make_pair(-1, 0);
	rots[make_pair(-1, 0)] = make_pair(0, -1);
	rots[make_pair(0, -1)] = make_pair(1, 0);
	return rots[dir];
}

map<pair<int, int>, int> traces;

set<pair<int, int>> visited;

void print_maze()
{
	int y = 0;
	int x = 0;
	for(auto v : maze) {
		for(char c : v) {
			if(visited.contains(mkp(x, y)))
				cout<<"~";
			else
				cout<<c;
			x++;
		}
		y++;
		x=0;
		cout<<endl;
	}
}

void race(pair<int, int> pos, pair<int, int> dir, int score)
{
	pair<int, int> ldir = rot(rot(rot(dir)));
	if(traces.count(pos)) {
		if(traces[pos] > score - 1000)
			traces[pos] = score;
		else
			goto onwards;
	}
	else {
		traces[pos] = score;
	}

	//print_maze();
	if(gt(adp(pos, dir)) != '#')
		race(adp(pos, dir), dir, score+1);
	if(gt(adp(pos, rot(dir))) != '#')
		race(adp(pos, rot(dir)), rot(dir), score+1001);
onwards:
	if(gt(adp(pos, ldir)) != '#')
		race(adp(pos, ldir), ldir, score+1001);
	if(gt(pos) == 'E')
		cout<<"Distance to E: "<<traces[pos]<<endl;
	return;
}


int main()
{
	pair<int, int> dir = mkp(1, 0);
	pair<int, int> pos;
	vector<char> row;
	int x = 0;
	int y = 0;
	while(!cin.eof()) {
		char c = cin.get();
		if(c == '\n' || c == '\r') {
			maze.push_back(row);
			row = vector<char>();
			y++;
			x=0;
			continue;
		} else if (c == 'S') {
			pos = mkp(x, y);
			row.push_back(c);
		} else {
			row.push_back(c);
		}
		x++;
	}
	for(auto v : maze) {
		for(char c : v)
			cout<<c;
		cout<<endl;
	}
	race(pos, dir, 0);
	cout<<"Supposed result... is: "<<traces[mkp(maze[1].size()-2, 1)]<<endl;
	return 0;
}



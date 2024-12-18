#include<iostream>
#include<set>
#include<list>
#include<map>

using namespace std;

const int BYTES = 1024;
const int WIDTH = 71;
const int HEIGHT = 71;

set<pair<int,int>> obstacles;

pair<int, int> mkp(int a, int b)
{
	return make_pair(a, b);
}

pair<int, int> adp(pair<int,int> a, pair<int, int> b) 
{
	return mkp(a.first+b.first, a.second+b.second);
}

pair<int, int> rot(pair<int, int> dir) {
	map<pair<int, int>, pair<int,int>> rots;
	rots[make_pair(1, 0)] = make_pair(0, 1);
	rots[make_pair(0, 1)] = make_pair(-1, 0);
	rots[make_pair(-1, 0)] = make_pair(0, -1);
	rots[make_pair(0, -1)] = make_pair(1, 0);
	return rots[dir];
}

list<pair<int,int>> adjacent(pair<int,int> cell)
{
	list<pair<int,int>> result;
	pair<int,int> dir = mkp(0, -1);
	for(int i = 0; i < 4; i++) {
		dir = rot(dir);
		auto neighbor = adp(cell, dir);
		if(neighbor.first >= 0 && neighbor.second >= 0
		   && neighbor.first < WIDTH && neighbor.second < HEIGHT
		   && (!obstacles.contains(neighbor)))
			result.push_back(neighbor);
	}
	return result;
}

int main()
{
	pair<int, int> startpos = mkp(0, 0), finish=mkp(WIDTH-1, HEIGHT-1);
	list<pair<int, int>> newcells;
	while(!cin.eof()) {
		int x, y;	
		cin>>x;
		if(cin.eof())
			break;
		cin>>y;
		if(obstacles.size() < BYTES)
			obstacles.insert(make_pair(x, y));
		else
			newcells.push_back(mkp(x, y));
	}
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if (obstacles.contains(make_pair(x, y)))
				cout<<'#';
			else
				cout<<'.';
		}
		cout<<endl;
	}
	pair<int, int> answer;
	map<pair<int,int>,pair<int,int>> source;
	for(auto blocker : newcells) {
		//breadth search!!!
		obstacles.insert(blocker);
		bool failure = true;
		source.clear();
		cout<<"Dropping ("<<blocker.first<<","<<blocker.second<<")";
		cout<<endl;
		list<pair<int, int>> cells;
		cells.push_front(startpos);
		while(!cells.empty()) {
			auto cell = cells.front();
			cells.pop_front();
			if(cell == finish) {
				failure = false;
				break; 
			}
			for(auto c : adjacent(cell)) {
				if(!source.count(c)) { 
					source[c] = cell;
					cells.push_back(c);
				}
			}
		}
		if(failure == true) {
			answer = blocker;
			break;
		}
	}
	set<pair<int, int>> trail;
	auto pos = finish;
	for(;;) {
		trail.insert(pos);
		if(source[pos] == startpos) {
			trail.insert(startpos);
			break;
		}
		pos = source[pos];
	}
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if (obstacles.contains(make_pair(x, y)))
				cout<<'#';
			else if (trail.contains(mkp(x,y)))
				cout<<'O';
			else
				cout<<'.';
		}
		cout<<endl;
	}
	cout<<"Result: ("<<answer.first<<","<<answer.second<<")"<<endl;
		
	return 0;
}

#include<iostream>
#include<vector>
#include<tuple>
#include<set>
#include<list>
#include<map>
#include<bits/stdc++.h>

using namespace std;

vector<vector<char>> racetrack;

int WIDTH = 0, HEIGHT = 0;

pair<int, int> mkp(int a, int b) {
	return make_pair(a, b);
}

pair<int, int> adp(pair<int,int> a, pair<int, int> b) 
{
	return mkp(a.first+b.first, a.second+b.second);
}


pair<int, int> t2p(tuple<int, int, int> t)
{
	pair<int, int> p = mkp(get<0>(t), get<1>(t));
	return p;
}

tuple<int, int, int> p2t(pair<int,int> p, int c)
{
	return {p.first, p.second, c};
}

tuple<int, int, int> mkt(int a, int b, int c)
{
	return {a, b, c};
}


char gt(pair<int, int> pos)
{
	return racetrack[pos.second][pos.first];
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
		   && gt(neighbor) != '#')
			result.push_back(neighbor);
	}
	return result;
}

list<tuple<int,int,int>> adjacent_cheating(tuple<int,int,int> cell)
{
	list<tuple<int,int,int>> result;
	int cheats = get<2>(cell);
	if(cheats == 0)
		return result;
	pair<int,int> dir = mkp(0, -1);
	for(int i = 0; i < 4; i++) {
		dir = rot(dir);
		auto neighbor = adp(t2p(cell), dir);
		if(neighbor.first >= 0 && neighbor.second >= 0
		   && neighbor.first < WIDTH && neighbor.second < HEIGHT
		   && 1){
			if(gt(neighbor) != '#')
				result.push_back(p2t(neighbor, cheats-1));
			else if(gt(neighbor) == '#' && cheats > 0)
				result.push_back(p2t(neighbor, cheats-1));
		}
	}
	list<tuple<int,int,int>> r2;
	for(auto r : result) {
		for(auto ac : adjacent_cheating(r))
			r2.push_back(ac);
	}
	for(auto r : r2) {
		result.push_back(r);
	}
	return result;
}

set<pair<int,int>> visited;

list<pair<int, int>> adjacent_dumb(pair<int, int> cell)
{
	list<pair<int,int>> result;
	pair<int,int> dir = mkp(0, -1);
	for(int i = 0; i < 4; i++) {
		dir = rot(dir);
		auto neighbor = adp(cell, dir);
		if(neighbor.first >= 0 && neighbor.second >= 0
		   && neighbor.first < WIDTH && neighbor.second < HEIGHT
		   && !visited.contains(neighbor)){
			result.push_back(neighbor);
			visited.insert(neighbor);
		}
	}

	return result;
}
list<pair<int,int>> next_level(list<pair<int,int>> level)
{
	list<pair<int,int>> result;
	for(auto p : level) {
		for(auto a : adjacent_dumb(p)) {
			result.push_back(a);
		}
	}
	return result;
}


int main()
{
	vector<char> row;
	int x = 0;
	int y = 0;
	pair<int, int> startpos, endpos;
	while(!cin.eof()) {
		char c = cin.get();
		if(c == EOF)
			break;
		if(c!='\n') {
			row.push_back(c);
			if(c == 'S')
				startpos = mkp(x,y);
			else if (c=='E')
				endpos = mkp(x, y);

			x++;
		} else {
			racetrack.push_back(row);
			row = vector<char>();
			x = 0;
			y++;
		}
	}
	HEIGHT = racetrack.size()-1;
	WIDTH = racetrack[0].size();
	cout<<"Height: "<<HEIGHT<<endl;
	cout<<"Width: "<<WIDTH<<endl;
	map<pair<int,int>,int> stepno;
	int stepn = 0;

	//breadth search!!!
	list<pair<int, int>> cells;
	cells.push_front(startpos);
	map<pair<int,int>,pair<int,int>> source;
	while(!cells.empty()) {
		auto cell = cells.front();
		//cout<<"("<<cell.first<<","<<cell.second<<")"<<endl;
		cells.pop_front();
		stepno[cell] = stepn;
		stepn++;
		if(cell == endpos)
			break; 
		for(auto c : adjacent(cell)) {
			//cout<<"("<<c.first<<","<<c.second<<")"<<endl;
			if(!stepno.count(c)) { 
				source[c] = cell;
				cells.push_back(c);
			}
		}
	}

	map<int, int> cheats;
	set<pair<int,int>> used;
	int result = 0;

	int i = 0;
	for(auto p : stepno) {
		auto pos = p.first;
		if(i%500 == 0)
			cout<<"Traversed "<<i<<" cells"<<endl;
		i++;
		list<pair<int,int>> level;
		visited.clear();
		level = adjacent_dumb(pos);
		visited.insert(pos);
		for(int j = 1; j <= 20; j++) {
			for(auto c2 : level) {
				int save;
				auto q = c2;
				if(stepno.count(q) &&
				   (save=stepno[q] - stepno[pos]-j) > 1
				   && !used.count(mkp(stepno[pos],stepno[q]))) {
					//cout<<"Trail saving "<<save<<endl;
					if(cheats.count(save))
						cheats[save]+=1;
					else
						cheats[save] = 1;
					used.insert(mkp(stepno[pos], stepno[q]));
					if(save>=100)
						result++;

				}
			}
			level = next_level(level);
		}
	}

	y = 0;
	for(auto r : racetrack) {
		x = 0;
		for(auto c : r) {
			if(stepno.count(mkp(x, y)))
				cout<<stepno[mkp(x,y)]%100/10<<stepno[mkp(x,y)]%10;
			else
				cout<<c<<c;
			x++;
		}
		cout<<endl;
		y++;
	}
	cout<<endl;
	for(auto p : cheats) {
		if(p.first>=50)
		cout<<p.second<<" cheats saving "<<p.first<<" picoseconds"
		    <<endl;
	}
	cout<<"Cheat paths saving over 100 steps: "<< result<<endl;
	return 0;
}

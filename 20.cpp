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
	if(gt(t2p(cell)) == '#' && cheats == 0)
		return result;
	pair<int,int> dir = mkp(0, -1);
	for(int i = 0; i < 4; i++) {
		dir = rot(dir);
		auto neighbor = adp(t2p(cell), dir);
		if(neighbor.first >= 0 && neighbor.second >= 0
		   && neighbor.first < WIDTH && neighbor.second < HEIGHT
		   && 1){
			if(gt(neighbor) != '#')
				result.push_back(p2t(neighbor, cheats));
			else if(gt(neighbor) == '#' && cheats > 0)
				result.push_back(p2t(neighbor, cheats-1));
		}
	}
	return result;
}
int traillength(map<pair<int,int>,pair<int,int>> source, 
                pair<int,int> endpos,
		pair<int,int> startpos)
{
	set<pair<int, int>> trail;
	auto pos = endpos;
	for(;;) {
		trail.insert(pos);
		if(source[pos] == startpos) {
			trail.insert(startpos);
			break;
		}
		pos = source[pos];
	}
	return trail.size();
}
set<pair<int,int>> trail(map<pair<int,int>,pair<int,int>> source, 
                pair<int,int> endpos,
		pair<int,int> startpos)
{
	set<pair<int, int>> trail;
	auto pos = endpos;
	for(;;) {
		trail.insert(pos);
		if(source[pos] == startpos) {
			trail.insert(startpos);
			break;
		}
		pos = source[pos];
	}
	return trail;
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
	int honest_trail = traillength(source, endpos, startpos)-1;
	cout<<"Honest trail length: "<<honest_trail<<endl;

	map<int, int> cheats;
	set<pair<int,int>> used;
	int result = 0;

	for(auto p : stepno) {
		auto pos = p.first;
		for(auto c1 : adjacent_cheating(p2t(pos, 2))) {
			for(auto c2 : adjacent_cheating(c1)) {
				int save;
				auto q = t2p(c2);
				if(stepno.count(q) &&
				   (save=stepno[q] - stepno[pos]-2) > 1
				   && !used.count(mkp(stepno[pos],stepno[q]))) {
					cout<<"Trail saving "<<save<<endl;
					if(cheats.count(save))
						cheats[save]+=1;
					else
						cheats[save] = 1;
					used.insert(mkp(stepno[pos], stepno[q]));
					if(save>=100)
						result++;

				}
			}
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
		cout<<p.second<<" cheats saving "<<p.first<<" picoseconds"
		    <<endl;
	}
	cout<<"Cheat paths saving over 100 steps: "<< result<<endl;
	return 0;
}

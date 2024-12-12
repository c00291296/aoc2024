#include<iostream>
#include<vector>
#include<map>
#include<set>

using namespace std;

vector<vector<char>> area;
set<pair<int, int>> flooded;
//borders

set<pair<int, int>> up;
set<pair<int, int>> down;
set<pair<int, int>> west;
set<pair<int, int>> east;
int width = 0;
int height = 0;

pair<int, int> mkp(int x, int y) {
	return make_pair(x, y);
}

void flood(int x, int y) { // oddly, returns the sides for this part :^)
	char here = area[y][x];
	pair<int, int> p = make_pair(x, y);
	if(flooded.count(make_pair(x, y))) {
		return;
	}
	flooded.emplace(make_pair(x, y));
	//west
	if(x == 0 || area[y][x-1] != here) {
		west.emplace(p);

	} else
		flood(x-1, y);
	//east
	if(x==width-1 || area[y][x+1] != here)
		east.emplace(p);
	else
		flood(x+1, y);

	//up
	if(y==0 || area[y-1][x] != here)
		up.emplace(p);
	else
		flood(x, y-1);
	//down
	if(y==height-1 || area[y+1][x] != here)
		down.emplace(p);
	else
		flood(x, y+1);
	return;
}

int count_sides() {
	int sides = 0; //actually ends...
	for(auto p : up) {
		int x = p.first;
		int y = p.second;
		if(!up.count(mkp(x+1, y)))
			sides++;
		if(!up.count(mkp(x-1, y)))
			sides++;
	}
	for(auto p : down) {
		int x = p.first;
		int y = p.second;
		if(!down.count(mkp(x+1, y)))
			sides++;
		if(!down.count(mkp(x-1, y)))
			sides++;

	}
	for(auto p : west) {
		int x = p.first;
		int y = p.second;
		if(!west.count(mkp(x, y+1)))
			sides++;
		if(!west.count(mkp(x, y-1)))
			sides++;


	}
	for(auto p : east) {
		int x = p.first;
		int y = p.second;
		if(!east.count(mkp(x, y+1)))
			sides++;
		if(!east.count(mkp(x, y-1)))
			sides++;
	}
	return sides/2;
}


void display_flood()
{
	int y =0;
	for(auto v : area) {
		int x = 0;
		for (char c : v) {
			if(flooded.count(make_pair(x, y)))
				cout<<"~";
			else
				cout<<c;
			x++;
		}
		y++;
		cout<<endl;
	}
	cout<<endl;
}

int main()
{
	vector<char> row;
	area = vector<vector<char>>();
	while(!cin.eof()) {
		char c;
		c = cin.get();
		if(c == '\n' || c == '\r') {
			area.push_back(row);
			if(!width)
				width = row.size();
			row = vector<char>();
		}
		else {
			row.push_back(c);
		}
	}
	area.pop_back();
	height = area.size();
	cout<<height<<endl;
	for(auto v : area) {
		for (char c : v) {
			cout<<c<<" ";
		}
		cout<<endl;
	}

	int total = 0;
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			up.clear();
			down.clear();
			west.clear();
			east.clear();
			int oldflood = flooded.size();
			flood(x, y);
			int sides = count_sides();
			cout<<"This flood had "<< sides <<" sides" <<endl;
			int newflood = flooded.size();
			int area = newflood - oldflood;
			if(area) {
				display_flood();
				total += area * sides;
			}
		}
	}

	
	cout<<"Total cost: "<<total<<endl;
	return 0;
}


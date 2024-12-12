#include<iostream>
#include<vector>
#include<map>
#include<set>

using namespace std;

vector<vector<char>> area;
set<pair<int, int>> flooded;
int width = 0;
int height = 0;

int flood(int x, int y) { // oddly, returns the perimeter :^)
	int perimeter = 0;
	char here = area[y][x];
	if(flooded.count(make_pair(x, y))) {
		return 0;
	}
	flooded.emplace(make_pair(x, y));
	//left
	if(x == 0 || area[y][x-1] != here)
		perimeter++;
	else
		perimeter+=flood(x-1, y);
	//right
	if(x==width-1 || area[y][x+1] != here)
		perimeter++;
	else
		perimeter+=flood(x+1, y);
	//up
	if(y==0 || area[y-1][x] != here)
		perimeter++;
	else
		perimeter+=flood(x, y-1);
	//down
	if(y==height-1 || area[y+1][x] != here)
		perimeter++;
	else
		perimeter+=flood(x, y+1);
	return perimeter;
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
			int oldflood = flooded.size();
			int perimeter = flood(x, y);
			int newflood = flooded.size();
			int area = newflood - oldflood;
			if(area) {
				display_flood();
				total += area * perimeter;
			}
		}
	}

	
	cout<<"Total cost: "<<total<<endl;
	return 0;
}


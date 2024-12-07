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

void print_area(map<pair<int, int>, pair<int, int>> visited,
		vector<vector<char>> area)
{
	int x = 0;
	int y = 0;
	for(auto r : area) {
			for (char c : r) {
				if(!visited.count(make_pair(x,y)))
					cout<<c;
				else
					cout<<"X";
				x++;
			}
			x = 0;
			y++;
			cout<<endl;
		}
}

int main()
{
	vector<vector<char>> area;
	vector<char> row;
	map<pair<int, int>, pair<int, int>> visited;
	pair<int, int> dir = make_pair(0, -1); 
	auto start_dir = make_pair(0, -1);
	int width = 0;
	int height = 0;
	int x = 0, y = 0;
	int gx = 0, gy = 0;
	int startx = 0, starty = 0;
	while(!cin.eof()) {
		char c = cin.get();
		if(c!='\r' && c!='\n') {
			if(is_guard(c)) {
				gx = x;
				gy = y;
				startx = gx;
				starty = gy;
				c = '.';
				visited[make_pair(gx, gy)] = dir;
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
	//all possible obstacle options
	int result = 0;
	cout<<"Simulating all permutations..."<<endl;
	for (y = 0; y < height; y++) {
		cout<<(y*width+x)*100/(width*height)<<"%"<<endl;
		for(x = 0; x < width; x++) {
			//can't put table at guard's starting position :)
			if(x == startx && y == starty)
				continue;
		    char tmp = area[y][x];
		    area[y][x] = 'O';
		    //guard journey
		    gx = startx;
		    gy = starty;
		    dir = start_dir;
		    visited.clear();
		    while(!(gx + dir.first >= width || gx + dir.first<0)
				    && !(gy+dir.second >= height || gy+ dir.second <0)) {
			    int newx = gx + dir.first;
			    int newy = gy + dir.second;
			    if(area[newy][newx] == '.') {
				    gx = newx;
				    gy = newy;
				    if (visited[make_pair(gx, gy)] == dir) {
					    result++;
					    break;
				    } else {
					    visited[make_pair(gx, gy)] = dir;
				    }
			    } else {
				    dir = rot(dir);
			    }
		    }
		    //debugging
		    /*print_area(visited, area);
		    cout<<endl;
		    cout<<result;
		    cout<<endl;*/
		    area[y][x] = tmp;
		}
	}
	cout<<"Possible loops: "<<result<<endl;
	return 0; }

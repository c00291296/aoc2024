#include<iostream>
#include<vector>

using namespace std;

pair<int, int> mkp(int a, int b) {
	return make_pair(a, b);
}

pair<int, int> arrow_dir(char g)
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

bool is_dir(char c)
{
	return c == '^' || c == 'v' || c=='<' || c=='>';
}

pair<int, int> adp(pair<int,int> a, pair<int, int> b) 
{
	return mkp(a.first+b.first, a.second+b.second);
}

vector<vector<char>> warehouse;

pair<int, int> botpos;

char gt(pair<int, int> pos)
{
	return warehouse[pos.second][pos.first];
}

void st(pair<int, int> pos, char c)
{
	warehouse[pos.second][pos.first] = c;
}

bool movebox(pair<int, int> box, pair<int, int> dir) {
	if(gt(box) == '.')
		return true;
	if(dir.second == 0) { // horizontal movement, ezpz
		auto newpos = adp(box, dir);
		if(gt(newpos) == '.') {
			char boxpart = gt(box);
			st(newpos, boxpart);
			st(box, '.');
			return true;
		} else if(gt(newpos) == '#') {
			return false;
		} else if(gt(newpos) == '[' || gt(newpos) == ']') {
			if(movebox(newpos, dir)) {
				movebox(box, dir);
				return true;
			} else {
				return false;
			}
		}
	} else { // OH NO vertical movement this is gonna be fun
		if(gt(box) == ']')
			box = mkp(box.first - 1, box.second);
		auto box2 = mkp(box.first+1, box.second);
		auto new1 = adp(box, dir);
		auto new2 = adp(mkp(box.first+1, box.second), dir);
		if(gt(new1) == '.' && gt(new2) == '.') {
			st(box, '.');
			st(box2, '.');
			st(new1, '[');
			st(new2, ']');
			return true;
		} else if (gt(new1) == '#' || gt(new2) == '#') {
			return false;
		} else if (gt(new1) == '[' || gt(new1) == ']' ||
				gt(new2) == '[' || gt(new2) == ']') {
			//HERE WE FREAKING GO
			vector<vector<char>> backup = warehouse;
			bool res1 = movebox(new1, dir);
			bool res2 = movebox(new2, dir);
			if(!(res1&&res2)) {
				warehouse = backup;
				return false;
			} else {
				movebox(box, dir);
				return true;
			}
		}
	}
	return false;
}


void move_bot(pair<int, int> dir)
{
	auto newpos = adp(botpos, dir);
	if(gt(newpos) == '.') {
		botpos = newpos;
		return;
	}
	if(gt(newpos) == '#')
		return;
	if(gt(newpos) == '[' || gt(newpos) == ']') { //OH MY GOD ITS AAAA FREAKING BOOOOX!!!!
		if(movebox(newpos, dir)) {
			botpos = newpos;
			return;
		} else {
			return;
		}
	}
	return; //we're not supposed to get here but whatevs mb theres
	        //garbage on the map or smth
}
void print_warehouse()
{
	int y = 0;
	int x = 0;
	for(auto v : warehouse) {
		for(auto c : v) {
			if(x == botpos.first && y == botpos.second)
				cout<<'@';
			else
				cout<<c;
			x++;
		}
		y++;
		x = 0;
		cout<<endl;
	}
}
int main()
{
	vector<char> row;
	vector<pair<int, int>> moves;
	char c = -1;
	char tile;
	int y = 0;
	int x = 0;
	while(1) {
		tile = cin.get();
		if(c == '\n' && tile == '\n')
			break;
		if(tile == '\n') {
			x = 0;
			y++;
			warehouse.push_back(row);
			row = vector<char>();
		}
		else if(tile == '@') {
			botpos = make_pair(x, y);
			row.push_back('.');
			row.push_back('.');
			x++;
			x++;
		} else {
			if(tile!='O') {
				row.push_back(tile);
				row.push_back(tile);
			} else {
				row.push_back('[');
				row.push_back(']');
			}
			x++;
			x++;
		}
		c = tile;

	}
	print_warehouse();
	while(!cin.eof()) {
		c = cin.get();
		if(is_dir(c)) {
			moves.push_back(arrow_dir(c));
		}
	}
	for (auto m : moves) {
		move_bot(m);
	}
	print_warehouse();
	for(auto d : moves)
		cout<<"("<<d.first<<","<<d.second<<")"<<endl;
	int result = 0;
	y = 0;
	for(auto r : warehouse) {
		x = 0;
		for(auto c : r) {
			if (c== '[')
				result+= y*100+x;
			x++;
		}
		y++;
	}

	cout<<"Result: "<<result<<endl;

	return 0;
}

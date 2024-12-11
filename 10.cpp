#include<iostream>
#include<set>
#include<vector>

using namespace std;

vector<vector<int>> area;
int width = 0;
int height = 0;

set<pair<int, int>> endpoints(int x, int y, int prev)
{
	set<pair<int, int>> result;
	result.clear();
	if(x >= width || x < 0 || y >= height || y <0) {
		return result;
	}
	int here = area[y][x];
	if(here - prev != 1) {
		return result;
	}
	if(here == 9) {
		result.emplace(make_pair(x, y));
		return result;
	}
	set<pair<int, int>> up = endpoints(x, y-1, here);
	set<pair<int, int>> down = endpoints(x, y+1, here);
	set<pair<int, int>> left = endpoints(x-1, y, here);
	set<pair<int, int>> right = endpoints(x+1, y, here);
	result.insert(up.begin(), up.end());
	result.insert(down.begin(), down.end());
	result.insert(left.begin(), left.end());
	result.insert(right.begin(), right.end());
	return result;
}



int main()
{
	vector<int> row;
	while(!cin.eof()) {
		char c = cin.get();
		if(c == '\n' || c == '\r') {
			area.push_back(row);
			if(!width)
				width = row.size();
			row = vector<int>();
			continue;
		} else {
			row.push_back(c - '0');
			continue;
		}
	}
	height = area.size()-1;
	cout<<"Width: "<<width<<endl;
	cout<<"Height: "<<height<<endl;
	for(auto r : area) {
		for (int n : r) {
			cout<<n<<" ";
		}
		cout<<endl;
	}
	int result = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			set<pair<int, int>> r = endpoints(x, y, -1);
			result+= r.size();
		}
	}
	cout<<"Result: "<<result;
			
	return 0;
}

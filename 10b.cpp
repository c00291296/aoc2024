#include<iostream>
#include<set>
#include<vector>

using namespace std;

vector<vector<int>> area;
int width = 0;
int height = 0;

int trails(int x, int y, int prev)
{
	int result = 0;
	if(x >= width || x < 0 || y >= height || y <0) {
		return result;
	}
	int here = area[y][x];
	if(here - prev != 1) {
		return result;
	}
	if(here == 9) {
		return 1;
	}
	result += trails(x, y-1, here);
	result += trails(x, y+1, here);
	result += trails(x-1, y, here);
	result += trails(x+1, y, here);
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
			result += trails(x, y, -1);
		}
	}
	cout<<"Result: "<<result<<endl;
			
	return 0;
}

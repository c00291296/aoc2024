#include<iostream>
#include<map>
#include<vector>

using namespace std;

long calibrate(long result, vector<long> nums) // returns 0 if can't
{
	long bits = nums.size()-1;
	long permutations = 1 << bits;
	for(long i = 0; i < permutations; i++) {
		long k = i;
		long r = nums[0];
		for(long j = 0; j < bits; j ++) {
			if(k%2)
				r += nums[j+1];
			else
				r *= nums[j+1];
			k>>=1;
		}
		if (r == result)
			return r;
	}
	return 0;
}
int main()
{
	map<long, vector<long>> equations;
	vector<long> row;
	long first;
	long result = 0;


	//getting that dumb input again...
	cin>>first;
	cin.get();
	cin.get();
	while(!cin.eof()) {
		long n;
		char c;
		cin>>n;
		c = cin.get();
		if(c != '\r' && c != '\n') {
			row.push_back(n);
		} else {
			row.push_back(n);
			equations[first] = row;
			row = vector<long>();
			if(!cin.eof()) {
				cin>>first;
				cin.get();
				cin.get();
			}
		}
	}
	
	for (auto p : equations) {
		result += calibrate(p.first, p.second);
	}
	
	cout<<"Result: "<<result<<endl;
	return 0;
}

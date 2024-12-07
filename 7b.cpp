#include<iostream>
#include<map>
#include<vector>
#include<cmath>

using namespace std;

long calibrate(long result, vector<long> nums) // returns 0 if can't
{
	long trits = nums.size()-1;
	long permutations = pow(3, trits);
	for(long i = 0; i < permutations; i++) {
		long k = i;
		long r = nums[0];
		for(long j = 0; j < trits; j ++) {
			long next = nums[j+1];
			switch(k%3) {
			case 0:
				r += next;
				break;
			case 1:
				r *= next;
				break;
			case 2:
				r = r*pow(10, (floor(log10(next))+1)) + next;
			}
			k/=3;
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

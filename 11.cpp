#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void print_stones(vector<long> stones)
{
	for(long n : stones) {
		cout<<n<<" ";
	}
	cout<<endl;
	return;
}

int digitcount(long n)
{
	int count = floor(log10(n))+1;
	//cout<<"Digit count of "<<n<<" is "<<count<<endl;
	return floor(log10(n))+1;
}

void blink(vector<long> &stones) {
	for(int i = 0; i < stones.size(); i++) {
		if(stones[i] == 0) {
			stones[i] = 1;
		} else if (digitcount(stones[i]) % 2 == 0) {
			long old = stones[i];
			int shift = digitcount(old)/2;
			stones[i] /= pow(10, shift);
			stones.insert(stones.begin()+i+1, old%(int)pow(10, shift));
			i++;
		} else {
			stones[i] *= 2024;
		}
	}
}


int main()
{
	vector<long> stones;
	while(!cin.eof()) {
		long n;
		cin>>n;
		stones.push_back(n);
	}
	print_stones(stones);
	for(int i = 0; i < 25; i++) {
		blink(stones);
		print_stones(stones);
	}
	cout<<"The result is "<<stones.size();
	
	cout<<endl;
	return 0;

}

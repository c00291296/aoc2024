#include<iostream>
#include<vector>
#include<cmath>
#include<map>

using namespace std;

int digitcount(long n)
{
	int count = floor(log10(n))+1;
	//cout<<"Digit count of "<<n<<" is "<<count<<endl;
	return floor(log10(n))+1;
}

map<long, pair<long, long>> split;
map<long, long> mul;

map<long,long>* blink(map<long, long> &stones) {
	map<long, long>* ns = new map<long, long>;
	map<long,long>& newstones = *ns;
	for(pair<long, long> q : stones) {
		long stone = q.first;
		long quantity = q.second;
		if(stone == 0) {
			newstones[1] = quantity;
		} else if (digitcount(stone) % 2 == 0) {
			pair<long, long> p;
			if(split.count(stone)) {
				p = split[stone];
			} else {
				long old = stone;
				int shift = digitcount(old)/2;
				long first = old / pow(10, shift);
				long second = old%(int)pow(10, shift);
				p = make_pair(first, second);
				split[old] = p;
			}
			if(!newstones.count(p.first))
				newstones[p.first] = 0;
			if(!newstones.count(p.second))
				newstones[p.second] = 0;
			newstones[p.first] += quantity;
			newstones[p.second] += quantity;
		} else {
			if(mul.count(stone)) {
				newstones[mul[stone]] = quantity;
			} else {
				long res = stone * 2024;
				mul[stone] = res;
				newstones[res] = quantity;
			}
		}
	}
	delete &stones;
	return ns;
}


int main()
{
	map<long, long>* stones = new map<long, long>();
	while(!cin.eof()) {
		long n;
		cin>>n;
		if(stones->count(n))
			(*stones)[n]++;
		else
			(*stones)[n] = 1;
	}
	for(int i = 0; i < 75; i++) {
		stones = blink(*stones);
		cout<<i*100/75<<"%"<<endl;
		//print_stones(stones);
	}
	long result = 0;
	for(auto p : (*stones)) {
		result += p.second;
	}
	cout<<"The result is "<<result;
	
	cout<<endl;
	return 0;

}

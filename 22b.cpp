#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<set>
#include<tuple>

#define R(I, M) for(int (I)=0; (I)<(M); (I)++)

using namespace std;

unsigned long evolve(unsigned long secret)
{
	int a = secret<<6;
	secret = secret ^ a;
	secret %= 16777216;

	int b = secret>>5;
	secret = secret ^ b;
	secret %=16777216;

	int c = secret<<11;
	secret = secret ^ c;
	secret %= 16777216;
	return secret;
}

typedef tuple<int,int,int,int> trade;

/*map<trade, long>*/void add(map<trade,long>& m, trade s, long q)
{
	if(!m.count(s)) {
		m[s] = q;
	} else {
		m[s] += q;
	}
	//return m;
}


tuple<int,int,int,int> shift(tuple<int,int,int,int> t, int a)
{
	return make_tuple(get<1>(t), get<2>(t), get<3>(t), a);
}

int main()
{
	//TODO: solve with just a hashtable of tuples with total earnings
	//for each tuple ;-D
	vector<int>codes;
	while(!cin.eof()) {
		int n;
		cin>>n;
		if(cin.eof())
			break;
		codes.push_back(n);
	}
	for(int n : codes)
		cout<<n<<endl;
	map<trade, long> earnings;
	int buyer = 0;
	int s = codes.size();
	int pc = 0;
	int pcc = s/100;
	int pccc = 0;
	for(int n : codes){
		set<trade> bought;
		//cout<<n<<":";
		unsigned m = n;
		trade prev;
		prev = make_tuple(-100, -100, -100, -100);
		int l = m%10;
		bought.clear();
		R(i, 2000) {
			m = evolve(m);
			auto c = m%10;
			prev = shift(prev, c-l);
			l = c;
			if(get<0>(prev) == -100)
				continue;
			if(bought.count(prev))
				continue;
			add(earnings, prev, c);
			/*
			if(!earnings.count(prev)) {
				earnings[prev] = c;
			} else {
				earnings[prev] += c;
			}
			*/
			bought.insert(prev);
		}
		//cout<<m<<endl;
	}
	tuple<int,int,int,int> biggest = make_tuple(-100,-100,-100,-100);
	for(auto p : earnings) {
		if(get<0>(biggest) == -100)
			biggest = p.first;
		if(earnings[biggest] < p.second)
			biggest = p.first;
	}
		
	cout<<"Resutl: ";
	cout<<get<0>(biggest)<<","
	    <<get<1>(biggest)<<","
	    <<get<2>(biggest)<<","
	    <<get<3>(biggest)<<endl;
	cout<<earnings[biggest]<<endl;
	return 0;
}

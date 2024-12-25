#include<iostream>
#include<vector>

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


int main()
{
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
	unsigned long result = 0;
	for(int n : codes){
		cout<<n<<":";
		unsigned m = n;
		R(i, 2000)
			m = evolve(m);
		cout<<m<<endl;
		result+=m;
	}
	cout<<"Resutl: "<<result<<endl;

	return 0;
}

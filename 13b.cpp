#include<iostream>

using namespace std;

pair<long, long> solve(long m, long n, long p, long q, long X, long Y)
{
	long A, B; //solution parts
	long det = m*q - n*p;
	auto no = make_pair(0, 0);
	if(det == 0)
		return no;
	A = q*X - p*Y;
	B = m*Y - n*X;
	if(A % det != 0 || B % det != 0)
		return no;
	A/=det;
	B/=det;
	if(A < 0 || B < 0)
		return no;
	return make_pair(A, B);
}

int main() {
	//assumes input cleaned with grep
	long result = 0;
	long i = 0;
	long lol = 10000000000000;
	while(!cin.eof()) {
		long m, n, p, q, X, Y;
		cin>>m;
		if(cin.eof())
			break;
		cin>>n;
		cin>>p;
		cin>>q;
		cin>>X;
		cin>>Y;
		X+=lol;
		Y+=lol;
		auto sol= solve(m,n,p,q,X,Y);
		result += (sol.first*3 + sol.second);
		i++;
		cout<<"Machine #"<<i<<": "<<sol.first<<","<<sol.second<<endl;
		cout<<"(Y="<<Y<<")"<<endl;
		cout<<"Running total: "<<result<<endl;

	}
	cout<<"Result: "<<result<<endl;

	return 0;
}

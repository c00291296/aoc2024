#include<iostream>

using namespace std;

pair<int, int> solve(int m, int n, int p, int q, int X, int Y)
{
	int A, B; //solution parts
	int det = m*q - n*p;
	auto no = make_pair(0, 0);
	if(det == 0)
		return no;
	A = q*X - p*Y;
	B = m*Y - n*X;
	if(A % det != 0 || B % det != 0)
		return no;
	A/=det;
	B/=det;
	if(A < 0 || A > 100 || B < 0 || B > 100)
		return no;
	return make_pair(A, B);
}

int main() {
	//assumes input cleaned with grep
	int result = 0;
	int i = 0;
	while(!cin.eof()) {
		int m, n, p, q, X, Y;
		cin>>m;
		if(cin.eof())
			break;
		cin>>n;
		cin>>p;
		cin>>q;
		cin>>X;
		cin>>Y;
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

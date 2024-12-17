#include<iostream>
#include<vector>

using namespace std;

long A, B, C;

long combo(long x)
{
	switch(x) {
		case 0:
		case 1:
		case 2:
		case 3:
			return x;
		case 4:
			return A;
		case 5:
			return B;
		case 6:
			return C;
		default:
			break;
	}

	return -1;
}

int main()
{
	vector<long> mem;
	cin>>A;
	cin>>B;
	cin>>C;
	while(!cin.eof()) {
		long n;
		cin>>n;
		if(cin.eof())
			break;
		mem.push_back(n);
	}
	int pc = 0;
	while(pc < mem.size()) {
		long op = mem[pc];
		long arg = mem[pc+1];
		switch(op) {
			case 0:
				A >>= combo(arg);
				pc+=2;
				break;
			case 1:
				B ^= arg;
				pc+=2;
				break;
			case 2:
				B = combo(arg) & 7;
				pc+=2;
				break;
			case 3:
				if(A==0)
					pc+=2;
				else
					pc = arg;
				break;
			case 4:
				B ^= C;
				pc+=2;
				break;
			case 5:
				cout<<(combo(arg) & 7)<<",";
				pc+=2;
				break;
			case 6:
				B = A >> combo(arg);
				pc+=2;
				break;
			case 7:
				C = A >> combo(arg);
				pc+=2;
				break;
			default:
				cout<<"unknown instruction"<<endl;
				break;
		}
	}

	return 0;
}

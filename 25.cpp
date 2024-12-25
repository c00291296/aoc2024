#include<iostream>
#include<vector>

#define R(I, M) for(int (I)=0; (I)<(M); (I)++)

using namespace std;

const long full = 0x7ffffffff;
const long l =    0x400000000;

void printval(long val)
{
	R(i, 7) {
		R(j, 5) {
			if((val & l) != 0)
				cout<<"#";
			else
				cout<<".";
			val<<=1;
		}
		cout<<endl;
	}
	cout<<endl;
	return;
}

int main()
{
	vector<long> keys;
	vector<long>locks;
	long code = 0;
	char prev = -1;
	while(!cin.eof()) {
		char c = cin.get();
		if(c==prev && prev == '\n') {
			if(code & 0x1f == 0x1f){
				keys.push_back(code);
				cout<<"Key:"<<hex<<code<<endl;
				code = 0;
			} else {
				locks.push_back(code);
				cout<<hex<<code<<endl;
				code = 0;
			}
		}
		if(c == '#') {
			code<<=1;
			code|=1;
		}
		else if (c=='.') {
			code<<=1;
		}
		prev = c;
	}
	for(auto key:keys)
		printval(key);
	for(auto lock:locks)
		printval(lock);
	int result = 0;
	for(auto key : keys) {
		for (auto lock : locks) {
			if((key & lock) == 0) {
				result++;
			}
		}
	}
	cout<<"The result is "<<dec<<result<<endl;
	return 0;
}

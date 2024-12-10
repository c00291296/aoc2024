#include<iostream>
#include<map>
#include<vector>

using namespace std;

void insert(vector<int> &disk, int n) {
	for(int i = 0; i < disk.size(); i++) {
		if(disk[i] == -1) {
			cout<<i*100/disk.size()<<"%"<<endl;
			disk[i] = n;
			return;
		}
	}
}

int retrieve(vector<int> &disk) {
	for(int i = disk.size()-1; i >= 0; i--) {
		if(disk[i] >=0) {
			int result = disk[i];
			disk[i] = -1;
			return result;
		}
	}
	cout<<"Retrieval failed"<<endl;
	return -1;
}

int flen(vector<int> disk, int fileno) {
	int flen = 0;
	for(int n : disk) {
		if(n == fileno)
			flen++;
	}
	return flen;
}

int findf(vector<int> disk, int fileno) {
	for(int i = 0; i < disk.size(); i++) {
		if(disk[i] == fileno)
			return i;
	}
	return -1;
}

bool space_fits(vector<int> disk, int size, int i) {
	int n = 0;
	for(int j = i; j < disk.size(); j++) {
		if(disk[j] == -1)
			n++;
		else
			break;
	}
	return n >= size;
}

int find_space(vector<int> disk, int size, int bound) {
	for(int i = 0; i < bound; i++) {
		if(space_fits(disk, size, i))
			return i;
	}
	return 0;
}

void mvfile(vector<int> &disk, int src, int dst, int size) {
	for(int i = 0; i < size; i++) {
		disk[dst+i] = disk[src+i];
		disk[src+i] = -1;
	}
}

int main()
{
	vector<int> disk;
	bool file = true;
	long fileno = 0;
	int ci = 0;
	while(!cin.eof()) {
		char c = cin.get();
		int n = c - '0';
		int data = !(ci%2) ? fileno : -1;
		if(c==EOF)
			break;
		if(c<'0' || c>'9')
			break;
		while(n > 0) {
			disk.push_back(data);
			n--;
		}
		if (!(ci%2)) {
			fileno++;
		}
		ci++;
	}
	for (int n : disk) {
		cout<<n<<" ";
	}
	cout<<endl;
	cout<<"Defragmenting..."<<endl;
	for(int f = fileno; f >= 0; f--) {
		int len = flen(disk, f);
		int src = findf(disk, f);
		int dst;
		cout<<(fileno-f)*100/fileno<<"%"<<endl;
		if(dst = find_space(disk, len, src))
			mvfile(disk, src, dst, len);
		else
			continue;
	}

	for (int n : disk) {
			if(n == -1)
				cout<<".";
			else
				cout<<n;
		}
		cout<<endl;
	cout<<"Calculating checksum..."<<endl;
	unsigned long long checksum = 0;
	for(int i = 0; i < disk.size(); i++) {
		if(disk[i] != -1) {
			checksum += i * disk[i];
		}
	}
	cout<<"Checksum: "<<checksum<<endl;
	return 0;
}
		
		

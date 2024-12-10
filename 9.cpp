#include<iostream>
#include<map>
#include<vector>

using namespace std;

bool contiguous(vector<int> disk) {
	bool file = true;
	for (int n : disk) {
		if(n == -1)
			file = false;
		if(!file && n >= 0)
			return false;
	}
	return true;
}

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
	while(!contiguous(disk)) {
		int q = retrieve(disk);
		insert(disk, q);
		/*for (int n : disk) {
			if(n == -1)
				cout<<".";
			else
				cout<<n;
		}
		cout<<endl;*/
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
		
		

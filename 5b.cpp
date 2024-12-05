#include<iostream>
#include<vector>
#include<map>

using namespace std;

map<pair<int, int>, bool> bigger;
map<pair<int, int>, bool> smaller;

int main()
{
	//parse rules
	vector<vector<int>> seqs = vector<vector<int>>();
	vector<int> seq = vector<int>();
	while(true) {
		char c;
		int n1, n2;
		cin>>n1;
		cin>>c;
		if(c=='|') {
			cin>>n2;
			smaller[make_pair(n1, n2)] = true;
			bigger[make_pair(n2, n1)] = true;
		}
		if(c==',') {
			seq.push_back(n1);
			break;
		}
	}

	while(!cin.eof()) {
		int n;
		char c;
		cin>>n;
		seq.push_back(n);
		c = cin.get();
		if(c!=',') {
			seqs.push_back(seq);
			seq = vector<int>();
		}
	}
	seqs.pop_back();
	for(pair<pair<int, int>, bool> p : smaller) {
		cout<<p.first.first<<"|"<<p.first.second<<endl;
	}
	for(vector<int> row : seqs) {
		for(int n : row) {
			cout<<n<<",";
		}
		cout<<endl;
	}

	int total = 0;
	auto comparator = [](const auto& a, const auto& b) {
					return smaller[make_pair(a, b)];};
	for(vector<int> row : seqs) {
		bool good = is_sorted(row.begin(), row.end(), comparator);
		if(!good) {
			sort(row.begin(), row.end(), comparator);
			total+=row[row.size()/2];
		}
	}
	cout<<"Total of middles of fixed bad rows: "<<total<<endl;

	return 0;
}

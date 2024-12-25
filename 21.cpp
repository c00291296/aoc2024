#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<list>
#include<algorithm>

#define R(I, M) for(int (I)=0; (I)<(M); (I)++)

using namespace std;

pair<int, int> mkp(int a, int b) {
	return make_pair(a, b);
}

pair<int, int> adp(pair<int,int> a, pair<int, int> b) 
{
	return mkp(a.first+b.first, a.second+b.second);
}

pair<int, int> sup(pair<int,int> a, pair<int, int> b) 
{
	return mkp(a.first-b.first, a.second-b.second);
}

vector<string> append(vector<string> l1, vector<string> l2)
{
	for(auto s : l2) {
		l1.push_back(s);
	}
	return l1;
}

pair<int,int> ch2pn(char c)
{
	map<char,pair<int,int>> pos;

	pos['7']=mkp(0,0);
	pos['8']=mkp(1,0);
	pos['9']=mkp(2,0);

	pos['4']=mkp(0,1);
	pos['5']=mkp(1,1);
	pos['6']=mkp(2,1);

	pos['1']=mkp(0,2);
	pos['2']=mkp(1,2);
	pos['3']=mkp(2,2);

	pos['X']=mkp(0,3); //BAD SQUARE!!!
	pos['0']=mkp(1,3);
	pos['A']=mkp(2,3);

	return pos[c];
}

pair<int,int> ch2p(char c)
{
	map<char,pair<int,int>> pos;

	pos['X'] = mkp(0,0);
	pos['^'] = mkp(1,0);
	pos['A'] = mkp(2,0);

	pos['<'] = mkp(0,1);
	pos['v'] = mkp(1,1);
	pos['>'] = mkp(2,1);
	return pos[c];
}

string construct_path(map<char,int> steps)
{
	string result = "";
	//best steps to take
	if(steps.count('>')) {
		for(int i = 0; i < steps['>']; i++)
			result+= '>';
	}
	if(steps.count('^')) {
		for(int i = 0; i < steps['^']; i++)
			result += '^';
	}
	//not as good but ok
	if(steps.count('v')) {
		for(int i = 0; i < steps['v']; i++)
			result+='v';
	}
	//the worst.
	if(steps.count('<')) {
		for(int i = 0; i < steps['<']; i++)
			result+='<';
	}
	return result;
}

pair<int, int> guard_dir(char g)
{
	switch (g) {
		case '^':
			return make_pair(0, -1);
		case 'v':
			return make_pair(0, 1);
		case '<':
			return make_pair(-1, 0);
		case '>':
			return make_pair(1, 0);
		default:
			return mkp(0,0);
	}
	return mkp(0, 0);
}

bool bad_path(string path, pair<int,int> start, bool numpad)
{
	pair<int,int>bad_square = numpad? ch2pn('X') : ch2p('X');
	auto pos = start;
	for(char c : path) {
		pos = adp(pos, guard_dir(c));
		if(pos == bad_square)
			return true;
	}
	return false;
}

map<pair<int,int>, vector<string>> paths_memo;
			
vector<string> paths(vector<string> acc, pair<int,int> diff, int depth)
{
	if(depth == 0) {
		if(paths_memo.count(diff))
			return paths_memo[diff];
	}
	vector<string> result = vector<string>();
	const int x = diff.first;
	const int y = diff.second;
	if(acc.empty()) 
		acc.push_back("");
	if(x == 0 && y == 0) {
		R(i, acc.size())
			acc[i] += 'A';
		return acc;
	}
	vector<string> l1 = acc;
	vector<string> l2 = acc;
	char rowchar = diff.first > 0 ? '>' : '<';
	int rowdec = diff.first > 0 ? -1 : 1;
	char colchar = diff.second < 0 ? '^' : 'v';
	int coldec = diff.second > 0 ? -1 : 1;
	if(x != 0) {
		R(i, l1.size()){
			l1[i] = l1[i] + rowchar;
			//cout<<l1[i]<<endl;
		}
		l1 = paths(l1, mkp(x+rowdec, y), depth-1);
		result = append(result, l1);
	}
	if(y!=0) {
		R(i, l2.size()){
			l2[i] = l2[i] + colchar;
			//cout<<l2[i]<<endl;
		}
		l2 = paths(l2, mkp(x, y+coldec), depth-1); 
		result = append(result, l2);
	}
	if(depth == 0)
		paths_memo[diff] = result;
	return result;	
}

vector<string> recombine(vector<vector<string>> v)
{
	vector<string> result;
	result.push_back("");
	for (auto range : v) {
		vector<string> b;
		for(string e : range) {
			for(auto r : result)
				b.push_back(r+e);
		}
		result = b;
	}
	return result;
}


int dirs2dirs(string dirs, int depth);

int room2dirs(string room)
{
	int result = 0;
	auto pos = ch2pn('A');
	vector<vector<string>> recs;
	for(auto c : room) {
		auto target = ch2pn(c);
		auto diff = sup(target, pos);
		//cout<<"diff computed"<<endl;
		//cout<<"now gonna compute options"<<endl;
		vector<string> options_bad = paths(vector<string>(), diff, 0);
		vector<string> options;
		options.clear();
		for(auto s : options_bad) {
			if(!bad_path(s, pos, true))
				options.push_back(s);
		}
		recs.push_back(options);
		options = vector<string>();
		//cout<<"options ok"<<endl;
		pos = target;
	}
	map<string,int> lens; 
	//cout<<"lens ok"<<endl;
	int i = 0;
	int size = recombine(recs).size();
	for(auto s : recombine(recs)) {
		cout<<i++*100/size<<"%"<<endl;
		lens[s] = dirs2dirs(s, 2);
	}
	//cout<<"now it's time to find the lowest one";
	//auto min=*min_element(lens.begin(), lens.end());
	//result=min.second;
	//cout<<min.first;
	string min = "f";
	for(auto p : lens) {
		if(min == "f")
			min = p.first;
		else {
			if(lens[min] > p.second)
				min = p.first;
		}
	}
	result = lens[min];
	cout<<min;
	return result;
}


int dirs2dirs(string dirs, int depth)
{
	if(depth<=0){
		return dirs.size();
	}
	int result = 0;
	auto pos = ch2p('A');
	vector<vector<string>> recs;
	for(char c : dirs) {
		auto target = ch2p(c);
		auto diff = sup(target, pos);
		vector<string> options_bad=paths(vector<string>(),diff,0);
		vector<string> options;
		options.clear();
		for(auto s : options_bad) {
			if(!bad_path(s, pos, false))
				options.push_back(s);
		}
		recs.push_back(options);
		options = vector<string>();
		pos = target;
	}
	map<string,int> lens; 
	//cout<<"lens ok"<<endl;
	int i = 0;
	int size = recombine(recs).size();
	for(auto s : recombine(recs)) {
		if(depth == 2)
			cout<<depth<<":"<<i++*100/size<<"%"<<endl;
		int min_child = dirs2dirs(s, depth-1);
		if(!lens.count(s))
			lens[s] = min_child;
		else
			lens[s] = lens[s] > min_child? min_child:lens[s];
	}
	//cout<<"now it's time to find the lowest one";
	string min = "f";
	for(auto p : lens) {
		if(min == "f")
			min = p.first;
		else {
			if(lens[min] > p.second)
				min = p.first;
		}
	}
	//auto min=*min_element(lens.begin(), lens.end());
	result=lens[min];

	return result;
}

int main()
{
	vector<string> rooms;
	string s0 = "";
	while(!cin.eof()) {
		char c = cin.get();
		if(c != '\n')
			s0+=c;
		else {
			rooms.push_back(s0);
			s0 = "";
		}
	}
	for(auto s : rooms)
		cout<<atoi(s.c_str())<<endl;
	int result = 0;
	for(auto room : rooms) {
		cout<<room<<endl;
		int size = room2dirs(room);
		cout<<"Room seq size: "<<size<<endl;
		result += (atoi(room.c_str()) * size);
	}
	cout<<"The result is "<<result<<endl;
	vector<vector<string>> recs;
	vector<string> a, b, c;
	a = {"0 ", "1 ", "2 "};
	b = {"A ", "B ", "C ", "D "};
	c = {"I", "II", "III", "IV"};
	recs.push_back(a);
	recs.push_back(b);
	recs.push_back(c);
	for(auto s : recombine(recs))
		cout<<s<<endl;
	cout<<recombine(recs).size()<<endl;
	for(auto s : paths(vector<string>(), mkp(2,5), 0))
		cout<<s<<endl;
	return 0;
}

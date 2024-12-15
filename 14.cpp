#include<iostream>
#include<vector>
#include<map>

using namespace std;

typedef struct {
	int x;
	int y;
	int vx;
	int vy;
} Robot;

const int W = 101;
const int H = 103;

Robot move(Robot robot)
{
	auto *r = &robot;
	r->x += r->vx;
	if(r->x >= W)
		r->x -= W;
	if(r->x < 0)
		r->x += W;
	r->y += r->vy;
	if(r->y >= H)
		r->y -= H;
	if(r->y < 0)
		r->y += H;
	return robot;
}

int quadrant(Robot *r)
{
	int q = 0;
	if(r->x == (W+0)/2 || r->y == (H+0)/2)
		return -1;
	if (r->x > W/2)
		q += 1;
	if (r->y > H/2)
		q += 2;
	return q;
}

int main()
{
	vector<Robot> vr;
	Robot *r = new Robot;
	//assumes input cleaned up with e.g. grep with only numbers left
	while(!cin.eof()) {
		cin>>r->x;
		if(cin.eof())
			break;
		cin>>r->y;
		cin>>r->vx;
		cin>>r->vy;
		vr.push_back(*r);
		r = new Robot;
	}

	for(auto a : vr) {
		cout<<"p="<<a.x<<","<<a.y<<" v="<<a.vx<<","<<a.vy<<endl;
	}

	for(int i = 0; i < 100; i++) {
		for(int j = 0; j < vr.size(); j++)
			vr[j]=move(vr[j]);
	}
	cout<<endl;
	for(auto a : vr) {
		cout<<"p="<<a.x<<","<<a.y<<" v="<<a.vx<<","<<a.vy<<endl;
	}

	map<int, int> quads;
	for(int i = -1; i < 4; i++)
		quads[i] = 0;

	for(auto r : vr) {
		quads[quadrant(&r)] ++;
	}

	int result = 1;

	for(int i = 0; i < 4; i++) {
		cout<<quads[i]<<endl;
		result*=quads[i];
	}

	cout<<"The result is: "<<result<<endl;

	return 0;
}

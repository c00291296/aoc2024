#include<iostream>
#include<vector>
#include<map>
#include<raylib.h>

using namespace std;

typedef struct {
	int x;
	int y;
	int vx;
	int vy;
} Robot;

const int W = 101;
const int H = 103;

Robot move(Robot robot, int dir) //direction in time
{
	auto *r = &robot;
	r->x += r->vx * dir;
	if(r->x >= W)
		r->x -= W;
	if(r->x < 0)
		r->x += W;
	r->y += r->vy * dir;
	if(r->y >= H)
		r->y -= H;
	if(r->y < 0)
		r->y += H;
	return robot;
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

	InitWindow(W*8, H*8, "AoC2024 Day 14 Part 2 Robots Simulation");
	int t = 0;
	SetTargetFPS(120);
	bool pause = false;
	int dir = 1;
	while(!WindowShouldClose()) {
		if(IsKeyReleased(KEY_LEFT))
			dir = -1;
		else
			dir = 1;
		if(!pause || IsKeyReleased(KEY_RIGHT) || 
				IsKeyReleased(KEY_LEFT)) {
			for(int j = 0; j < vr.size(); j++)
				vr[j]=move(vr[j], dir);
			t+=dir;
		}
		//the numbers subtracted from t are 
		//first occurences of horizontal and vertical recurring number
		//respectively. wait till the glorious easter egg pattern is
		//revealed!
		if((t - 69) % W == 0 && (t-12) % H == 0)
			pause = true;
		if(IsKeyReleased(KEY_SPACE)) pause = !pause;
		BeginDrawing();
		ClearBackground(BLACK);
		for(auto robot : vr)
			DrawRectangle(robot.x*8, robot.y*8, 8, 8, GREEN);
		DrawText(TextFormat("Time: %i", t), 0, 0, 20, WHITE);
		EndDrawing();
	}
	return 0;
}

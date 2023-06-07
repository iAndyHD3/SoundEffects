#pragma once
#include <iostream>

#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

void print();
// Recursive function to print remaining arguments
template<typename T, typename... Args>
void print(const T& arg, const Args&... args) {
    //std::cout << arg << ' ';
    //print(args...);
}

// Function that uses template variable arguments to push everything to std::cout
template<typename... Args>
void printAll(const Args&... args) {
    //print(args...);
    //std::cout << std::endl;
}

enum SoundEffect {
	CUBE_JUMP,
	BALL_JUMP,
	UFO_JUMP,
	WAVE_JUMP,
	ROBOT_JUMP,
	SPIDER_JUMP,
	
	PINK_ORB,
	YELLOW_ORB,
	RED_ORB,
	BLUE_ORB,
	GREEN_ORB,
	BLACK_ORB,
	GREEN_DASH_ORB,
	PINK_DASH_ORB,
	
	PINK_PAD,
	YELLOW_PAD,
	RED_PAD,
	
	COLLECTIBLE,
	COLLECT_COIN,
	
	SPEED_05,
	SPEED_1,
	SPEED_2,
	SPEED_3,
	SPEED_4,

	//not added yet
	/*CUBE_PORTAL,
	SHIP_PORTAL,
	BALL_PORTAL,
	UFO_PORTAL,
	WAVE_PORTAL,
	ROBOT_PORTAL,
	SPIDER_PORTAL,

	TELEPORT_PORTAL,
	GRAVITY_NORMAL_PORTAL,
	GRAVITY_INVERTED_PORTAL,
	ENTER_MINI_PORTAL,
	EXIT_MINI_PORTAL,
	*/
	UNKNOWN,
};

void playSound(SoundEffect s);
const char* getSoundFile(SoundEffect s);
void playJumpSoundForGameMode(void* player);

bool is_cube(void* p);
bool is_ship(void* p);
bool is_ball(void* p);
bool is_ufo(void* p);
bool is_wave(void* p);
bool is_robot(void* p);
bool is_spider(void* p);

bool is_gravity_normal(void* p);
bool is_gravity_flipped(void* p);


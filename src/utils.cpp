#include "utils.h"
#include <fmt/format.h>

void print() {}

const char* getSoundFile(SoundEffect s)
{
	switch(s)
	{
		case CUBE_JUMP:      return "cubeJump.ogg";
		case BALL_JUMP:      return "ballJump.ogg";
		case UFO_JUMP:       return "ufoJump.ogg";
		case WAVE_JUMP:      return "waveJump.ogg";
		case ROBOT_JUMP:     return "robotJump.ogg";
		case SPIDER_JUMP:    return "spiderJump.ogg";
		
		case PINK_ORB:       return "pinkOrb.ogg";
		case YELLOW_ORB:     return "yellowOrb.ogg";
		case RED_ORB:        return "redOrb.ogg";
		case BLUE_ORB:       return "blueOrb.ogg";
		case GREEN_ORB:      return "greenOrb.ogg";
		case BLACK_ORB:      return "blackOrb.ogg";
		case GREEN_DASH_ORB: return "greenDashOrb.ogg";
		case PINK_DASH_ORB:  return "pinkDashOrb.ogg";

		case PINK_PAD:       return "pinkPad.ogg";
		case YELLOW_PAD:     return "yellowPad.ogg";
		case RED_PAD:        return "redPad.ogg";
		
		
		case COLLECTIBLE:    return "collectItem.ogg";
		case COLLECT_COIN:   return "collectCoin.ogg";
		
		case SPEED_05:       return "speed05.ogg";
		case SPEED_1:        return "speed1.ogg";
		case SPEED_2:        return "speed2.ogg";
		case SPEED_3:        return "speed3.ogg";
		case SPEED_4:        return "speed4.ogg";
/*
		case CUBE_PORTAL:   return "cubePortal.ogg";
		case SHIP_PORTAL:   return "shipPortal.ogg";
		case BALL_PORTAL:   return "ballPortal.ogg";
		case UFO_PORTAL:    return "ballPortal.ogg";
		case WAVE_PORTAL:   return "wavePortal.ogg";
		case ROBOT_PORTAL:  return "robotPortal.ogg";
		case SPIDER_PORTAL: return "spiderPortal.ogg";
		
		case TELEPORT_PORTAL:         return "teleportPortal.ogg";
		case GRAVITY_NORMAL_PORTAL:   return "gravityPortalNormal.ogg";
		case GRAVITY_INVERTED_PORTAL: return "gravityPortalInverted.ogg";
		case ENTER_MINI_PORTAL:       return "enterMiniPortal.ogg";
		case EXIT_MINI_PORTAL:        return "exitMiniPortal.ogg";
		*/
		case UNKNOWN: return "unknown.ogg";
	}
	return nullptr;
}

void playSound(SoundEffect s)
{
	if(const char* sound = getSoundFile(s); sound)
	{
		//fmt::println("Sound Played: {}", sound);
		extern void soundmanager_playsound(const char*);
		soundmanager_playsound(sound);		
	}
}

void playJumpSoundForGameMode(void* po)
{
	SoundEffect sound = 
		is_cube(po)  ?   CUBE_JUMP  :
		is_ball(po)  ?   BALL_JUMP  :
		is_ufo(po)   ?   UFO_JUMP   :
		is_robot(po) ?   ROBOT_JUMP : UNKNOWN
	;
		
	playSound(sound);
}



bool is_cube(void* p) {
	return
		!is_ship(p) &&
		!is_ball(p) &&
		!is_ufo(p) &&
		!is_wave(p) &&
		!is_robot(p) &&
		!is_spider(p)
	;
}

bool is_ship(void* p) {
	return MBO(bool, p, 1592);
}

bool is_ball(void* p) {
	return MBO(bool, p, 1594);
}

bool is_ufo(void* p) {
	return MBO(bool, p, 1593);
}

bool is_wave(void* p) {
	return MBO(bool, p, 1595);
}

bool is_robot(void* p) { 
	return MBO(bool, p, 1596);
}

bool is_spider(void* p) { 
	return MBO(bool, p, 1597);
}

bool is_gravity_flipped(void* p)
{
	return MBO(bool, p, 1598);
}

bool is_gravity_normal(void* p)
{
	return !is_gravity_flipped(p);
}




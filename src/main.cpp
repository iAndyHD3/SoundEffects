#include <matdash.hpp>

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

// matdash::create_console
#include <matdash/console.hpp>

// gd.h includes cocos2d.h
#include <gd.h>
#include "utils.h"

using namespace gd;

int getObjectID(void* object) {
	return MBO(int, object, 0x360);
}

void soundmanager_playsound(const char* sound) {
	gd::GameSoundManager::sharedState()->playSound(sound);
}

PlayerObject* getPlayer()
{
	auto pl = GameManager::sharedState()->getPlayLayer();
	if(!pl) return nullptr;
	PlayerObject* po = pl->m_pPlayer1;
	if(!po) return nullptr;
	return po;
}
bool ignoreOrbs = false;
//orb
void PlayerObject_ringJump(void* self, GameObject* ring)
{
	ignoreOrbs = true;
    matdash::orig<&PlayerObject_ringJump>(self, ring);
	ignoreOrbs = false;
	if(ring->m_bHasBeenActivated)
	{
		switch(getObjectID(ring))
		{
			case 36:   return playSound(YELLOW_ORB);
			case 84:   return playSound(BLUE_ORB);
			case 141:  return playSound(PINK_ORB);
			case 1022: return playSound(GREEN_ORB);
			case 1330: return playSound(BLACK_ORB);
			case 1333: return playSound(RED_ORB);
			case 1704: return playSound(GREEN_DASH_ORB);
			case 1751: return playSound(PINK_DASH_ORB);
		}
		//printAll("test", getObjectID(ring));
	}
}
//pad
void GJBaseGameLayer_bumpPlayer(void* self, PlayerObject* player, GameObject* pad)
{
    matdash::orig<&GJBaseGameLayer_bumpPlayer>(self, player, pad);
	if(pad->m_bHasBeenActivated)
	{
		switch(getObjectID(pad))
		{
			case 35:   return playSound(YELLOW_PAD);
			case 140:  return playSound(PINK_PAD);
			case 1332: return playSound(RED_PAD);
		}
	}
}


//collectible
void EffectGameObject_triggerObject(void* self, void* bgl)
{
	matdash::orig<&EffectGameObject_triggerObject>(self, bgl);
	int objectID = getObjectID(self);
	////printAll("objectID", objectID, "triggered");
	switch(objectID)
	{
		case 1275:
		case 1587:
		case 1588:
		case 1589:
		case 1614:
		playSound(COLLECTIBLE);
	}
}

//coin
void GameObject_destroyObject(void* self)
{
	
	int objectID = getObjectID(self);
	if(objectID == 142 || objectID == 1329) {
		playSound(COLLECT_COIN);
	}
	matdash::orig<&GameObject_destroyObject>(self);
}

void PlayerObject_incrementJumps(PlayerObject* self)
{
	matdash::orig<&PlayerObject_incrementJumps>(self);
	if(!ignoreOrbs && getPlayer())
	playJumpSoundForGameMode(self);
}

void PlayerObject_spiderTestJump(void* self, bool idk)
{	
	matdash::orig<&PlayerObject_spiderTestJump>(self, idk);
	if(getPlayer()) playSound(SPIDER_JUMP);
}

void GJBaseGameLayer_pushButton(void* self, int a, int b)
{
	matdash::orig<&GJBaseGameLayer_pushButton>(self, a, b);
	auto player = getPlayer();
	if(!player) return;

	if(is_ufo(player))       playSound(UFO_JUMP);
	else if(is_wave(player)) playSound(WAVE_JUMP);
}

//this function is JUST for speed objects smh 
void GameObject_triggerObject(void* self, void* a)
{
	matdash::orig<GameObject_triggerObject>(self, a);
	int objectID = getObjectID(self);
	switch(objectID)
	{
		case 200:  return playSound(SPEED_05);
		case 201:  return playSound(SPEED_1);
		case 202:  return playSound(SPEED_2);
		case 203:  return playSound(SPEED_3);
		case 1334: return playSound(SPEED_4);
	}
}

//blue orb is special and it doesnt trigger bump player for some reason
void PlayerObjecT_propellPlayer(void* self, float idk)
{
	matdash::orig<&PlayerObjecT_propellPlayer>(self, idk);
	if(idk == 0.8f) playSound(BLUE_ORB);
}
void mod_main(HMODULE)
{

	//make sure to comment this for release
	//matdash::create_console();
	
    //matdash::add_hook<&GameObject_activatedByPlayer>(gd::base + 0xef0e0);
   // matdash::add_hook<&PlayLayer_switchedMode>(gd::base + 0x1f6f70);
    matdash::add_hook<&PlayerObjecT_propellPlayer>(gd::base + 0x1f8b50);
    matdash::add_hook<&GameObject_triggerObject>(gd::base + 0xd1790);
    matdash::add_hook<&GJBaseGameLayer_pushButton>(gd::base + 0x111500);
    matdash::add_hook<&PlayerObject_spiderTestJump>(gd::base + 0x1ed360);
    matdash::add_hook<&GameObject_destroyObject>(gd::base + 0xE5D80);
    matdash::add_hook<&PlayerObject_incrementJumps>(gd::base + 0x1e9a20);
    matdash::add_hook<&PlayerObject_ringJump>(gd::base + 0x1F4FF0);
    matdash::add_hook<&GJBaseGameLayer_bumpPlayer>(gd::base + 0x10ED50);
    matdash::add_hook<&EffectGameObject_triggerObject>(gd::base + 0x253D60);
}

/*

matdash::add_hook<&PlayLayer_pickupItem>(gd::base + 0x208240);
matdash::add_hook<&GJBaseGameLayer_collectItem>(gd::base + 0x111890);
matdash::add_hook<&GJBaseGameLayer_collectObject>(gd::base + 0x111830);
	
void GJBaseGameLayer_collectItem(void* self, int a, int b) {
	
	//std::cout << fmt::format("a: {}, b: {}", a, b) << std::endl;
	matdash::orig<&GJBaseGameLayer_collectItem>(self, a, b);
}

void GJBaseGameLayer_collectObject(void* self, void* obj) {
	
	int objectID = MBO(int, obj, 0x360);
	//std::cout << fmt::format("obid: {}", objectID) << std::endl;
	matdash::orig<&GJBaseGameLayer_collectObject>(self, obj);
}

void PlayLayer_pickupItem(void* self, void* obj) {
	
	int objectID = MBO(int, obj, 0x360);
	//std::cout << fmt::format("obid: {}", objectID) << std::endl;
	matdash::orig<&PlayLayer_pickupItem>(self, obj);
}
*/


/*
void GameObject_activatedByPlayer(void* self, void* a)
{
	int objectID = MBO(int, self, 0x360);
	//printAll("activatedByPlayer self", objectID);
	void* po = getPlayer();
	
	if(objectID == 10 && is_gravity_flipped(po)) {
		playSound(GRAVITY_NORMAL_PORTAL);
	}

	if(objectID == 11 && is_gravity_normal(po)) {
		playSound(GRAVITY_INVERTED_PORTAL);
	}
	
	matdash::orig<&GameObject_activatedByPlayer>(self, a);
}


void PlayLayer_switchedMode(void* self, int type)
{
	matdash::orig<&PlayLayer_switchedMode>(self, type);
	//printAll("switched mode", type);
}
*/



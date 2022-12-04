#include <matdash.hpp>

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

// matdash::create_console
#include <matdash/console.hpp>

// gd.h includes cocos2d.h
#include <gd.h>
#include <fmt/format.h>
using namespace gd;


#define playSound(str) gd::GameSoundManager::sharedState()->playSound(str)
#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

/*
to debug sounds existing .ogg files can be used e.g
gold01.ogg, gold02.ogg, quitSound_01.ogg
however std::cout is better than randomly playing sounds lol
*/

void PlayerObject_ringJump(void* self, GameObject* ring) {
    matdash::orig<&PlayerObject_ringJump>(self, ring);
	if(ring->m_bHasBeenActivated) playSound("orbJump01.ogg");
}

void GJBaseGameLayer_bumpPlayer(void* self, PlayerObject* player, GameObject* pad) {
    matdash::orig<&GJBaseGameLayer_bumpPlayer>(self, player, pad);
	if(pad->m_bHasBeenActivated) playSound("padJump01.ogg");
}



void PlayLayer_update_(gd::PlayLayer* self, float dt) {
	
	auto p1 = self->m_pPlayer1;
	
	bool isFalling = p1->playerIsFalling();
	bool isPressingDown = MBO(int, p1, 0x611) != 0;
	bool onGround = !p1->m_isOnGround && (int)p1->unk610 == 213;
	
	matdash::orig<&PlayLayer_update_, matdash::Thiscall>(self, dt);

	//idk this is crazy (and stupid)
	if(!isFalling && !p1->playerIsFalling() && isPressingDown && onGround){
		//std::cout << "jumped" << std::endl;
		playSound("jump01.ogg");
	}
	//std::cout << fmt::format("isFalling: {}, isPressingDown: {}, onGround: {}, p1->playerIsFalling: {}", isFalling, isPressingDown, onGround, p1->playerIsFalling()) << std::endl;
}



void mod_main(HMODULE) {

	//make sure to comment this for release
	//matdash::create_console();
  
    matdash::add_hook<&PlayerObject_ringJump>(gd::base + 0x1F4FF0);
    matdash::add_hook<&GJBaseGameLayer_bumpPlayer>(gd::base + 0x10ED50);
    matdash::add_hook<&PlayLayer_update_, matdash::Thiscall>(gd::base + 0x2029C0);
}
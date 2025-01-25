#pragma once
#include <km7dev.server_api/include/ServerAPIEvents.hpp>
namespace Midnight {
// bg helper functions
struct bgHelper {
	CCSprite* NewBG1;
	CCSprite* NewBG2;
	CCSprite* NewBG3;
	CCSprite* NewBG4;
	CCSprite* NewBG5;
	CCSprite* NewBG6;
};
inline CCSprite *CreateBg() {
	CCSprite *plahh = CCSprite::create("Background-logo.png"_spr);
	plahh->setColor({255, 255, 255});
	plahh->setZOrder(-100);
	plahh->setScale(0.37);
	plahh->setAnchorPoint({0, 0});
	return plahh;
}

// enums
namespace emums {
	enum class IconType {
		Cube = 0,
		Ship = 1,
		Ball = 2,
		Ufo = 3,
		Wave = 4,
		Robot = 5,
		Spider = 6,
		Swing = 7,
		Jetpack = 8,
		Bounce = 910,
		DeathEffect = 98,
		Special = 99,
		Item = 100,
		ShipFire = 101
	};
}
inline std::pair<const char *, int> IconTypes[] = {
    {"Bounce", static_cast<int>(Midnight::emums::IconType::Bounce)},
};
// server
inline ServerAPIEvents::Server serverID = ServerAPIEvents::registerServer("https://gdmidnight.ps.fhgdps.com", 100);

// logo
inline CCSprite *CovertLogo(CCSprite *mainTitle) {
	auto MidNight = CCSprite::createWithSpriteFrameName("MidNight.png"_spr);
	if (!MidNight)
		return nullptr;

	MidNight->setPosition({mainTitle->getContentSize().width / 2, -13});
	MidNight->setScale(0.75f);
	mainTitle->setDisplayFrame(CCSpriteFrameCache::get()->spriteFrameByName("Geometry-Dash.png"_spr));
	mainTitle->addChild(MidNight);
	mainTitle->setPositionY(mainTitle->getPositionY() + 15.f);
	return MidNight;
}
}; // namespace Midnight
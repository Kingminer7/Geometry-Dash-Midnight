#pragma once
#include <km7dev.server_api/include/ServerAPIEvents.hpp>
namespace Midnight {
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
inline ServerAPIEvents::Server serverID = ServerAPIEvents::registerServer("https://gdmidnight.ps.fhgdps.com", 100);
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
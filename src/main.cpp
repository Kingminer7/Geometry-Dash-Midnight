#include "namespace.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <km7dev.server_api/include/ServerAPIEvents.hpp>
using namespace geode::prelude;

class $modify(MenuLayerLogo, MenuLayer) {
	bool init() {
		if (!MenuLayer::init())
			return false;
		if (CCNode *mainTitle = this->getChildByID("main-title"))
			if (CCSprite *Logoimg = typeinfo_cast<CCSprite *>(mainTitle)) {
				Midnight::CovertLogo(Logoimg);
			};
		return true;
	}
};

class $modify(LoadingLayerLogo, LoadingLayer) {
	bool init(bool fromReload) {
		if (!LoadingLayer::init(fromReload))
			return false;

		auto SFC = CCSpriteFrameCache::get();

		auto director = CCDirector::get();
		auto winSize = director->getWinSize();
		auto GM = GameManager::sharedState();

		auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";
		CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str());

		SFC->addSpriteFramesWithFile("Midnight-logo.plist"_spr);
		if (CCNode *mainTitle = this->getChildByID("gd-logo"))
			if (CCSprite *Logoimg = typeinfo_cast<CCSprite *>(mainTitle)) {
				Midnight::CovertLogo(Logoimg);
			};

		if (!GM->getUGV("30")) { // fuck the stupid popup imo
			GM->setUGV("30", true);
		}

		return true;
	}
};
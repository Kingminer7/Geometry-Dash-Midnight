#include "namespace.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/MenuGameLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <km7dev.server_api/include/ServerAPIEvents.hpp>
using namespace geode::prelude;

class $modify(MenuGameLayerMidnightColors, MenuGameLayer) {
	struct Fields {
		double m_tickcount = 0;
		Midnight::bgHelper m_bgs = {nullptr, nullptr, nullptr};
		double movementMult = -3;
		bool tweeningval = false;
		int tweeningto = -3;
	}; // 63 63 56

	bool init() {
		if (!MenuGameLayer::init())
			return false;

		GJGroundLayer *groundLayer = this->m_groundLayer;
		this->m_backgroundSprite->setVisible(false);

		this->m_fields->m_bgs.NewBG1 = Midnight::CreateBg();
		this->m_fields->m_bgs.NewBG2 = Midnight::CreateBg();
		this->m_fields->m_bgs.NewBG3 = Midnight::CreateBg();
		this->m_fields->m_bgs.NewBG4 = Midnight::CreateBg();
		this->m_fields->m_bgs.NewBG5 = Midnight::CreateBg();
		this->m_fields->m_bgs.NewBG6 = Midnight::CreateBg();
		// parent them
		this->addChild(this->m_fields->m_bgs.NewBG1);
		this->addChild(this->m_fields->m_bgs.NewBG2);
		this->addChild(this->m_fields->m_bgs.NewBG3);
		this->addChild(this->m_fields->m_bgs.NewBG4);
		this->addChild(this->m_fields->m_bgs.NewBG5);
		this->addChild(this->m_fields->m_bgs.NewBG6);
		// start pos
		this->m_fields->m_bgs.NewBG1->setPositionX(0);
		this->m_fields->m_bgs.NewBG2->setPositionX(this->m_fields->m_bgs.NewBG1->getPositionX() + this->m_fields->m_bgs.NewBG1->getScaledContentWidth());
		this->m_fields->m_bgs.NewBG3->setPositionX(this->m_fields->m_bgs.NewBG2->getPositionX() + this->m_fields->m_bgs.NewBG2->getScaledContentWidth());
		this->m_fields->m_bgs.NewBG4->setPositionX(this->m_fields->m_bgs.NewBG3->getPositionX() + this->m_fields->m_bgs.NewBG3->getScaledContentWidth());
		this->m_fields->m_bgs.NewBG5->setPositionX(this->m_fields->m_bgs.NewBG4->getPositionX() + this->m_fields->m_bgs.NewBG4->getScaledContentWidth());
		this->m_fields->m_bgs.NewBG6->setPositionX(this->m_fields->m_bgs.NewBG5->getPositionX() + this->m_fields->m_bgs.NewBG5->getScaledContentWidth());

		CCSpriteBatchNode *col = typeinfo_cast<CCSpriteBatchNode *>(groundLayer->getChildByID("ground-sprites"));
		col->setTexture(CCTextureCache::get()->textureForKey("LogoGround.png"_spr));
		col->getChildByType<CCSprite *>(0)->setColor({255, 255, 255});
		col->getChildByType<CCSprite *>(0)->setChildColor({255, 255, 255});
		return true;
	}
	void update(float p0) {
		MenuGameLayer::update(p0);
		if (this->m_fields->tweeningval) {
			if (this->m_fields->movementMult > this->m_fields->tweeningto) {
				this->m_fields->movementMult -= p0 * 1.5;
				if (this->m_fields->movementMult < this->m_fields->tweeningto) {
					this->m_fields->movementMult = this->m_fields->tweeningto;
					this->m_fields->tweeningval = false;
				}
			} else {
				if (this->m_fields->movementMult < this->m_fields->tweeningto) {
					this->m_fields->movementMult += p0 * 1.5;
					if (this->m_fields->movementMult > this->m_fields->tweeningto) {
						this->m_fields->movementMult = this->m_fields->tweeningto;
						this->m_fields->tweeningval = false;
					}
				} else {
					this->m_fields->tweeningval = false;
				}
			}
		}
		if (this->m_fields->m_bgs.NewBG1) {
			if (this->m_fields->m_tickcount < -900) {
				this->m_fields->tweeningto = 3;
				this->m_fields->tweeningval = true;
			}

			if (this->m_fields->m_tickcount > -10 && this->m_fields->movementMult == 3) {
				this->m_fields->tweeningto = -3;
				this->m_fields->tweeningval = true;
			}
			this->m_fields->m_bgs.NewBG1->setPositionX(this->m_fields->m_tickcount);
			this->m_fields->m_bgs.NewBG2->setPositionX(this->m_fields->m_bgs.NewBG1->getPositionX() + this->m_fields->m_bgs.NewBG1->getScaledContentWidth());
			this->m_fields->m_bgs.NewBG3->setPositionX(this->m_fields->m_bgs.NewBG2->getPositionX() + this->m_fields->m_bgs.NewBG2->getScaledContentWidth());
			this->m_fields->m_bgs.NewBG4->setPositionX(this->m_fields->m_bgs.NewBG3->getPositionX() + this->m_fields->m_bgs.NewBG3->getScaledContentWidth());
			this->m_fields->m_bgs.NewBG5->setPositionX(this->m_fields->m_bgs.NewBG4->getPositionX() + this->m_fields->m_bgs.NewBG4->getScaledContentWidth());
			this->m_fields->m_bgs.NewBG6->setPositionX(this->m_fields->m_bgs.NewBG5->getPositionX() + this->m_fields->m_bgs.NewBG5->getScaledContentWidth());
		};
		this->m_fields->m_tickcount += (this->m_fields->movementMult * p0);
	}
	void updateColor(float p0) {
		// ticker
	}
};

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
// load custom pack!
$on_mod(Loaded) {
	auto PackPath = geode::Mod::get()->getResourcesDir().string();
	CCFileUtils::get()->addTexturePack(CCTexturePack{.m_id = Mod::get()->getID(), .m_paths = {PackPath}});
}

class $modify(LoadingLayerLogo, LoadingLayer) {
	bool init(bool fromReload) {

		if (!LoadingLayer::init(fromReload))
			return false;

		auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";
		CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str());

		m_textArea->setString(Midnight::LoadingMessages.at(rand() % (Midnight::LoadingMessages.size() - 1)).c_str());

		auto version = CCLabelBMFont::create(fmt::format("{}", Mod::get()->getVersion().toVString(true)).c_str(), "goldFont.fnt");
		version->setPosition({5, 5});
		version->setAnchorPoint({0, 0});
		version->setScale(0.5f);
		version->setOpacity(15);
		this->addChild(version);

		auto SFC = CCSpriteFrameCache::get();
		auto TFC = CCTextureCache::get();
		auto director = CCDirector::get();
		auto winSize = director->getWinSize();
		auto GM = GameManager::sharedState();

		SFC->addSpriteFramesWithFile("Midnight-logo.plist"_spr);
		TFC->addImage("LogoGround.png"_spr, true);
		TFC->addImage("Background-logo"_spr, true);

		if (CCNode *mainTitle = this->getChildByID("gd-logo"))
			if (CCSprite *Logoimg = typeinfo_cast<CCSprite *>(mainTitle)) {
				Midnight::CovertLogo(Logoimg);
			};

		if (CCNode *BgTexture = this->getChildByID("bg-texture")) {
			CCSprite *Background = Midnight::CreateBg();
			this->addChild(Background);
			CCSprite *BackgroundFiller = Midnight::CreateBg();
			BackgroundFiller->setPositionX(Background->getPositionX() + Background->getScaledContentWidth());
			this->addChild(BackgroundFiller);
			BgTexture->setVisible(false);
		};
		if (!GM->getUGV("30")) { // fuck the stupid popup imo
			GM->setUGV("30", true);
		}

		return true;
	}
};
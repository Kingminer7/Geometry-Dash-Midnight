#include "namespace.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/SimplePlayer.hpp>
using namespace geode::prelude;

class $modify(MIDNIGHTSimplePlayer, SimplePlayer) {
	struct Fields {
		Midnight::emums::IconType m_icontype;
		CCSprite *m_BounceTexture;
	};
	bool init(int p0) {
		if (!SimplePlayer::init(p0))
			return false;
		this->m_fields->m_BounceTexture = CCSprite::createWithSpriteFrameName("MidNight.png"_spr);
		this->m_fields->m_BounceTexture->setVisible(false);
		this->m_fields->m_BounceTexture->setID("bounce-icon/texture"_spr);
		this->addChild(this->m_fields->m_BounceTexture);
		return true;
	}
	void updatePlayerFrame(int iconID, IconType type) {
		this->m_fields->m_icontype = static_cast<Midnight::emums::IconType>(type);
		SimplePlayer::updatePlayerFrame(iconID, type);
		UpdateMidnightTextures();
	}
	void updatePlayerFrame(int iconID, Midnight::emums::IconType type) {
		this->m_fields->m_icontype = type;
		SimplePlayer::updatePlayerFrame(iconID, static_cast<IconType>(0));
		UpdateMidnightTextures();
	}
	void UpdateMidnightTextures() {
		bool isCustomIcon;
		for (const auto data : Midnight::IconTypes) {
			isCustomIcon = data.second == static_cast<int>(this->m_fields->m_icontype);
			if (isCustomIcon)
				break;
		}
		if (isCustomIcon) {
			if (this->m_fields->m_icontype == Midnight::emums::IconType::Bounce) {
				this->m_fields->m_BounceTexture->setVisible(true);
				this->m_firstLayer->setVisible(false);
			}
		}
	}
};

class $modify(MIDNIGHTGarageLay, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init())
			return false;

		auto gm = GameManager::get();

		auto menu = getChildByID("shards-menu");

		if (auto shards = menu->getChildByID("shards-button"))
			shards->setVisible(false);

		if (auto paint = menu->getChildByID("color-button"))
			paint->setPositionY(paint->getPositionY() + 25);

		if (auto shopButton = getChildByID("top-left-menu")->getChildByID("shop-button"))
			shopButton->setVisible(false);

		if (auto categoryMenu = static_cast<CCMenu *>(getChildByID("category-menu"))) {
			auto trailButton = categoryMenu->getChildByID("trail-button");
			auto effectButton = categoryMenu->getChildByID("death-effect-button");
			effectButton->removeFromParentAndCleanup(false);
			trailButton->removeFromParentAndCleanup(false);

			for (const auto data : Midnight::IconTypes) {
				const char *buttonName = data.first;
				int buttonEnum = data.second;

				auto sprOff = IconSelectButtonSprite::createWithSpriteFrameName("MidNight.png"_spr, 1.5, IconSelectBaseColor::Unselected);
				sprOff->setScale(.9f);

				auto sprOn = IconSelectButtonSprite::createWithSpriteFrameName("MidNight.png"_spr, 1.5, IconSelectBaseColor::Selected);
				sprOn->setScale(.9f);

				auto toggler = CCMenuItemToggler::create(sprOff, sprOn, this, menu_selector(GJGarageLayer::onSelectTab));
				toggler->setID(fmt::format("{}-button"_spr, buttonName));
				toggler->setTag(buttonEnum);
				toggler->setEnabled(true);

				categoryMenu->addChild(toggler);
			}

			categoryMenu->addChild(trailButton);
			categoryMenu->addChild(effectButton);
			categoryMenu->updateLayout();
		};
		return true;
	}

	void onSelectTab(CCObject *sender) {
		GJGarageLayer::onSelectTab(sender);
		auto tag = sender->getTag();

		auto arr = getChildByID("category-menu")->getChildren();

		if (arr) {
			for (auto child : CCArrayExt<CCMenuItemToggler *>(arr)) {
				child->toggle(false);
				child->setEnabled(true);
				if (child->getTag() == tag) {
					child->toggle(true);
					child->setEnabled(false);
				}
			}
		}

		auto size = CCDirector::sharedDirector()->getWinSize();
		bool isCustomIcon = false;
		for (const auto data : Midnight::IconTypes) {
			isCustomIcon = data.second == tag;
			if (isCustomIcon)
				break;
		}
		if (isCustomIcon) {
			auto itemArray = CCArray::create();

			auto square = CCSprite::createWithSpriteFrameName("playerSquare_001.png");

			square->setOpacity(0);

			auto vehicleID = static_cast<IconType>(tag);

			auto itemIcon = SimplePlayer::create(0);
			itemIcon->updatePlayerFrame(1, vehicleID);

			itemIcon->setColor(GameManager::sharedState()->colorForIdx(17));
			itemIcon->setPosition(square->getContentSize() / 2);

			square->addChild(itemIcon);

			auto selectIcon = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
			selectIcon->setPosition(square->getContentSize() / 2);

			square->addChild(selectIcon);

			square->setScale(.8f);

			auto button = CCMenuItemSpriteExtra::create(square, this, menu_selector(MIDNIGHTGarageLay::onCustomSelect));
			button->setTag(tag);

			itemArray->addObject(button);

			auto buttonBar = m_iconSelection;

			auto extendedLayer = buttonBar->m_scrollLayer->m_extendedLayer;
			extendedLayer->removeAllChildrenWithCleanup(true);

			auto menu = CCMenu::create();
			menu->setPosition({size.width / 2 - 160, size.height / 2 - 40});

			menu->addChild(button);

			extendedLayer->addChild(menu);
		}
	}

	void onCustomSelect(CCObject *sender) {
		auto icon = static_cast<IconType>(sender->getTag());
		auto iconUnlock = static_cast<UnlockType>(sender->getTag());

		m_playerObject->updatePlayerFrame(1, icon);

		ItemInfoPopup::create(1, iconUnlock)->show();
	}

	void onBack(CCObject *sender) { GJGarageLayer::onBack(sender); }
};


//later me to sort out
/*
#include <Geode/modify/GameObject.hpp>

class NEWEnhancedPortalGameObject : public EnhancedGameObject {
	public:
		static NEWEnhancedPortalGameObject* create() {
				auto ret = new NEWEnhancedPortalGameObject;

				if (ret && ret->init()) {
					ret->autorelease();
					return ret;
				}

				CC_SAFE_DELETE(ret);
				return nullptr;
			};
	bool init(){
		if (!EnhancedGameObject::init("ring_01_001.png")) {
			return false;
		};
		return true;
	}
	virtual void activatedByPlayer(PlayerObject* p0) {
		if (p0) {
			p0->toggleSwingMode(true,true);
		}
		log::debug("i've been touched?");
	};
	public:
		void xd() {
			log::debug("i've been touched?");
		};
};



// new portal 7854001

class $modify(GameObjectNewObjects, GameObject) {
	static GameObject* createWithKey(int p0) {
		GameObject* obj;
		if (p0 == 4395) {
			obj = NEWEnhancedPortalGameObject::create();
			obj->setColor({0,0,0});
			obj->m_objectID = 4395;
		} else {
			obj = GameObject::createWithKey(p0);
		}
		return obj;
	};
};

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayerMidNight, PlayLayer) {
	void addObject(GameObject *obj) {
		if (obj->m_objectID == 4395) {
			PlayLayer::addObject(obj);
			if (typeinfo_cast<RingObject*>(obj)) {
				log::debug("My object is a ring");
			};
			log::debug("La portal is {}",obj);
			PlayLayerMidNight::AddCustomPortal(obj);
		} else {
			PlayLayer::addObject(obj);
		};
	};
	void AddCustomPortal(GameObject *portal) {
		log::debug("La portal is {}",portal);
	}
};

#include <Geode/modify/PlayerObject.hpp>
class $modify(PlayerObjectMidNight, PlayerObject) {
	void switchedToMode(GameObjectType newMode) {
		// well i will need this later
		switch (newMode) {
		case GameObjectType::ShipPortal:
			toggleBirdMode(false, false);
			toggleRollMode(false, false);
			toggleDartMode(false, false);
			toggleRobotMode(false, false);
			toggleSpiderMode(false, false);
			toggleSwingMode(false, false);
			break;
		case GameObjectType::CubePortal:
			toggleFlyMode(false, false);
			toggleBirdMode(false, false);
			toggleRollMode(false, false);
			toggleDartMode(false, false);
			toggleRobotMode(false, false);
			toggleSpiderMode(false, false);
			toggleSwingMode(false, false);
			break;

		case GameObjectType::BallPortal:
			toggleFlyMode(false, false);
			toggleBirdMode(false, false);
			toggleDartMode(false, false);
			toggleRobotMode(false, false);
			toggleSpiderMode(false, false);
			toggleSwingMode(false, false);
			break;

		case GameObjectType::WavePortal:
			toggleFlyMode(false, false);
			toggleBirdMode(false, false);
			toggleRollMode(false, false);
			toggleRobotMode(false, false);
			toggleSpiderMode(false, false);
			toggleSwingMode(false, false);
			break;

		case GameObjectType::RobotPortal:
			toggleFlyMode(false, false);
			toggleBirdMode(false, false);
			toggleRollMode(false, false);
			toggleDartMode(false, false);
			toggleSpiderMode(false, false);
			toggleSwingMode(false, false);
			break;

		case GameObjectType::SpiderPortal:
			toggleFlyMode(false, false);
			toggleBirdMode(false, false);
			toggleRollMode(false, false);
			toggleDartMode(false, false);
			toggleRobotMode(false, false);
			toggleSwingMode(false, false);
			break;

		case GameObjectType::SwingPortal:
			toggleFlyMode(false, false);
			toggleBirdMode(false, false);
			toggleRollMode(false, false);
			toggleDartMode(false, false);
			toggleRobotMode(false, false);
			toggleSpiderMode(false, false);
			break;

		default:
			break;
		};
	};
};
*/
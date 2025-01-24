#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
using namespace geode::prelude;
class $modify(GauntletSelectLayerMidNight, GauntletSelectLayer) {
	void onInfo(CCObject *) {
		FLAlertLayer::create("Gauntlets", "<cg>Gauntlets</c> are <cp>themed</c> collection of <cc>5 rated</c> levels that give a speical <cy>reward</c> once beaten. They are made by the <cl>midnight team</c> or <ca>the community</c>.", "OK")->show();
	};
};

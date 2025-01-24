#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>
using namespace geode::prelude;

class $modify(MidNightSave, GManager) {

	void setup() {
		auto compare = std::string(m_fileName);

		compare.insert(std::string_view(compare).find(".dat"), "Midnight");

		m_fileName = compare;
		GManager::setup();
	}
};

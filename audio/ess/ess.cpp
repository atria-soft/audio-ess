/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <etk/types.hpp>

#include <audio/river/Interface.hpp>
#include <audio/river/Manager.hpp>
#include <audio/ess/ess.hpp>
#include <audio/ess/debug.hpp>
#include <ejson/ejson.hpp>
#include <etk/uri/uri.hpp>

ememory::SharedPtr<audio::river::Manager> g_audioManager;
ememory::SharedPtr<audio::ess::Effects> g_effects;
ememory::SharedPtr<audio::ess::Music> g_music;

void audio::ess::init() {
	g_audioManager = audio::river::Manager::create("ewol-sound-set");
	g_effects = ememory::makeShared<audio::ess::Effects>(g_audioManager);
	g_music = ememory::makeShared<audio::ess::Music>(g_audioManager);
}

void audio::ess::unInit() {
	g_effects.reset();
	g_music.reset();
	g_audioManager.reset();
}

void audio::ess::soundSetParse(const etk::String& _data) {
	ejson::Document doc;
	doc.parse(_data);
	ejson::Object obj = doc["musics"].toObject();
	if (    obj.exist() == true
	     && g_music != null) {
		for (auto &it : obj.getKeys()) {
			etk::String file = obj[it].toString().get();
			EWOLSA_INFO("load Music : '" << it << "' file=" << file);
			g_music->load(file, it);
		}
	}
	obj = doc["effects"].toObject();
	if (    obj.exist() == true
	     && g_effects != null) {
		for (auto &it : obj.getKeys()) {
			etk::String file = obj[it].toString().get();
			EWOLSA_INFO("load Effect : '" << it << "' file=" << file);
			g_effects->load(file, it);
		}
	}
}

void audio::ess::soundSetLoad(const etk::Uri& _uri) {
	etk::String data;
	etk::uri::readAll(_uri, data);
	soundSetParse(data);
}

void audio::ess::musicPlay(const etk::String& _name) {
	if (g_music == null) {
		return;
	}
	g_music->play(_name);
}

void audio::ess::musicStop() {
	if (g_music == null) {
		return;
	}
	g_music->stop();
}

void audio::ess::musicSetVolume(float _dB) {
	if (g_audioManager == null) {
		return;
	}
	g_audioManager->setVolume("MUSIC", _dB);
}

float audio::ess::musicGetVolume() {
	if (g_audioManager == null) {
		return 0.0f;
	}
	return g_audioManager->getVolume("MUSIC");
}

void audio::ess::musicSetMute(bool _mute) {
	if (g_audioManager == null) {
		return;
	}
	g_audioManager->setMute("MUSIC", _mute);
}

bool audio::ess::musicGetMute() {
	if (g_audioManager == null) {
		return 0.0f;
	}
	return g_audioManager->getMute("MUSIC");
}

int32_t audio::ess::effectGetId(const etk::String& _name) {
	if (g_effects == null) {
		return -1;
	}
	return g_effects->getId(_name);
}

void audio::ess::effectPlay(int32_t _id, const vec3& _pos) {
	if (g_effects == null) {
		return;
	}
	g_effects->play(_id, _pos);
}

void audio::ess::effectPlay(const etk::String& _name, const vec3& _pos) {
	if (g_effects == null) {
		return;
	}
	g_effects->play(_name, _pos);
}

void audio::ess::effectSetVolume(float _dB) {
	if (g_audioManager == null) {
		return;
	}
	g_audioManager->setVolume("EFFECT", _dB);
}

float audio::ess::effectGetVolume() {
	if (g_audioManager == null) {
		return 0.0f;
	}
	return g_audioManager->getVolume("EFFECT");
}

void audio::ess::effectSetMute(bool _mute) {
	if (g_audioManager == null) {
		return;
	}
	g_audioManager->setMute("EFFECT", _mute);
}

bool audio::ess::effectGetMute() {
	if (g_audioManager == null) {
		return 0.0f;
	}
	return g_audioManager->getMute("EFFECT");
}


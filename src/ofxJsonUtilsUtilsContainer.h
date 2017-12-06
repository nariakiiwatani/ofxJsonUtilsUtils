#pragma once

#include "ofxWatchFile.h"
#include "ofxJsonUtils.h"

namespace ofx { namespace JsonUtilsUtils {
template<typename ConvertType, bool NDJson>
class Container : public ConvertType
{
public:
	using Type = ConvertType;
	using Json = typename std::conditional<NDJson, std::vector<ofJson>, ofJson>::type;
	Container() {
		watcher_.addListener(this, &Container::reload);
	}
	bool load(const std::string &filepath, std::vector<std::string> hierarchy={}) {
		hierarchy_ = hierarchy;
		filepath_ = filepath;
		return watcher_.setTargetPath(filepath);
	}
	void setTargetPath(const std::string &filepath) {
		filepath_ = filepath;
		watcher_.setTargetPath(filepath, false);
	}
	void setWillSaveListener(std::function<void(const Type&, Json&)> callback) {
		save_callback_ = callback;
	}
	void setDidLoadListener(std::function<void(Type&, const Json&)> callback) {
		loaded_callback_ = callback;
	}
	bool reload() {
		return watcher_.load();
	}
	bool overwrite(int indent=4) const {
		return writeToFile(filepath_, indent);
	}
	bool writeToFile(const std::string &filepath, int indent=4) const {
		if(filepath == "") {
			return false;
		}
		Json json = loadFunc(filepath);
		Json local = ofxJsonUtils::convert(*(Type*)this);
		if(save_callback_) {
			save_callback_(*this, local);
		}
		hierarchySet(local, json);
		bool is_watching = watcher_.isWatching();
		watcher_.disableWatching();
		bool ret = saveFunc(filepath, json, true, indent);
		if(is_watching) {
			watcher_.enableWatching();
		}
		return ret;
	}
	void loadJson(const ofJson &json) {
		ofxJsonUtils::parse(json, *(Type*)this);
	}
	ofJson toJson() const {
		return ofxJsonUtils::convert(*(Type*)this);
	}
	template<typename ReturnType, typename ...ArgTypes>
	ReturnType userFunc(ArgTypes...);
private:
	void reload(ofFile &file) {
		Json json = loadFunc(file.path());
		json = hierarchyGet(json);
		ofxJsonUtils::parse(json, *this);
		if(loaded_callback_) {
			loaded_callback_(*this, json);
		}
	}
	mutable ofxWatchFile watcher_;
	std::string filepath_="";
	std::vector<std::string> hierarchy_={};
	std::function<void(const Type&, Json&)> save_callback_ = nullptr;
	std::function<void(Type&, const Json&)> loaded_callback_ = nullptr;
	
	template<typename T = Json>
	auto loadFunc(const std::string &filepath) const
	-> typename std::enable_if<NDJson, T>::type {
		return ofxJsonUtils::loadNDJsonFromFile(filepath);
	}
	template<typename T = Json>
	auto loadFunc(const std::string &filepath) const
	-> typename std::enable_if<!NDJson, T>::type {
		return ofxJsonUtils::loadFromFile(filepath);
	}
	
	template<typename T = bool>
	auto saveFunc(const std::string &filepath, const Json &json, bool isInDataDir = true, int indent=-1) const
	-> typename std::enable_if<NDJson, T>::type {
		return ofxJsonUtils::writeToNDJsonFile(filepath, json, isInDataDir, -1);
	}
	template<typename T = bool>
	auto saveFunc(const std::string &filepath, const Json &json, bool isInDataDir = true, int indent=4) const
	-> typename std::enable_if<!NDJson, T>::type {
		return ofxJsonUtils::writeToFile(filepath, json, isInDataDir, indent);
	}
	
	std::vector<ofJson> hierarchyGet(const std::vector<ofJson> &json) const {
		auto ret = json;
		for(auto &j : ret) {
			for(auto &h : hierarchy_) {
				j = j[h];
			}
		}
		return ret;
	}
	ofJson hierarchyGet(const ofJson &json) const {
		auto ret = json;
		for(auto &h : hierarchy_) {
			ret = ret[h];
		}
		return ret;
	}
	void hierarchySet(const std::vector<ofJson> &json, std::vector<ofJson> &root) const {
		root.resize(json.size());
		for(int i = 0, num = json.size(); i < num; ++i) {
			auto *dst = &root[i];
			for(auto &h : hierarchy_) {
				dst = &(*dst)[h];
			}
			*dst = json[i];
		}
	}
	void hierarchySet(const ofJson &json, ofJson &root) const {
		auto *dst = &root;
		for(auto &h : hierarchy_) {
			dst = &(*dst)[h];
		}
		*dst = json;
	}
};
}}
template<typename Type, bool NDJson=false>
using ofxJsonContainer = ofx::JsonUtilsUtils::Container<Type, NDJson>;

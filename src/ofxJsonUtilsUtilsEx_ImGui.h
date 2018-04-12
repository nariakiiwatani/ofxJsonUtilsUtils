#pragma once

#include "imgui.h"
#include "ofSystemUtils.h"

namespace ofx { namespace JsonUtilsUtils { namespace ImGuiEx {
template<typename Container>
static inline bool Save(Container &container, const std::string &default_filename="", int indent=-1) {
	bool success = false;
	bool tried = false;
	if(ImGui::Button("Save")) {
		tried = true;
		success = container.overwrite(indent);
	}
	ImGui::SameLine();
	if(ImGui::Button("Save As") || (tried && !success)) {
		auto result = ofSystemSaveDialog(default_filename, "Save As...");
		if(result.bSuccess) {
			if(container.writeToFile(result.getPath(), indent)) {
				container.setTargetPath(result.getPath());
				success = true;
			}
		}
	}
	return success;
}
template<typename Container>
static inline bool Load(Container &container) {
	bool success = false;
	bool tried = false;
	if(ImGui::Button("Reload")) {
		tried = true;
		success = container.reload();
	}
	ImGui::SameLine();
	if(ImGui::Button("Load From") || (tried && !success)) {
		auto result = ofSystemLoadDialog("Load From...");
		if(result.bSuccess) {
			if(container.load(result.getPath())) {
				container.setTargetPath(result.getPath());
				success = true;
			}
		}
	}
	return success;
}
template<typename Container>
static inline void SaveLoad(Container &container, bool &saved, bool &loaded, const std::string &default_filename="", int indent=4) {
	saved = Save(container, default_filename, indent);
	ImGui::SameLine();
	loaded = Load(container);
}
template<typename Container>
static inline void SaveLoad(Container &container, const std::string &default_filename="", int indent=4) {
	Save(container, default_filename, indent);
	ImGui::SameLine();
	Load(container);
}
}}}

namespace ofxJsonImGui = ofx::JsonUtilsUtils::ImGuiEx;

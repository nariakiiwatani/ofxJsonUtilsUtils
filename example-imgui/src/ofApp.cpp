#include "ofApp.h"

#include "imgui.h"
#include "ofxJsonUtilsUtilsEx_ImGui.h"

// you can add any functionality(s) using template function.
// this time, I use it for imgui.
template<> template<>
void ofxJsonContainer<Data>::userFunc()
{
	ImGui::DragFloat("radius", &circle_size);
	ImGui::ColorEdit4("circle color", &circle_color[0]);
	ImGui::DragFloat("line width", &line_width);
	ImGui::ColorEdit4("line color", &line_color[0]);
	if(ImGui::TreeNode("points")) {
		for(int i = 0, num = points.size(); i < num; ++i) {
			ImGui::SliderFloat2(("p"+ofToString(i,2)).c_str(), &points[i][0], 0, max(ofGetWidth(),ofGetHeight()));
		}
		ImGui::TreePop();
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	data_.load("data.json");
	gui_.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushStyle();
	ofNoFill();
	ofSetColor(data_.line_color);
	ofSetLineWidth(data_.line_width);
	ofBeginShape();
	for(auto &p : data_.points) {
		ofVertex(p.x, p.y);
	}
	ofEndShape();
	
	ofFill();
	ofSetColor(data_.circle_color);
	for(auto &p : data_.points) {
		ofDrawCircle(p, data_.circle_size);
	}
	ofPopStyle();
	
	ofDrawBitmapStringHighlight("click to add a point.", 10,10);
	ofDrawBitmapStringHighlight("press enter to save to file.", 10,30);
	ofDrawBitmapStringHighlight("when you edit data.json manually, it will reload automatically.", 10,50);
	ofDrawBitmapStringHighlight("or you can save/load by GUI buttons.", 10,70);
	
	gui_.begin();
	if(ImGui::Begin("data")) {
		// add save/load buttons to gui
		ofxJsonImGui::SaveLoad(data_, "data.json");
		data_.userFunc<void>();
	}
	ImGui::End();
	gui_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case OF_KEY_RETURN:
			data_.overwrite();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(!ImGui::IsMouseHoveringAnyWindow()) {
		data_.points.emplace_back(x,y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	data_.load("data.json");
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
	data_.points.emplace_back(x,y);
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

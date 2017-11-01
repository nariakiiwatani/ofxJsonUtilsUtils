#pragma once

#include "ofMain.h"

#include "ofxJsonUtilsUtils.h"
#include "ofxJsonUtilsUtilsContainer.h"

// define struct or class you want to bind to json
struct Data {
	float circle_size;
	ofFloatColor circle_color;
	float line_width;
	ofFloatColor line_color;
	vector<ofVec2f> points;

	// just put this to implement `loadJson` and `toJson`
	// in this example, circle_size is not binded to json file directory.
	JSON_FUNCS(circle_color,line_width,line_color,points);
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
private:
	ofxJsonContainer<Data> data_;
};

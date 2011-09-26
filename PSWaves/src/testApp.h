#pragma once

#include "ofMain.h"
#include "ofxOcean.h"
#include "ofxGameCamera.h"
#include "ofxOceanRenderer.h"

class testApp : public ofBaseApp{

  public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofFbo fbo;
	ofxOcean* ocean;
	ofxOceanRenderer* renderer;

	ofxGameCamera cam;
	ofVideoGrabber vid;
	
	
    int oceanTileSizeX;
    int oceanTileSizeY;
	float windSpeed;
	float waveScale;
	float choppyScale;
	float waveSpeed;
	
};

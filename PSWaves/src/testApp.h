#pragma once

#include "ofMain.h"
#include "ofxOcean.h"
#include "ofxGameCamera.h"
#include "ofxOceanRenderer.h"

#include "ofxPSScreen.h"

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
	
	void splitAndDraw();
	void saveScreens();
	void loadScreens();

    int oceanTileSizeX;
    int oceanTileSizeY;
	float windSpeed;
	float waveScale;
	float choppyScale;
	float waveSpeed;
	
	//edit mode stuff
	vector<ofxPSScreen*> screens;
	bool editingHandles;
	bool editingTextureRatios;
		
	bool draggingCorner;
	ofxPSScreen* currentScreen;
	int currentPointDragIndex;
	ofVec2f dragOffset;
	
	void gaussian_elimination(float *input, int n);
	void findHomography(ofVec2f src[4], ofVec2f dst[4], float homography[16]);
};

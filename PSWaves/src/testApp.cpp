#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
//	ofBackground(0);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
    ofEnableAlphaBlending();
	
	fbo.allocate(6144, 768, GL_RGB, 4);
	
	cam.setScale(1,-1,1);
	cam.speed = 1.5;
	cam.useArrowKeys = false;
	cam.usemouse = true;
	cam.autosavePosition = true;
	cam.loadCameraPosition();
	
	
	oceanTileSizeX = 200;
	oceanTileSizeY = 200;
	
	ocean = new ofxOcean();
    ocean->size = ofVec3f(oceanTileSizeX, 1.0, oceanTileSizeY);
    ocean->windSpeed = 32;
	
    //all other ocean params are set per frame
    ocean->setup();
	
	renderer = new ofxOceanRenderer();
	renderer->shaderLocation = "";
	renderer->setup(ocean, 9, 9);
	
}

//--------------------------------------------------------------
void testApp::update(){
    ocean->waveScale = ofGetMouseX()/100.0;
    ocean->choppyScale = ofGetMouseY()/200.0;
	
    ocean->waveSpeed = 10;
	ocean->setFrameNum(ofGetFrameNum());
    ocean->update();
	
	renderer->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	fbo.begin();
	ofClear(0, 0, 0, 255);
	
	/*
	ofNoFill();
	ofSetLineWidth(10);
	ofBeginShape();
	for(int i = 0; i < fbo.getWidth(); i+=30){
		ofVertex( i, (sin(i/10.0 + ofGetElapsedTimef()) + .5) * fbo.getHeight() );
	}
	ofEndShape();
	*/
	
	cam.begin(ofRectangle(0, 0, fbo.getWidth(), fbo.getHeight()));
	
	ofSetColor(255, 255, 255, 255);
	renderer->drawWireframe();
	
	cam.end();
	
	fbo.end();
	

	//calculate how to draw onto main screen
	float widthRatio = ofGetWidth()/fbo.getWidth();
	float newHeight = fbo.getHeight()*widthRatio;
	fbo.getTextureReference().draw(0,0,ofGetWidth(), newHeight);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
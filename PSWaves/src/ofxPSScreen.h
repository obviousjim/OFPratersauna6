/**
 *  ofxPSScreen.h
 *  PSWaves
 *
 *  Created by Jim on 9/27/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"

class ofxPSScreen {
  public:
	ofVec2f source[4];
	ofVec2f dest[4];
	float textureStartPercent;
	float textureStopPercent;
	int topCrop;
	int bottomCrop;
	
	GLfloat correctionMatrix[16];
};
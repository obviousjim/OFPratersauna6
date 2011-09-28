/*
 *  ofxOceanContourGenerator.h
 *  PSWaves
 *
 *  Created by Jim on 9/28/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOceanContour.h"

class ofxOceanContourGenerator {
  public:
	float tileSize;
	float step;
	
	void generate();
	void update();
	void draw();
	
	ofxOcean* ocean;
	vector<ofxOceanContour*> contours;
};
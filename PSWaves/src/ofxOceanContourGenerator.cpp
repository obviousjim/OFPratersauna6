/*
 *  ofxOceanContourGenerator.cpp
 *  PSWaves
 *
 *  Created by Jim on 9/28/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#include "ofxOceanContourGenerator.h"

void ofxOceanContourGenerator::generate(){
	for(int i = 0; i < tileSize; i += step){
		ofxOceanContour* c = new ofxOceanContour();
		c->startpos = ofVec2f(i, 0);
		c->endpos = ofVec2f(i, tileSize);
		
		c->velocity = ofVec2f(0,0);
		c->thickness = .1;
		c->sampleStep = 4;
		
		c->ocean = ocean;
		
		contours.push_back( c );
	}
	
	for(int i = 0; i < tileSize; i += step){
		ofxOceanContour* c = new ofxOceanContour();
		c->startpos = ofVec2f(0, i);
		c->endpos = ofVec2f(tileSize, i);
		
		c->velocity = ofVec2f(0,0);
		c->thickness = .1;
		c->sampleStep = 4;
		
		c->ocean = ocean;
		
		contours.push_back( c );
	}
	
}

void ofxOceanContourGenerator::update(){
	
	for(int i = 0; i < contours.size(); i++){
		contours[i]->update();
	}
	
		
}

void ofxOceanContourGenerator::draw(){
	for(int i = 0; i < contours.size(); i++){
		contours[i]->draw();
	}
}

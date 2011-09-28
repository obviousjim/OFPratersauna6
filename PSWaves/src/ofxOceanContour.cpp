/*
 *  ofxOceanContour.cpp
 *  PSWaves
 *
 *  Created by Jim on 9/28/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#include "ofxOceanContour.h"

ofxOceanContour::ofxOceanContour(){
	age = 0;
	velocity = ofVec2f(0,0);
	
	startpos = ofVec2f(0,0);
	endpos = ofVec2f(0,0);
	thickness = 10;
	sampleStep = 5;
	
	ocean = NULL;
	
}

void ofxOceanContour::update(){
	startpos += velocity;
	endpos += velocity;
	age++;
}

void ofxOceanContour::draw(){
	
	ofVec2f currentPoint = startpos;
	ofVec2f trajectory = (endpos - startpos).normalized();
	ofVec2f leftStep = trajectory.getRotated(90);
	ofVec2f rightStep = trajectory.getRotated(-90);
	 
	int numsteps = (startpos.distance(endpos)/sampleStep);
	
	vector<ofVec3f> points;
	vector<ofFloatColor> colors;
	for(int i = 0; i < numsteps; i++){
		ofVec3f buoyLeft  = ocean->floatingPosition( currentPoint + leftStep*thickness/2.0  );
		ofVec3f buoyRight = ocean->floatingPosition( currentPoint + rightStep*thickness/2.0 );
		points.push_back( buoyLeft );
		points.push_back( buoyRight );
		
		ofFloatColor colorLeft  = ofFloatColor(1.0,1.0,1.0);
		ofFloatColor colorRight = ofFloatColor(1.0,1.0,1.0);
		colors.push_back(colorLeft);
		colors.push_back(colorRight);
		
		currentPoint += trajectory*sampleStep;
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(ofFloatColor), &(colors[0].r));
	glVertexPointer(3, GL_FLOAT, sizeof(ofVec3f), &(points[0].x));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, colors.size());
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	
}

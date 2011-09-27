#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
    ofEnableAlphaBlending();
	
	fbo.allocate(6144, 768, GL_RGB, 4);
	
	ofSetWindowPosition(0, 0);
	ofSetWindowShape(fbo.getWidth(), fbo.getHeight());
	
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

	
	editingHandles = false;
	editingTextureRatios = false;	
	currentScreen = NULL;
	loadScreens();
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
		
	cam.begin(ofRectangle(0, 0, fbo.getWidth(), fbo.getHeight()));
	
	ofSetColor(255, 255, 255, 255);
	renderer->drawWireframe();
	cam.end();
	fbo.end();
	
	splitAndDraw();
	
	if(editingHandles){
		ofPushStyle();
		for(int i = 0; i < screens.size(); i++){
			ofxPSScreen* s = screens[i];
			
			//draw handles
			for(int p = 0; p < 4; p++){
				if(s == currentScreen && p == currentPointDragIndex){
					ofFill();
				}
				else{
					ofNoFill();
				}
				ofSetColor(255, 0, 0);
				ofCircle(s->dest[p], 10);
				ofSetColor(255, 255, 0);
				ofCircle(s->dest[p], 3);
			}
			
			ofNoFill();
			//draw outline
			if(s == currentScreen){
				ofSetColor(255, 0, 0);
			}
			else{
				ofSetColor(255, 255, 0);
			}
			ofSetLineWidth(2);
			ofBeginShape();
			for(int p = 0; p < 4; p++){
				ofVertex(s->dest[p].x,s->dest[p].y);
			}	
			ofEndShape(true);
		}
		ofPopStyle();
	}
	
	

//	//calculate how to draw onto main screen
//	float widthRatio = ofGetWidth()/fbo.getWidth();
//	float newHeight = fbo.getHeight()*widthRatio;
//	fbo.getTextureReference().draw(0,0,ofGetWidth(), newHeight);

}

void testApp::splitAndDraw(){
	
	fbo.getTextureReference().bind();
	
	for(int i = 0; i < screens.size(); i++){
		ofPushMatrix();
		
		ofxPSScreen* screen = screens[i];
		findHomography(screen->source, screen->dest,screen->correctionMatrix);
		
		glMultMatrixf(screen->correctionMatrix);
		glBegin(GL_QUADS);
		glTexCoord2f(fbo.getWidth()*screen->textureStartPercent, 0);
		glVertex2f(screen->source[0].x, screen->source[0].y);
		
		glTexCoord2f(fbo.getWidth()*screen->textureStopPercent, 0);
		glVertex2f(screen->source[1].x, screen->source[1].y);

		glTexCoord2f(fbo.getWidth()*screen->textureStopPercent, fbo.getHeight());
		glVertex2f(screen->source[2].x, screen->source[2].y);

		glTexCoord2f(fbo.getWidth()*screen->textureStartPercent, fbo.getHeight());
		glVertex2f(screen->source[3].x, screen->source[3].y);
		
		glEnd();
		
		ofPopMatrix();
	}
	
	fbo.getTextureReference().unbind();
}

void testApp::saveScreens(){
}

void testApp::loadScreens(){
	ofxXmlSettings savedsettings;
	if(savedsettings.loadFile("screens.xml")){
		//parse em out
	}
	else{
		//make new ones
		for(int i = 0; i < 6; i++){
			ofxPSScreen* s = new ofxPSScreen();
			s->bottomCrop = 0;
			s->topCrop = 0;
			s->textureStartPercent = i/6.0;
			s->textureStopPercent = (i+1)/6.0;
			s->source[0] = s->dest[0] = ofPoint(s->textureStartPercent*fbo.getWidth(), 0);
			s->source[1] = s->dest[1] = ofPoint(s->textureStopPercent*fbo.getWidth(), 0);
			s->source[2] = s->dest[2] = ofPoint(s->textureStopPercent*fbo.getWidth(), fbo.getHeight());
			s->source[3] = s->dest[3] = ofPoint(s->textureStartPercent*fbo.getWidth(), fbo.getHeight());
			screens.push_back( s );
		}
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' '){
		editingHandles = !editingHandles;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(editingHandles && currentScreen != NULL){
		currentScreen->dest[currentPointDragIndex] = ofVec2f(x,y) - dragOffset;
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(editingHandles){
		ofVec2f mousePoint(x,y);
		for(int i = 0; i < screens.size(); i++){
			for (int p = 0; p < 4; p++) {
				if(mousePoint.distance(screens[i]->dest[p]) < 20){
					currentScreen = screens[i];
					currentPointDragIndex = p;
					dragOffset = screens[i]->dest[p] - mousePoint;
					break;
				}
			}
		}
	}
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

void testApp::gaussian_elimination(float *input, int n){
	// ported to c from pseudocode in
	// http://en.wikipedia.org/wiki/Gaussian_elimination
	float * A = input;
	int i = 0;
	int j = 0;
	int m = n-1;
	while (i < m && j < n)
	{
		// Find pivot in column j, starting in row i:
		int maxi = i;
		for(int k = i+1; k<m; k++)
		{
			if(fabs(A[k*n+j]) > fabs(A[maxi*n+j]))
			{
				maxi = k;
			}
		}
		if (A[maxi*n+j] != 0)
		{
			//swap rows i and maxi, but do not change the value of i
			if(i!=maxi)
				for(int k=0; k<n; k++)
				{
					float aux = A[i*n+k];
					A[i*n+k]=A[maxi*n+k];
					A[maxi*n+k]=aux;
				}
			//Now A[i,j] will contain the old value of A[maxi,j].
			//divide each entry in row i by A[i,j]
			float A_ij=A[i*n+j];
			for(int k=0; k<n; k++)
			{
				A[i*n+k]/=A_ij;
			}
			//Now A[i,j] will have the value 1.
			for(int u = i+1; u< m; u++)
			{
				//subtract A[u,j] * row i from row u
				float A_uj = A[u*n+j];
				for(int k=0; k<n; k++)
				{
					A[u*n+k]-=A_uj*A[i*n+k];
				}
				//Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
			}
			i++;
		}
		j++;
	}
	
	//back substitution
	for(int i=m-2; i>=0; i--)
	{
		for(int j=i+1; j<n-1; j++)
		{
			A[i*n+m]-=A[i*n+j]*A[j*n+m];
			//A[i*n+j]=0;
		}
	}
}


void testApp::findHomography(ofVec2f src[4], ofVec2f dst[4], float homography[16]) {
	
	// create the equation system to be solved
	//
	// from: Multiple View Geometry in Computer Vision 2ed
	//       Hartley R. and Zisserman A.
	//
	// x' = xH
	// where H is the homography: a 3 by 3 matrix
	// that transformed to inhomogeneous coordinates for each point
	// gives the following equations for each point:
	//
	// x' * (h31*x + h32*y + h33) = h11*x + h12*y + h13
	// y' * (h31*x + h32*y + h33) = h21*x + h22*y + h23
	//
	// as the homography is scale independent we can let h33 be 1 (indeed any of the terms)
	// so for 4 points we have 8 equations for 8 terms to solve: h11 - h32
	// after ordering the terms it gives the following matrix
	// that can be solved with gaussian elimination:
	float P[8][9]=
	{
		{-src[0].x, -src[0].y, -1,   0,   0,  0, src[0].x*dst[0].x, src[0].y*dst[0].x, -dst[0].x }, // h11
		{  0,   0,  0, -src[0].x, -src[0].y, -1, src[0].x*dst[0].y, src[0].y*dst[0].y, -dst[0].y }, // h12
		{-src[1].x, -src[1].y, -1,   0,   0,  0, src[1].x*dst[1].x, src[1].y*dst[1].x, -dst[1].x }, // h13
		{  0,   0,  0, -src[1].x, -src[1].y, -1, src[1].x*dst[1].y, src[1].y*dst[1].y, -dst[1].y }, // h21
		{-src[2].x, -src[2].y, -1,   0,   0,  0, src[2].x*dst[2].x, src[2].y*dst[2].x, -dst[2].x }, // h22
		{  0,   0,  0, -src[2].x, -src[2].y, -1, src[2].x*dst[2].y, src[2].y*dst[2].y, -dst[2].y }, // h23
		{-src[3].x, -src[3].y, -1,   0,   0,  0, src[3].x*dst[3].x, src[3].y*dst[3].x, -dst[3].x }, // h31
		{  0,   0,  0, -src[3].x, -src[3].y, -1, src[3].x*dst[3].y, src[3].y*dst[3].y, -dst[3].y }, // h32
	};
	
	
	gaussian_elimination(&P[0][0],9);
	
	
	// gaussian elimination gives the results of the equation system
	// in the last column of the original matrix.
	// opengl needs the transposed 4x4 matrix:
	float aux_H[]= { P[0][8],P[3][8],0,P[6][8], // h11  h21 0 h31
		P[1][8],P[4][8],0,P[7][8], // h12  h22 0 h32
		0      ,      0,0,0,       // 0    0   0 0
		P[2][8],P[5][8],0,1
	};      // h13  h23 0 h33
	
	for(int i=0; i<16; i++) homography[i] = aux_H[i];
}

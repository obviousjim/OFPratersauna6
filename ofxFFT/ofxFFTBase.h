/*
 *  AudioAbstract.h
 *  openFrameworks
 *
 *  Created by lukasz karluk on 29/08/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AUDIO_ABSTRACT_H
#define AUDIO_ABSTRACT_H

#include "ofMain.h"
#include "fft.h"

#define OFX_FFT_WIDTH           512
#define OFX_FFT_HEIGHT          256
#define OFX_FFT_NO_OF_BANDS		256

struct ofxFFTData
{
	int				size;
	
	vector<float>	data;
	vector<float>	dataNorm;
	vector<float>	dataMax;
	vector<float>	dataPeak;
	vector<int>		dataCut;
	
	float			maxDecay;
    float           peakValue;
	float			peakDecay;
	float			peakAverage;
	float			cutThreshold;
	
	float			linearEQIntercept;
	float			linearEQSlope;
};

class ofxFFTBase : public ofBaseApp
{

public :
	
	 ofxFFTBase();
	~ofxFFTBase();
	
	virtual void  setup				();
	virtual void  update			();
	
	virtual void  draw				( int x = 0, int y = 0 );
	virtual void  draw				( int x, int y, int w, int h );
	
	virtual void  drawData			( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );
	virtual void  drawBg			( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );
	virtual void  drawGlitchData	( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );
	virtual void  drawFftData		( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );
	virtual void  drawFftNormData	( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );	
	virtual void  drawFftPeakData	( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );
	virtual void  drawThresholdLine ( const ofxFFTData &audioData, int w = OFX_FFT_WIDTH, int h = OFX_FFT_HEIGHT );
    virtual void  drawBorder        ( int w, int h );
	
	virtual void  initFFT			();
	virtual void  killFFT			();
	
	virtual void  initAudioData		( ofxFFTData &audioData, int dataSize );
	virtual void  updateAudioData	( ofxFFTData &audioData, float *dataNew );
	virtual void  mirrorAudioData	( ofxFFTData &audioData );
	virtual void  resetAudioData	( ofxFFTData &audioData );
	
	virtual void  setNoOfBands		( int value );
	virtual int   getNoOfBands		( );
	virtual void  setThreshold		( float value );
	virtual float getThreshold		( );
	virtual float getAveragePeak	( );
	virtual void  setPeakDecay		( float value );
	virtual float getPeakDecay		( );
	virtual void  setMaxDecay		( float value );
	virtual float getMaxDecay		( );
	virtual void  setMirrorData		( bool value );
	
	virtual void  getFftData		( float *data, int length );
	virtual void  getFftPeakData	( float *data, int length );
	virtual void  getGlitchData		( int   *data, int length );
	
protected :	
	
	int		audioNoOfBands;
	int		audioNoOfBandsHalf;
	
	float	*specData;
	
	fft		myfft;
	float	*fftMagnitude;
	float	*fftPhase;
	float	*fftPower;
	float	*fftFreq;
	float	fftAveragePower;
	
	bool	bMirrorData;
	
	ofxFFTData	rawData;
	ofxFFTData	fftData;
	
	//-- render bits.
	
	int		renderBorder;
	int		renderSingleBandWidth;
	
    ofMutex mutex;
};

#endif
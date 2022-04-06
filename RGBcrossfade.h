/*
RGB Crossfade library
Project started Dec 2018 by Daniel Meyer
dmeyer302@gmail.com

This library is based on concepts found at this link:
https://www.arduino.cc/en/Tutorial/ColorCrossfader

*/
#ifndef RGBcrossfade_h
#define RGBcrossfade_h

#include "Arduino.h"

class RGBcrossfade
{
public:
	void begin(byte rPin, byte gPin, byte bPin, byte wPin, bool dimmingCurve);
	void fadeToBlack(int seconds);
	void fadeToWhite(int seconds);
	void fadeToWhiteLevel(byte level, int seconds);
	void fadeToColor(byte color[4], int seconds);
	void updateRGB();
	void color(byte color[4]);
	void black();
	void white();
	
	bool done;

	byte r();
	byte g();
	byte b();
	byte w();
	

private:
	void initializeFadeEvent(byte color[4], int seconds);
	void writeValues();
	int sign(int x);

	byte _rPin;
	byte _gPin;
	byte _bPin;
	byte _wPin;

	byte _rVal;
	byte _gVal;
	byte _bVal;
	byte _wVal;

	byte _desiredR;
	byte _desiredG;
	byte _desiredB;
	byte _desiredW;

	unsigned long _rTime;
	unsigned long _gTime;
	unsigned long _bTime;
	unsigned long _wTime;

	int _rDirection;
	int _gDirection;
	int _bDirection;
	int _wDirection;

	long _numSteps;
	const byte ledTable[256] = { 0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9,10,10,10,11,11,12,12,12,13,13,14,14,15,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,23,23,24,24,25,25,26,27,27,28,28,29,30,30,31,32,32,33,34,34,35,36,36,37,38,39,39,40,41,42,42,43,44,45,45,46,47,48,49,49,50,51,52,53,54,55,55,56,57,58,59,60,61,62,63,64,65,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,83,84,85,86,87,88,89,90,91,92,94,95,96,97,98,99,100,102,103,104,105,106,108,109,110,111,113,114,115,116,118,119,120,121,123,124,125,127,128,129,131,132,133,135,136,137,139,140,142,143,144,146,147,149,150,152,153,154,156,157,159,160,162,163,165,166,168,169,171,172,174,175,177,179,180,182,183,185,186,188,190,191,193,195,196,198,200,201,203,205,206,208,210,211,213,215,216,218,220,222,223,225,227,229,230,232,234,236,238,239,241,243,245,247,249,250,252,255 };
	
	unsigned long _previousMillisR;
	unsigned long _previousMillisG;
	unsigned long _previousMillisB;
	unsigned long _previousMillisW;

	bool _update;
	bool _dimmingCurve;


};

#endif
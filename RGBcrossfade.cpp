/*
  RGB Crossfade library
  Project started Dec 2018 by Daniel Meyer
  dmeyer302@gmail.com

  This library is based on concepts found at this link:
  https://www.arduino.cc/en/Tutorial/ColorCrossfader
  
*/

#include "Arduino.h"
#include "RGBcrossfade.h"

// Constructor
//RGBcrossfade::RGBcrossfade(){}

// Functions

void RGBcrossfade::begin(byte rPin, byte gPin, byte bPin, byte wPin, bool dimmingCurve)
{
	_rVal = 0;
	_gVal = 0;
	_bVal = 0;
	_wVal = 0;

	pinMode(rPin, OUTPUT);
	pinMode(gPin, OUTPUT);
	pinMode(bPin, OUTPUT);
	pinMode(wPin, OUTPUT);

	_rPin = rPin;
	_gPin = gPin;
	_bPin = bPin;
	_wPin = wPin;

	_dimmingCurve = dimmingCurve;

}


void RGBcrossfade::initializeFadeEvent(byte color[4], int seconds)
{
	_desiredR = color[0];
	_desiredG = color[1];
	_desiredB = color[2];
	_desiredW = color[3];

	// Error checking
	if (_desiredR > 255) {_desiredR = 255;}
	else if (_desiredR < 0) {_desiredR = 0;}

	if (_desiredG > 255) {_desiredG = 255;}
	else if (_desiredG < 0) {_desiredG = 0;}

	if (_desiredB > 255) {_desiredB = 255;}
	else if (_desiredB < 0) {_desiredB = 0;}

	if (_desiredW > 255) {_desiredW = 255;}
	else if (_desiredW < 0) {_desiredW = 0;}

	// Calculates amount value must change over fade period
	int deltaR = _desiredR - _rVal;
	int deltaG = _desiredG - _gVal;
	int deltaB = _desiredB - _bVal;
	int deltaW = _desiredW - _wVal;

	// Determines which direction to fade each color
	_rDirection = sign(deltaR);
	_gDirection = sign(deltaG);
	_bDirection = sign(deltaB);
	_wDirection = sign(deltaW);

	// Calculates time interval between each fade step
	_rTime = (seconds * 1000) / abs(deltaR);
	_gTime = (seconds * 1000) / abs(deltaG);
	_bTime = (seconds * 1000) / abs(deltaB);
	_wTime = (seconds * 1000) / abs(deltaW);
}

void RGBcrossfade::updateRGB(void)
{
	if(_rVal != _desiredR)
		if (millis() - _previousMillisR >= _rTime)
		{
			_rVal = _rVal + _rDirection;
			
			if (_rVal > 255) {
				_rVal = 255;
			}
			else if (_rVal < 0) {
				_rVal = 0;
			}

			_previousMillisR = millis();
		}

	if (_gVal != _desiredG)
		if (millis() - _previousMillisG >= _gTime)
		{
			_gVal = _gVal + _gDirection;

			if (_gVal > 255) {
				_gVal = 255;
			}
			else if (_gVal < 0) {
				_gVal = 0;
			}

			_previousMillisG = millis();
		}

	if (_bVal != _desiredB)
		if (millis() - _previousMillisB >= _bTime)
		{
			_bVal = _bVal + _bDirection;

			if (_bVal > 255) {
				_bVal = 255;
			}
			else if (_bVal < 0) {
				_bVal = 0;
			}

			_previousMillisB = millis();
		}

	if (_wVal != _desiredW)
		if (millis() - _previousMillisW >= _wTime)
		{
			_wVal = _wVal + _wDirection;

			if (_wVal > 255) {
				_wVal = 255;
			}
			else if (_wVal < 0) {
				_wVal = 0;
			}

			_previousMillisW = millis();
		}

	if ((_rVal == _desiredR) &&	(_gVal == _desiredG) &&	(_bVal == _desiredB) &&	(_wVal == _desiredW)) {
		done = 1;
	}
	else { done = 0; }
	//Serial.println(done);

	writeValues();
}

void RGBcrossfade::fadeToBlack(int seconds)
{
	byte color[4] = { 0,0,0,0 };
	initializeFadeEvent(color, seconds);
	Serial.println("here2");
}

void RGBcrossfade::fadeToWhite(int seconds)
{
	byte color[4] = {0, 0, 0, 255};
	initializeFadeEvent(color, seconds);
}

void RGBcrossfade::fadeToWhiteLevel(byte level, int seconds)
{
	byte color[4] = { 0,0,0,level };
	initializeFadeEvent(color, seconds);
}

void RGBcrossfade::fadeToColor(byte color[4], int seconds)
{
	initializeFadeEvent(color,seconds);
}

void RGBcrossfade::color(byte color[4])
{
	_rVal = color[0];
	_gVal = color[1];
	_bVal = color[2];
	_wVal = color[3];

	_desiredR = color[0];
	_desiredG = color[1];
	_desiredB = color[2];
	_desiredW = color[3];

	writeValues();

}

void RGBcrossfade::black()
{
	_rVal = 0;
	_gVal = 0;
	_bVal = 0;
	_wVal = 0;

	_desiredR = 0;
	_desiredG = 0;
	_desiredB = 0;
	_desiredW = 0;

	writeValues();
}

void RGBcrossfade::white()
{
	_rVal = 0;
	_gVal = 0;
	_bVal = 0;
	_wVal = 255;

	_desiredR = 0;
	_desiredG = 0;
	_desiredB = 0;
	_desiredW = 255;

	writeValues();
}

void RGBcrossfade::writeValues(void)
{
	if (_dimmingCurve) {
		analogWrite(_rPin, _rVal);
		analogWrite(_gPin, _gVal);
		analogWrite(_bPin, _bVal);
		analogWrite(_wPin, ledTable[_wVal]);
	}

	else {
		analogWrite(_rPin, _rVal);
		analogWrite(_gPin, _gVal);
		analogWrite(_bPin, _bVal);
		analogWrite(_wPin, _wVal);
	}
}

int RGBcrossfade::sign(int x) {
	return (x > 0) - (x < 0);
}

byte RGBcrossfade::r(void) {
	return _rVal;
}

byte RGBcrossfade::g(void) {
	return _gVal;
}

byte RGBcrossfade::b(void) {
	return _bVal;
}

byte RGBcrossfade::w(void) {
	return _wVal;
}
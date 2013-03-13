#include "testApp.h"

#include "ofxKeyValueOSC.h"

ofxKeyValueOSC keyValue;

class MyObject
{
public:
	
	ofVec3f pos;
	ofFloatColor color;
	
	void draw()
	{
		ofFill();
		ofSetColor(color);
		
		ofCircle(pos, 100);
	}
	
};

MyObject myObject1;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(0);
	
	keyValue.setup(5500);
}

//--------------------------------------------------------------
void testApp::update()
{
	
	// get value directly
	
	string s;
	if (keyValue.get("/string_value", s))
	{
		cout << "/string_value: " << s << endl;
	}
	
	
	// get value as osc message
	
	ofxOscMessage m;
	if (keyValue.get("/test", m))
	{
		cout << "/test: " << m.getArgAsFloat(0) << endl;
	}
	
	
	// use Key-Value-Store style address

	keyValue.get("/myObject1.pos", myObject1.pos);
	keyValue.get("/myObject1.color", myObject1.color);
	
	
	// FIFO queue access
	
	int value;
	while (keyValue.get("/uzi", value))
	{
		printf("%i\n", value);
	}

}

//--------------------------------------------------------------
void testApp::draw()
{
	myObject1.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
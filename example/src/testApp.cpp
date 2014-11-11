#include "testApp.h"

#include "ofxKeyValueOSC.h"

ofxKeyValueOSC keyValue;
ofParameter<float> param1;
ofParameter<bool> param2;
ofParameter<ofVec2f> param3;
ofParameterGroup params;

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

	params.setName("params");
  params.add( param1.set("param1float", 0.5f) );
  params.add( param2.set("param2bool", false) );
  params.add( param3.set("param3vec2", ofVec2f(0.1,0.2)) );
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


  for (int i = 0; i < params.size(); i++)
  {
    string name = "/"+params.getName(i);
    if ( keyValue.get( name, params.get(i) ) )
      cout << "update param " << name << " = " << params.get(i) << endl;
  }

	
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

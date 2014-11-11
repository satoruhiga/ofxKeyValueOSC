#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofBackground(100);

  sender.setup("localhost", 5500);

  col.addListener(this, &ofApp::update_col);
  pos.addListener(this, &ofApp::update_pos);

  gui.setup("panel");

  gui.add( col.set( "myObject1.color", ofFloatColor(0.5,0.5,0.7,1.0), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1) ) );

  gui.add( pos.set( "myObject1.pos", ofVec3f(ofGetWidth()*.5, ofGetHeight()*.5, 0.), ofVec3f(0,0,0), ofVec3f(ofGetWidth(),ofGetHeight(), 1000) ) );

  gui.add( param1.set( &sender, "param1float", 0.5f, 0.0f, 0.1f) );
  gui.add( param2.set( &sender, "param2bool", true) );
  gui.add( param3.set( &sender, "param3vec2", ofVec2f(1.0,2.0), ofVec2f(0,0), ofVec2f(1,1)) );
}

void ofApp::update_col(ofFloatColor& _col)
{
  ofxOscMessage m;
  m.setAddress("/"+col.getName());
  m.addFloatArg( _col.r );
  m.addFloatArg( _col.g );
  m.addFloatArg( _col.b );
  m.addFloatArg( _col.a );
  sender.sendMessage(m);
};

void ofApp::update_pos(ofVec3f& _pos)
{
  ofxOscMessage m;
  m.setAddress("/"+pos.getName());
  m.addFloatArg( _pos.x );
  m.addFloatArg( _pos.y );
  m.addFloatArg( _pos.z );
  sender.sendMessage(m);
};


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

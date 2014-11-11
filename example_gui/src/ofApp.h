#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "oscParamSender.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxPanel gui;
    ofxOscSender sender;

    ofParameter<ofFloatColor> col;
    ofParameter<ofVec3f> pos;
    void update_col(ofFloatColor& col);
    void update_pos(ofVec3f& pos);

    oscParamSender<float> param1;
    oscParamSender<bool> param2;
    oscParamSender<ofVec2f> param3;

};

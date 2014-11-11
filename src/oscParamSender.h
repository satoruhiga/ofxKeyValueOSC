#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

template<typename T>
class oscParamSender
{
  public:

    oscParamSender(){};
    ~oscParamSender()
    {
      _param.removeListener(this, &oscParamSender::update);
      sender = NULL;
    };

    ofParameter<T>& set( ofxOscSender* sender, string name, T value, T min, T max  ) 
    {
      _param.set(name, value, min, max);
      return init( sender );
    };

    ofParameter<T>& set( ofxOscSender* sender, string name, T value ) 
    {
      _param.set(name, value);
      return init( sender );
    };

  private:

    ofParameter<T>& init( ofxOscSender* sender ) 
    {
      this->sender = sender;
      _param.addListener(this, &oscParamSender::update);
      return _param;
    };

    void update(T& value)
    {
      string name = "/"+_param.getName();
      //cout << "oscParamSender update " << name << " = " << value << endl;
      m.clear();
      m.setAddress( name );
      update_msg( value );
      sender->sendMessage(m);
    };

    void update_msg( float& value )
    { m.addFloatArg( value ); };

    void update_msg( double& value )
    { m.addFloatArg( value ); };

    void update_msg( int& value )
    { m.addIntArg( value ); };

    void update_msg( bool& value )
    { m.addIntArg( value ); };

    void update_msg( string& value )
    { m.addStringArg( value ); };

    void update_msg( ofVec2f& value )
    { 
      m.addFloatArg( value.x );
      m.addFloatArg( value.y );
    };

    void update_msg( ofVec3f& value )
    { 
      m.addFloatArg( value.x );
      m.addFloatArg( value.y );
      m.addFloatArg( value.z );
    };

    void update_msg( ofColor& value )
    { 
      m.addIntArg( value.r );
      m.addIntArg( value.g );
      m.addIntArg( value.b );
      m.addIntArg( value.a );
    };

    void update_msg(ofFloatColor& value)
    { 
      m.addFloatArg( value.r );
      m.addFloatArg( value.g );
      m.addFloatArg( value.b );
      m.addFloatArg( value.a );
    };

    ofxOscSender* sender;
    ofxOscMessage m;
    ofParameter<T> _param;
};

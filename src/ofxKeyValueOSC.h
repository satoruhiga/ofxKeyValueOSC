#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

#include <queue>

#ifndef HAS_CPP11
#include <tr1/unordered_map>
#include <tr1/memory>

namespace std {
	using std::tr1::unordered_map;
}
#endif

/*

HOW TO USE
==========

ofxKeyValueOSC keyValue;

void testApp::setup()
{
	// ...

	keyValue.setup(9000);

	// ...
}

void testApp::update()
{
	// ...

 
	// get value directly
 
	string s;
	keyValue.get("/string_value", s);

	cout << s << endl;
 
 
	// get value as osc message
 
	ofxOscMessage m;
	if (keyValue.get("/test", m))
	{
		cout << "/test " << m.getArgAsFloat(0) << endl;
	}
 
 
	// use Key-Value-Store style address
 
	MyObject myObject1;
	keyValue.get("myObject1.pos", myObject1.pos);
	keyValue.get("myObject1.color", myObject1.color);

	
	// FIFO queue access
	
	int value;
	while (keyValue.get("/uzi", value))
	{
		printf("%i\n", value);
	}

	// ...
}

*/

class ofxKeyValueOSC
{
	typedef ofPtr<ofxOscMessage> ofxOscMessageRef;
	
	struct MessageList {
		typedef vector<ofxOscMessageRef>::iterator iterator;
		
		vector<ofxOscMessageRef> msgs;
		iterator itor;
	};
	
	std::unordered_map<string, MessageList> keyValue;

	ofxOscReceiver receiver;
	
public:
	
	void setup(int port)
	{
		receiver.setup(port);
		setEnable();
	}
	
	void clear()
	{
		keyValue.clear();
	}

	bool get(const string& key, ofxOscMessage &m, bool get_latest = false)
	{
		MessageList &msg_list = keyValue[key];
		if (msg_list.msgs.empty()) return false;

		if (get_latest)
		{
			const ofxOscMessageRef& ref = msg_list.msgs.back();
			if (!ref) return false;

			m = *ref;
			return true;
		}
		else
		{
			MessageList::iterator &it = msg_list.itor;
			
			if (it == msg_list.msgs.end())
			{
				it = msg_list.msgs.begin();
				return false;
			}
			
			const ofxOscMessageRef& ref = *it;
			if (!ref) return false;
			
			m = *ref;
			it++;
			
			return true;
		}
	}
	
	template <typename T>
	bool getLatest(const string& key, T& value)
	{
		return get(key, value, true);
	}

	void remove(const string& key)
	{
		keyValue.erase(key);
	}
	
	void setEnable(bool v = true)
	{
		if (v)
			ofAddListener(ofEvents().update, this, &ofxKeyValueOSC::onUpdate, OF_EVENT_ORDER_BEFORE_APP);
		else
			ofRemoveListener(ofEvents().update, this, &ofxKeyValueOSC::onUpdate, OF_EVENT_ORDER_BEFORE_APP);
	}
	
	void setDisable()
	{
		setEnable(false);
	}
		
	//
	// other type shortcuts
	//
	
	bool get(const string& key, float &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value = m.getArgAsFloat(0);
		
		return true;
	}
	
	bool get(const string& key, double &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value = m.getArgAsFloat(0);
		
		return true;
	}
	
	bool get(const string& key, int &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value = m.getArgAsInt32(0);
		
		return true;
	}
	
	bool get(const string& key, bool &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value = m.getArgAsInt32(0);
		
		return true;
	}
	
	bool get(const string& key, string &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value = m.getArgAsString(0);
		
		return true;
	}
	
	bool get(const string& key, ofVec2f &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value.x = m.getArgAsFloat(0);
		value.y = m.getArgAsFloat(1);
		
		return true;
	}
	
	bool get(const string& key, ofVec3f &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value.x = m.getArgAsFloat(0);
		value.y = m.getArgAsFloat(1);
		value.z = m.getArgAsFloat(2);
		
		return true;
	}
	
	bool get(const string& key, ofColor &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value.r = m.getArgAsInt32(0);
		value.g = m.getArgAsInt32(1);
		value.b = m.getArgAsInt32(2);
		
		if (m.getNumArgs() == 4)
		{
			value.a = m.getArgAsInt32(3);
		}
		
		return true;
	}
	
	bool get(const string& key, ofFloatColor &value, bool get_latest = false)
	{
		ofxOscMessage m;
		if (!get(key, m, get_latest)) return false;
		
		value.r = m.getArgAsFloat(0);
		value.g = m.getArgAsFloat(1);
		value.b = m.getArgAsFloat(2);
		
		if (m.getNumArgs() == 4)
		{
			value.a = m.getArgAsFloat(3);
		}
		
		return true;
	}

  bool get(const string& key, ofAbstractParameter& param, bool get_latest = false)
	{

    ofxOscMessage m;
    if (!get(key, m, get_latest)) return false;

    ofAbstractParameter* p = &param;

    if ( p->type() == typeid(ofParameter<int>).name() ) 
    {
      p->cast<int>() = m.getArgAsInt32(0);
      return true;
    }

    else if ( p->type() == typeid(ofParameter<bool>).name() ) 
    {
      p->cast<bool>() = m.getArgAsInt32(0);
      return true;
    }

    else if ( p->type() == typeid(ofParameter<float>).name() ) 
    {
      p->cast<float>() = m.getArgAsFloat(0);
      return true;
    }

    else if ( p->type() == typeid(ofParameter<double>).name() ) 
    {
      p->cast<double>() = m.getArgAsFloat(0);
      return true;
    }

    else if ( p->type() == typeid(ofParameter<string>).name() )
    {
      p->cast<string>() = m.getArgAsString(0);
      return true;
    }

    else if ( p->type() == typeid(ofParameter<ofVec2f>).name() )
    {
      p->cast<ofVec2f>().set( ofVec2f(m.getArgAsFloat(0), m.getArgAsFloat(1)) );
      return true;
    }

    else if ( p->type() == typeid(ofParameter<ofVec3f>).name() )
    {
      p->cast<ofVec3f>().set( ofVec3f(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2)) );
      return true;
    }

    else if ( p->type() == typeid(ofParameter<ofColor>).name() )
    {
      if (m.getNumArgs() == 3)
      {
        p->cast<ofColor>().set( ofColor(m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsInt32(2)) );
      }
      else
      {
        p->cast<ofColor>().set( ofColor(m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsInt32(2), m.getArgAsInt32(3)) );
      }

      return true;
    }

    else if ( p->type() == typeid(ofParameter<ofFloatColor>).name() )
    {
      if (m.getNumArgs() == 3)
      {
        p->cast<ofFloatColor>().set( ofFloatColor(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2)) );
      }
      else
      {
        p->cast<ofFloatColor>().set( ofFloatColor(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3)) );
      }

      return true;
    }

    return false;
	}

protected:
	
	void set(const string& key, ofxOscMessage &m)
	{
		ofxOscMessageRef ref(new ofxOscMessage(m));
		keyValue[key].msgs.push_back(ref);
	}

	void onUpdate(ofEventArgs&)
	{
		{
			std::unordered_map<string, MessageList>::iterator it = keyValue.begin();
			while (it != keyValue.end())
			{
				if (keyValue[(*it).first].itor != (*it).second.msgs.begin())
				{
					ofLogWarning("ofxKeyValueOSC") << "iterator error detected: " << (*it).first;
				}
				
				it++;
			}
		}
		
		clear();
		
		ofxOscMessage m;
		while (receiver.hasWaitingMessages())
		{
			receiver.getNextMessage(m);
			
			const string& addr = m.getAddress();
			set(addr, m);
		}
		
		{
			std::unordered_map<string, MessageList>::iterator it = keyValue.begin();
			while (it != keyValue.end())
			{
				keyValue[(*it).first].itor = (*it).second.msgs.begin();
				it++;
			}
		}
	}

};

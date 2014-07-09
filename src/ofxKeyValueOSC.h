#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

#include <tr1/unordered_map>
#include <tr1/memory>
#include <queue>

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
	typedef std::tr1::shared_ptr<ofxOscMessage> ofxOscMessageRef;
	typedef std::deque<ofxOscMessageRef> MessageList;
	std::tr1::unordered_map<string, MessageList> keyValue;
	std::tr1::unordered_map<string, MessageList::iterator> keyValueIter;

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
		keyValueIter.clear();
	}

	bool get(const string& key, ofxOscMessage &m)
	{
		MessageList &l = keyValue[key];
		if (l.empty()) return false;
		
		MessageList::iterator &it = keyValueIter[key];
		
		if (it == l.end())
		{
			it = l.begin();
			return false;
		}
		
		ofxOscMessageRef ref = *it;
		if (!ref) return false;

		m = *ref;
		it++;
		
		return true;
	}
	
	void remove(const string& key)
	{
		keyValue.erase(key);
		keyValueIter.erase(key);
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
	
	bool get(const string& key, float &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value = m.getArgAsFloat(0);
		
		return true;
	}
	
	bool get(const string& key, double &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value = m.getArgAsFloat(0);
		
		return true;
	}
	
	bool get(const string& key, int &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value = m.getArgAsInt32(0);
		
		return true;
	}
	
	bool get(const string& key, bool &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value = m.getArgAsInt32(0);
		
		return true;
	}
	
	bool get(const string& key, string &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value = m.getArgAsString(0);
		
		return true;
	}
	
	bool get(const string& key, ofVec3f &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value.x = m.getArgAsFloat(0);
		value.y = m.getArgAsFloat(1);
		value.z = m.getArgAsFloat(2);
		
		return true;
	}
	
	bool get(const string& key, ofColor &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value.r = m.getArgAsInt32(0);
		value.g = m.getArgAsInt32(1);
		value.b = m.getArgAsInt32(2);
		
		if (m.getNumArgs() == 4)
		{
			value.a = m.getArgAsInt32(3);
		}
		
		return true;
	}
	
	bool get(const string& key, ofFloatColor &value)
	{
		ofxOscMessage m;
		if (!get(key, m)) return false;
		
		value.r = m.getArgAsFloat(0);
		value.g = m.getArgAsFloat(1);
		value.b = m.getArgAsFloat(2);
		
		if (m.getNumArgs() == 4)
		{
			value.a = m.getArgAsFloat(3);
		}
		
		return true;
	}
	
protected:
	
	void set(const string& key, ofxOscMessage &m)
	{
		ofxOscMessageRef ref = ofxOscMessageRef(new ofxOscMessage(m));
		keyValue[key].push_back(ref);
	}

	void onUpdate(ofEventArgs&)
	{
		clear();
		
		while (receiver.hasWaitingMessages())
		{
			ofxOscMessage m;
			receiver.getNextMessage(&m);
			
			string addr = m.getAddress();
			set(addr, m);
		}
		
		std::tr1::unordered_map<string, MessageList>::iterator it = keyValue.begin();
		while (it != keyValue.end())
		{
			keyValueIter[(*it).first]= (*it).second.begin();
			it++;
		}
	}

};

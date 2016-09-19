
#ifndef incl__rainbow
#define incl__rainbow




#include <cassert>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <utility>

using namespace std;




class RainbowKey
{
public:
    unsigned char k[3];
public:
    RainbowKey();
	RainbowKey(RainbowKey const& cpy);
    RainbowKey(unsigned char const* const key);
public:
	virtual bool operator<(RainbowKey const& o) const;
    virtual bool operator==(RainbowKey const& o) const;
    virtual RainbowKey& operator=(RainbowKey const& o);
};

class RainbowValue
{
public:
    unsigned int v[5];
public:
    RainbowValue();
	RainbowValue(RainbowValue const& cpy);
    RainbowValue(unsigned int const* const val);
public:
    virtual bool operator==(RainbowValue const& o) const;
    virtual RainbowValue& operator=(RainbowValue const& o);
};


class RainbowTable
{
public:
	vector<pair<RainbowKey, RainbowValue>> rainbow_list;
    //map<RainbowKey, RainbowValue> rainbow_map;
public:
    RainbowTable();
    virtual ~RainbowTable();
public:
    virtual void read(string filename);
    virtual void write(string filename);
};




#endif


#ifndef incl__rainbow
#define incl__rainbow




#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <functional>

using namespace std;




class RainbowKey
{
    unsigned char[3] k;
public:
    RainbowKey();
    RainbowKey(const char const* key);
public:
    bool operator==(RainbowKey const& o);
    RainbowKey& operator=(RainbowKey const& o);
};

class RainbowValue
{
    unsigned int[5] v;
public:
    RainbowValue();
    RainbowValue(const int const* val);
public:
    bool operator==(RainbowKey const& o);
    RainbowValue& operator=(RainbowValue const& o);
};


class RainbowTableBlock
{
    unordered_map<RainbowKey, RainbowValue> rainbow_map;
    function<RainbowValue, RainbowKey> reduce_func;
public:
    RainbowTableBlock();
    virtual ~RainbowTableBlock();
public:
    void read(string filename);
    void write(string filename);
};




#endif

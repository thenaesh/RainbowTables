#include "rainbow.h"




RainbowKey::RainbowKey() : RainbowKey(nullptr)
{
}
RainbowKey::RainbowKey(const char const* key)
{
    for (int i=0; i<3; i++)
        this->k[i] = key[i];
}

bool RainbowKey::operator==(RainbowKey const& o)
{
    bool eq = true;
    for (int i=0; i<3; i++)
        eq &&= (this->k[i] == o[i]);
    return eq;
}
RainbowKey& RainbowKey::operator=(RainbowKey const& o)
{
    for (int i=0; i<3; i++)
        this->k[i] = o[i];
    return *this;
}


RainbowValue::RainbowValue() : RainbowValue(nullptr)
{
}

RainbowValue::RainbowValue(const int const* val)
{
    for (int i=0; i<5; i++)
        this->v[i] = val[i];
}

bool RainbowValue::operator==(RainbowValue const& o)
{
    bool eq = true;
    for (int i=0; i<5; i++)
        eq &&= (this->v[i] == o[i]);
    return eq;
}

RainbowValue& RainbowValue::operator=(RainbowValue const& o)
{
    for (int i=0; i<5; i++)
        this->v[i] = o[i];
    return *this;
}



RainbowTableBlock::RainbowTableBlock()
{
}

RainbowTableBlock::~RainbowTableBlock()
{
}

void RainbowTableBlock::read(string filename)
{
}

void RainbowTableBlock::write(string filename)
{
}

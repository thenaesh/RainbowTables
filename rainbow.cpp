#include "rainbow.hpp"
#include "sha1/sha1.h"




RainbowKey::RainbowKey()
{
}
RainbowKey::RainbowKey(RainbowKey const& cpy)
{
	for (int i=0; i<3; i++)
		this->k[i] = cpy.k[i];
}
RainbowKey::RainbowKey(unsigned char const* const key)
{
    for (int i=0; i<3; i++)
        this->k[i] = key[i];
}

bool RainbowKey::operator<(RainbowKey const& o) const
{
	for (int i=0; i<3; i++)
		if (this->k[i] < o.k[i])
			return true;
	return false;
}
bool RainbowKey::operator==(RainbowKey const& o) const
{
    bool eq = true;
    for (int i=0; i<3; i++)
        eq = eq && (this->k[i] == o.k[i]);
    return eq;
}
RainbowKey& RainbowKey::operator=(RainbowKey const& o)
{
    for (int i=0; i<3; i++)
        this->k[i] = o.k[i];
    return *this;
}

RainbowValue RainbowKey::hash()
{
	unsigned int hashed[5];
	SHA1 sha;
	sha.Reset();
	sha.Input(this->k[0]); sha.Input(this->k[1]); sha.Input(this->k[2]);
	sha.Result(hashed);
	// TODO: increment global SHA1 use count
	
	RainbowValue result(hashed);
	return result;
}


RainbowValue::RainbowValue()
{
	for (int i=0; i<5; i++)
		this->v[i] = 6;
}
RainbowValue::RainbowValue(RainbowValue const& cpy)
{
	for (int i=0; i<5; i++)
		this->v[i] = cpy.v[i];
}
RainbowValue::RainbowValue(unsigned int const* const val)
{
    for (int i=0; i<5; i++)
        this->v[i] = val[i];
}

bool RainbowValue::operator==(RainbowValue const& o) const
{
    bool eq = true;
    for (int i=0; i<5; i++)
        eq = eq && (this->v[i] == o.v[i]);
    return eq;
}
RainbowValue& RainbowValue::operator=(RainbowValue const& o)
{
    for (int i=0; i<5; i++)
        this->v[i] = o.v[i];
    return *this;
}



RainbowTable::RainbowTable()
{
}

RainbowTable::~RainbowTable()
{
}

void RainbowTable::read(string filename)
{
	FILE* file_handle = nullptr;
	file_handle = fopen(filename.c_str(), "r");

	while (!feof(file_handle)) {
		RainbowKey   k;
		RainbowValue v;

		int r = fscanf(file_handle, "%c %c %c %u %u %u %u %u\n",
							k.k,
							k.k+1,
							k.k+2,
							v.v,
							v.v+1,
							v.v+2,
							v.v+3,
							v.v+4);
		if (r < 8) break;
		this->rainbow_list.push_back(make_pair(k, v));
	}

	fclose(file_handle);
}

void RainbowTable::write(string filename)
{
	FILE* file_handle = nullptr;
	file_handle = fopen(filename.c_str(), "w");

	for (auto const& entry : this->rainbow_list) {
		RainbowKey   k; k = entry.first.k;
		RainbowValue v; v = entry.second.v;

		fprintf(file_handle, "%c %c %c %u %u %u %u %u\n",
							k.k[0],
							k.k[1],
							k.k[2],
							v.v[0],
							v.v[1],
							v.v[2],
							v.v[3],
							v.v[4]);
	}

	fflush(file_handle);
	fclose(file_handle);
}



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
#include <tuple>

using namespace std;

// FORWARD DECLARATIONS
class RainbowKey;
class RainbowValue;




class RainbowKey
{
public:
    unsigned char k[3];	// 3 bytes

    RainbowKey();
	RainbowKey(RainbowKey const& cpy);
    RainbowKey(unsigned char const* const key);

    virtual bool operator==(RainbowKey const& o) const;
    virtual bool operator!=(RainbowKey const& o) const;
    virtual RainbowKey& operator=(RainbowKey const& o);

	virtual RainbowValue hash();

	virtual void dbgPrint();
	virtual void dbgPrintln();
};

class RainbowValue
{
public:
    unsigned int v[5];	// 20 bytes

    RainbowValue();
	RainbowValue(RainbowValue const& cpy);
    RainbowValue(unsigned int const* const val);

    virtual bool operator==(RainbowValue const& o) const;
    virtual bool operator!=(RainbowValue const& o) const;
    virtual RainbowValue& operator=(RainbowValue const& o);

    virtual RainbowKey reduce(unsigned int c0,
	                          unsigned int c1,
							  unsigned int c2);
	virtual RainbowKey reduce(tuple<int, int, int> cs);

	virtual void dbgPrint();
	virtual void dbgPrintln();
};


class RainbowTable
{
public:
	vector<pair<RainbowKey, RainbowValue>> rainbow_list;
	const vector<tuple<int, int, int>> reduce_seq;

	RainbowTable(vector<tuple<int, int, int>> reduce_seq_);
    virtual ~RainbowTable();

    virtual void read(string filename);
    virtual void write(string filename);

	/*
	 * takes a starting key, k0
	 * assuming this->reduce_seq = r0,r1,...,r(k-1) and
	 * for all i: ki -> vi = h(ki) -> k(i+1) = ri(vi)
	 * return (k0, vk)
	 */
	virtual pair<RainbowKey, RainbowValue> computeChain(RainbowKey k0);
	/*
	 * takes in a list of start points, words
	 * populates rainbow_list using reduce_seq
	 */
	void buildTable(vector<RainbowKey> const& words);
	/*
	 * takes a hashed value, v
	 * checks if v is one of the terminating hashes
	 * returns true and the corresponding starting key if so
	 * returns false and some random key otherwise
	 */
	virtual pair<bool, RainbowKey> getChainStart(RainbowValue v);
	/*
	 * takes a hash, v
	 * takes a starting key, start
	 * traverses the hash chain to find the key that hashes to v
	 * returns that key
	 * ASSUMPTION: such a key exists
	 */
	virtual RainbowKey getInverseInChain(RainbowValue v, RainbowKey start);
	/*
	 * takes a hash, v
	 * finds a chain to start from and traverses the chain
	 * to find the key that hashes to v
	 * returns true and the key if found
	 * returns false and a random key otherwise (FAILURE)
	 * 
	 * THIS IS THE WHOLE POINT OF THE RAINBOW TABLE
	 */
	virtual pair<bool, RainbowKey> getInverse(RainbowValue v);
};




#endif


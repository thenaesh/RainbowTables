
#ifndef incl__rainbow
#define incl__rainbow




#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <utility>
#include <tuple>
#include <stdexcept>

using namespace std;

// FORWARD DECLARATIONS
class RainbowKey;
class RainbowValue;




/*
 * class representing a 3-byte message
 * size: 3 bytes
 */
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
	static unsigned int hashcounter;

	virtual void dbgPrint() const;
	virtual void dbgPrintln() const;
};

/*
 * class representing a 20-byte SHA1 hash of a 3-byte message
 * size: 20 bytes
 */
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

	virtual void dbgPrint() const;
	virtual void dbgPrintln() const;
};


namespace std
{
	template<>
	class hash<RainbowValue>
	{
	public:
		/*
		 * implementation of FNV
		 * so that RainbowValue can be used in unordered_list
		 */
		size_t operator()(RainbowValue const& val) const
		{
			size_t h = 2166136261;
			for (int i=0; i<20; i++) {
				unsigned char oct = ((unsigned char*) val.v)[i];
				h = h ^ oct;
				h = h * 16777619;
			}
			return h;
		}
	};

	template<>
	class less<RainbowValue>
	{
	public:
		bool operator()(RainbowValue const& a, RainbowValue const& b) const
		{
			for (int i=0; i<5; i++) {
				if		(a.v[i] < b.v[i]) return true;
				else if	(a.v[i] > b.v[i]) return false;
			}

			// they are equal if we reach this point
			return false;
		}
	};
}


class RainbowTable
{
public:
	unordered_map<RainbowValue, RainbowKey> rainbow_map;
	vector<tuple<RainbowKey, RainbowKey, RainbowValue>> rainbow_list;
	vector<unsigned char> collisions;
	vector<RainbowKey> autogen_words;
	vector<tuple<int, int, int>> reduce_seq;

	RainbowTable(vector<tuple<int, int, int>> const& reduce_seq);
	RainbowTable();
    virtual ~RainbowTable();

    virtual void read(string filename);
	virtual void read(string filename, string collisionfilename);
	virtual void write(string filename, string collisionfilename);
	virtual void write(string filename);

	/*
	 * takes a starting key, k0
	 * assuming this->reduce_seq = r0,r1,...,r(k-1) and
	 * for all i: ki -> vi = h(ki) -> k(i+1) = ri(vi)
	 * return (k0, vk)
	 */
	virtual pair<RainbowKey, RainbowValue>
			computeChain(RainbowKey k0) const;
	/*
	 * same thing as above, but also yields the penultimate key
	 * after the last reduce, before hashing to the final value
	 */
	virtual tuple<RainbowKey, RainbowKey, RainbowValue>
			computeChainPenultimate(RainbowKey k0) const;
	/*
	 * either takes in a list of start points, words
	 * or takes in nothing and builds the words according to a rule
	 * populates rainbow_list using reduce_seq
	 */
	virtual void buildTable(vector<RainbowKey> const& words);
	virtual void buildTable();

	virtual void generateWords();

	/*
	 * takes a hashed value, v
	 * checks if v is one of the terminating hashes
	 * returns true and the corresponding starting key if so
	 * returns false and some random key otherwise
	 */
	virtual pair<bool, RainbowKey>
			getChainStart(RainbowValue v) const;
	/*
	 * takes a hash, v
	 * takes a starting key, start
	 * traverses the hash chain to find the key that hashes to v
	 * returns that key
	 * ASSUMPTION: such a key exists
	 */
	virtual pair<bool, RainbowKey>
			getInverseInChain(RainbowValue v, RainbowKey start) const;
	/*
	 * takes a hash, v
	 * finds a chain to start from and traverses the chain
	 * to find the key that hashes to v
	 * returns true and the key if found
	 * returns false and a random key otherwise (FAILURE)
	 * 
	 * THIS IS THE WHOLE POINT OF THE RAINBOW TABLE
	 */
	virtual pair<bool, RainbowKey>
			getInverse(RainbowValue v) const;
};




#endif


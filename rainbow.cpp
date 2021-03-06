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

bool RainbowKey::operator==(RainbowKey const& o) const
{
    bool eq = true;
    for (int i=0; i<3; i++)
        eq = eq && (this->k[i] == o.k[i]);
    return eq;
}
bool RainbowKey::operator!=(RainbowKey const& o) const
{
    return !((*this) == o);
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

	//increment global SHA1 use count
	hashcounter += 1;
	
	RainbowValue result(hashed);
	return result;
}
unsigned int RainbowKey::hashcounter = 0;

void RainbowKey::dbgPrint() const
{
	for (int i=0; i<3; i++) printf("%c", this->k[i]);
}
void RainbowKey::dbgPrintln() const
{
	this->dbgPrint();
	printf("\n");
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
bool RainbowValue::operator!=(RainbowValue const& o) const
{
    return !((*this) == o);
}
RainbowValue& RainbowValue::operator=(RainbowValue const& o)
{
    for (int i=0; i<5; i++)
        this->v[i] = o.v[i];
    return *this;
}

RainbowKey RainbowValue::reduce(unsigned int c0, unsigned int c1, unsigned int c2)
{
    unsigned char reduced[3];

	reduced[0] = (unsigned char)((this->v[0] + c0) % 256);
	reduced[1] = (unsigned char)((this->v[1] + c1) % 256);
	reduced[2] = (unsigned char)((this->v[2] + c2) % 256);

    RainbowKey result(reduced);
    return result;
}
RainbowKey RainbowValue::reduce(tuple<int, int, int> cs)
{
	return this->reduce(get<0>(cs), get<1>(cs), get<2>(cs));
}

void RainbowValue::dbgPrint() const
{
	for (int i=0; i<5; i++) printf("%u ", this->v[i]);
}
void RainbowValue::dbgPrintln() const
{
	this->dbgPrint();
	printf("\n");
}



RainbowTable::RainbowTable(vector<tuple<int, int, int>> const& reduce_seq)
{
	this->reduce_seq = reduce_seq;
}
RainbowTable::RainbowTable()
{
	for (int a = 0; a < 56; a++)
		this->reduce_seq.push_back(make_tuple(a, 0, 0));
}
RainbowTable::~RainbowTable()
{
}

void RainbowTable::read(string filename)
{
	FILE* file_handle = nullptr;
	file_handle = fopen(filename.c_str(), "r");

	while (!feof(file_handle)) {
		RainbowKey		ki;
		RainbowKey		kf;

		int r = fscanf(file_handle, "%c%c%c%c%c%c",
							ki.k,
							ki.k+1,
							ki.k+2,
							kf.k,
							kf.k+1,
							kf.k+2);
		if (r < 6) break;
		this->rainbow_list.push_back(make_tuple(ki, kf, kf.hash()));
	}

	fclose(file_handle);

	for (auto const& entry : this->rainbow_list)
		this->rainbow_map[get<2>(entry)] = get<0>(entry);
}
void RainbowTable::read(string filename, string collisionfilename)
{
	FILE* file_handle		= fopen(filename.c_str(), "r");
	FILE* collision_handle	= fopen(collisionfilename.c_str(), "r");

	this->generateWords();
	long wordcount = 0;

	while (!(feof(file_handle) || feof(collision_handle))) {
		RainbowKey		ki;
		RainbowKey		kf;
		unsigned char	skip;
		
		// number of characters read in each scanf call
		int r = fscanf(file_handle, "%c%c%c", kf.k, kf.k+1, kf.k+2);
		int rp = fscanf(collision_handle, "%c", &skip);

		// checking for malformed input files
		if (r < 3 || rp != 1) break;

		wordcount += skip;
		ki = this->autogen_words[wordcount++];

		this->rainbow_list.push_back(make_tuple(ki, kf, kf.hash()));
		this->collisions.push_back(skip);
	}

	fclose(collision_handle);
	fclose(file_handle);

	for (auto const& entry : this->rainbow_list)
		this->rainbow_map[get<2>(entry)] = get<0>(entry);
}
void RainbowTable::write(string filename, string collisionfilename)
{
	FILE* file_handle		= fopen(filename.c_str(), "w");
	FILE* collision_handle	= fopen(collisionfilename.c_str(), "w");

	for (int it = 0; it < this->rainbow_list.size(); it++) {
		auto const& entry	= this->rainbow_list[it];
		unsigned char skip	= this->collisions[it];

		RainbowKey kf = get<1>(entry);

		fprintf(file_handle, "%c%c%c", kf.k[0], kf.k[1], kf.k[2]);
		fprintf(collision_handle, "%c", skip);
	}

	fflush(collision_handle);	fflush(file_handle);
	fclose(collision_handle);	fclose(file_handle);
}
void RainbowTable::write(string filename)
{
	FILE* file_handle = nullptr;
	file_handle = fopen(filename.c_str(), "w");

	for (auto const& entry : this->rainbow_list) {
		RainbowKey ki = get<0>(entry);
		RainbowKey kf = get<1>(entry);

		fprintf(file_handle, "%c%c%c%c%c%c",
							ki.k[0],
							ki.k[1],
							ki.k[2],
							kf.k[0],
							kf.k[1],
							kf.k[2]);
	}

	fflush(file_handle);
	fclose(file_handle);
}

pair<RainbowKey, RainbowValue> RainbowTable::computeChain(RainbowKey k0) const
{
	RainbowKey currkey = k0;
	RainbowValue currval;

	for (unsigned int i = 0; i < this->reduce_seq.size(); i++) {
		currval = currkey.hash();
		currkey = currval.reduce(this->reduce_seq[i]);
	}
	currval = currkey.hash();

	return make_pair(k0, currval);
}
tuple<RainbowKey, RainbowKey, RainbowValue> RainbowTable::computeChainPenultimate(RainbowKey k0) const
{
	RainbowKey currkey = k0;
	RainbowValue currval;

	for (unsigned int i = 0; i < this->reduce_seq.size(); i++) {
		currval = currkey.hash();
		currkey = currval.reduce(this->reduce_seq[i]);
	}
	currval = currkey.hash();

	return make_tuple(k0, currkey, currval);
}
void RainbowTable::buildTable(vector<RainbowKey> const& words)
{
	unsigned char collision_streak = 0;
	unsigned char max_collision = 0;

	for (RainbowKey word : words) {
		auto chain = this->computeChainPenultimate(word);
		auto currently_exists = this->getChainStart(get<2>(chain)).first;


		if (!currently_exists) {
			this->rainbow_list.push_back(chain);			// if we do this
			this->rainbow_map[get<2>(chain)] = get<0>(chain);

			this->collisions.push_back(collision_streak);	// we also do this
			collision_streak = 0;
		}
		else collision_streak++;
	}

	assert(this->rainbow_list.size() == this->collisions.size());
}
void RainbowTable::buildTable()
{
	this->generateWords();
	this->buildTable(this->autogen_words);
}

void RainbowTable::generateWords()
{
	for (unsigned short c1 = 0; c1 < 256; c1 += 2) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 4) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 8) {
				RainbowKey word;

				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				this->autogen_words.push_back(word);
			}
		}
	}
}

pair<bool, RainbowKey> RainbowTable::getChainStart(RainbowValue v) const
{
	pair<bool, RainbowKey> retval;

	try {
		RainbowKey chainstart = this->rainbow_map.at(v);
		retval = make_pair(true, chainstart);
	} catch (out_of_range e) {
		RainbowKey fake_key;
		retval = make_pair(false, fake_key);
	}

	return retval;
}
pair<bool, RainbowKey> RainbowTable::getInverseInChain(RainbowValue v, RainbowKey start) const
{
	RainbowKey   key = start;
	RainbowValue val = start.hash();

	for (int i = 0; i < this->reduce_seq.size(); i++) {
		if (val == v) return make_pair(true, key);

		key = val.reduce(this->reduce_seq[i]);
		val = key.hash();
	}

	if (val != v)	return make_pair(false, key);
	else			return make_pair(true,  key);
}
pair<bool, RainbowKey> RainbowTable::getInverse(RainbowValue v) const
{
	int K = this->reduce_seq.size();

	for (int i=K; i>=0; i--) {
		RainbowValue hash_to_check = v;

		for (int j = i; j<K; j++) {
			hash_to_check = hash_to_check.reduce(this->reduce_seq[j]).hash();
		}

		auto chain_to_start_traversing = this->getChainStart(hash_to_check);
		if (chain_to_start_traversing.first) {
			// we have found a guaranteed starting point
			auto inv = this->getInverseInChain(v, chain_to_start_traversing.second);
			if (inv.first) return make_pair(true, inv.second);
		}
	}
	// if we reach this point, FAIL
	RainbowKey fake_key;
	return make_pair(false, fake_key);
}


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
	// TODO: increment global SHA1 use count
	
	RainbowValue result(hashed);
	return result;
}

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

void RainbowTable::populateRainbowHashmap()
{
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
void RainbowTable::buildTable(vector<RainbowKey> const& words)
{
	for (RainbowKey word : words)
		this->rainbow_list.push_back(this->computeChain(word));
}
void RainbowTable::buildTable()
{
	RainbowKey word;

	for (unsigned short c1 = 0; c1 < 256; c1 += 5) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 7) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 11) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				auto chain = this->computeChain(word);
				auto currently_exists = this->getChainStart(chain.second).first;

				if (!currently_exists)
					this->rainbow_list.push_back(chain);

				printf("%s %u %u %u\n", currently_exists ? "not added" : "added",
						static_cast<unsigned char>(c1),
						static_cast<unsigned char>(c2),
						static_cast<unsigned char>(c3));
			}
		}
	}
}

pair<bool, RainbowKey> RainbowTable::getChainStart(RainbowValue v) const
{
	for (auto const& p : this->rainbow_list) {
		if (p.second == v) return make_pair(true, p.first);
	}

	// not found, if we reach this point
	
	RainbowKey fake_key;
	return make_pair(false, fake_key);
}
pair<bool, RainbowKey> RainbowTable::getInverseInChain(RainbowValue v, RainbowKey start) const
{
	RainbowKey   key = start;
	RainbowValue val = start.hash();

	for (int i = 0; i < this->reduce_seq.size(); i++) {
		//printf("Current val before R%d: ", i); val.dbgPrintln();
		if (val == v) return make_pair(true, key);

		key = val.reduce(this->reduce_seq[i]);
		val = key.hash();
	}

	//printf("val = "); val.dbgPrintln();

	if (val != v)	return make_pair(false, key);
	else			return make_pair(true,  key);
}
pair<bool, RainbowKey> RainbowTable::getInverse(RainbowValue v) const
{
	int K = this->reduce_seq.size();

	for (int i=K; i>=0; i--) {
		RainbowValue hash_to_check = v;

		//printf("i = %d\n", i);
		for (int j = i; j<K; j++) {
			//printf("%d ", j);
			hash_to_check = hash_to_check.reduce(this->reduce_seq[j]).hash();
		}
		//printf("\n");

		auto chain_to_start_traversing = this->getChainStart(hash_to_check);
		if (chain_to_start_traversing.first) {
			// we have found a guaranteed starting point
			//printf("start traversing, K = %d, i = %d\n", K, i);
			//printf("Hash to find: "); v.dbgPrintln();
			//printf("Hash to check: "); hash_to_check.dbgPrintln();
			//printf("Key to start from: "); chain_to_start_traversing.second.dbgPrintln();
			auto inv = this->getInverseInChain(v, chain_to_start_traversing.second);
			if (inv.first) return make_pair(true, inv.second);
		}
	}
	// if we reach this point, FAIL
	RainbowKey fake_key;
	return make_pair(false, fake_key);
}


#include "rainbow.hpp"

/*
 * UTILITY FUNCTIONS
 */

void createReduceSequence1(vector<tuple<int, int, int>>& reduce_seq);
void createReduceSequence2(vector<tuple<int, int, int>>& reduce_seq);

void fetchDigests(vector<RainbowValue>& digests);
void printKeyInHex(RainbowKey const& key);


///////////////////////////////////////////////////////////////////////////////


int main()
{
	vector<tuple<int, int, int>> reduce_seq1; createReduceSequence1(reduce_seq1);
	vector<tuple<int, int, int>> reduce_seq2; createReduceSequence2(reduce_seq2);

	RainbowTable tbl1(reduce_seq1);
	RainbowTable tbl2(reduce_seq2);

#ifdef GENERATE
	tbl1.buildTable(); tbl1.write("RAINBOW1", "COLLISION1");
	tbl2.buildTable(); tbl2.write("RAINBOW2", "COLLISION2");
#else
	tbl1.read("RAINBOW1", "COLLISION1");
	tbl2.read("RAINBOW2", "COLLISION2");
#endif

	vector<RainbowTable*> tbls = {&tbl1, &tbl2};


	vector<RainbowValue> digests; fetchDigests(digests);

	RainbowKey::hashcounter = 0;

	int attempts = 0;
	int successes = 0;

	for (int i = 0; i < 5000; i++) {
		RainbowValue val = digests[i];
		pair<bool, RainbowKey> inv;

		for (RainbowTable* tbl : tbls) {
			inv = tbl->getInverse(val);
			if (inv.first) break;
		}

		if (inv.first) {
			attempts++; successes++;
			assert(inv.second.hash() == val);
			printKeyInHex(inv.second);
		} else {
			attempts++;
			printf("0\n");
		}
	}

	//printf("t: %u\n", RainbowKey::hashcounter);
	//printf("C: %f\n", 100 * ((float) successes / (float) attempts));
	//printf("F: %lu\n", (1L<<23) * 5000 / RainbowKey::hashcounter);

	printf("The total number of words found is: %d\n", successes);

	return 0;
}


///////////////////////////////////////////////////////////////////////////////


void fetchDigests(vector<RainbowValue>& digests)
{
	for (int i=0; i<5000; i++) {
		RainbowValue val;

		for (int j=0; j<5; j++)
			scanf("%X", val.v+j);

		digests.push_back(val);
	}
}
void printKeyInHex(RainbowKey const& key)
{
	printf("%X%X%X%X%X%X\n",
			(unsigned int)key.k[0]/16, (unsigned int)key.k[0]%8,
			(unsigned int)key.k[1]/16, (unsigned int)key.k[1]%8,
			(unsigned int)key.k[2]/16, (unsigned int)key.k[2]%8);
}

void createReduceSequence1(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int a = 0; a < 145; a++)
		reduce_seq.push_back(make_tuple(a, 0, 0));
}
void createReduceSequence2(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int b = 0; b < 200; b++)
		reduce_seq.push_back(make_tuple(0, b, 0));
}

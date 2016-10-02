#include "rainbow.hpp"


void createReduceSequence1(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int a = 0; a < 180; a++)
		reduce_seq.push_back(make_tuple(a, 0, 0));
}
void createReduceSequence2(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int b = 0; b < 180; b++)
		reduce_seq.push_back(make_tuple(0, b, 0));
}


int main()
{
	vector<tuple<int, int, int>> reduce_seq1;
	vector<tuple<int, int, int>> reduce_seq2;
	createReduceSequence1(reduce_seq1);
	createReduceSequence2(reduce_seq2);

	RainbowTable tbl1(reduce_seq1);
	RainbowTable tbl2(reduce_seq2);

	bool build = true;
	if (build) {
		tbl1.buildTable(); tbl1.write("RAINBOW1");
		tbl2.buildTable(); tbl2.write("RAINBOW2");
	} else {
		tbl1.read("RAINBOW1");
		tbl2.read("RAINBOW2");
	}

	
	vector<RainbowTable*> tbls = {&tbl1, &tbl2};
	int T = 2;

	for (int i = 0; i < T; i++) {
		printf("Table %d Size: %u\n",				i+1, static_cast<unsigned int>(tbls[i]->rainbow_list.size()));
		printf("Reduce Sequence %d Length: %u\n",	i+1, static_cast<unsigned int>(tbls[i]->reduce_seq.size()  ));
	}

	RainbowKey::hashcounter = 0;
	printf("\nNumber of Hashes: %u\n", RainbowKey::hashcounter);

	int attempts = 0;
	int successes = 0;

	for (int i=0; i<500; i++) {
		attempts++;

		RainbowKey sample;
		for (int i=0; i<3; i++) sample.k[i] = rand() % 256;
		RainbowValue samplehash = sample.hash();

		pair<bool, RainbowKey> inv;
		for (int i = 0; i < T; i++) {
			inv = tbls[i]->getInverse(samplehash);
			if (inv.first && inv.second == sample) {
				successes++;
				break;
			}
		}
	}

	printf("\n");
	printf("attempts: %d\n", attempts);
	printf("successes: %d\n", successes);
	printf("\n");

	printf("Number of Hashes: %u\n\n", RainbowKey::hashcounter);
	printf("Speedup Factor: %lu\n", (1L<<23) * 500 / RainbowKey::hashcounter);

	return 0;
}

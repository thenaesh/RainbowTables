#include "rainbow.hpp"


void createReduceSequence1(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int a = 0; a < 256; a++)
		reduce_seq.push_back(make_tuple(a, 0, 0));
}
void createReduceSequence2(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int b = 0; b < 256; b++)
		reduce_seq.push_back(make_tuple(0, b, 0));
}
void createReduceSequence3(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int c = 0; c < 256; c++)
		reduce_seq.push_back(make_tuple(0, 0, c));
}
void createReduceSequence4(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int d = 0; d < 256; d++)
		reduce_seq.push_back(make_tuple(d, (d*d)%256, 1));
}
void createReduceSequence5(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int e = 0; e < 256; e++)
		reduce_seq.push_back(make_tuple(1, e, (e*e*e)%256));
}

int main()
{
	vector<tuple<int, int, int>> reduce_seq1;
	vector<tuple<int, int, int>> reduce_seq2;
	vector<tuple<int, int, int>> reduce_seq3;
	vector<tuple<int, int, int>> reduce_seq4;
	vector<tuple<int, int, int>> reduce_seq5;
	createReduceSequence1(reduce_seq1);
	createReduceSequence2(reduce_seq2);
	createReduceSequence3(reduce_seq3);
	createReduceSequence4(reduce_seq4);
	createReduceSequence5(reduce_seq5);

	RainbowTable tbl1(reduce_seq1);
	RainbowTable tbl2(reduce_seq2);
	RainbowTable tbl3(reduce_seq3);
	RainbowTable tbl4(reduce_seq4);
	RainbowTable tbl5(reduce_seq5);
	
	/*
	tbl1.buildTable(); tbl1.write("RAINBOW1");
	tbl2.buildTable(); tbl2.write("RAINBOW2");
	tbl3.buildTable(); tbl3.write("RAINBOW3");
	tbl4.buildTable(); tbl4.write("RAINBOW4");
	tbl5.buildTable(); tbl5.write("RAINBOW5");
	*/

	tbl1.read("RAINBOW1");
	tbl2.read("RAINBOW2");
	tbl3.read("RAINBOW3");
	tbl4.read("RAINBOW4");
	tbl5.read("RAINBOW5");
	
	vector<RainbowTable*> tbls = {&tbl1, &tbl2, &tbl3, &tbl4, &tbl5};

	for (int i = 0; i < 5; i++) {
		printf("Table %d Size: %u\n",				i+1, static_cast<unsigned int>(tbls[i]->rainbow_list.size()));
		printf("Reduce Sequence %d Length: %u\n",	i+1, static_cast<unsigned int>(tbls[i]->reduce_seq.size()  ));
	}

	RainbowKey::hashcounter = 0;
	printf("\nNumber of Hashes: %u\n", RainbowKey::hashcounter);

	int attempts = 0;
	int successes = 0;

	for (int i=0; i<5000; i++) {
		attempts++;

		RainbowKey sample;
		for (int i=0; i<3; i++) sample.k[i] = rand() % 256;
		RainbowValue samplehash = sample.hash();

		pair<bool, RainbowKey> inv;
		for (RainbowTable* tbl : tbls) {
			inv = tbl->getInverse(samplehash);
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

	return 0;
}

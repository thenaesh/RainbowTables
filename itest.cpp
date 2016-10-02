#include "rainbow.hpp"


void createReduceSequence1(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int a = 0; a < 220; a++)
		reduce_seq.push_back(make_tuple(a, 0, 0));
}
void createReduceSequence2(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int b = 0; b < 220; b++)
		reduce_seq.push_back(make_tuple(0, b, 0));
}
void createReduceSequence3(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int c = 0; c < 210; c++)
		reduce_seq.push_back(make_tuple(0, 0, c));
}
void createReduceSequence4(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int d = 0; d < 210; d++)
		reduce_seq.push_back(make_tuple(d, (d*d)%256, 1));
}
void createReduceSequence5(vector<tuple<int, int, int>>& reduce_seq)
{
	for (int e = 0; e < 210; e++)
		reduce_seq.push_back(make_tuple(1, e, (e*e*e)%256));
}

void generateWords(vector<RainbowKey>& words)
{
	RainbowKey word;
	for (unsigned short c1 = 0; c1 < 256; c1 += 5) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 7) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 9) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				words.push_back(word);
			}
		}
	}
}
void generateWords1(vector<RainbowKey>& words)
{
	RainbowKey word;
	for (unsigned short c1 = 0; c1 < 256; c1 += 2) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 4) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 8) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				words.push_back(word);
			}
		}
	}
}
void generateWords2(vector<RainbowKey>& words)
{
	RainbowKey word;
	for (unsigned short c1 = 1; c1 < 256; c1 += 2) {
		for (unsigned short c2 = 1; c2 < 256; c2 += 4) {
			for (unsigned short c3 = 1; c3 < 256; c3 += 8) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				words.push_back(word);
			}
		}
	}
}
void generateWords3(vector<RainbowKey>& words)
{
	RainbowKey word;
	for (unsigned short c1 = 0; c1 < 256; c1 += 7) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 3) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 7) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				words.push_back(word);
			}
		}
	}
}
void generateWords4(vector<RainbowKey>& words)
{
	RainbowKey word;
	for (unsigned short c1 = 0; c1 < 256; c1 += 7) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 3) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 7) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				words.push_back(word);
			}
		}
	}
}
void generateWords5(vector<RainbowKey>& words)
{
	RainbowKey word;
	for (unsigned short c1 = 0; c1 < 256; c1 += 3) {
		for (unsigned short c2 = 0; c2 < 256; c2 += 7) {
			for (unsigned short c3 = 0; c3 < 256; c3 += 7) {
				word.k[0] = static_cast<unsigned char>(c1);
				word.k[1] = static_cast<unsigned char>(c2);
				word.k[2] = static_cast<unsigned char>(c3);

				words.push_back(word);
			}
		}
	}
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

	vector<RainbowKey> words1;
	vector<RainbowKey> words2;
	vector<RainbowKey> words3;
	vector<RainbowKey> words4;
	vector<RainbowKey> words5;
	generateWords1(words1);
	generateWords2(words2);
	generateWords3(words3);
	generateWords4(words4);
	generateWords5(words5);

	RainbowTable tbl1(reduce_seq1);
	RainbowTable tbl2(reduce_seq2);
	RainbowTable tbl3(reduce_seq3);
	RainbowTable tbl4(reduce_seq4);

	bool build = true;
	if (build) {
		tbl1.buildTable(words1); tbl1.write("RAINBOW1");
		tbl2.buildTable(words2); tbl2.write("RAINBOW2");
		//tbl3.buildTable(words3); tbl3.write("RAINBOW3");
		//tbl4.buildTable(words3); tbl4.write("RAINBOW3");
	} else {
		tbl1.read("RAINBOW1");
		tbl2.read("RAINBOW2");
		//tbl3.read("RAINBOW3");
		//tbl4.read("RAINBOW4");
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

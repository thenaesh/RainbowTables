#include "rainbow.hpp"
#include "sha1/sha1.h"

void printRainbowSequence(vector<tuple<int, int, int>> const& seq)
{
	printf("RAINBOW SEQUENCE USED:\n");
	int i = 0;
	for (auto const& r : seq) {
		printf("r%d: %d %d %d\n", i++, get<0>(r), get<1>(r), get<2>(r));
	}
	printf("\n");
}

bool io_test()
{
	RainbowTable tbl0;

	unsigned char k1_[3];
	k1_[0] = 'l';
	k1_[1] = 'o';
	k1_[2] = 'l';
	RainbowKey k1(k1_);

	unsigned char k2_[3];
	k2_[0] = 'w';
	k2_[1] = 't';
	k2_[2] = 'f';
	RainbowKey k2(k2_);

	unsigned char k3_[3];
	k3_[0] = 'c';
	k3_[1] = 'c';
	k3_[2] = 'b';
	RainbowKey k3(k3_);

	unsigned char k4_[3];
	k4_[0] = 'o';
	k4_[1] = 'm';
	k4_[2] = 'g';
	RainbowKey k4(k4_);

	unsigned char k5_[3];
	k5_[0] = 'b';
	k5_[1] = 'b';
	k5_[2] = 'q';
	RainbowKey k5(k5_);

	vector<RainbowKey> words = {k1, k2, k3, k4, k5};
	tbl0.buildTable(words);

	tbl0.write("RAINBOW");


	RainbowTable tbl1;

	tbl1.read("RAINBOW");
	
	if (tbl0.rainbow_list != tbl1.rainbow_list) return false;

	auto p1 = tbl1.rainbow_list.at(0);
	auto p2 = tbl1.rainbow_list.at(1);
	auto p3 = tbl1.rainbow_list.at(2);
	auto p4 = tbl1.rainbow_list.at(3);
	auto p5 = tbl1.rainbow_list.at(4);
	get<0>(p1).dbgPrint(); printf(" | "); get<1>(p1).dbgPrint(); printf("\t| "); get<2>(p1).dbgPrint(); printf("\n");
	get<0>(p2).dbgPrint(); printf(" | "); get<1>(p2).dbgPrint(); printf("\t| "); get<2>(p2).dbgPrint(); printf("\n");
	get<0>(p3).dbgPrint(); printf(" | "); get<1>(p3).dbgPrint(); printf("\t| "); get<2>(p3).dbgPrint(); printf("\n");
	get<0>(p4).dbgPrint(); printf(" | "); get<1>(p4).dbgPrint(); printf("\t| "); get<2>(p4).dbgPrint(); printf("\n");
	get<0>(p5).dbgPrint(); printf(" | "); get<1>(p5).dbgPrint(); printf("\t| "); get<2>(p5).dbgPrint(); printf("\n");

    return true;
}

/*
bool hash_test()
{
	unsigned char testkey[3];
	unsigned int testhash[5];

	testkey[0] = 'o';
	testkey[1] = 'm';
	testkey[2] = 'g';

	SHA1 sha;
	sha.Reset();
	sha.Input(testkey[0]); sha.Input(testkey[1]); sha.Input(testkey[2]);
	sha.Result(testhash);

	RainbowKey testkeywrapper(testkey);
	RainbowValue testhashwrapper(testhash);

    printf("HASH TEST BEGIN\n");
	printf("hypothesis\n");
	testkeywrapper.dbgPrint(); printf(" | "); testhashwrapper.dbgPrint(); printf("\n");
	printf("result\n"); testkeywrapper.dbgPrint(); printf(" | "); testkeywrapper.hash().dbgPrint(); printf("\n");
    printf("HASH TEST END\n");

	if (testhashwrapper != testkeywrapper.hash()) return false;

    return true;
}

bool reduce_test()
{
    RainbowValue testval;

    // all fit in the first byte on a little-endian system
    testval.v[0] = 182; // byte 0   = 182
    testval.v[1] = 255; // byte 4   = 255
    testval.v[2] = 69;  // byte 8   = 69
    testval.v[3] = 42;  // byte 12  = 42
    testval.v[4] = 32;  // byte 16  = 32

    RainbowKey testkey;
    
    testkey.k[0] = (unsigned char) 255;
    testkey.k[1] = (unsigned char) 69;
    testkey.k[2] = (unsigned char) 32;

    printf("REDUCE TEST BEGIN\n");
    printf("hypothesis: "); testkey.dbgPrintln();
    printf("result: ");     testval.reduce(4,8,16).dbgPrintln();
    printf("REDUCE TEST END\n");

    if (testkey != testval.reduce(4,8,16)) return false; // 4 8 16

    return true;
}

bool chain_start_test()
{
	RainbowTable tbl;

	unsigned char k1_[3];
	k1_[0] = 'l';
	k1_[1] = 'o';
	k1_[2] = 'l';
	RainbowKey k1(k1_);

	unsigned char k2_[3];
	k2_[0] = 'w';
	k2_[1] = 't';
	k2_[2] = 'f';
	RainbowKey k2(k2_);

	unsigned char k3_[3];
	k3_[0] = 'o';
	k3_[1] = 'm';
	k3_[2] = 'g';
	RainbowKey k3(k3_);

	auto p1 = tbl.computeChain(k1);
	auto p2 = tbl.computeChain(k2);
	auto p3 = tbl.computeChain(k3);

	tbl.rainbow_list.push_back(p1);
	tbl.rainbow_list.push_back(p3);

	printf("p1: "); p1.first.dbgPrint(); printf(" | "); p1.second.dbgPrint(); printf("\n");
	printf("p2: "); p2.first.dbgPrint(); printf(" | "); p2.second.dbgPrint(); printf("\n");
	printf("p3: "); p3.first.dbgPrint(); printf(" | "); p3.second.dbgPrint(); printf("\n");

	if (!(tbl.getChainStart(p1.second).first && tbl.getChainStart(p1.second).second == p1.first)) {
		printf("p1 wrong value: ");
		tbl.getChainStart(p1.second).second.dbgPrintln();
		return false;
	}
	if (tbl.getChainStart(p2.second).first) {
		printf("p2 wrong value: ");
		tbl.getChainStart(p2.second).second.dbgPrintln();
		return false;
	}
	if (!(tbl.getChainStart(p3.second).first && tbl.getChainStart(p3.second).second == p3.first)) {
		printf("p3 wrong value: ");
		tbl.getChainStart(p3.second).second.dbgPrintln();
		return false;
	}

	return true;
}

bool chain_inverse_test()
{
	RainbowTable tbl;

	unsigned char k1_[3];
	k1_[0] = 'l';
	k1_[1] = 'o';
	k1_[2] = 'l';
	RainbowKey k1(k1_);
	RainbowValue v1 = k1.hash();
	if (tbl.getInverseInChain(v1, k1).second != k1) return false;

	unsigned char k2_[3];
	k2_[0] = 'w';
	k2_[1] = 't';
	k2_[2] = 'f';
	RainbowKey k2(k2_);
	RainbowValue v2 = k2.hash()
						.reduce(tbl.reduce_seq[0]).hash();
	if (tbl.getInverseInChain(v2, k2).second != k2.hash()
												  .reduce(tbl.reduce_seq[0])) return false;

	unsigned char k3_[3];
	k3_[0] = 'c';
	k3_[1] = 'c';
	k3_[2] = 'b';
	RainbowKey k3(k3_);
	RainbowValue v3 = k3.hash()
						.reduce(tbl.reduce_seq[0]).hash()
						.reduce(tbl.reduce_seq[1]).hash()
						.reduce(tbl.reduce_seq[2]).hash();
	if (tbl.getInverseInChain(v3, k3).second != k3.hash()
												  .reduce(tbl.reduce_seq[0]).hash()
												  .reduce(tbl.reduce_seq[1]).hash()
												  .reduce(tbl.reduce_seq[2])) return false;

	return true;
}

bool full_inverse_test()
{
	unsigned char k1_[3];
	k1_[0] = 'g';
	k1_[1] = 'g';
	k1_[2] = 'g';
	RainbowKey k1(k1_);

	unsigned char k2_[3];
	k2_[0] = 'b';
	k2_[1] = 'c';
	k2_[2] = 'd';
	RainbowKey k2(k2_);

	unsigned char k3_[3];
	k3_[0] = 'a';
	k3_[1] = 'b';
	k3_[2] = 'c';
	RainbowKey k3(k3_);

	RainbowTable tbl;

	vector<RainbowKey> words;
	words.push_back(k1);
	words.push_back(k2);

	tbl.buildTable(words);

	RainbowKey t1 = k1;
	RainbowKey t2 = k2.hash().reduce(tbl.reduce_seq[0])
					  .hash().reduce(tbl.reduce_seq[1])
					  .hash().reduce(tbl.reduce_seq[2])
					  .hash().reduce(tbl.reduce_seq[3])
					  .hash().reduce(tbl.reduce_seq[4])
					  .hash().reduce(tbl.reduce_seq[5])
					  .hash().reduce(tbl.reduce_seq[6]);
	RainbowKey t3 = k3.hash().reduce(tbl.reduce_seq[0]).hash().reduce(tbl.reduce_seq[1]);

	auto inv1 = tbl.getInverse(t1.hash());
	auto inv2 = tbl.getInverse(t2.hash());
	auto inv3 = tbl.getInverse(t3.hash());

	if (!(inv1.first && inv1.second == t1)) return false;
	if (!(inv2.first && inv2.second == t2)) return false;
	if (inv3.first) return false;

	return true;
}

bool general_test()
{
	RainbowTable tbl;

	tbl.buildTable();
	//tbl.read("RAINBOW");
	printf("Size of Table: %u\n", static_cast<unsigned int>(tbl.rainbow_list.size()));

	tbl.write("RAINBOW");


	unsigned char k1_[3];
	k1_[0] = 'g';
	k1_[1] = 'g';
	k1_[2] = 'g';
	RainbowKey k1(k1_);

	unsigned char k2_[3];
	k2_[0] = 'b';
	k2_[1] = 'c';
	k2_[2] = 'd';
	RainbowKey k2(k2_);

	unsigned char k3_[3];
	k3_[0] = 'a';
	k3_[1] = 'b';
	k3_[2] = 'c';
	RainbowKey k3(k3_);

	RainbowValue v1 = k1.hash();
	RainbowValue v2 = k2.hash();
	RainbowValue v3 = k3.hash();

	auto p1 = tbl.getInverse(v1);
	auto p2 = tbl.getInverse(v2);
	auto p3 = tbl.getInverse(v3);

	int num_success = 3;
	if (!(p1.first && p1.second == k1)) num_success--;
	if (!(p2.first && p2.second == k2)) num_success--;
	if (!(p3.first && p3.second == k3)) num_success--;
	printf("Number of Hits: %d\n", num_success);

	return false;;
}

bool uniqueness_test()
{
	RainbowTable tbl;
	//tbl.read("RAINBOW");
	tbl.buildTable(); tbl.write("RAINBOW");

	bool passed = true;

	for (int i = 0; i < tbl.rainbow_list.size(); i++) {
		int num_elements = 0;
		for (int j = 0; j < tbl.rainbow_list.size(); j++)
			if (tbl.rainbow_list[i].second == tbl.rainbow_list[j].second)
				num_elements += 1;
		if (num_elements != 1) passed = passed && false;
		printf("uniqueness test %s for i = %d\n", (num_elements != 1) ? "failed" : "passed", i);
	}

	return passed;
}
*/

int main()
{
	RainbowTable tbl;
	printRainbowSequence(tbl.reduce_seq);
	printf("Reduce Sequence Length: %u\n", static_cast<unsigned int>(tbl.reduce_seq.size()));
	map<string, bool> test_results;

    test_results["I/O Test"]				= io_test();
	//test_results["Hash Test"]				= hash_test();
    //test_results["Reduce Test"]				= reduce_test();
	//test_results["Chain Start Test"]		= chain_start_test();
	//test_results["Chain Inverse Test"]		= chain_inverse_test();
	//test_results["Full Inverse Test"]		= full_inverse_test();
	//test_results["General Test"]			= general_test();
	//test_results["Uniqueness Test"]			= uniqueness_test();

    printf("\n\n");
    for (auto const& test_result : test_results)
        printf("%s: %s\n", test_result.first.c_str(), test_result.second ? "Passed" : "Failed");
}

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

// some reduce functions
tuple<int, int, int> r0 = make_tuple(1, 4, 7);
tuple<int, int, int> r1 = make_tuple(3, 6, 2);
tuple<int, int, int> r2 = make_tuple(14, 9, 16);
tuple<int, int, int> r3 = make_tuple(13, 5, 11);
tuple<int, int, int> r4 = make_tuple(6, 1, 12);

vector<tuple<int, int, int>> reduce_seq = {r0, r1, r2, r3, r4};

bool io_test()
{
	RainbowTable tbl0(reduce_seq);

	unsigned char k1_[3];
	k1_[0] = 'l';
	k1_[1] = 'o';
	k1_[2] = 'l';
	RainbowKey k1(k1_);

	unsigned int v1_[5];
	v1_[0] = 3;
	v1_[1] = 1;
	v1_[2] = 4;
	v1_[3] = 1;
	v1_[4] = 5;
	RainbowValue v1(v1_);

	unsigned char k2_[3];
	k2_[0] = 'w';
	k2_[1] = 't';
	k2_[2] = 'f';
	RainbowKey k2(k2_);

	unsigned int v2_[5];
	v2_[0] = 9;
	v2_[1] = 8;
	v2_[2] = 7;
	v2_[3] = 6;
	v2_[4] = 8;
	RainbowValue v2(v2_);

	unsigned char k3_[3];
	k3_[0] = 'c';
	k3_[1] = 'c';
	k3_[2] = 'b';
	RainbowKey k3(k3_);

	unsigned int v3_[5];
	v3_[0] = 1;
	v3_[1] = 2;
	v3_[2] = 7;
	v3_[3] = 4;
	v3_[4] = 5;
	RainbowValue v3(v3_);

	unsigned char k4_[3];
	k4_[0] = 'o';
	k4_[1] = 'm';
	k4_[2] = 'g';
	RainbowKey k4(k4_);

	unsigned int v4_[5];
	v4_[0] = 5;
	v4_[1] = 4;
	v4_[2] = 3;
	v4_[3] = 9;
	v4_[4] = 1;
	RainbowValue v4(v4_);

	unsigned char k5_[3];
	k5_[0] = 'b';
	k5_[1] = 'b';
	k5_[2] = 'q';
	RainbowKey k5(k5_);

	unsigned int v5_[5];
	v5_[0] = 100;
	v5_[1] = 102;
	v5_[2] = 104;
	v5_[3] = 106;
	v5_[4] = 108;
	RainbowValue v5(v5_);

	tbl0.rainbow_list.push_back(make_pair(k1, v1));
	tbl0.rainbow_list.push_back(make_pair(k2, v2));
	tbl0.rainbow_list.push_back(make_pair(k3, v3));
	tbl0.rainbow_list.push_back(make_pair(k4, v4));
	tbl0.rainbow_list.push_back(make_pair(k5, v5));

	tbl0.write("RAINBOW");


	RainbowTable tbl1(reduce_seq);

	tbl1.read("RAINBOW");

	pair<RainbowKey, RainbowValue> p1 = tbl1.rainbow_list.at(0);
	pair<RainbowKey, RainbowValue> p2 = tbl1.rainbow_list.at(1);
	pair<RainbowKey, RainbowValue> p3 = tbl1.rainbow_list.at(2);
	pair<RainbowKey, RainbowValue> p4 = tbl1.rainbow_list.at(3);
	pair<RainbowKey, RainbowValue> p5 = tbl1.rainbow_list.at(4);
	p1.first.dbgPrint(); printf(" | "); p1.second.dbgPrint(); printf("\n");
	p2.first.dbgPrint(); printf(" | "); p2.second.dbgPrint(); printf("\n");
	p3.first.dbgPrint(); printf(" | "); p3.second.dbgPrint(); printf("\n");
	p4.first.dbgPrint(); printf(" | "); p4.second.dbgPrint(); printf("\n");
	p5.first.dbgPrint(); printf(" | "); p5.second.dbgPrint(); printf("\n");

    return true;
}

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
	RainbowTable tbl(reduce_seq);

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

	auto p1 = tbl.computeChain(k1);
	auto p2 = tbl.computeChain(k2);
	auto p3 = tbl.computeChain(k3);

	tbl.rainbow_list.push_back(p1);
	tbl.rainbow_list.push_back(p3);

	if (!(tbl.getChainStart(p1.second).first && tbl.getChainStart(p1.second).second == p1.first)) return false;
	if (tbl.getChainStart(p2.second).first)  return false;
	if (!(tbl.getChainStart(p3.second).first && tbl.getChainStart(p3.second).second == p3.first)) return false;

	return true;
}

bool chain_inverse_test()
{
	RainbowTable tbl(reduce_seq);

	unsigned char k1_[3];
	k1_[0] = 'l';
	k1_[1] = 'o';
	k1_[2] = 'l';
	RainbowKey k1(k1_);
	RainbowValue v1 = k1.hash();
	if (tbl.getInverseInChain(v1, k1) != k1) return false;

	unsigned char k2_[3];
	k2_[0] = 'w';
	k2_[1] = 't';
	k2_[2] = 'f';
	RainbowKey k2(k2_);
	RainbowValue v2 = k2.hash()
						.reduce(tbl.reduce_seq[0]).hash();
	if (tbl.getInverseInChain(v2, k2) != k2.hash()
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
	if (tbl.getInverseInChain(v3, k3) != k3.hash()
										   .reduce(tbl.reduce_seq[0]).hash()
										   .reduce(tbl.reduce_seq[1]).hash()
										   .reduce(tbl.reduce_seq[2])) return false;

	return true;
}

bool full_inverse_test()
{
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

	RainbowTable tbl(reduce_seq);

	vector<RainbowKey> words;
	words.push_back(k1);
	words.push_back(k2);

	tbl.buildTable(words);

	RainbowKey t1 = k1;
	RainbowKey t2 = k2.hash().reduce(tbl.reduce_seq[0]);
	RainbowKey t3 = k3.hash().reduce(tbl.reduce_seq[0]).hash().reduce(tbl.reduce_seq[1]);

	auto inv1 = tbl.getInverse(t1.hash());
	auto inv2 = tbl.getInverse(t2.hash());
	auto inv3 = tbl.getInverse(t3.hash());

	if (!(inv1.first && inv1.second == t1)) return false;
	if (!(inv2.first && inv2.second == t2)) return false;
	if (inv3.first) return false;

	return true;
}


int main()
{
	printRainbowSequence(reduce_seq);
	map<string, bool> test_results;

    test_results["Hash Test"]				= hash_test();
    test_results["Reduce Test"]				= reduce_test();
	test_results["Chain Start Test"]		= chain_start_test();
	test_results["Chain Inverse Test"]		= chain_inverse_test();
	test_results["Full Inverse Test"]		= full_inverse_test();

    printf("\n\n");
    for (auto const& test_result : test_results)
        printf("%s: %s\n", test_result.first.c_str(), test_result.second ? "Passed" : "Failed");
}

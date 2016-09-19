#include "rainbow.hpp"
#include "sha1/sha1.h"


void io_test()
{
	RainbowTable tbl0;

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


	RainbowTable tbl1;

	tbl1.read("RAINBOW");

	pair<RainbowKey, RainbowValue> p1 = tbl1.rainbow_list.at(0);
	pair<RainbowKey, RainbowValue> p2 = tbl1.rainbow_list.at(1);
	pair<RainbowKey, RainbowValue> p3 = tbl1.rainbow_list.at(2);
	pair<RainbowKey, RainbowValue> p4 = tbl1.rainbow_list.at(3);
	pair<RainbowKey, RainbowValue> p5 = tbl1.rainbow_list.at(4);
	for (int i=0; i<3; i++) printf("%c", p1.first.k[i]); printf(" | ");
	for (int i=0; i<5; i++) printf("%d ", p1.second.v[i]); printf("\n");
	for (int i=0; i<3; i++) printf("%c", p2.first.k[i]); printf(" | ");
	for (int i=0; i<5; i++) printf("%d ", p2.second.v[i]); printf("\n");
	for (int i=0; i<3; i++) printf("%c", p3.first.k[i]); printf(" | ");
	for (int i=0; i<5; i++) printf("%d ", p3.second.v[i]); printf("\n");
	for (int i=0; i<3; i++) printf("%c", p4.first.k[i]); printf(" | ");
	for (int i=0; i<5; i++) printf("%d ", p4.second.v[i]); printf("\n");
	for (int i=0; i<3; i++) printf("%c", p5.first.k[i]); printf(" | ");
	for (int i=0; i<5; i++) printf("%d ", p5.second.v[i]); printf("\n");
}

void hash_test()
{
	unsigned char testkey[3];
	unsigned int testhash[5];

	testkey[0] = 'w';
	testkey[1] = 't';
	testkey[2] = 'f';

	SHA1 sha;
	sha.Reset();
	sha.Input(testkey[0]); sha.Input(testkey[1]); sha.Input(testkey[2]);
	sha.Result(testhash);

	RainbowKey testkeywrapper(testkey);
	RainbowValue testhashwrapper(testhash);

	assert(testhashwrapper == testkeywrapper.hash());

	printf("hypothesis\n");
	for (int i=0; i<3; i++) printf("%c", testkeywrapper.k[i]);
	printf(" | ");
	for (int i=0; i<5; i++) printf(" %d ", testhashwrapper.v[i]);
	printf("\n");

	printf("result\n");
	for (int i=0; i<3; i++) printf("%c", testkeywrapper.k[i]);
	printf(" | ");
	for (int i=0; i<5; i++) printf(" %d ", testkeywrapper.hash().v[i]);
	printf("\n");
}


int main()
{
	hash_test();
}

#include "rainbow.hpp"




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

bool RainbowKey::operator<(RainbowKey const& o) const
{
	for (int i=0; i<3; i++)
		if (this->k[i] < o.k[i])
			return true;
	return false;
}
bool RainbowKey::operator==(RainbowKey const& o) const
{
    bool eq = true;
    for (int i=0; i<3; i++)
        eq = eq && (this->k[i] == o.k[i]);
    return eq;
}
RainbowKey& RainbowKey::operator=(RainbowKey const& o)
{
    for (int i=0; i<3; i++)
        this->k[i] = o.k[i];
    return *this;
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
RainbowValue& RainbowValue::operator=(RainbowValue const& o)
{
    for (int i=0; i<5; i++)
        this->v[i] = o.v[i];
    return *this;
}



RainbowTable::RainbowTable()
{
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


int main()
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

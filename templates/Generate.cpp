/*--------
  This program generates random digests 

to compile:
 g++ Generate.cpp sha1.cpp -o Generate

to run
  ./Generate 0 5000

------------*/

#include <iostream>
#include <iomanip>
#include "sha1.h"

using namespace std;

//-----   H A S H      ------------------------------------------------
//   getrandom (m) :     generate a random word. 
//---------------------------------------------------------------------
int getrandom( unsigned char  m[3])
{
      m[0]= (unsigned char) (random() % 256);
      m[1]= (unsigned char) (random() % 256);
      m[2]= (unsigned char) (random() % 256);

      return(0);
}

//-----   H A S H      ------------------------------------------------
//   Hash (m, d) :      compute the hash of m. The digest is stored in d.
//---------------------------------------------------------------------
int Hash (unsigned char m[3], unsigned int d[5] )
{
   SHA1 sha;
   
   sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);  
   sha.Result(d);
   return(0);
}

int main( int argc, char*argv[])
{
    SHA1          sha;
    unsigned int  d[5];   // 32 x 5 = 160 bits  digest
    unsigned char m[3];   // 24-bit word

    int seed    = atoi (argv[1]); 
    int number  = atoi (argv[2]); 
    srandom(seed);

    cout.setf(ios::hex,ios::basefield);    // format the output to be hex
    cout.setf(ios::uppercase);           

    for (int i=0; i<number; i++)
      { 
        getrandom(m); Hash(m,d);
        cout << "  " << setw(8) << setfill('0') << d[0]          // setw(8) set the width to be 8.
             << "  " << setw(8) << d[1] 
             << "  " << setw(8) << d[2] 
             << "  " << setw(8) << d[3] 
             << "  " << setw(8) << d[4] << endl;
      }

}


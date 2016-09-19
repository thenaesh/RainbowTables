/*--------
(1) Read in a Rainbow table (built using B.cpp)
(2) Read 1000 digests from standard input and  output the preimage. 
------------*/

#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "sha1.h"

using namespace std;
unsigned long TOTAL_SHA=0;       // Count the number of hashes performed.

unsigned char M[1024*512][3];    // array to store the word read from the table (head of chain)
unsigned int  D[1024*512][5];    // array to store the digest read from the table  (end of chain)

//-------   Data Structure for searching    -----------//
unordered_map <unsigned int, unsigned int> HashTable;
unordered_map <unsigned int, unsigned int>::const_iterator G;


//-----------    Hash     ----------------------------//
int Hash (unsigned char m[3], unsigned int d[5] )
{
   SHA1 sha;
   sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);  
   sha.Result(d);

   TOTAL_SHA = TOTAL_SHA +1;
   return(0);
}

//-----------    Reduce  -----------------------------//
//   d:   input digest
//   m:   output word
//   i:   the index of the reduce function 
//---------------------------------------------------//
int Reduce (unsigned int d[5], unsigned char m[3],  int i )
{
   m[0]=(unsigned char)( (d[0]+i ) %256);   //8 bits
   m[1]=(unsigned char)( (d[1]   ) %256);   //8 bits
   m[2]=(unsigned char)( (d[2]   ) %256);   //8 bits

   return(0);
}


//------------  Read in the Table ------------------//
//   Store the result in M and D                    //
int ReadT()
{
  return(0);
}


//------------------------------------------------------------------------------------
//      Given a digest,  search for the pre-image   answer_m[3].
//------------------------------------------------------------------------------------
int search( unsigned int target_d[5] ,   unsigned char answer_m[3])
{
  unsigned int j,i;
  unsigned char Colour_m[MAX_LEN ][3];
  unsigned int  Colour_d[MAX_LEN ][5];
  unsigned int  flag    [MAX_LEN ];


  for ( j=0; j< L_CHAIN ;  j++)
      {
          Colour_d[j][0]= target_d[0];
          Colour_d[j][1]= target_d[1];
          Colour_d[j][2]= target_d[2];
          Colour_d[j][3]= target_d[3];
          Colour_d[j][4]= target_d[4];
      }

  for ( j=0; j< L_CHAIN ;  j++)
  {
     for (int k=0; k< j+1 ; k++)
        {
               Reduce ( Colour_d[k], Colour_m[k], j); 
               Hash ( Colour_m[k], Colour_d[k] );
    
               //-------- search for the digest Colour_d[k] in the data structure. 

               //-------- if found, call transverse the chain starting from the head to find the pre-image.

        }
  }
  return (0);
}


//-----------   reading the next digest from the standard input  ----------------//
void readnextd (unsigned  int d[5])
{
   cin.setf(ios::hex,ios::basefield); cin.setf(ios::uppercase);
   cin >> d[0]; cin >> d[1]; cin >> d[2]; cin >> d[3]; cin >> d[4]; 
}


int main( int argc, char*argv[])
{
    int found;
    int total_found;
    int total_not_found;

    SHA1        sha;
    unsigned int d[5];   // 32 x 5 = 160 bits



    //------------ R E A D     R A I N B O W    T A B L E  --------//
    ReadT();       cout << "READ DONE" << endl;


    //--------  PROJECT  INPUT/OUTPUT FORMAT ----------------//

    total_found=0;
    total_not_found=0;

    cout.setf(ios::hex,ios::basefield);       //   setting display to Hexdecimal format.  (this is the irritating part of using C++).
    cout.setf(ios::uppercase); 

    for (int i=0; i<5000; i++)
      { 
        readnextd(d); 
        if (search (d,m)) 
               { total_found ++;
                 //------   print the word in hexdecimal format   -----------
                 cout << setw(1) << (unsigned int)m2[0]/16;
                 cout << setw(1) << (unsigned int)m2[0]%8;
                 cout << setw(1) << (unsigned int)m2[1]/16;
                 cout << setw(1) << (unsigned int)m2[1]%8;
                 cout << setw(1) << (unsigned int)m2[2]/16;
                 cout << setw(1) << (unsigned int)m2[2]%8  << endl;
                } 
        else
               {  total_not_found ++;
                  cout << setw(6)<< 0 << endl;
               }
      }
 
    cout.setf(ios::dec);
    cout << "Accuracy       C is: " << total_found/5000.0 << endl;
    cout << "Speedup factor F is: " << (5000.0/TOTAL_SHA)*8388608 << endl;

}


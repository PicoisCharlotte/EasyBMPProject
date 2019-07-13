#include "EasyBMP.h"
#include <iostream>
#include <fstream>

int main( int argc, char* argv[] )
{
  int k;
  for( k=1 ; k < argc ; k++ )
  {
   BMFH bmfh = GetBMFH( argv[k] );
   // if it isn't a BMP file, don't do anything!
   if( bmfh.bfType == 19778 )
   {

    // determine the output filename
    char OutputName [2049];
    strcpy( OutputName , argv[k] );
    int i,j;
    int Length = strlen(OutputName);
    OutputName[Length-4] = 'G';
    OutputName[Length-3] = 'r';
    OutputName[Length-2] = 'e';
    OutputName[Length-1] = 'y';
    OutputName[Length] = '\0';
    strcat( OutputName , ".bmp");

    // declare and read the bitmap
    BMP Image;
    Image.ReadFromFile( argv[k] );

    // convert each pixel to greyscale
    for( int i=0 ; i < Image.TellWidth() ; i++)
    {
     for( int j=0 ; j < Image.TellHeight() ; j++)
     {
      Image(i,j)->Red   = (ebmpBYTE) 255 - ( Image(i,j)->Red   );
      Image(i,j)->Green = (ebmpBYTE) 255 - ( Image(i,j)->Green );
      Image(i,j)->Blue  = (ebmpBYTE) 255 - ( Image(i,j)->Blue  );
     }
    }

    Image.SetBitDepth( 8 );

    // write the output file
    Image.WriteToFile( OutputName );

   }
  }
}

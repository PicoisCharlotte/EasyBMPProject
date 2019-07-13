//
// Created by lukile on 13/07/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include <omp.h>

#include "EasyBMP.h"

double redGreyscale = 0.30;
double greenGreyscale = 0.59;
double blueGreyscale = 0.11;

using namespace std;

BMP BlackAndWhite;

BMP Negatif;


void blackAndWhite();
void negatif();

void blackAndWhite(){
    int i,j;
    BlackAndWhite.ReadFromFile( "EasyBMPbackground.bmp" );

    for( int i=0 ; i < BlackAndWhite.TellWidth() ; i++)
    {
        for( int j=0 ; j < BlackAndWhite.TellHeight() ; j++)
        {
            double Temp = 0.30*( BlackAndWhite(i,j)->Red   ) +
                          0.59*( BlackAndWhite(i,j)->Green ) +
                          0.11*( BlackAndWhite(i,j)->Blue  );
            BlackAndWhite(i,j)->Red   = (ebmpBYTE) Temp;
            BlackAndWhite(i,j)->Green = (ebmpBYTE) Temp;
            BlackAndWhite(i,j)->Blue  = (ebmpBYTE) Temp;
        }
    }

    BlackAndWhite.SetBitDepth( 8 );

    CreateGrayscaleColorTable( BlackAndWhite );

    BlackAndWhite.WriteToFile( "BlackAndWhiteEasyBMPbackground.bmp" );

}

void negatif() {
    //int k;
    //for( k=1 ; k < argc ; k++ )
    //{
       // BMFH bmfh = GetBMFH( argv[k] );
        // if it isn't a BMP file, don't do anything!
        //if( bmfh.bfType == 19778 )
        //{

            // determine the output filename
            //char OutputName [2049];
            //strcpy( OutputName , argv[k] );
            int i,j;
            //int Length = strlen(OutputName);
            /*OutputName[Length-7] = 'N';
            OutputName[Length-6] = 'e';
            OutputName[Length-5] = 'g';
            OutputName[Length-4] = 'a';
            OutputName[Length-3] = 't';
            OutputName[Length-2] = 'i';
            OutputName[Length-1] = 'f';
            OutputName[Length] = '\0';
            strcat( OutputName , ".bmp");*/

            // declare and read the bitmap
            //BMP Image;
            Negatif.ReadFromFile( "EasyBMPbackground.bmp");

            // convert each pixel to greyscale
            for( int i=0 ; i < Negatif.TellWidth() ; i++)
            {
                for( int j=0 ; j < Negatif.TellHeight() ; j++)
                {
                    Negatif(i,j)->Red   = (ebmpBYTE) 255 - ( Negatif(i,j)->Red   );
                    Negatif(i,j)->Green = (ebmpBYTE) 255 - ( Negatif(i,j)->Green );
                    Negatif(i,j)->Blue  = (ebmpBYTE) 255 - ( Negatif(i,j)->Blue  );
                }
            }

            Negatif.SetBitDepth( 8 );

            // write the output file
            Negatif.WriteToFile( "NegatifEasyBMPbackground.bmp" );

        //}
   // }
}


int main(int argc, char* argv[]) {
    int choice;

    cout << "\n1. Black And White BMP\n2. Negatif BMP" << endl;
    cin >> choice;

    switch(choice) {
        case 1:
            blackAndWhite();
            break;
        case 2:
            negatif();
            break;
        default:
            cout << "Choice error !\n" << endl;
    }

}
//
// Created by lukile on 13/07/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <omp.h>

#include "EasyBMP.h"
#include "Resize.cpp"

BMP BlackAndWhite;
double redGreyscale = 0.30;
double greenGreyscale = 0.59;
double blueGreyscale = 0.11;
int i,j;
double blackAndWhiteStart;
double blackAndWhiteEnd;
double negativeStart;
double negativeEnd;
double resizeStart;
double resizeEnd;

BMP Negatif;

BMP ResizeIn;
BMP ResizeOut;

int NewWidth = 0;
int NewHeight = 0;

using namespace std;

void blackAndWhite();
void negatif();
void resize(char* argv[], int Percentage);

void blackAndWhite(){
    BlackAndWhite.ReadFromFile( "EasyBMPbackground.bmp" );

    blackAndWhiteStart = omp_get_wtime();

#pragma omp parallel for private(i, j)
    for(i = 0 ; i < BlackAndWhite.TellWidth() ; i++) {
        for(j = 0 ; j < BlackAndWhite.TellHeight() ; j++) {
            double res = redGreyscale * (BlackAndWhite(i,j)->Red) +
                         greenGreyscale * (BlackAndWhite(i,j)->Green) +
                         blueGreyscale * (BlackAndWhite(i,j)->Blue);
            BlackAndWhite(i,j)->Red   = (ebmpBYTE) res;
            BlackAndWhite(i,j)->Green = (ebmpBYTE) res;
            BlackAndWhite(i,j)->Blue  = (ebmpBYTE) res;
        }
    }

    BlackAndWhite.SetBitDepth(8);

    CreateGrayscaleColorTable(BlackAndWhite);

    blackAndWhiteEnd = omp_get_wtime();

    cout << "Black and White program has been processed in " << (blackAndWhiteEnd - blackAndWhiteStart) * 1000 << " milliseconds\n" << endl;

    BlackAndWhite.WriteToFile("BlackAndWhiteEasyBMPbackground.bmp");
}

void negatif() {
    int i,j;
    Negatif.ReadFromFile( "EasyBMPbackground.bmp");

    negativeStart = omp_get_wtime();

#pragma omp parallel for private(i, j)
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

    negativeEnd = omp_get_wtime();

    cout << "Negative program has been processed in " << (negativeEnd - negativeStart) * 1000 << " milliseconds\n" << endl;

    Negatif.WriteToFile( "NegatifEasyBMPbackground.bmp" );
}

void resize(char* argv[], int Percentage) {


    ResizeIn.ReadFromFile( "EasyBMPbackground.bmp" );

    resizeStart = omp_get_wtime();

    ResizeOut.SetSize( NewWidth, NewHeight );

    if( ResizeIn.TellBitDepth() == 32 ) {
        ResizeOut.SetBitDepth( 32 );
    } else {
        ResizeOut.SetBitDepth( 24 );
    }

    Resize(ResizeIn, 'P', Percentage);

    resizeEnd = omp_get_wtime();

    cout << "Resize program has been processed in " << (resizeEnd - resizeStart) * 1000 << " milliseconds\n" << endl;

    ResizeIn.WriteToFile( "ResizeEasyBMPbackground.bmp" );
}

int main(int argc, char* argv[]) {
    int Percentage;

    int choice;

    cout << "\n1. Black And White BMP\n2. Negatif BMP\n3. Resize BMP" << endl;
    cin >> choice;

    switch(choice) {
        case 1:
            blackAndWhite();
            break;
        case 2:
            negatif();
            break;
        case 3:
            cout << "Enter percentage" << endl;
            cin >> Percentage;

            resize(argv, Percentage);
            break;
        default:
            cout << "Choice error !\n" << endl;
    }
}

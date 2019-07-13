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
    int i,j;
    Negatif.ReadFromFile( "EasyBMPbackground.bmp");

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

    Negatif.WriteToFile( "NegatifEasyBMPbackground.bmp" );
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
/**************************************************************
*                                                             *
*  EasyBMP Cross-Platform Windows Bitmap Library Code Sample  * 
*                                                             *
*  Author: Paul Macklin                                       *
*   email: macklin01@users.sourceforge.net                    *
*     WWW: http://easybmp.sourceforge.net                     *
*                                                             *
*    file: ColorToGrey.cpp                                    *
*    date: 5-26-2006                                          *
* version: 1.02                                               *
*                                                             *
*   License: GPL v 2                                          *
* Copyright: 2005-6 by the EasyBMP Project                    *
*                                                             *
* description: Code sample for EasyBMP library that converts  *
*              any 1, 4, 8, 16, 24, or 32-bit BMP to greyscale*
*                                                             *
**************************************************************/

#include <iostream>
#include <fstream>
#include "../EasyBMP.h"
#include <omp.h>

using namespace std;

int main( int argc, char* argv[] )
{
    char* DATE = "May 26";
    char* YEAR = "2006";
    char* AUTHOR = "Paul Macklin";
    char* LICENSE = "GPL v. 2";
    char* GROUP = "the EasyBMP Project";
    char* CONTACT = "http://easybmp.sourceforge.net";

    // determine if the user asked for help
    bool HelpMode = false;
    if( argc > 1 )
    {
        char HelpTemp [1025];
        strcpy( HelpTemp , argv[1] );
        if( HelpTemp[0] == '-' && HelpTemp[1] == '-' &&
            HelpTemp[2] == 'h' && HelpTemp[3] == 'e' &&
            HelpTemp[4] == 'l' && HelpTemp[5] == 'p' )
        { HelpMode = true; }
    }
    // if the user asked for help or is confused, spit out help info
    if( argc == 1 || HelpMode )
    {
        cout << "\nColorToGrey usage: \n\n"
             << "The following convert color (Windows) bitmap files to greyscale\n\n"
             << "          ColorToGrey <filename1> <filename2> <filename3> ... \n"
             << "          ColorToGrey *.bmp \n"
             << "          ColorToGrey *\n\n"
             << "The program will append 'Grey' to the filename just before the '.bmp'\n\n"
             << "This gives this help information:\n\n"
             << "          ColorToGrey --help\n\n"
             << " Created on " << DATE << ", " << YEAR << " by " << AUTHOR << ".\n"
             << " Uses the EasyBMP library, Version " << _EasyBMP_Version_ << ".\n"
             << " Licensed under " << LICENSE << " by " << GROUP << ".\n"
             << " Copyright (c) " << YEAR << " " << GROUP << "\n"
             << " Contact: " << CONTACT << "\n\n";
        return 1;
    }
    // spit out copyright / license information
    cout  << "\n Created on " << DATE << ", " << YEAR << " by " << AUTHOR << ".\n"
          << " Uses the EasyBMP library, Version " << _EasyBMP_Version_ << ".\n"
          << " Licensed under " << LICENSE << " by " << GROUP << ".\n"
          << " Copyright (c) " << YEAR << " " << GROUP << "\n"
          << " Contact: " << CONTACT << "\n\n";

    int k;
    for( k=1 ; k < argc ; k++ )
    {
        BMFH bmfh = GetBMFH( argv[k] );
        // if it isn't a BMP file, don't do anything!
        if( bmfh.bfType == 19778 )
        {
            cout << "Processing file " << argv[k] << " ...\n";

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
                    double Temp = 0.30*( Image(i,j)->Red   ) +
                                  0.59*( Image(i,j)->Green ) +
                                  0.11*( Image(i,j)->Blue  );
                    Image(i,j)->Red   = (ebmpBYTE) Temp;
                    Image(i,j)->Green = (ebmpBYTE) Temp;
                    Image(i,j)->Blue  = (ebmpBYTE) Temp;
                }
            }

            Image.SetBitDepth( 8 );

            // Create a greyscale color table
            CreateGrayscaleColorTable( Image );

            // write the output file
            Image.WriteToFile( OutputName );

        }
        else
        {
            cout << "Skipping (non-bmp) file " << argv[k] << " ...\n";
        }

    }

    return 0;
}

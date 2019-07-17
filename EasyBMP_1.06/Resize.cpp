#include "EasyBMP.h"

bool Resize( BMP& InputImage , char mode, int NewDimension )
{
  using namespace std;
   int UserChoice = toupper( mode );

   BMP OldImage( InputImage );

   if( UserChoice != 'P' &&
       UserChoice != 'W' &&
       UserChoice != 'H' &&
       UserChoice != 'F' )
   {
     char ErrorMessage [1024];
     sprintf( ErrorMessage, "EasyBMP Error: Unknown rescale mode %c requested\n" , mode );
     cout << ErrorMessage;

    return false;
   }

   int NewWidth  =0;
   int NewHeight =0;

   int OldWidth = OldImage.TellWidth();
   int OldHeight= OldImage.TellHeight();

   if( UserChoice == 'P' )
   {
    NewWidth = (int) floor( OldWidth * NewDimension / 100.0 );
    NewHeight = (int) floor( OldHeight * NewDimension / 100.0 );
   }
   if( UserChoice == 'F' )
   {
    if( OldWidth > OldHeight )
    { UserChoice = 'W'; }
    else
    { UserChoice = 'H'; }
   }

   if( UserChoice == 'W' )
   {
    double percent = (double) NewDimension / (double) OldWidth;
    NewWidth = NewDimension;
    NewHeight = (int) floor( OldHeight * percent );
   }
   if( UserChoice == 'H' )
   {
    double percent = (double) NewDimension / (double) OldHeight;
    NewHeight = NewDimension;
    NewWidth = (int) floor( OldWidth * percent );
   }

   if( NewWidth < 1 )
   { NewWidth = 1; }
   if( NewHeight < 1 )
   { NewHeight = 1; }

   InputImage.SetSize( NewWidth, NewHeight );
   InputImage.SetBitDepth( 24 );

   int I,J;
   double  OldWidthPerNewWidth , OldHeightPerNewHeight ;

   for( int j=0; j < NewHeight-1 ; j++ )
   {
     OldHeightPerNewHeight  = (double)(j*(OldHeight-1.0))
            /(double)(NewHeight-1.0);
    J	= (int) floor(  OldHeightPerNewHeight  );
     OldHeightPerNewHeight  -= J;

    for( int i=0; i < NewWidth-1 ; i++ )
    {
      OldWidthPerNewWidth  = (double)(i*(OldWidth-1.0))
             /(double)(NewWidth-1.0);
     I = (int) floor(  OldWidthPerNewWidth  );
      OldWidthPerNewWidth  -= I;

     InputImage(i,j)->Red = (ebmpBYTE)
                            ( (1.0- OldWidthPerNewWidth - OldHeightPerNewHeight + OldWidthPerNewWidth * OldHeightPerNewHeight )*(OldImage(I,J)->Red)
                             +( OldWidthPerNewWidth - OldWidthPerNewWidth * OldHeightPerNewHeight )*(OldImage(I+1,J)->Red)
                             +( OldHeightPerNewHeight - OldWidthPerNewWidth * OldHeightPerNewHeight )*(OldImage(I,J+1)->Red)
                             +( OldWidthPerNewWidth * OldHeightPerNewHeight )*(OldImage(I+1,J+1)->Red) );
     InputImage(i,j)->Green = (ebmpBYTE)
                            ( (1.0- OldWidthPerNewWidth - OldHeightPerNewHeight + OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I,J)->Green
                             +( OldWidthPerNewWidth - OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I+1,J)->Green
                             +( OldHeightPerNewHeight - OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I,J+1)->Green
                             +( OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I+1,J+1)->Green );
     InputImage(i,j)->Blue = (ebmpBYTE)
                            ( (1.0- OldWidthPerNewWidth - OldHeightPerNewHeight + OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I,J)->Blue
                             +( OldWidthPerNewWidth - OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I+1,J)->Blue
                             +( OldHeightPerNewHeight - OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I,J+1)->Blue
                             +( OldWidthPerNewWidth * OldHeightPerNewHeight )*OldImage(I+1,J+1)->Blue );
    }
     InputImage(NewWidth-1,j)->Red = (ebmpBYTE)
                              ( (1.0- OldHeightPerNewHeight )*(OldImage(OldWidth-1,J)->Red)
                            +  OldHeightPerNewHeight *(OldImage(OldWidth-1,J+1)->Red) );
     InputImage(NewWidth-1,j)->Green = (ebmpBYTE)
                              ( (1.0- OldHeightPerNewHeight )*(OldImage(OldWidth-1,J)->Green)
                            +  OldHeightPerNewHeight *(OldImage(OldWidth-1,J+1)->Green) );
     InputImage(NewWidth-1,j)->Blue = (ebmpBYTE)
                              ( (1.0- OldHeightPerNewHeight )*(OldImage(OldWidth-1,J)->Blue)
                            +  OldHeightPerNewHeight *(OldImage(OldWidth-1,J+1)->Blue) );
   }

   for( int i=0 ; i < NewWidth-1 ; i++ )
   {
     OldWidthPerNewWidth  = (double)(i*(OldWidth-1.0))
            /(double)(NewWidth-1.0);
    I = (int) floor(  OldWidthPerNewWidth  );
     OldWidthPerNewWidth  -= I;
    InputImage(i,NewHeight-1)->Red = (ebmpBYTE)
                              ( (1.0- OldWidthPerNewWidth )*(OldImage(I,OldHeight-1)->Red)
                            +  OldWidthPerNewWidth *(OldImage(I,OldHeight-1)->Red) );
    InputImage(i,NewHeight-1)->Green = (ebmpBYTE)
                              ( (1.0- OldWidthPerNewWidth )*(OldImage(I,OldHeight-1)->Green)
                            +  OldWidthPerNewWidth *(OldImage(I,OldHeight-1)->Green) );
    InputImage(i,NewHeight-1)->Blue = (ebmpBYTE)
                              ( (1.0- OldWidthPerNewWidth )*(OldImage(I,OldHeight-1)->Blue)
                            +  OldWidthPerNewWidth *(OldImage(I,OldHeight-1)->Blue) );
   }

   *InputImage(NewWidth-1,NewHeight-1) = *OldImage(OldWidth-1,OldHeight-1);
   return true;
}

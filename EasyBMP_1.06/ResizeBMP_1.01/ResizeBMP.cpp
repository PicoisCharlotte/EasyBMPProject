#include "../EasyBMP.h"

using namespace std;

// use bilinear interpolation to get the desired pixel from the old image

RGBApixel GetPixel( BMP &Old , int i, int M , int j , int N )
{
 RGBApixel Output;
 double s = (i+0.0)*(Old.TellWidth()-1.0)/(M-1.0);
 double t = (j+0.0)*(Old.TellHeight()-1.0)/(N-1.0);
 
 // stability fixes for the weird case where Old is 1x1 
 if( Old.TellWidth() == 1 )
 { s = 0.0; }
 if( Old.TellHeight() == 1 )
 { t = 0.0; }
 
 // safety
 if( s < 1e-12 ){ s = 0.0; }
 if( s > Old.TellWidth() -1.0-1e-12 ){ s = Old.TellWidth()-1.0; }
 if( t < 1e-12 ){ t = 0.0; }
 if( t > Old.TellHeight() -1.0-1e-12 ){ t = Old.TellHeight()-1.0; }
 
 int I = (int) floor( s ); double ThetaS = s - I;
 int J = (int) floor( t ); double ThetaT = t - J;
 
 ebmpWORD Upper;
 ebmpWORD Lower;
 
 // special case: right edge

 if( I == Old.TellWidth()-1 )
 {
  if( J == Old.TellHeight()-1 )
  {
   Output.Red = Old(I,J)->Red;
   Output.Green = Old(I,J)->Green;
   Output.Blue = Old(I,J)->Blue;
   Output.Alpha = Old(I,J)->Alpha;
   return Output;
  }
  Output.Red = (ebmpWORD) ( (1.0-ThetaT)*( Old(I,J)->Red + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Red + 0.0 ) );  
  Output.Green = (ebmpWORD) ( (1.0-ThetaT)*( Old(I,J)->Green + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Green + 0.0 ) );  
  Output.Blue = (ebmpWORD) ( (1.0-ThetaT)*( Old(I,J)->Blue + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Blue + 0.0 ) );  
  Output.Alpha = (ebmpWORD) ( (1.0-ThetaT)*( Old(I,J)->Alpha + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Alpha + 0.0 ) );  
  return Output;  
 }
 
 // special case: top edge
 
 if( J == Old.TellHeight()-1 )
 {
  if( I == Old.TellWidth()-1 )
  {
   Output.Red = Old(I,J)->Red;
   Output.Green = Old(I,J)->Green;
   Output.Blue = Old(I,J)->Blue;
   Output.Alpha = Old(I,J)->Alpha;
   return Output;
  }
  Output.Red = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Red + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Red + 0.0 ) );  
  Output.Green = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Green + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Green + 0.0 ) );  
  Output.Blue = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Blue + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Blue + 0.0 ) );  
  Output.Alpha = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Alpha + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Alpha + 0.0 ) );  
  return Output; 
 }
 
 // interpolate red

 Upper = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J+1)->Red + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Red + 0.0 ) );
 Lower = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Red + 0.0 )
       +  ThetaS*( Old(I+1,J)->Red + 0.0 ) );

 Output.Red = (ebmpWORD) (  (1.0-ThetaT)*( Lower + 0.0 )
                + ThetaT*( Upper + 0.0 ) );
		
 // interpolate green
 
 Upper = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J+1)->Green + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Green + 0.0 ) );
 Lower = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Green + 0.0 )
       +  ThetaS*( Old(I+1,J)->Green + 0.0 ) );
 Output.Green = (ebmpWORD) (  (1.0-ThetaT)*( Lower + 0.0 )
                  + ThetaT*( Upper + 0.0 ) );
 
 // interpolate blue
 
 Upper = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J+1)->Blue + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Blue + 0.0 ) );
 Lower = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Blue + 0.0 )
       +  ThetaS*( Old(I+1,J)->Blue + 0.0 ) );
 Output.Blue = (ebmpWORD) (  (1.0-ThetaT)*( Lower + 0.0 )
                  + ThetaT*( Upper + 0.0 ) );

 // interpolate alpha
 
 Upper = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J+1)->Alpha + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Alpha + 0.0 ) );
 Lower = (ebmpWORD) ( (1.0-ThetaS)*( Old(I,J)->Alpha + 0.0 )
       +  ThetaS*( Old(I+1,J)->Alpha + 0.0 ) );
 Output.Alpha = (ebmpWORD) (  (1.0-ThetaT)*( Lower + 0.0 )
                  + ThetaT*( Upper + 0.0 ) );
                  
 return Output;
}



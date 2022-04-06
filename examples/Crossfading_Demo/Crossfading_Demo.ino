#include <RGBcrossfade.h>

byte cycle = 0;


// All colors are used as a 4-position byte array, {R,G,B,W}
byte red[4] = {255,0,0,0};
byte orange[4] = {255,153,51,0};
byte yellow[4] = {255,255,0,0};
byte green[4] = {51,204,51,0};
byte blue[4] = {0,0,255,0};
byte violet[4] = {204,51,255,0};
byte fuchsia[4] = {255,0,255,0};


RGBcrossfade rgb;



void setup() {
  
Serial.begin(9600);


// Initialize the RGBcrossfade services with (R pin, G pin, B pin, W pin, BOOL Dimming Curve)
// The dimming curve will make LEDs appear to fade steadily. See this link for more information on this phenomenon: https://www.eldoled.com/support/learning-center/why-you-need-dimming-curves/
// The dimming curve is applied to the WHITE channel only. Using the curve with RGB causes incorrect colors.
// Most applications should leave the dimming curve argument set to 1.
rgb.begin(22,10,23,9,1);


// Fades white channel to 255, all others to 0, argument is Seconds
rgb.fadeToWhite(2);


        // For demo only
        while(millis() < 3000){
          rgb.updateRGB();
        }


// Fades all channels to 0, argument is Seconds
rgb.fadeToBlack(2);


        // For demo only
        while(millis() < 6000){
          rgb.updateRGB();
        }


// Fades white to level (0-255) specified in first argument, second argument is Seconds
rgb.fadeToWhiteLevel(50,1);


        // For demo only
        while(millis() < 10000){
          rgb.updateRGB();
        }


// Goes instantly to black without fade
rgb.black();
delay(1000);

// Goes instantly to white without fade
rgb.white();
delay(1000);

// Goes instantly to a color without fade
rgb.color(fuchsia);
delay(1000);

// NOTE: Using delay() will pause any active fade events. delay() is not recommended outside this quick demonstration.

}



void loop() {


/*=================================================================================================
   Place this function call anywhere in your loop. The code will not run at all if this is not done!
   For most applications you can let it run indefinitely.
   In some cases you might want to disable this library from operating temporarily, or during busy times, etc. You can do:
   if(condition){
      rgb.updateRGB();
      }
      
   This function is checking to see if a fade event is occuring,
     and if it's time to increment the fade values. */
     
rgb.updateRGB();

/*================================================================================================*/


Serial.print("Current R val is: ");
Serial.println(rgb.r());
/*
 Library can be queried for current levels
 rgb.g();
 rgb.b();
 rgb.w();
*/


// rgb.done is true when there is no active fade event
if(rgb.done){

  
  if(cycle == 0){
    rgb.fadeToColor(red,1);
    cycle = 1;
  }
  else if(cycle == 1){
    rgb.fadeToColor(orange,1);
    cycle = 2;
  }
    else if(cycle == 2){
    rgb.fadeToColor(yellow,1);
    cycle = 3;
  }
    else if(cycle == 3){
    // Colors can be defined locally
    byte localGreen[4] = {0,255,0,0};
    rgb.fadeToColor(localGreen,1);
    cycle = 4;
  }
    else if(cycle == 4){
    // Colors can be defined programmatically
    byte x = 255;
    byte localBlue[4] = {0,0,x,0};
    rgb.fadeToColor(localBlue,1);
    cycle = 5;
  }
      else if(cycle == 5){
    rgb.fadeToColor(violet,1);
    cycle = 6;
  }
      else if(cycle == 6){
    rgb.fadeToBlack(4);
    cycle = 0;
  }
}

}

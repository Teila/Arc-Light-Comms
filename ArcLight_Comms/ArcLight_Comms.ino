#include <FastLED.h>
#include <string.h>

#define NUM_LEDS 12     //number of total leds in strip
#define DATA_PIN 6      //control pin

String str2 = "$";      //start data flag
String str3 = "*";      //end data flag
String str[37];     //set expected string length

int counter;
int x;
int y;
int arrayData[3][4];        //array to be built for ((r1,g1,b1,a1)(r2,b2,g2,a2)(w,null,null,null))

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    Serial.flush();     //flush comms
    counter = 0;
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);        //setup strip controls
}

void loop() {
    while (Serial.available() > 0) {        // wait til data comes in over serial
        String str = Serial.readString();
        if (str.startsWith("$")) {      //if str starts with $
            if (str.endsWith("*")) {        //and ends with *
                str.remove(0, 1);
                str.remove(35);
                parseData(str);     // call parse code here
            }
        }
        delay (10);        //cycle delay
    }
    fill_solid( &(leds[(NUM_LEDS / 2) - (arrayData[2][0] / 2)])/*start location*/, arrayData[2][0] /*number of leds*/, CRGB(arrayData[0][0],arrayData[0][1],arrayData[0][2]) );        //main LEDs
    fill_solid( &(leds[(NUM_LEDS / 2) + (arrayData[2][0] / 2)])/*start location*/, (NUM_LEDS /  2) - (arrayData[2][0] / 2) /*number of leds*/, CRGB(arrayData[1][0],arrayData[1][1],arrayData[1][2]) );       //ambiant left LEDs
    fill_solid( &(leds[0])/*start location*/, (NUM_LEDS /  2) - (arrayData[2][0] / 2) /*number of leds*/, CRGB(arrayData[1][0],arrayData[1][1],arrayData[1][2]) );       //ambiant right LEDs
    FastLED.show();     // start show
    delay (1);
}
void parseData(String com) {
    char com_new[com.length() + 1];
    com.toCharArray(com_new, sizeof(com_new));
    char *split = strtok (com_new, ",");
    int splitdata[9];       //total split values
    int cnt1 = 0;
    while (split != NULL) {
        splitdata[cnt1] = atoi(split);
        cnt1++;
        split = strtok(NULL,",");
    }
    int cnt2 = 0;
    for (x = 0; x < 3; x++) {
        if (x < 2) {
            for (y = 0; y < 4; y++) {
                arrayData[x][y] = splitdata[cnt2];
                cnt2++;
            }
        } else {
            arrayData[x][0] = splitdata[cnt2];
        }
    }
}
//$045,000,000,255,110,090,045,255,001* example string data

#include "FastLED.h"
#include "string.h"

#define NUM_LEDS 10
#define DATA_PIN 6

String str2 = "$";
String str3 = "*";
String str[37];

int counter;
int x;
int y;
int arrayData[3][4];

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    Serial.flush();
    counter = 0;
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    while (Serial.available() > 0) {
        Serial.println("DATA:");            //status
        String str = Serial.readString();
        Serial.println(str);                //status
        if (str.startsWith("$")) { //if str starts with $
            if (str.endsWith("*")) { //and ends with *
                str.remove(0, 1);
                str.remove(35);
                Serial.println("stripped:");  //status
                Serial.println(str);          //status
                parseData(str); // call parse code here?
            }
        }
        delay (1000);
    }
    fill_solid( &(leds[0]), arrayData[2][0] /*number of leds*/, CRGB(arrayData[0][0],arrayData[0][1],arrayData[0][2]) );
    fill_solid( &(leds[arrayData[2][0]]), NUM_LEDS - arrayData[2][0] /*number of leds*/, CRGB(arrayData[1][0],arrayData[1][1],arrayData[1][2]) );
    FastLED.show();
    delay (500);
}
void parseData(String com) {
    char com_new[com.length() + 1];
    com.toCharArray(com_new, sizeof(com_new));
    char *split = strtok (com_new, ",");
    int splitdata[9];
    int cnt1 = 0;
    while (split != NULL) {
        splitdata[cnt1] = atoi(split);        
            //Serial.println(cnt1);  // 0 1 2 3 4 5 6 7 8 0 1 2
        cnt1++;
        split = strtok(NULL,",");
    }
    int cnt2 = 0;
    for (x = 0; x < 3; x++) {
      //Serial.println(x);    // 255 255 255 255 255 1 128 128 128 255 255 255
        if (x < 2) {
            for (y = 0; y < 4; y++) {
                arrayData[x][y] = splitdata[cnt2];
                    //Serial.println(cnt2);  //
                cnt2++;
            }
        } else {
            arrayData[x][0] = splitdata[cnt2];
        }
    }
}
//$045,000,000,255,110,090,045,255,001* example string data
//int r1 = Serial.parseInt();

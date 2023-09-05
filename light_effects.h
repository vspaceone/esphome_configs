#include <cmath>

void rainbow_cricle(AddressableLight& it) {
    uint16_t len = it.size();
    double hue_shift = std::fmod((double)millis() / 10000.0, 360.0);
    double per_led = 360.0 / len;
    for (uint16_t i = 0; i < len; i++) it[i]=ESPHSVColor(hue_shift+(per_led*i),255,255);
}

struct flag_t {
    uint8_t len=0;
    Color colors[];
};

Color pride_flag[] = {
    Color(255,0,0),
    Color(255,128,0),
    Color(255,255,0),
    Color(0,255,0),
    Color(32,64,255),
    Color(255,0,255)
};

Color trans_flag[] = {
    Color(0,255,255),
    Color(255,0,192),
    Color(255,255,255),
    Color(255,0,192),
    Color(0,255,255)
};

void pride_circle(AddressableLight& it, const Color* flag, uint8_t flag_len) {
    uint16_t len = it.size();
    double leds_per_band = ((double)len/2.0) / (double)flag_len;
    for (uint16_t i = 0; i < flag_len; i++) {
        uint16_t pos = leds_per_band*i;
        it.range(pos,pos+leds_per_band).set(flag[i]);
    }
    for (uint16_t i = 0; i < flag_len; i++) {
        uint16_t pos = len - (leds_per_band*i);
        it.range(pos-leds_per_band,pos).set(flag[i]);
    }
}

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
    Color(255,192,0),
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

Color enby_flag[] = {
    Color(255,255,0),
    Color(255,255,255),
    Color(192,0,255),
    Color(24,24,24)
};

void pride_circle(AddressableLight& it, const Color* flag, uint8_t flag_len) {
    uint16_t len = it.size();
    double leds_per_band = ((double)len/2.0) / (double)flag_len;
    for (uint16_t i = 0; i < flag_len; i++) {
        uint16_t pos = leds_per_band*i;
        it.range(floor(pos),ceil(pos+leds_per_band)).set(flag[i]);
    }
    for (uint16_t i = 0; i < flag_len; i++) {
        uint16_t pos = len - (leds_per_band*i);
        it.range(floor(pos-leds_per_band),ceil(pos)).set(flag[i]);
    }
}

constexpr float two_pi = 2.0*PI;
void sine_effect(AddressableLight& it, Color col) {
	float m = millis()/3140.0;
	uint16_t len = it.size();
	for (uint16_t i = 0; i < len; i++) it[i].set_green( 127 * (std::sin( i*(two_pi/float(len-1.0)) +m) +1.0) );
}


void ha_state_to_led(std::string ha_state, AddressableLightState*& led) {
    std::map<std::string,Color> state_to_color {
        {"on",Color(0,255,0)}, //green for on
        {"off",Color(255,0,128)}, //puple for  off (red-green blindness accessibility)
        {"unknown",Color(255,192,0)}, //yellow for unknown
        {"unavailable",Color(255,64,0)} //red for unavailable
    };
    Color c = Color(255,255,255); 
    if (state_to_color.find(ha_state) != state_to_color.end()) c = state_to_color[ha_state]; //color found
    auto call = led->turn_on();
    call.set_rgb(c.red,c.green,c.blue);
    if (ha_state == "unavailable")call.set_effect("blink");
    call.perform();
}

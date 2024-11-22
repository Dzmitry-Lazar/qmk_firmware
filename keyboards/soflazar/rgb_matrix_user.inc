// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t array[] = {1, 3, 5, 7, 9, 11, 13, 15, 20, 21, 27, 29, 34, 35, 41, 43, 45, 47, 49, 51};
static uint8_t hue        = 0;
// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    
    hue += 1; // Increment hue to cycle through colors
    if (hue > 255) hue = 0;

    HSV     hsv   = rgb_matrix_config.hsv;
    //uint8_t scale = scale8(64, rgb_matrix_config.speed);

    uint8_t skipIndex = 0;
    int     arrLen    = sizeof(array) / sizeof(array[0]);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // The y range will be 0..64, map this to 0..4
        // Relies on hue being 8-bit and wrapping

        uint8_t skip = 0;
        if (skipIndex < arrLen) {
            skip = array[skipIndex];
        }
        if (i == skip) {
            hsv.h   = 100;
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            skipIndex++;
        } else {
            hsv.h   = hue; // rgb_matrix_config.hsv.h + scale * (g_led_config.point[i].y >> 4);
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);

            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include <esc/program.h>

#include <esc/helpers.h>
#include <esc/motor.h>
#include <esc/timing.h>
#include <esc/encoder.h>
#include <esc/semihost_debug.h>

#include <stdio.h>

void program_init(void) {
    // Calibrate the encoder
    motor_set_mode(MOTOR_MODE_ENCODER_CALIBRATION);
}

void program_event_adc_sample(float dt) {
    motor_update_state(dt);

    static uint32_t last_print_ms = 0;
    uint32_t tnow_ms = millis();
    if (tnow_ms-last_print_ms > 100) {
        float angle = encoder_get_angle_rad()*180.0f/M_PI_F;
        semihost_debug_printf("encoder angle = %.6f\n", angle);
        last_print_ms = tnow_ms;
    }

    motor_run_commutation(dt);
}

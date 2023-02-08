#ifndef _LED_H
#define _LED_H

extern int init_pwm_led(void);
extern const struct pwm_dt_spec get_pwm_led_dt(void);

#endif /* _LED_H */
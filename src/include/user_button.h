#ifndef _USER_BUTTON_H_
#define _USER_BUTTON_H_

enum button_evt {
    BUTTON_EVT_PRESSED,
    BUTTON_EVT_RELEASED
};

typedef void (*button_event_handler_t)(enum button_evt evt);

extern int button_init(button_event_handler_t handler);

#endif /* _USER_BUTTON_H_ */
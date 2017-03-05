#pragma once

enum button_event {
    BUTTON_EVENT_NONE,
    BUTTON_EVENT_PRESS,
    BUTTON_EVENT_LONG_PRESS,
};

enum button_event button_event();

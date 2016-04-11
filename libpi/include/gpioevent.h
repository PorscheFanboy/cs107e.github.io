
enum {
    GPIO_RISING_EDGE        = 0,
    GPIO_FALLING_EDGE       = 1,
    GPIO_ASYNC_RISING_EDGE  = 2,
    GPIO_ASYNC_FALLING_EDGE = 3,
    GPIO_HIGH_LEVEL         = 4,
    GPIO_LOW_LEVEL          = 5
};
void gpio_detect_falling_edge(unsigned pin);
void gpio_detect_rising_edge(unsigned pin);
void gpio_detect_async_rising_edge(unsigned pin);
void gpio_detect_async_falling_edge(unsigned pin);
void gpio_detect_high_level(unsigned pin);
void gpio_detect_low_level(unsigned pin);
unsigned gpio_check_event(unsigned pin);
void gpio_clear_event(unsigned pin);
unsigned gpio_check_and_clear_event(unsigned pin);

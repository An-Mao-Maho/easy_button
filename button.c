#include "button.h"
#include "multi_button.h"
#include "main.h"

struct _Button btn1, btn2, btn3, btn4;

uint8_t read_button_gpio(uint8_t button_id)
{
    switch (button_id) {
        case 1:
            return HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);
        case 2:
            return HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin);
        case 3:
            return HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin);
        case 4:
            return HAL_GPIO_ReadPin(BTN4_GPIO_Port, BTN4_Pin);
        default:
            return 0;
    }
}

void btn1_press_down(Button *btn) {
    (void) btn;
    key1_press_down();
}

void btn1_long_press_start(Button *btn) {
    (void) btn;
    key1_long_press_start();
}

void btn1_press_up(Button *btn) {
    (void) btn;
    key1_press_up();
}

void btn1_double_click(Button *btn) {
    (void) btn;
    key1_double_click();
}

void btn2_press_down(Button *btn) {
    (void) btn;
    key2_press_down();
}

void btn2_long_press_start(Button *btn) {
    (void) btn;
    key2_long_press_start();
}

void btn2_press_up(Button *btn) {
    (void) btn;
    key2_press_up();
}

void btn2_double_click(Button *btn) {
    (void) btn;
    key2_double_click();
}

void btn3_press_down(Button *btn) {
    (void) btn;
    key3_press_down();
}


void btn3_long_press_start(Button *btn) {
    (void) btn;
    key3_long_press_start();
}

void btn3_press_up(Button *btn) {
    (void) btn;
    key3_press_up();
}

void btn3_double_click(Button *btn) {
    (void) btn;
    key3_double_click();
}

void btn4_press_down(Button *btn) {
    (void) btn;
    key4_press_down();
}

void btn4_long_press_start(Button *btn) {
    (void) btn;
    key4_long_press_start();
}

void btn4_press_up(Button *btn) {
    (void) btn;
    key4_press_up();
}

void btn4_double_click(Button *btn) {
    (void) btn;
    key4_double_click();
}

void initialize_and_attach_callbacks(Button* btn, uint8_t button_id, uint8_t active_level, BtnCallback press_down_cb, BtnCallback long_press_start_cb, BtnCallback press_up_cb, BtnCallback double_click_cb) {
    button_init(btn, read_button_gpio, active_level, button_id);
    if (press_down_cb) {
        button_attach(btn, BTN_PRESS_DOWN, press_down_cb);
    }
    if (long_press_start_cb) {
        button_attach(btn, BTN_LONG_PRESS_START, long_press_start_cb);
    }
    if (press_up_cb) {
        button_attach(btn, BTN_PRESS_UP, press_up_cb);
    }
    if (double_click_cb) {
        button_attach(btn, BTN_DOUBLE_CLICK, double_click_cb);
    }
    button_start(btn);
}

void buttons_init(void) {
    initialize_and_attach_callbacks(&btn1, 1, BTN1_ACTIVE_LEVEL, btn1_press_down, btn1_long_press_start, btn1_press_up, btn1_double_click);
    initialize_and_attach_callbacks(&btn2, 2, BTN2_ACTIVE_LEVEL, btn2_press_down, btn2_long_press_start, btn2_press_up, btn2_double_click);
    initialize_and_attach_callbacks(&btn3, 3, BTN3_ACTIVE_LEVEL, btn3_press_down, btn3_long_press_start, btn3_press_up, btn3_double_click);
    initialize_and_attach_callbacks(&btn4, 4, BTN4_ACTIVE_LEVEL, btn4_press_down, btn4_long_press_start, btn4_press_up, btn4_double_click);
}

__attribute__((weak)) void key1_press_down(void){}
__attribute__((weak)) void key1_long_press_start(void){}
__attribute__((weak)) void key1_press_up(void){}
__attribute__((weak)) void key1_double_click(void){}
__attribute__((weak)) void key2_press_down(void){}
__attribute__((weak)) void key2_long_press_start(void){}
__attribute__((weak)) void key2_press_up(void){}
__attribute__((weak)) void key2_double_click(void){}
__attribute__((weak)) void key3_press_down(void){}
__attribute__((weak)) void key3_long_press_start(void){}
__attribute__((weak)) void key3_press_up(void){}
__attribute__((weak)) void key3_double_click(void){}
__attribute__((weak)) void key4_press_down(void){}
__attribute__((weak)) void key4_long_press_start(void){}
__attribute__((weak)) void key4_press_up(void){}
__attribute__((weak)) void key4_double_click(void){}

void button_timer_irq_handler(TIM_HandleTypeDef *htim) {
    if (htim->Instance == BUTTON_TIMER) {
        button_ticks();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    button_timer_irq_handler(htim);
}

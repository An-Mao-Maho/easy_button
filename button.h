#ifndef BUTTON_H
#define BUTTON_H
// -------------------------- 按芯片系列修改这行 ----------------------------
#include "stm32f1xx_hal_tim.h"
// --------------------------- 用户需修改下列宏 -----------------------------
#define BUTTON_TIMER TIM2    // 按键定时器（5ms）
#define BTN1_ACTIVE_LEVEL 0  // 按键有效电平（0或1）
#define BTN2_ACTIVE_LEVEL 0
#define BTN3_ACTIVE_LEVEL 0
#define BTN4_ACTIVE_LEVEL 0
// --- 按键对应引脚，推荐CubeMX直接将按键引脚命名为KEY1234，或自行修改下列宏定义 ---
#define BTN1_GPIO_Port KEY1_GPIO_Port
#define BTN1_Pin       KEY1_Pin
#define BTN2_GPIO_Port KEY2_GPIO_Port
#define BTN2_Pin       KEY2_Pin
#define BTN3_GPIO_Port KEY3_GPIO_Port
#define BTN3_Pin       KEY3_Pin
#define BTN4_GPIO_Port KEY4_GPIO_Port
#define BTN4_Pin       KEY4_Pin
// ------------- 库对外提供的接口（用户按需选择并实现所需功能即可）---------------
extern void key1_press_down(void);       //按键按下
extern void key1_long_press_start(void); //长按
extern void key1_press_up(void);         //按键抬起
extern void key1_double_click(void);     //双击

extern void key2_press_down(void);
extern void key2_long_press_start(void);
extern void key2_press_up(void);
extern void key2_double_click(void);

extern void key3_press_down(void);
extern void key3_long_press_start(void);
extern void key3_press_up(void);
extern void key3_double_click(void);

extern void key4_press_down(void);
extern void key4_long_press_start(void);
extern void key4_press_up(void);
extern void key4_double_click(void);
// -----------------------------------------------------------------------
/**
  * @brief  按键库初始化函数
  * @note   需在系统初始化（HAL_Init、时钟配置）完成后调用，仅需初始化一次
  * @param  无
  * @retval None
  * @attention 初始化完成后，需确保按键定时器已启动（中断5ms触发一次）。
  */
void buttons_init(void);

/**
 * @brief  按键定时器中断处理函数（核心接口）
 * @note   用户重写HAL_TIM_PeriodElapsedCallback时，需调用此函数
 * @param  htim: 定时器句柄（由中断回调传入）
 */
void button_timer_irq_handler(TIM_HandleTypeDef *htim);

#endif //BUTTON_H
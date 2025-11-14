# STM32 按键库（HAL 库版）
**零门槛，使用简单**的 STM32 按键库，支持消抖、单击/长按/双击，适配全系列 STM32 芯片。
（仅需必要的配置，实现接口函数即可实现按键功能）

## 一、快速上手（3步搞定）

### 1. CubeMx 配置
#### ① 按键 GPIO 配置
1. 打开 CubeMx → 选择芯片；
2. 按键对应引脚配置为「GPIO_Input」；
3. 右键按键引脚点击Enter User Label修改用户标签为KEY1,KEY2,KEY3,KEY4(最多4个按键)
4. 「Pull-up/Pull-down」根据按键实际情况选择。

#### ② 定时器配置（5ms 中断）（主频72MHz，TIM2 为例）
1. 「Timers」→ 选择TIM2 → Clock Source → 选择internal Clock；
2. 「Parameter Settings」：
    - Prescaler：7199（72MHz 时钟 → 10kHz 计数，1个计数=100us）；
    - Counter Period：49（100us × 50 = 5ms，计数到49触发中断）；
3. 「NVIC Settings」→ 勾选「TIM2 global Interrupt」→ 使能中断（优先级默认）；
4.  生成代码。

### 2. 代码集成
1. 下载 `button.h`、`button.c`、`multi_button.h`、`multi_button.c`；
2. 复制到项目 `Core/Src`（.c）和 `Core/Inc`（.h）；
3. 或者直接将button文件夹复制到Drivers或其他文件夹下，自行配置路径。

### 3. 库配置（修改 `button.h`）
```c
// 1. 按芯片改 HAL 头文件（F4/L4/G4 等）
#include "stm32f1xx_hal.h"

// 2. 配置按键定时器（和 CubeMx 一致）
#define BUTTON_TIMER TIM2 //若用其他定时器，改为对应定时器

// 3. 配置按键有效电平，低电平有效为 0，高电平有效为 1。
#define BTN1_ACTIVE_LEVEL 0

// 4. 按键对应引脚，若按键标签修改为KEY1、KEY2、KEY3、KEY4，则无需修改。否则自行修改下列宏定义。
#define BTN1_GPIO_Port KEY1_GPIO_Port
#define BTN1_Pin       KEY1_Pin
......

// 5. 如需修改消抖时长，打开`multi_button.h`，修改下列行
#define DEBOUNCE_TICKS 1 // MAX 7 (0 ~ 7) - debounce filter depth
```

## 二、按键库初始化和按键功能函数的实现

### 1.按键库初始化
在系统初始化（HAL_Init、时钟配置）完成后调用buttons_init()，仅需初始化一次。

### 2.在你的应用程序里按需选择并实现下列函数，按键中断触发后会运行你所实现的函数内容
```c
void key1_press_down(void);       //按键按下
void key1_long_press_start(void); //长按
void key1_press_up(void);         //按键抬起
void key1_double_click(void);     //双击
......
```

### 3.适配中断回调
- 若你不重写 HAL_TIM_PeriodElapsedCallback → 无需操作，直接编译运行；
- 若你重写了该回调 → 在你的回调中第一行调用 button_timer_irq_handler(htim)。
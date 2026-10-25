# Pinout - Motion-Mirroring Teleoperator (STM32C031C6, LQFP48)

> Джерело істини: `firmware/*.ioc` (STM32CubeMX) та `firmware/Core/Src/stm32c0xx_hal_msp.c`.
> Посилання: DS13619 (STM32C031C6 datasheet), RM0490 (Reference manual), UM1724 (Nucleo-64 user manual).

## 1. Зведена таблиця

| Пін МК | AF | Периферійний блок / сигнал | Nucleo (Morpho / Arduino) | Пін пристрою | Рівень | Pull-up/down | Джерело |
|---|---|---|---|---|---|---|---|
| PB8  | AF6 | I2C1_SCL | CN10-3 / D15 | MPU SCL, LCD SCL | 3.3 V | 4.7 kΩ на модулі GY-521 | DS13619 Table 15, RM0490 §24 |
| PB9  | AF6 | I2C1_SDA | CN10-5 / D14 | MPU SDA, LCD SDA | 3.3 V | 4.7 kΩ на модулі | DS13619 Table 15 |
| PA5  | AF0 | SPI1_SCK | CN10-11 / D13 | W25Q64 CLK | 3.3 V | - | DS13619 Table 14 |
| PA6  | AF0 | SPI1_MISO | CN10-13 / D12 | W25Q64 DO | 3.3 V | - | DS13619 Table 14 |
| PA7  | AF0 | SPI1_MOSI | CN10-15 / D11 | W25Q64 DI | 3.3 V | - | DS13619 Table 14 |
| PB6  | GPIO_OUT | SPI1_CS (software) | CN10-17 / D10 | W25Q64 /CS | 3.3 V | 10 kΩ на модулі | RM0490 §8.3.10 |
| PB0  | AF1 | TIM3_CH3 (PWM) | CN10-19 / D9 | SG92R signal | 3.3 V | - | AN4776 §3.3 |
| PA2  | AF1 | USART2_TX | CN10-21 / D1 | ST-Link VCP RX | 3.3 V | - | UM1724 §6.8 |
| PA3  | AF1 | USART2_RX | CN10-23 / D0 | ST-Link VCP TX | 3.3 V | - | UM1724 §6.8 |
| PA0  | Analog | ADC1_IN0 | CN8-1 / A0 | Potentiometer wiper | 0–3.3 V | - | DS13619 Table 15 |

## 2. Таблиця адрес та ідентифікаторів

| Пристрій | Шина | 7-bit адреса | Ідентифікатор | Очікуване значення | Джерело |
|---|---|---|---|---|---|
| MPU-6050 | I2C1 | 0x68 (AD0=GND) | WHO_AM_I (0x75) | 0x68 | MPU-6000 Register Map, §4.34 |
| LCD1602+PCF8574 | I2C1 | 0x27 | - | - | PCF8574 datasheet |
| W25Q64 | SPI1 | - | JEDEC ID (0x9F) | 0xEF 0x40 0x17 | W25Q64JV datasheet §7.4 |

## 3. Бюджет живлення

| Пристрій | Idle | Peak | Джерело | Запас 3V3 Nucleo (300 mA) |
|---|---|---|---|---|
| MPU-6050 (GY-521) | 3.9 mA | 5 mA | 3V3 | - |
| LCD1602 + PCF8574 | 20 mA | 25 mA | 5V | - |
| W25Q64 | 4 mA | 15 mA | 3V3 | - |
| SG92R × 2 | 10 mA | 1400 mA | **окреме джерело 5V/2A** | ❌ **не** від Nucleo |

## 4. Відхилені варіанти

**Варіант 1: PWM servo на PA6 (TIM3_CH1)** - відхилено, бо PA6 на C031C6 використовується як SPI1_MISO. Конфлікт з W25Q64. Рішення - перенесли PWM на PB0.
**Варіант 2: Окрема I²C-шина для LCD (I2C2 на PB10/PB11)** - відхилено, бо виводи PB10/PB11 у LQFP48 зайняті SWD (SWO). Спільна шина з MPU не створює конфлікту адрес.
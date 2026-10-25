# Лабораторна робота №1 — Motion-Mirroring Teleoperator

**Курс:** Системне програмування вбудованих систем
**Форма:** B (Wokwi Simulator)
**Автор:** Штифлюк Ольга Володимирівна
**Платформа:** NUCLEO-C031C6 (STM32C031C6)

## Про проєкт

Система дзеркалення руху руки на сервоприводах. Оператор одягає IMU MPU-6050, а сервопривід повторює рухи. Демонструє I²C, SPI, ADC, PWM, UART через HAL.

## Структура

- `docker/` — Dockerfile для ARM-тулчейну
- `firmware/` — CubeMX-згенерований проєкт (Core, Drivers, Makefile)
- `docs/` — PRD, hardware-components, report
- `wokwi.toml` — конфігурація Wokwi
- `diagram.json` — схема підключень

## Як зібрати

```bash
make build
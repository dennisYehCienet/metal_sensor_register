#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <hal/nrf_gpio.h>  // 引入 GPIO 控制的庫

#define LED_PIN NRF_GPIO_PIN_MAP(0,13)     // LED 連接的引腳號（根據實際情況確認）
#define SENSOR_PIN NRF_GPIO_PIN_MAP(0,28)   // 傳感器 D0 連接的引腳號 (P0.28)

void setup() {
        nrf_gpio_cfg_output(LED_PIN);          // 設定 LED 引腳為輸出
        nrf_gpio_cfg_input(SENSOR_PIN, NRF_GPIO_PIN_NOPULL); // 設定 Pin28 引腳為輸入
        nrf_gpio_pin_set(LED_PIN);           // 初始化時將 LED 設置為關閉
}

int main(void) {
	setup();

	while (1) {	
		// toggle the LED once the sensor triggered.
		k_msleep(500); // 每秒檢查一次
                // 讀取傳感器的輸出
                int sensor_value = nrf_gpio_pin_read(SENSOR_PIN);
                printk("Sensor value: %d\n", sensor_value); // 打印傳感器的數值
                
                static bool led_state = false; // 記錄 LED 的當前狀態
                if (sensor_value == 1) { // 如果 D0 輸出高電平
                        // 切換 LED 狀態
                        led_state = !led_state; // 切換 LED 狀態
                        if (led_state) {
                                nrf_gpio_pin_set(LED_PIN); // 關閉內建 LED
                                printk("LED OFF.\n");
                        } else {
                                nrf_gpio_pin_clear(LED_PIN); // 開啟內建 LED
                                printk("LED ON.\n");
                        }
                        k_msleep(50);
                }
	}
}

#include "ti_msp_dl_config.h"

int main() {
    SYSCFG_DL_init();
    while (1) {
        DL_GPIO_togglePins(LED_PORT, LED_PIN_0_PIN);
        delay_cycles(32000000);
    }
    return 0;
}

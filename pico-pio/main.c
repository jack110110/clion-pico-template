#include "pico/stdlib.h"
#include <stdio.h>
#include <hardware/clocks.h>
#include <hardware/pio.h>
#include "hardware/structs/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/pll.h"
#include "pico-pio.pio.h"

void measure_freqs(void){
    uint f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    uint f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    uint f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    uint f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    uint f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    uint f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    uint f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
    uint f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);

    printf("pll_sys  = %dkHz\n", f_pll_sys);
    printf("pll_usb  = %dkHz\n", f_pll_usb);
    printf("rosc     = %dkHz\n", f_rosc);
    printf("clk_sys  = %dkHz\n", f_clk_sys);
    printf("clk_peri = %dkHz\n", f_clk_peri);
    printf("clk_usb  = %dkHz\n", f_clk_usb);
    printf("clk_adc  = %dkHz\n", f_clk_adc);
    printf("clk_rtc  = %dkHz\n", f_clk_rtc);
}
int main()
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    PIO pio = pio0;
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    sleep_ms(5000);
    measure_freqs();
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    48 * MHZ,
                    48 * MHZ
    );
    pll_deinit(pll_sys);

    clock_configure(clk_peri,
                    0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                    48 * MHZ,
                    48 * MHZ);
    stdio_init_all();
    measure_freqs();
    printf("Hello 48Mhz");

    uint offset = pio_add_program(pio,&main_program);
    uint sm = pio_claim_unused_sm(pio,true);
    main_program_init(pio,sm,offset,1);

    while (true)
    {
//        gpio_put(LED_PIN, 1);
//        //printf("hello world1\n");
//        sleep_ms(500);
//        gpio_put(LED_PIN, 0);
//        //printf("hello world2\n");
//        sleep_ms(500);
        /*  全速
         * 延时的最小1us不是很准
         * 1.5MHz 41%占空比
         * */
        pio_sm_put_blocking(pio,sm,1);
//        sleep_us(1);
        pio_sm_put_blocking(pio,sm,0);
//        sleep_us(1);

    }
}
//==========================================================
// -- Bibliotecas externas ---
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include <driver/adc.h>
#include <esp_adc_cal.h>
#include "sdkconfig.h"

//==========================================================
// -- Mapeamento de Hardware ---

#define POTENCIOMETRO_1 ADC1_CHANNEL_0
#define LED_1  14
#define LED_2  27
#define LED_3  26
#define BTN_1  33
#define BTN_2  32



// ADC
esp_adc_cal_characteristics_t adc_cal;        //Estrutura que contem as informacoes para calibracao


//==========================================================
// -- Criação Tasks ---

void vTaskPotenciometro_1 (void * params)
{
    // CALIBRACAO ADC ESP
    adc1_config_width(ADC_WIDTH_BIT_12);                          // Resolucao 12 bits
    adc1_config_channel_atten(POTENCIOMETRO_1, ADC_ATTEN_DB_11);   // Atenuacao 11dB
    esp_adc_cal_value_t adc_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_cal);   // Funcao de calibracao

    while(true)
    {
        int leitura_potenciometro_1 = 0;
        leitura_potenciometro_1 = adc1_get_raw(POTENCIOMETRO_1);
        leitura_potenciometro_1 =esp_adc_cal_raw_to_voltage(leitura_potenciometro_1, &adc_cal);
        printf("ADC: %dmV\n ",leitura_potenciometro_1);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}




void app_main(void)
{

    xTaskCreate(vTaskPotenciometro_1,"Leitura potenciometro 1",2048,NULL,1,NULL);

}

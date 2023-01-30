#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_flash.h"

#include "mupeWifi.h"
#include "mupeMdnsNtp.h"
#include "mupeMQTT.h"
#include "mupeWeb.h"





void init() {
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES
			|| ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	mupeWifiInit();
	mupeMdnsNtpInit();
	mupeMqttInit();
	mupeWebInit();


}

void app_main(void) {

	init();
    xTaskCreatePinnedToCore(mupeMqttServerTask, "mupeMQTT_server_task",4096, NULL, 1, NULL, 0);


}

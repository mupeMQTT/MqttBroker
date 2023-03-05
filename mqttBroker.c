
// Copyright Peter Müller mupe
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_flash.h"

#include "mupeWifi.h"
#include "mupeMdnsNtp.h"
#include "mupeMQTT.h"
#include "mupeWeb.h"
#include "mupeModbusMQTT.h"
#include "mupeClientMqtt.h"
#include "mupeSdCard.h"



void init() {
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES
			|| ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
	mupeSdCardInit();
	mupeWifiInit();
	mupeMdnsNtpInit();
	mupeMqttInit();
	mupeModbusInit();
	mupeClientMqttInit();
	mupeWebInit();
}

void app_main(void) {
	init();
    xTaskCreatePinnedToCore(mupeMqttServerTask, "mupeMQTT_server_task",4096, NULL, 1, NULL, 0);
}

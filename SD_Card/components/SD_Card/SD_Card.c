#include "SD_Card.h"
#include "esp_vfs_fat.h" //fatfs headder file
#include "sdmmc_cmd.h"

sdmmc_card_t* card;
esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = true,
    .max_files = 5,
    .allocation_unit_size = 8 * 1024
};

//mount the sd card 
void mount_sdcard(void) {
    ESP_LOGI(TAG, "Initializing SD card");

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = SPI_MOSI_GPIO,
        .miso_io_num = SPI_MISO_GPIO,
        .sclk_io_num = SPI_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SPI bus");
        return;
    }

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = SPI_CS_GPIO;
    slot_config.host_id = SPI2_HOST;

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    ret = esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_config, &mount_config, &card);  // Mount only the directory
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount SD card: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG, "SD card mounted successfully");
    sdmmc_card_print_info(stdout, card);
}

//write 
void write_to_sdcard(const char* data) {
    FILE* f = fopen(MOUNT_POINT, "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file: %s", MOUNT_POINT);
        return;
    }
    fprintf(f, "%s\n", data);
    fclose(f);
    ESP_LOGI(TAG, "Data written to %s", MOUNT_POINT);
}

//append
void append_to_sdcard(const char* data) {
    FILE* f = fopen(MOUNT_POINT, "a");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file: %s", MOUNT_POINT);
        return;
    }
    fprintf(f, "%s\n", data);
    fclose(f);
    ESP_LOGI(TAG, "Data appended to %s", MOUNT_POINT);
}

//read
void read_from_sdcard(void) {
    FILE* f = fopen(MOUNT_POINT, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file: %s", MOUNT_POINT);
        return;
    }
    
    char line[128];
    ESP_LOGI(TAG, "Reading from %s:", MOUNT_POINT);
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);
}

//delete
void delete_file(void) {
    esp_err_t ret = remove(MOUNT_POINT);  // Delete the file
    if (ret == 0) {
        ESP_LOGI(TAG, "File deleted successfully: %s", MOUNT_POINT);
    } else {
        ESP_LOGE(TAG, "Failed to delete file: %s", MOUNT_POINT);
    }
}

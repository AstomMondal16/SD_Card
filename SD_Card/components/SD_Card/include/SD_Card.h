#ifndef SD_CARD_H
#define SD_CARD_H

#include "esp_log.h"
#include "esp_vfs_fat.h" //fatfs headder file
#include "driver/spi_master.h"
#include "sdmmc_cmd.h"

#define TAG "SD_CARD"

#define MOUNT_POINT "/sdcard/test.csv"  // Define full file path here

// Define SPI pins for the sd card
#define SPI_MOSI_GPIO 46
#define SPI_MISO_GPIO 2
#define SPI_SCLK_GPIO 1
#define SPI_CS_GPIO 8

//function used in the source file
void mount_sdcard(void);
void write_to_sdcard(const char* data);
void append_to_sdcard(const char* data);
void read_from_sdcard(void);
void delete_file(void);

#endif // SD_CARD_H

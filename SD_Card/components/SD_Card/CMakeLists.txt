idf_component_register(SRCS "SD_Card.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver fatfs sdmmc)

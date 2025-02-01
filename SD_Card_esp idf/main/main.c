#include "SD_Card.h"

void app_main(void) {
    mount_sdcard();//init the sd_card
    
    const char* data = "enter the data to store in the sd card";// data that is storing in the sd_card
    
    write_to_sdcard(data);//to write the data in the file
    append_to_sdcard(data);//to append the data in the file
    read_from_sdcard();//read the data from the file
    delete_file();  // Call the delete function
}

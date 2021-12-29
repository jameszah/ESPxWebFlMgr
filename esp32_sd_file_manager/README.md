![screen](https://github.com/jameszah/ESPxWebFlMgr/blob/master/esp32_sd_file_manager/screen.jpg)

Circles from top to bottom

1. SD card size and free space
2. Click here to return to the root directory of SD card
3. Folders are colored whitish, click to enter folder, files alternate with the orange/blue
4. Click on the file to download it to your browser/computer
5. Size of the file in bytes
6. D for delete the file
7. R for rename the file
8. E for edit the file - only for text files
9. Make a zip or all files and download

Notes:
1.  Drag and drop files from your computer to your browser at "File Drop Zone", and they will upload to current folder
2.  Downloading files from subfolder gives the name "subfolder_file.txt" rather than creating a subfolder on your computer
3.  When you download zip, the zip will contain the subfolders with proper filenames
4.  Download is about 3.5 Mbps for regular files, and less for zips depending on the other cpu reqirements on your esp32
5.  Zero size files cannot be downloaded individually, but can within a zip (i think ?)
6.  See here for adding file manager to your own project https://github.com/jameszah/ESP32-CAM-Video-Recorder-junior

You just need to add the include, and the two calls as below:

```
#include "ESPxWebFlMgr.h"
const word filemanagerport = 8080;
ESPxWebFlMgr filemgr(filemanagerport); 

void setup(){
  filemgr.begin();
}

void loop() {
  filemgr.handleClient();
}
```

esp32_sd_file_manager  

  This is a esp32 program that lets you move files back and forth between your Windows/Android/etc 
  web browser and the SD card on a ESP32 module.  This is just a  demo program to show how to use the 
  libraries to add the file transfer to esp32 projects that need easy ad-hoc access to the esp32 storage.
  The program allows you to upload download files, edit files, and download entire folders as a zip file.
  Also allows access for the sub-directories of the sd card using the FAT32 format.
  
  https://github.com/jameszah/ESPxWebFlMgr  
  
  Amusing MIT licencse here:   
  https://github.com/jameszah/ESPxWebFlMgr/blob/master/LICENSE  
  https://github.com/holgerlembke/ESPxWebFlMgr/blob/master/LICENSE  
  
  This is based on the orignal work that does the same thing for esp8266 and esp32 using the SPIFFS and LittleFS
  file systems, which are the file systems in the flash of the esp32/8266 devices. 
  https://github.com/holgerlembke/ESPxWebFlMgr
  
  These mods are Dec 28, 2021 by James Zahary and are stored with all necessary files.
    
  esp32_sd_file_manager.ino - 2019-07-03 https://github.com/holgerlembke/ESP8266WebFlMgr
   - this demo program (add your ssid and password to use this)
 
  CRC32.cpp and CRC32.h - by <https://christopherbaker.net> Copyright (c) 2013 Christopher Baker 
   - calculates the crc for zip files

  ESPxWebFlMgr.cpp and ESPxWebFlMgr.h - 2019-07-03 https://github.com/holgerlembke/ESP8266WebFlMgr
   - the c++ code runing on the esp32 that handles the file manager
 
  ESPxWebFlMgrWp.h - 2019-07-03 https://github.com/holgerlembke/ESP8266WebFlMgr
   - this is the html javascript and css that the esp32 sends to your browser to interact with the c++ code on esp32

  ESPxWebFlMgrWpF.f - 2019-07-03 https://github.com/holgerlembke/ESP8266WebFlMgr
   - similar file for the in-place file editor function.

  All files (except crc and web edit include) have small mods to implement this project.
  See the github site for some photos with insctructions.
  As well, if you can interact with the esp32 code with simple http commands, if you want to access the files with a python and javascript
  program, rather than a human with a web browser.
  
  http://192.168.1.82/ - assume your esp32 establishes this web site (and your project uses this)  
  http://192.168.1.82:8080/ - this is the file manager web page operating in parallel to your project web sire  
  http://192.168.1.82:8080/i - quick simple list of files in the sd root  
  http://192.168.1.82:8080/i?subdir=/20211102b - quick simple directory of 20211102b folder  
  http://192.168.1.82:8080/c?dwn=/desklens42.007.avi - download the file from root "desklens42.avi"  
  ... commands for deleting renaming editing etc all in the code  
  

![screen](https://github.com/jameszah/ESPxWebFlMgr/blob/master/esp32_sd_file_manager/screen.jpg)

Circles from top to bottom

1. SD card size and used space
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
5.  Zero size files cannot be downloaded within a zip so are ignored
6.  See here for adding file manager to your own project https://github.com/jameszah/ESP32-CAM-Video-Recorder-junior

You just need to add the include, declaration and the two calls as below:

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

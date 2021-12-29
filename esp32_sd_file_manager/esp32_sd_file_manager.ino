
/*

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

  This mods are Dec 28, 2021 by James Zahary and are stored with all necessary files.
    
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

Using library WiFi at version 1.0 in folder: C:\ArduinoPortable\arduino-1.8.13\portable\packages\esp32\hardware\esp32\1.0.6\libraries\WiFi 
Using library FS at version 1.0 in folder: C:\ArduinoPortable\arduino-1.8.13\portable\packages\esp32\hardware\esp32\1.0.6\libraries\FS 
Using library SD_MMC at version 1.0 in folder: C:\ArduinoPortable\arduino-1.8.13\portable\packages\esp32\hardware\esp32\1.0.6\libraries\SD_MMC 
Using library WebServer at version 1.0 in folder: C:\ArduinoPortable\arduino-1.8.13\portable\packages\esp32\hardware\esp32\1.0.6\libraries\WebServer 
"C:\\ArduinoPortable\\arduino-1.8.13\\portable\\packages\\esp32\\tools\\xtensa-esp32-elf-gcc\\1.22.0-97-gc752ad5-5.2.0/bin/xtensa-esp32-elf-size" -A "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_569425/esp32_sd_file_manager.ino.elf"
Sketch uses 903762 bytes (28%) of program storage space. Maximum is 3145728 bytes.
Global variables use 39564 bytes (12%) of dynamic memory, leaving 288116 bytes for local variables. Maximum is 327680 bytes.

   
 */


#include <WiFi.h>
#include <FS.h>
#include <SD_MMC.h> 

#include "ESPxWebFlMgr.h"

const word filemanagerport = 8080;

const String hlssid ="...";
const String hlpwd = "...";

ESPxWebFlMgr filemgr(filemanagerport); // we want a different port than the webserver

void setup() {
  // the usual Serial stuff....
  Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }
  Serial.println("\n\n esp32_sd_file_manager"); // BASIC and WebServer And GZIPper

  if (!SD_MMC.begin("/sdcard",true)) { 
    Serial.println("SD_MMC Mount Failed");  
    return;
  }

  // login into WiFi
  WiFi.begin(hlssid.c_str(), hlpwd.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Open Filemanager with http://");
    Serial.print(WiFi.localIP());
    Serial.print(":");
    Serial.print(filemanagerport);
    Serial.print("/");
    Serial.println();

  }

  filemgr.begin();
  filemgr.setBackGroundColor("Gray");
}

void loop() {
  filemgr.handleClient();
}

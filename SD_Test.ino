#include <SD.h>
#include <SPI.h>

File file;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Initialising SD Card...");
  if (!SD.begin(4)) {
    Serial.println("Card Failed!");
    return;
  }

  Serial.println("SD Card Initialised!");

  Serial.println("Creating File...");

  file = SD.open("log.txt", FILE_WRITE);
  file.close();

  Serial.println("File Created!");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (millis() < 10000) {
    if (SD.exists("log.txt")) {
      Serial.println("File Exists!");

      file = SD.open("log.txt", FILE_WRITE);

      if (file) {
        Serial.println("Ok, we can write!");
        file.println("Hello, the time is: " + String(millis()));
        file.close();
      } else {
        Serial.println("We can't write!");
      }
    } else {
      Serial.println("File Doesn't Exist!");
    }

    delay(1000);
  }

  if (millis() > 10000 && millis() < 20000) {
    file = SD.open("log.txt");
    if (file) {
      Serial.println("Ok, we can read!");
      while (file.available()) {
        Serial.write(file.read());
      }
      file.close();
    } else {
      Serial.println("We can't read!");
    }
    delay(2000);
  }

  if (millis() > 20000) {
    Serial.println("Preparing to Delete...");
    SD.remove("log.txt");

    if (!SD.exists("log.txt")) {
      Serial.println("File Deleted!");
    } else {
      Serial.println("File Not Deleted!");
    }
  }
}

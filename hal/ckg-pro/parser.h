

#include <Arduino.h>

#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

void addButton(int screenIndex, int index, String label, int x, int y, int w, int h, String icon);

void parse() {

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }

  // Open the config file
  File file = SPIFFS.open("/config.json", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Allocate a buffer to store contents of the file
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);

  // Read the file into the buffer
  file.readBytes(buf.get(), size);

  // Parse the JSON
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.print("Failed to parse file: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract the widgets array
  JsonArray widgets = doc["widgets"];

  // Iterate over the widgets
  int index = 0;
  for (JsonObject widget : widgets) {
    String label = widget["label"].as<String>();
    int x = widget["x"];
    int y = widget["y"];
    int w = widget["w"];
    int h = widget["h"];
    const char* icon = widget["icon"];
    JsonArray commands = widget["commands"];

    Serial.printf("Widget label: %s, x: %d, y: %d, w: %d, h: %d, icon: %s\n", label, x, y, w, h, icon);
    addButton(0, index, label, x, y, w, h, icon);
    for (const char* command : commands) {
      Serial.printf("  Command: %s\n", command);
    }
    index++;
  }

  // Close the file
  file.close();
}

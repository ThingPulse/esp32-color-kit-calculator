


//#include <ArduinoJson.h>
//#include <iostream>
//#include <fstream>
//#include <string>

//void addButton(int index, String label, int x, int y, int w, int h, String icon);

/*char* load_file_to_buffer(const char* file_path, size_t& file_size) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate); // Open file in binary mode and move the cursor to the end
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return nullptr;
    }

    // Get file size
    file_size = file.tellg();
    file.seekg(0, std::ios::beg); // Move the cursor back to the start

    // Allocate memory for the buffer
    char* buffer = new char[file_size + 1]; // +1 for null-terminator
    file.read(buffer, file_size);

    // Null-terminate the buffer
    buffer[file_size] = '\0';

    file.close();
    return buffer;
}*/

/*void parse(char* buffer, size_t& file_size) {



  // Allocate a buffer to store contents of the file
  size_t size = file_size;


  // Parse the JSON
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buffer);
  if (error) {
    //Serial.print("Failed to parse file: ");
    //Serial.println(error.c_str());
    return;
  }

  // Extract the widgets array
  JsonArray widgets = doc["widgets"];

  // Iterate over the widgets
  int index = 0;
  for (JsonObject widget : widgets) {
    //String label = widget["label"].as<String>();
    int x = widget["x"];
    int y = widget["y"];
    int w = widget["w"];
    int h = widget["h"];
    const char* icon = widget["icon"];
    JsonArray commands = widget["commands"];

    //Serial.printf("Widget label: %s, x: %d, y: %d, w: %d, h: %d, icon: %s\n", label, x, y, w, h, icon);
    //addButton(index, label, x, y, w, h, icon);
    for (const char* command : commands) {
      //Serial.printf("  Command: %s\n", command);
    }
    index++;
  }

}*/

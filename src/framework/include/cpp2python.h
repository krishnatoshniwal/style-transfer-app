#include "libraries.h"

std::string exec(const char* cmd);

std::string make_cmd(const std::string img_path, const std::string style_path, const std::string save_path, const float x1, const float y1, const float x2, const float y2);

std::string CToPy(const std::string img_path, const std::string style_path, const std::string save_path, const float x1, const float y1, const float x2, const float y2);
#include "cpp2python.h"


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

std::string make_cmd(const std::string img_path, const std::string style_path, const std::string save_path, const float x1, const float y1, const float x2, const float y2){
    std::ostringstream oss;
    oss << "python ../../../src/iLearn/Project/arbitrary_style_transfer/main.py " << img_path << " " << style_path << " " << save_path << " " << x1 << " " << y1 << " " << x2 << " " << y2;
    std::string cmd = oss.str();
    return cmd;
}

std::string CToPy(const std::string img_path, const std::string style_path, const std::string save_path, const float x1, const float y1, const float x2, const float y2){
    auto result = exec(make_cmd(img_path,style_path,save_path,x1,y1,x2,y2).c_str());
    // printf("Result is: %s\n",result.c_str());

    return result.c_str();    
}


// auto transfer_path = CToPy("../../../src/iLearn/Project/images/dancing.jpg",
//     "../../../src/iLearn/Project/images/picasso.jpg",
//     "../../../src/iLearn/Project/images",0,100,0,100);
// printf("Transfer Path is: %s\n", transfer_path.c_str());
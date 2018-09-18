//
// Created by krishna on 4/28/18.
//

#ifndef PROJECT_BMPLOCATIONS_H
#define PROJECT_BMPLOCATIONS_H

#include "essentials.h"

namespace BmpLocations {
    /**
     * This namespace stores the location of all the BMPs used in the UI
     */
    extern std::string styleBmpLoc, contentBmpLoc, outputBmpLoc;
    extern int contentNum, numContent;

    void RemoveDotDotDot(vector<std::string> &files);

    void ReadFilesFromLoc(const std::string &path, vector<std::string> &fileLocs, vector<std::string> &fileNames);

    void ReadFileFromLoc(const std::string &path, std::string &fileLoc, std::string &fileName);

    void ReadContentBmp(const std::string &path, std::string &fileLoc, std::string &fileName, int num);

    void GetStyleBmpLocs(vector<std::string> &fileLocs, vector<std::string> &fileNames);

    void GetContentBmpLoc(std::string &fileLoc, std::string &fileName);

    void GetOutputBmpLoc(std::string &fileLoc, std::string &fileName);

    void IncrementContentNum();

    void DecrementContentNum();
}


#endif //PROJECT_BMPLOCATIONS_H

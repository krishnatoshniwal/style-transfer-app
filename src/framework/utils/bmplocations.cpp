//
// Created by krishna on 4/28/18.
//

#include "bmplocations.h"

namespace BmpLocations {
    std::string styleBmpLoc, contentBmpLoc, outputBmpLoc;
    int contentNum = 0, numContent = 1;

    void SetLocs() {
        std::string dataPath = "./images/";
        styleBmpLoc = dataPath + "style";
        contentBmpLoc = dataPath + "content";
        outputBmpLoc = dataPath + "output";
    }

    void GetStyleBmpLocs(vector<std::string> &fileLocs, vector<std::string> &fileNames) {
        SetLocs();
        ReadFilesFromLoc(styleBmpLoc, fileLocs, fileNames);
    }

    void GetContentBmpLoc(std::string &fileLoc, std::string &fileName) {
        SetLocs();
        vector<std::string> fileLocs, fileNames;
        ReadFilesFromLoc(contentBmpLoc, fileLocs, fileNames);
        numContent = fileLocs.size();
        fileLoc = fileLocs[contentNum];
        fileName = fileNames[contentNum];
    }

    void GetOutputBmpLoc(std::string &fileLoc, std::string &fileName) {
        SetLocs();
        ReadFileFromLoc(outputBmpLoc, fileLoc, fileName);
    }

    void ReadFilesFromLoc(const std::string &path, vector<std::string> &fileLocs, vector<std::string> &fileNames) {
        /**
         * Reads all the files stored in a given location and returns a vector object
         * of all the paths as strings
         */
        fileLocs.clear();
        fileNames.clear();
        DIR *dir;
        dirent *pdir;
        // Read the file dirs
        dir = opendir(path.c_str());

        while (pdir = readdir(dir)) {
            fileLocs.push_back(pdir->d_name);
        }
        RemoveDotDotDot(fileLocs);
        fileNames = fileLocs;

        for (auto &file:fileLocs) {
            // append the path to the file loc
            file = path + '/' + file;
        }
    }

    void ReadFileFromLoc(const std::string &path, std::string &fileLoc, std::string &fileName) {
        /**
         * Reads all the files in the path and returns the first file in the path
         * Useful when you only want to read one file
         */
        vector<std::string> fileLocs, fileNames;
        ReadFilesFromLoc(path, fileLocs, fileNames);
        fileLoc = fileLocs[0];
        fileName = fileNames[0];
    }
//    void ReadContentBmp(const std::string &path, std::string &fileLoc, std::string &fileName, int num){
//        vector<std::string> fileLocs, fileNames;
//        ReadFilesFromLoc(path, fileLocs, fileNames);
//        fileLoc = fileLocs[num];
//        fileName = fileNames[num];
//    }

    void RemoveDotDotDot(vector<std::string> &files) {
        /**
         * Removes ./ and ../ items from a given directory
         */
        std::string dotFile = ".", dotdotFile = "..";
        for (auto fi = files.begin(); fi != files.end(); fi++) {
            if (dotFile == *fi) {
                files.erase(fi);
                break;
            }
        }
        for (auto fi = files.begin(); fi != files.end(); fi++) {
            if (dotdotFile == *fi) {
                files.erase(fi);
                break;
            }
        }
    }

    void IncrementContentNum() {
        contentNum = (contentNum + 1) % numContent;
    }

    void DecrementContentNum() {
        contentNum = (contentNum - 1 + numContent) % numContent;
    }

}
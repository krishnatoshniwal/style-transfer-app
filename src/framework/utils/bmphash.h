//
// Created by krishna on 4/28/18.
//

#ifndef PROJECT_BMPHASH_H
#define PROJECT_BMPHASH_H

#include "essentials.h"
#include "bmplocations.h"

class BmpHash {
    /**
     * Stores all the bmps used in the UI in a hashset
     * set contains all style bmps & content, style and output bmps
     */
protected:
    class BmpHashSet {
        /**
         * The hashset records the all the bmps
         */
    protected:
        std::unordered_map<std::string, SimpleBitmap> bmpMap;
        std::unordered_map<std::string, SimpleBitmap>::const_iterator cur_item;
    public:
        void Insert(std::string str, SimpleBitmap bmp);

        SimpleBitmap GetBmp(const std::string &str);

        void CleanUp() { bmpMap.clear(); }

        ~BmpHashSet() { CleanUp(); }
    };

    class NameHashSet {
        /**
         * The hashset records the names of all the bmps
         * with the Format!
         * Call Get
         */
    protected:
        std::unordered_map<std::string, std::string> nameMap;
        std::unordered_map<std::string, std::string>::const_iterator cur_item;
    public:
        void Insert(std::string key, std::string name);

        std::string GetName(const std::string &str);

        void CleanUp() { nameMap.clear(); }

        ~NameHashSet() { CleanUp(); }
    };

    BmpHashSet bmpHashSet;
    NameHashSet nameHashSet;
//    std::pair<SimpleBitmap, std::string> bmp_name;

public:

    int nStyleImages = 0;
    bool contentPresent = false, stylePresent = false, outputPresent = false;

    void BuildHash() {
        AddAllImages();
    }

    void UpdateStyleBmps(const vector<std::string> &bmpPaths, const vector<std::string> &bmpNames);

    void UpdateStyleBmps();

    void UpdateContentBmp(const std::string &bmpLoc, const std::string &bmpName);

    void UpdateContentBmp();

    void SetStyleBmp(int num);

    void UpdateOutputBmp(const std::string &bmpLoc, const std::string &bmpName);

    void AddAllImages();

    void AddStylesBmp(const std::string &bmpPath, const std::string &bmpName);

    // Get Bmp functions

    SimpleBitmap GetBmp(const std::string &type) {
        /**
         * Gets the bmp hashed by type
         */
        return bmpHashSet.GetBmp(type);
    }

    SimpleBitmap GetStyleBmp(int num) {
        /**
         * Gets the style bmp of the number specified
         */
        return bmpHashSet.GetBmp(GetStyleBmpKeyFromIndex(num));
    }

    // Get name functions


    std::string GetName(const std::string &type) {
        /**
         * Gets the name of bmp hashed by type
         */
        return nameHashSet.GetName(type);
    }

    std::string GetStyleName(int num) {
        /**
         * Gets the style bmp of the number specified
         */
        return nameHashSet.GetName(GetStyleBmpKeyFromIndex(num));
    }

    std::string GetNameWithoutFormat(const std::string &type) {
        auto name = GetName(type);
        std::string toErase(".png");
        size_t pos = name.find(toErase);

        if (pos != std::string::npos) {
            // If found then erase it from string
            name.erase(pos, toErase.length());
        }
        return name;
    }

    std::string GetStyleName() {
        return GetNameWithoutFormat(GetStyleBmpKey());
    }

    std::string GetContentName() {
        return GetNameWithoutFormat(GetContentBmpKey());
    }

    // Get path Functions

    std::string GetStylePath() {
        /**
         * Gets the path of the current style bmp
         */

        std::string styleName = nameHashSet.GetName(GetStyleBmpKey());
        std::string path = BmpLocations::styleBmpLoc + "/" + styleName;
        return path;
    }

    std::string GetContentPath() {
        /**
         * Gets the path of the content bmp
         */
        std::string contentName = nameHashSet.GetName(GetContentBmpKey());
        std::string path = BmpLocations::contentBmpLoc + "/" + contentName;
        return path;
    }

    std::string GetOutputPath() {
        /**
         * Gets the path of the content bmp
         */
//        std::string outputName = nameHashSet.GetName(GetOutputBmpKey());
        std::string path = BmpLocations::outputBmpLoc;
        return path;
    }

    void GetOutputFileForCurrent(std::string &outputPath, std::string &outputName) {
        outputName = GetStyleName() + "-" + GetContentName() + ".png";
        outputPath = std::string(GetOutputPath() + "/" + outputName);
    }

    // Get Keys
    std::string GetStyleBmpKeyFromIndex(int num) {
        /**
         * Returns the hashkey of style[num]
         */
        std::string hashKey;
        char key[2];
        sprintf(key, "%d", num);
        hashKey = "st " + std::string(key);
        return hashKey;
    }

    std::string GetStyleBmpKey() { return std::string("style"); }

    std::string GetContentBmpKey() { return std::string("content"); }

    std::string GetOutputBmpKey() { return std::string("output"); }
};

extern BmpHash bmpHash;

#endif //PROJECT_BMPHASH_H

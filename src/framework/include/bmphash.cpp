//
// Created by krishna on 4/28/18.
//

#include "bmphash.h"

// The all powerful Hash function!
BmpHash bmpHash;

void BmpHash::BmpHashSet::Insert(std::string str, SimpleBitmap bmp) {
    cur_item = bmpMap.find(str);
    if (cur_item == bmpMap.end()) {
        // Insert if the element is not present
        bmpMap.insert(std::make_pair(str, bmp));
    } else {
        // Update the element
        bmpMap.at(str) = bmp;
    }
}

std::string BmpHash::NameHashSet::GetName(const std::string &str) {
    cur_item = nameMap.find(str);
    if (cur_item == nameMap.end())
        std::cout << str << " name not found in the Hash\n";
    return cur_item->second;
}

void BmpHash::NameHashSet::Insert(std::string key, std::string name) {

    cur_item = nameMap.find(key);
    if (cur_item == nameMap.end()) {
        // Insert if the element is not present
        nameMap.insert(std::make_pair(key, name));
    } else {
        // Update the element
        nameMap.at(key) = name;
    }
}


SimpleBitmap BmpHash::BmpHashSet::GetBmp(const std::string &str) {
    cur_item = bmpMap.find(str);
    if (cur_item == bmpMap.end())
        std::cout << str << " bmp not found in BmpHash\n";
    return cur_item->second;
}


void BmpHash::UpdateStyleBmps(const vector<std::string> &bmpPaths, const vector<std::string> &bmpNames) {
    int num = bmpPaths.size();
    for (int i = 0; i < num; i++) {
        AddStylesBmp(bmpPaths[i], bmpNames[i]);
    }
}
void BmpHash::UpdateStyleBmps() {
    vector<std::string> fileLocs, fileNames;
    BmpLocations::GetStyleBmpLocs(fileLocs, fileNames);
    UpdateStyleBmps(fileLocs, fileNames);
    SetStyleBmp(0);
}
void BmpHash::SetStyleBmp(int num) {
    /**
     * Updates the style bmp to the selected number
     */
    // Check if hashKey exists or not
    std::string hashKey(GetStyleBmpKey());
    SimpleBitmap styleBmp = GetStyleBmp(num);
    std::string styleName = GetStyleName(num);

    bmpHashSet.Insert(hashKey, styleBmp);
    nameHashSet.Insert(hashKey, styleName);
    stylePresent = true;
}


void BmpHash::UpdateContentBmp(const std::string &bmpPath, const std::string &bmpName) {
    /**
     * Updates the content bmp by fetching the image from the location if present
     */
    std::string hashKey(GetContentBmpKey());
    SimpleBitmap contentBmp;
    if (GetBmpFromLocation(bmpPath, contentBmp)) {
        bmpHashSet.Insert(hashKey, contentBmp);
        nameHashSet.Insert(hashKey, bmpName);
        contentPresent = true;
    }
}
void BmpHash::UpdateContentBmp(){
    std::string fileLoc, fileName;
    BmpLocations::GetContentBmpLoc(fileLoc, fileName);
    UpdateContentBmp(fileLoc, fileName);
}


void BmpHash::UpdateOutputBmp(const std::string &bmpLoc, const std::string &bmpName) {
    /**
     * Updates the content bmp by fetching the image from the location if present
     */
    std::string hashKey(GetOutputBmpKey());
    SimpleBitmap outputBmp;
    if (GetBmpFromLocation(bmpLoc, outputBmp)) {
        bmpHashSet.Insert(hashKey, outputBmp);
        nameHashSet.Insert(hashKey, bmpName);
        outputPresent = true;
    }
}

void BmpHash::AddAllImages() {
    bmpHashSet.CleanUp();
    nameHashSet.CleanUp();

    vector<std::string> fileLocs, fileNames;
    BmpLocations::GetStyleBmpLocs(fileLocs, fileNames);
    UpdateStyleBmps(fileLocs, fileNames);
    SetStyleBmp(0);

    UpdateContentBmp();

//    BmpLocations::GetOutputBmpLoc(fileLoc, fileName);
//    UpdateOutputBmp(fileLoc, fileName);
    print("Hash Built, default centre style Image set to 0");
}

void BmpHash::AddStylesBmp(const std::string &bmpPath, const std::string &bmpName) {
    /**
     * Adds the style bmp by fetching the image from the location if present
     * Adds bmp and the name one by one, called from the function Update Style Bmps
     */
    std::string hashKey;
    char key[2];
    sprintf(key, "%d", nStyleImages);
    hashKey = "st " + std::string(key);
    SimpleBitmap styleBmp;
    if (GetBmpFromLocation(bmpPath, styleBmp)) {
        bmpHashSet.Insert(hashKey, styleBmp);
        nameHashSet.Insert(hashKey, bmpName);
        nStyleImages += 1;
    }
}
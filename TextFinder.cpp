/* 
 * File:   TextFinder.cpp
 * Author: hapan
 * 
 * Created on February 5, 2013, 8:03 PM
 */

#include <vector>
#include <stdlib.h>
#include <iostream>

#include "FileSystem.h"
#include "TextFinder.h"

using namespace FileSystem;

extern "C" ITextFinder* gMakeObj() {
  return new TextFinder;
}

ITextFinder* ITextFinder::makeObj() {
  return new TextFinder;
}

TextFinder::TextFinder() {
  m_path = ".";
  m_string = "";
  m_filelist.clear();
  m_matchedlist.clear();
}

TextFinder::TextFinder(const std::string& path, const std::string& str) {
  m_path = path;
  m_string = str;
  m_filelist.clear();
  m_matchedlist.clear();
}

TextFinder::~TextFinder() {
  m_filelist.clear();
  m_matchedlist.clear();
}

void TextFinder::setPath(const std::string& path) {
  m_path = path;
}

void TextFinder::setString(const std::string& str) {
  m_string = str;
}

std::string TextFinder::getPath() {
  return m_path;
}

std::string TextFinder::getString() {
  return m_string;
}

std::vector<std::string> TextFinder::getAllFiles() {
  if(m_filelist.size() == 0) {
    addFile(m_path, "*.*");
  }
  //print(m_filelist);
  return m_filelist;
}
std::vector<std::string> TextFinder::getMatchedFiles() {
  if(m_filelist.size() == 0) {
    addFile(m_path, "*.*");
  }  
  std::vector<std::string> ret = parseFile();
  
  //print(m_filelist);
  //std::cout << "\n The following files have the string: " << m_string;
  //print(ret);
  
  return ret;
}

// using recursion store all the files in the directory tree
void TextFinder::addFile(const std::string& path, const std::string& filetype) {
  Directory d;
  std::vector<std::string> filelist = d.getFiles(path, filetype);
  addFileList(path, filelist);
  
  std::vector<std::string> direlist = d.getDirectories(path, filetype);
  for(size_t i=0; i<direlist.size(); i++) {
    std::string new_path;
    if(path[path.size()-1] == '/')
      new_path = path + direlist[i];
    else
      new_path = path + "/" +direlist[i];
    addFile(new_path, filetype);
  }
}

// helper: merge two vector of string together
void TextFinder::addFileList(const std::string& path, const std::vector<std::string>& filelist) {
  for(size_t i=0; i<filelist.size(); i++) {
    if(path[path.size()-1] == '/')
      m_filelist.push_back(path + filelist[i]);
    else
      m_filelist.push_back(path + "/" + filelist[i]);
  }
}

// read all the files in the m_filelist and parse them to see if matching the string
std::vector<std::string> TextFinder::parseFile() {
  for(size_t i=0; i<m_filelist.size(); i++) {
    if(isMatched(m_filelist[i], m_string)) {
      m_matchedlist.push_back(m_filelist[i]);
    }
  }
  return m_matchedlist;
}

bool TextFinder::isMatched(const std::string& filespec, const std::string& str) {
  File file(filespec);
  file.open(File::in);
  if(!file.isGood()) {
    std::cout << "\n Cannot open file:\n " << filespec;
    return false;
  }
  while(file.isGood()) {
    std::string line = file.getLine();
    size_t found = line.find(str);
    if(found != std::string::npos)
      return true;
  }
  return false; 
}
// helper: print the content of a filelist
void TextFinder::print(const std::vector<std::string>& filelist) {
  std::cout << "\n Printing filelist";
  std::cout << "\n ====================\n";
  for(size_t i=0; i<filelist.size(); i++) {
    std::cout << filelist[i] << std::endl;
  }
  std::cout << "\n =========================";
  std::cout << "\n Printing filelist ends";
  std::cout << "\n It has " << filelist.size() << " files in total\n";
}


//----< test stub >---------------
#ifdef TEST_TEXTFINDER

int main(int argc, char* argv[]) {
  std::string str1 = std::string(getenv("HOME")) + "/Documents";
  std::string str2 = "#include";
  if(argc > 2) {
    str1 = argv[1];
    str2 = argv[2];
  } else if(argc > 1) {
    str1 = argv[1];
  }
  
  TextFinder tf(str1, str2);
  std::cout << "\n Looking for all files in directory: " << tf.getPath()
          << " that contain the string: " << tf.getString() << "\n";
  
  std::vector<std::string> allfiles = tf.getAllFiles();
  std::cout << "\n Printing all files in the directory tree: " << tf.getPath();
  std::cout << "\n=============================================\n";
  for(size_t i=0; i<allfiles.size(); i++) {
    std::cout << allfiles[i] << std::endl;
  }
  std::cout << "=============================================";
  std::cout << "\n It has " << allfiles.size() << " files in total\n";
  
  std::vector<std::string> matchedfiles = tf.getMatchedFiles();
  std::cout << "\n Printing all files that contain the string: " << tf.getString();
  std::cout << "\n=============================================\n";
  for(size_t i=0; i<matchedfiles.size(); i++) {
    std::cout << matchedfiles[i] << std::endl;
  }
  std::cout << "=============================================";
  std::cout << "\n It has " << matchedfiles.size() << " files in total\n";
  
}

#endif

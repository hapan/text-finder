/* 
 * File:   TextFinder.cpp
 * Author: hapan
 * 
 * Created on February 5, 2013, 8:03 PM
 */

#include <vector>
#include <stdlib.h>
#include <iostream>

#include "TextFinder.h"
#include "FileSystem.h"

using namespace FileSystem;

TextFinder::TextFinder() {
  m_path = "~";
  m_string = "";
  m_filelist.clear();
}

TextFinder::TextFinder(const std::string& path, const std::string& str) {
  m_path = path;
  m_string = str;
  m_filelist.clear();
}

TextFinder::~TextFinder() {
  m_filelist.clear();
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

std::vector<std::string> TextFinder::getMatchedFiles() {
  m_filelist.clear();
  addFile(m_path, "*.*");
  print(m_filelist);
  return m_filelist;
}

// helper: merge two vector of string together
void TextFinder::addFileList(std::string path, std::vector<std::string>& filelist) {
  for(size_t i=0; i<filelist.size(); i++) {
    m_filelist.push_back(path + "/" + filelist[i]);
  }
}

// using recursion store all the files in the directory tree
void TextFinder::addFile(std::string path, std::string filetype) {
  Directory d;
  std::vector<std::string> filelist = d.getFiles(path, filetype);
  addFileList(path, filelist);
  
  std::vector<std::string> direlist = d.getDirectories(path, filetype);
  for(size_t i=0; i<direlist.size(); i++) {
    std::string new_path = path + "/" + direlist[i];
    addFile(new_path, filetype);
  }
}

// helper: print the content of a filelist
void TextFinder::print(std::vector<std::string>& filelist) {
  std::cout << "Printing filelist" << std::endl;
  for(size_t i=0; i<filelist.size(); i++) {
    std::cout << filelist[i] << std::endl;
  }
  std::cout << std::endl;
}
//----< test stub >---------------
#ifdef TEST_TEXTFINDER

int main(int argc, char* argv[]) {
  std::string fn1;
  if(argc > 1)
    fn1 = argv[1];
  else
    fn1 = std::string(getenv("HOME")) + "/cse775";
  
  TextFinder tf;
  tf.setPath(fn1);
  tf.getMatchedFiles();
}

#endif

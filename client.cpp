/* 
 * File:   main.cpp
 * Author: hapan
 *
 * Created on February 5, 2013, 8:02 PM
 */

#include <cstdlib>
#include <iostream>
#include <dlfcn.h>
#include "ITextFinder.h"


int main(int argc, char* argv[]) {
  std::string str1 = std::string(getenv("HOME")) + "/Documents";
  std::string str2 = "#include";
  if(argc > 2) {
    str1 = argv[1];
    str2 = argv[2];
  } else if(argc > 1) {
    str1 = argv[1];
  }
  
  void * lib_handle = dlopen("./dist/Debug/GNU-Linux-x86/libtext_finder.so", RTLD_LAZY);
  if(lib_handle == NULL){
    std::cout << "\n Can't open libtext_finder.so" << std::endl;
    return 0;
  }

  typedef ITextFinder* (*gMO)();
  gMO makeObj = (ITextFinder* (*)())dlsym(lib_handle, "gMakeObj");
  if(!makeObj) {
    std::cout << "\n Failed to create gMakeObj";
    return 0;
  }
  ITextFinder* pTextFinder = makeObj();
  pTextFinder->setPath(str1);
  pTextFinder->setString(str2);
  
  std::cout << "\n Looking for all files in directory: " << pTextFinder->getPath()
          << " that contain the string: " << pTextFinder->getString() << "\n";
  
  std::vector<std::string> allfiles = pTextFinder->getAllFiles();
  std::cout << "\n Printing all files in the directory tree: " << pTextFinder->getPath();
  std::cout << "\n=============================================\n";
  for(size_t i=0; i<allfiles.size(); i++) {
    std::cout << allfiles[i] << std::endl;
  }
  std::cout << "=============================================";
  std::cout << "\n It has " << allfiles.size() << " files in total\n";
  
  std::vector<std::string> matchedfiles = pTextFinder->getMatchedFiles();
  std::cout << "\n Printing all files that contain the string: " << pTextFinder->getString();
  std::cout << "\n=============================================\n";
  for(size_t i=0; i<matchedfiles.size(); i++) {
    std::cout << matchedfiles[i] << std::endl;
  }
  std::cout << "=============================================";
  std::cout << "\n It has " << matchedfiles.size() << " files in total\n";
  
}


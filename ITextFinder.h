/* 
 * File:   ITextFinder.h
 * Author: hapan
 *
 * Created on February 7, 2013, 2:58 PM
 */

#ifndef ITEXTFINDER_H
#define	ITEXTFINDER_H

#include <string>
#include <vector>

class ITextFinder {
public:
  static ITextFinder* makeObj(); // static member object factory

  virtual void setPath(const std::string& path) = 0;
  virtual void setString(const std::string& str) = 0;
  virtual std::string getPath() = 0;
  virtual std::string getString() = 0;

  virtual std::vector<std::string> getAllFiles() = 0;
  virtual std::vector<std::string> getMatchedFiles() = 0;
};

extern "C" {
  ITextFinder* gMakeObj(); // global object 
}

#endif	/* ITEXTFINDER_H */


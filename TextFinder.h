/* 
 * File:   TextFinder.h
 * Author: hapan
 *
 * Created on February 5, 2013, 8:03 PM
 */

#ifndef TEXTFINDER_H
#define	TEXTFINDER_H
/////////////////////////////////////////////////////////////////////////////
// TextFinder.h - identify all files in a directory tree that              //
//                contain a specified string                               //
// Linux ver 1.0                                                           //
// ----------------------------------------------------------------------- //
// copyright � Haiyang Pan, 2012                                           //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    gcc/g++ v4.6.3                                             //
// Platform:    ACER Aspire 5750G, Core i5, kubuntu v12.04 LST             //
// Application: Distributed Objects, Spring 2013                           //
// Author:      Haiyang Pan, Syracuse University                           //
//              
/////////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This package provides
 * 
 */

#include <string>
#include <vector>

class TextFinder {
public:
  TextFinder();
  TextFinder(const std::string& path, const std::string& str);
  virtual ~TextFinder();
  
  void setPath(const std::string& path);
  void setString(const std::string& str);
  std::string getPath();
  std::string getString();
  
  std::vector<std::string> getMatchedFiles();
private:
  std::string m_path;
  std::string m_string;
  std::vector<std::string> m_filelist;
  
  void addFileList(std::string path, std::vector<std::string>& filelist);
  void addFile(std::string path, std::string filetype);
  
  void print(std::vector<std::string>& filelist);
};

#endif	/* TEXTFINDER_H */


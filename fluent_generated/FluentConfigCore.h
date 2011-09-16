#pragma once

#include <string>
#include <iostream>

struct FluentConfigCore
{
  void SetUrl( std::string s )
  {
    std::cout<<"Setting Url to "<<s<<std::endl;
  }
  void SetPost()
  {
    std::cout<<"Setting mode to POST"<<std::endl;
  }
  void SetGet()
  {
    std::cout<<"Setting mode to GET"<<std::endl;
  }
  void AddPostData(std::string key, std::string value)
  {
    std::cout<<"Adding Post Data :"<<key<<","<<value<<std::endl;
  }
};


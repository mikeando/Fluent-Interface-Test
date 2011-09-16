#include <string>
#include <iostream>

#include "FluentConfigCore.h"
#include "transitions.h"

int main()
{
  FluentConfigCore fcc;
  ZZZState(&fcc)
    .SetUrl("blue")
    .SetPost()
    .AddPostData("a","1")
    .AddPostData("b","2");

// This will not compile 
// It gives this error with clang++ (And something a little more cryptic on g++)
// fluent_interface3.cpp:262:6: error: no member named 'SetPostData' in 'FluentConfigState<UGZState>'
//   .SetPostData("a","1")
//    ^
//
//  ZZZState(/*&fcc*/)
//    .SetUrl("blue")
//    .SetGet()
//    .SetPostData("a","1")
//    .SetPostData("b","2");
}

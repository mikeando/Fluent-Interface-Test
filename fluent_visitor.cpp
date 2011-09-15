#include <string>
#include <iostream>

/*
struct FluentConfig
{
  FluentConfig & SetUrl( std::string ) { return *this; }
  FluentConfig & SetPost() { return *this; }
  FluentConfig & AddPostData( int i ) { return *this; }
  FluentConfig & SetGet() { return *this; }
};
*/

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

template< typename STATE >
struct FluentConfigState
{
   explicit FluentConfigState( FluentConfigCore* in_data) : data(in_data) {}

   FluentConfigState<typename STATE::AfterUrl> SetUrl( std::string s )
   {
     data->SetUrl(s);
     return FluentConfigState<typename STATE::AfterUrl>( data );
   };
   FluentConfigState<typename STATE::AfterPost> SetPost()
   {
     data->SetPost();
     return FluentConfigState<typename STATE::AfterPost>( data );
   };
   FluentConfigState<typename STATE::AfterPostData> SetPostData(std::string key,std::string value)
   {
     data->AddPostData(key,value);
     return FluentConfigState<typename STATE::AfterPostData>( data );
   };
   FluentConfigState<typename STATE::AfterGet> SetGet()
   {
     data->SetGet();
     return FluentConfigState<typename STATE::AfterGet>( data );
   };

   FluentConfigCore * data;
};

struct UZZState;
struct ZPZState;
struct ZGZState;
struct UPZState;
struct UGZState;
struct ZPDState;
struct UPDState;

struct nullState;

struct BaseState
{
  typedef nullState   AfterUrl;
  typedef nullState   AfterPost;
  typedef nullState   AfterPostData;
  typedef nullState   AfterGet;
};


struct ZZZState : public BaseState
{
  typedef UZZState   AfterUrl;
  typedef ZPZState   AfterPost;
  typedef ZGZState   AfterGet;
};

struct UZZState : public BaseState
{
  typedef UPZState   AfterPost;
  typedef UGZState   AfterGet;
};

struct ZPZState : public BaseState
{
  typedef UPZState  AfterUrl;
  typedef ZPDState  AfterPostData;
};

struct ZPDState : public BaseState
{
  typedef UPDState  AfterUrl;
  typedef ZPDState  AfterPostData;
};

struct UPZState : public BaseState
{
  typedef UPDState   AfterPostData;
};

struct UGZState : public BaseState
{
};

struct UPDState : public BaseState
{
  typedef UPDState  AfterPostData;
};


int main()
{
  FluentConfigCore fcc;
  FluentConfigState<ZZZState>(&fcc)
    .SetUrl("blue")
    .SetPost()
    .SetPostData("a","1")
    .SetPostData("b","2");

// This will not compile 
// It gives this error with clang++ (And something a little more cryptic on g++)
//
// fluent_interface.cpp:39:38: error: no type named 'AfterUrl' in 'nullState'
//     FluentConfigState<typename STATE::AfterUrl> SetUrl( std::string s )
//                       ~~~~~~~~~~~~~~~~^~~~~~~~
// fluent_interface.cpp:135:6: note: in instantiation of template class 'FluentConfigState<nullState>' requested here
//     .SetPostData("a","1")
//      ^
//
//  FluentConfigState<ZZZState>(&fcc)
//    .SetUrl("blue")
//    .SetGet()
//    .SetPostData("a","1")
//    .SetPostData("b","2");
}

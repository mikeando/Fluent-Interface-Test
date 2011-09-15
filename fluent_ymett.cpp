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

template<class T>
struct Void
{
  typedef void type;
};

#define BUILD_RETURN_HELPER(X) \
  template<class T, class=void> \
  struct X##Return \
  { \
      typedef void type; \
  }; \
  template<class T> \
  struct X##Return<T, typename Void<typename T::X>::type> \
  { \
    typedef typename T::X type; \
  }

BUILD_RETURN_HELPER(AfterUrl);
BUILD_RETURN_HELPER(AfterPost);
BUILD_RETURN_HELPER(AfterPostData);
BUILD_RETURN_HELPER(AfterGet);

#undef BUILD_RETURN_HELPER

template< typename STATE >
struct FluentConfigState
{
   explicit FluentConfigState( FluentConfigCore* in_data) : data(in_data) {}

   FluentConfigState<typename AfterUrlReturn<STATE>::type> SetUrl( std::string s )
   {
     data->SetUrl(s);
     return FluentConfigState<typename STATE::AfterUrl>( data );
   };
   FluentConfigState<typename AfterPostReturn<STATE>::type> SetPost()
   {
     data->SetPost();
     return FluentConfigState<typename STATE::AfterPost>( data );
   };
   FluentConfigState<typename AfterPostDataReturn<STATE>::type> SetPostData(std::string key,std::string value)
   {
     data->AddPostData(key,value);
     return FluentConfigState<typename STATE::AfterPostData>( data );
   };
   FluentConfigState<typename AfterGetReturn<STATE>::type> SetGet()
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

struct ZZZState
{
  typedef UZZState   AfterUrl;
  typedef ZPZState   AfterPost;
  typedef ZGZState   AfterGet;
};

struct UZZState
{
  typedef UPZState   AfterPost;
  typedef UGZState   AfterGet;
};

struct ZPZState
{
  typedef UPZState  AfterUrl;
  typedef ZPDState  AfterPostData;
};

struct ZPDState
{
  typedef UPDState  AfterUrl;
  typedef ZPDState  AfterPostData;
};

struct UPZState
{
  typedef UPDState   AfterPostData;
};

struct UGZState
{
};

struct UPDState
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
// fluent_interface2.cpp:106:47: error: no type named 'AfterPostData' in 'UGZState'
//    return FluentConfigState<typename STATE::AfterPostData>( data );
//                             ~~~~~~~~~~~~~~~~^~~~~~~~~~~~~
// fluent_interface2.cpp:180:6: note: in instantiation of member function 'FluentConfigState<UGZState>::SetPostData' requested here
//     .SetPostData("a","1")
//      ^
//
//  FluentConfigState<ZZZState>(&fcc)
//    .SetUrl("blue")
//    .SetGet()
//    .SetPostData("a","1")
//    .SetPostData("b","2");
}

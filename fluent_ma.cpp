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

#define BUILD_HAS_TYPEDEF_HELPER(X) \
template <typename T> \
struct has_##X \
{ \
  typedef char yes[1]; \
  typedef char no[2]; \
  template <typename C> static yes& test(typename C::X*); \
  template <typename> static no& test(...); \
  static const bool value = sizeof(test<T>(0)) == sizeof(yes); \
}

BUILD_HAS_TYPEDEF_HELPER( AfterUrl );
BUILD_HAS_TYPEDEF_HELPER( AfterPost );
BUILD_HAS_TYPEDEF_HELPER( AfterGet );
BUILD_HAS_TYPEDEF_HELPER( AfterPostData );

#undef BUILD_HAS_TYPEDEF_HELPER


template<typename STATE> struct FluentConfigState;


struct FluentConfigStateVirtualBase
{
  explicit FluentConfigStateVirtualBase( FluentConfigCore * in_data ) : data(in_data) {}
  FluentConfigStateVirtualBase() : data(NULL) {}
  FluentConfigCore * data;
};

struct AfterUrlTag {};
struct AfterPostTag {};
struct AfterGetTag {};
struct AfterPostDataTag {};

template<typename STATE,bool HAS_TYPEDEF, typename TAG>
struct FluentConfigStateTagged : virtual public FluentConfigStateVirtualBase
{
};

template<typename STATE>
struct FluentConfigStateTagged<STATE,true, AfterUrlTag> : virtual public FluentConfigStateVirtualBase
{
  FluentConfigState<typename STATE::AfterUrl> SetUrl( std::string url)
  {
     data->SetUrl(url);
     return FluentConfigState<typename STATE::AfterUrl>( data );
  }
};

template<typename STATE>
struct FluentConfigStateTagged<STATE,true, AfterPostTag> : virtual public FluentConfigStateVirtualBase
{
  FluentConfigState<typename STATE::AfterPost> SetPost()
  {
     data->SetPost();
     return FluentConfigState<typename STATE::AfterPost>( data );
  }
};

template<typename STATE>
struct FluentConfigStateTagged<STATE,true, AfterGetTag> : virtual public FluentConfigStateVirtualBase
{
  FluentConfigState<typename STATE::AfterGet> SetGet()
  {
     data->SetGet();
     return FluentConfigState<typename STATE::AfterGet>( data );
  }
};

template<typename STATE>
struct FluentConfigStateTagged<STATE,true, AfterPostDataTag> : virtual public FluentConfigStateVirtualBase
{
  FluentConfigState<typename STATE::AfterPostData> SetPostData( std::string key, std::string value )
  {
     data->AddPostData(key,value);
     return FluentConfigState<typename STATE::AfterPostData>( data );
  }
};

//TODO: It feels like we should be able to combine the has_AfterUrl<STATE>::value and AfterUrlTag
//      in such a way that the FluentConfigStateTagged only takes two templater arguments
template<typename STATE>
struct FluentConfigState : 
  public FluentConfigStateTagged<STATE, has_AfterUrl<STATE>::value, AfterUrlTag>,
  public FluentConfigStateTagged<STATE, has_AfterPost<STATE>::value, AfterPostTag>,
  public FluentConfigStateTagged<STATE, has_AfterGet<STATE>::value, AfterGetTag>,
  public FluentConfigStateTagged<STATE, has_AfterPostData<STATE>::value, AfterPostDataTag>
{
  FluentConfigState( FluentConfigCore * in_data ) : FluentConfigStateVirtualBase(in_data)
  {
  }
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
// fluent_interface3.cpp:262:6: error: no member named 'SetPostData' in 'FluentConfigState<UGZState>'
//   .SetPostData("a","1")
//    ^
//
//  FluentConfigState<ZZZState>(&fcc)
//    .SetUrl("blue")
//    .SetGet()
//    .SetPostData("a","1")
//    .SetPostData("b","2");
}

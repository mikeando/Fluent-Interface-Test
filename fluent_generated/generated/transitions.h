class FluentConfigCore;
#include <string>
class UGZState;
class ZZZState;
class ZGZState;
class UZZState;
class UPZState;
class UPDState;
class ZPDState;
class ZPZState;
class UGZState
{
   public:
     explicit UGZState( FluentConfigCore * in_core ) : core(in_core) {}
   protected:
     FluentConfigCore * core;
};

class ZZZState
{
   public:
     explicit ZZZState( FluentConfigCore * in_core ) : core(in_core) {}
    UZZState SetUrl(std::string url);
    ZPZState SetPost();
    ZGZState SetGet();
   protected:
     FluentConfigCore * core;
};

class ZGZState
{
   public:
     explicit ZGZState( FluentConfigCore * in_core ) : core(in_core) {}
    UGZState SetUrl(std::string url);
   protected:
     FluentConfigCore * core;
};

class UZZState
{
   public:
     explicit UZZState( FluentConfigCore * in_core ) : core(in_core) {}
    UGZState SetGet();
    UPZState SetPost();
   protected:
     FluentConfigCore * core;
};

class UPZState
{
   public:
     explicit UPZState( FluentConfigCore * in_core ) : core(in_core) {}
    UPDState AddPostData(std::string key, std::string value);
   protected:
     FluentConfigCore * core;
};

class UPDState
{
   public:
     explicit UPDState( FluentConfigCore * in_core ) : core(in_core) {}
    UPDState AddPostData(std::string key, std::string value);
   protected:
     FluentConfigCore * core;
};

class ZPDState
{
   public:
     explicit ZPDState( FluentConfigCore * in_core ) : core(in_core) {}
    ZPDState AddPostData(std::string key, std::string value);
    UPDState SetUrl(std::string url);
   protected:
     FluentConfigCore * core;
};

class ZPZState
{
   public:
     explicit ZPZState( FluentConfigCore * in_core ) : core(in_core) {}
    UPZState SetUrl(std::string url);
    ZPDState AddPostData(std::string key, std::string value);
   protected:
     FluentConfigCore * core;
};


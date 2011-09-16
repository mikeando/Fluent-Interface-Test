#include "transitions.h"
#include "FluentConfigCore.h"
UZZState ZZZState::SetUrl(std::string url)
{
  core->SetUrl(url);
  return UZZState(core);
};

ZPZState ZZZState::SetPost()
{
  core->SetPost();
  return ZPZState(core);
};

ZGZState ZZZState::SetGet()
{
  core->SetGet();
  return ZGZState(core);
};

UGZState ZGZState::SetUrl(std::string url)
{
  core->SetUrl(url);
  return UGZState(core);
};

UGZState UZZState::SetGet()
{
  core->SetGet();
  return UGZState(core);
};

UPZState UZZState::SetPost()
{
  core->SetPost();
  return UPZState(core);
};

UPDState UPZState::AddPostData(std::string key, std::string value)
{
  core->AddPostData(key,value);
  return UPDState(core);
};

UPDState UPDState::AddPostData(std::string key, std::string value)
{
  core->AddPostData(key,value);
  return UPDState(core);
};

ZPDState ZPDState::AddPostData(std::string key, std::string value)
{
  core->AddPostData(key,value);
  return ZPDState(core);
};

UPDState ZPDState::SetUrl(std::string url)
{
  core->SetUrl(url);
  return UPDState(core);
};

UPZState ZPZState::SetUrl(std::string url)
{
  core->SetUrl(url);
  return UPZState(core);
};

ZPDState ZPZState::AddPostData(std::string key, std::string value)
{
  core->AddPostData(key,value);
  return ZPDState(core);
};


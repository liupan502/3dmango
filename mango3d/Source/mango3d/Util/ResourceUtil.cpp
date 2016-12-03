#include "ResourceUtil.h"

ResourceUtil* ResourceUtil::instance_ = NULL;

ResourceUtil* ResourceUtil::Instance() {
  if (instance_ == NULL) {
    instance_ = new ResourceUtil();
  }
  return instance_;
}

ResourceUtil::ResourceUtil() {
  ;
}

ResourceUtil::~ResourceUtil() {

}

UStaticMesh* ResourceUtil::GetStaticMesh(const FString& meshId) {
  return NULL;
}

UMaterial* ResourceUtil::GetMaterial(const FString& matId) {
  return NULL;
}


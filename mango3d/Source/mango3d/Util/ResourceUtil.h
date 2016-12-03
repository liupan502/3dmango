#pragma once
#include "mango3d.h"
#include <vector>
#include <map>



class ResourceUtil {
  static ResourceUtil* Instance();
  virtual ~ResourceUtil();
  UStaticMesh* GetStaticMesh( const FString& meshId);
  UMaterial* GetMaterial(const FString& matId)
protected:
  ResourceUtil();
  static ResourceUtil* instance_;
  std::map<FString, UStaticMesh*> mesh_map_;
  std::map<FString, UMaterial*> mat_map_;
};

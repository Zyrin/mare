
#pragma once

#include "Tools/String.h"
#include "Tools/List.h"
#include "Tools/Scope.h"
#include "Namespace.h"

class Script;

class Engine : public Scope
{
public:

  typedef void (*ErrorHandler)(void* userData, unsigned int line, const String& message);

  Engine(ErrorHandler errorHandler, void* userData) : errorHandler(errorHandler), errorUserData(userData), currentSpace(0) {}

  bool load(const String& file);
  void error(const String& message);

  bool enterKey(const String& key, bool allowInheritance = true);
  void enterUnnamedKey();
  void enterDefaultKey(const String& key);

  bool resolveScript(const String& key, Script*& script);

  bool leaveKey();
  void getKeys(List<String>& keys);
  void getKeys(const String& key, List<String>& keys, bool allowInheritance = true);
  String getFirstKey();

  void addDefaultKey(const String& key);
  void addDefaultKey(const String& key, const String& value);
  void setDefaultKey(const String& key);
  void addResolvableKey(const String& key, const String& value = String());

  void pushKey();
  bool popKey();

private:
  ErrorHandler errorHandler;
  void* errorUserData;
  Namespace* currentSpace;
  List<Namespace*> stashedKeys;
};

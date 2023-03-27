//
// Created by Admin on 19.08.2021.
//

#ifndef IMGUIANDROID_CUSTOM_OBFUSCATE_H
#define IMGUIANDROID_CUSTOM_OBFUSCATE_H
using namespace BNM; // remember to use the macros to protect offsets from static analysis
#include "instr.h"
#define OBFUSCATE_OFFSET(data) getRealOffset(string2Offset(STRING_OBFUSCATE_KEY(data, STRING_OBFUSCATE_DEFAULT_KEY)))

#define OBFUSCATE_BYNAME_METHOD(namespaze, classname, methodname, paramcount) \
LoadClass(STRING_OBFUSCATE_KEY(namespaze, STRING_OBFUSCATE_DEFAULT_KEY).operator char *(), STRING_OBFUSCATE_KEY(classname, STRING_OBFUSCATE_DEFAULT_KEY).operator char *()).GetMethodOffsetByName(STRING_OBFUSCATE_KEY(methodname, STRING_OBFUSCATE_DEFAULT_KEY).operator char *(), N(paramcount))
#define OBFUSCATE_BYNAME_CLASS(namespaze, classname) \
LoadClass(STRING_OBFUSCATE_KEY(namespaze, STRING_OBFUSCATE_DEFAULT_KEY).operator char *(), STRING_OBFUSCATE_KEY(classname, STRING_OBFUSCATE_DEFAULT_KEY).operator char *())
#define OBFUSCATE_BYNAME_FIELD(namespaze, classname, fieldname) \
LoadClass(STRING_OBFUSCATE_KEY(namespaze, STRING_OBFUSCATE_DEFAULT_KEY).operator char *(), STRING_OBFUSCATE_KEY(classname, STRING_OBFUSCATE_DEFAULT_KEY).operator char *()).GetFieldOffset(STRING_OBFUSCATE_KEY(fieldname, STRING_OBFUSCATE_DEFAULT_KEY).operator char *())

#endif //IMGUIANDROID_CUSTOM_OBFUSCATE_H

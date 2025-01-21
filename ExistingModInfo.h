#pragma once
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/utsname.h>
#include "ElfSymInfos.h"
#include "Common.h"
typedef struct utsname uname_t;
class ExistingModInfo
{
public:
    ExistingModInfo();
    ~ExistingModInfo();
    void printKMods();
    unsigned long findSym(string symname);
private:
    void queryKMods();
    void initAllSymbolVerInfo();
    map<string, unsigned long> m_va_infos;
    multimap<string, string> m_kmods;
    uname_t m_system_info;
};

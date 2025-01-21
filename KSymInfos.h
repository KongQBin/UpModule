#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "Common.h"
using namespace std;
struct KSymInfo
{
    string name;
    unsigned long crc;
    string origin;
    string export_type;
};
class KSymInfos
{
public:
    KSymInfos();
    KSymInfos(string path);
    ~KSymInfos();
    void setPath(string path);
    void initInfos();
    void printInfos();
    unsigned long findSym(string symname);
private:
    string m_path;
    map<string,KSymInfo> m_infos;
};

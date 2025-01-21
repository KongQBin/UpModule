#pragma once
#include <list>
#include <cstring>
#include <linux/types.h>
#include "ElfPtrs.h"

// 大部分实现参考/复制至内核源码
// include/linux/moduleparam.h:21
#define MAX_PARAM_PREFIX_LEN (64 - sizeof(unsigned long))
// include/linux/module.h:34
#define MODULE_NAME_LEN MAX_PARAM_PREFIX_LEN
// include/linux/module.h:36
struct modversion_info {
    unsigned long crc;
    char name[MODULE_NAME_LEN];
};

class ElfSymInfos
{
public:
    ElfSymInfos(){}
    ElfSymInfos(string file, bool rdwr, bool show = true);
    ~ElfSymInfos();
    void printModInfo();
    void printSymInfo();
    list<char*>* getMInfo();
    map<string, unsigned long> getSymVerInfo();
    map<string,modversion_info*> *getVInfo();
private:
    bool initModInfo();
    bool initSymInfo();
    char* nextString(char *str, unsigned long *secsize);
    ElfPtrs *m_eptrs;
    list<char*> m_minfo;
    map<string,modversion_info*> m_vinfo;
};

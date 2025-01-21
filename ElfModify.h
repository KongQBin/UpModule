#pragma once
#include "KSymInfos.h"
#include "ElfSymInfos.h"
#include "ExistingModInfo.h"
class ElfModify
{
public:
    ElfModify(string file);
    ElfModify(string file1, string file);
    ~ElfModify();
    bool motify();
private:
    KSymInfos m_kinfo;
    ElfSymInfos m_einfo;
    ExistingModInfo m_minfo;
};

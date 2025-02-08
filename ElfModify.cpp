#include "ElfModify.h"
ElfModify::ElfModify(string mod) :
    m_einfo(mod,true)
{

}

ElfModify::ElfModify(string symver, string mod) :
    m_kinfo(symver), m_einfo(mod,true)
{

}

ElfModify::~ElfModify()
{

}

bool ElfModify::motify()
{
    bool ret = true;
    // 修改符号CRC
    map<string, modversion_info *> *vinfo = m_einfo.getVInfo();
    for(auto it = vinfo->begin(); it != vinfo->end(); ++it)
    {
        unsigned long crc =  m_kinfo.findSym(it->first);
        if(!crc)
        {
            printf("Symbol: %-32s is not found\n",it->first.c_str());
            ret = false;
        }
        else
        {
            if(crc != it->second->crc)
            {
                printf("modify symbol %-32s crc %lu to %lu\n",it->first.c_str(),it->second->crc,crc);
                it->second->crc = crc;
            }
            else
            {
//                printf("sym %-32s crc = %lu kinfo crc = %lu\n",it->first.c_str(),it->second->crc,crc);
            }
        }
    }
    // 修改版本魔术
    list<char *>* modinfo = m_einfo.getMInfo();
    for(list<char *>::iterator it = modinfo->begin(); it != modinfo->end(); ++it)
    {
        char *vIndex = strstr(*it,"vermagic=");
        if(!vIndex) continue;

        vIndex+=strlen("vermagic=");
        string curSysVer = m_minfo.getVermagic();
        if(strlen(vIndex) >= curSysVer.length())
        {
            strncpy(vIndex,curSysVer.c_str(),strlen(vIndex));
            printf("modify ver str magic to %s\n",vIndex);
        }
        else
        {
            printf("Error: vIndex = %s curSysVer = %s, len(vIndex) < len(curSysVer)!",
                   vIndex,curSysVer.c_str());
            ret = false;
        }
        break;
    }
    return ret;
}

#include "ElfModify.h"
ElfModify::ElfModify(string path) :
    m_einfo(path,true)
{

}

ElfModify::ElfModify(string file1, string file2) :
    m_kinfo(file1), m_einfo(file2,true)
{

}

ElfModify::~ElfModify()
{

}

bool ElfModify::motify()
{
//    string sym = "find_symbol";
//    auto tmp = m_minfo.findSym(sym);
//    printf("sym %-32s is %s found\n",sym.c_str(),tmp ? "" : "not");
//    return true;
    map<string, modversion_info *> *vinfo = m_einfo.getVInfo();
    for(auto it = vinfo->begin(); it != vinfo->end(); ++it)
    {
//        unsigned long crc =  m_minfo.findSym(it->first);
        unsigned long crc =  m_kinfo.findSym(it->first);
        if(!crc)
        {
            printf("Symbol: %-32s is not found\n",it->first.c_str());
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
    list<char *>* modinfo = m_einfo.getMInfo();
    for(list<char *>::iterator it = modinfo->begin(); it != modinfo->end(); ++it)
    {
        char *vIndex = strstr(*it,"5.15.0-126-generic");
        if(vIndex)
        {
            strncpy(vIndex,"5.15.0-130-generic",strlen("5.15.0-130-generic"));
            printf("modify ver str magic to %s\n",*it);
        }
    }
    return true;
}

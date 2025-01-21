#pragma once
#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/limits.h>
#include <map>
#include <string.h>
#include "ErrorLog.h"

struct TableInfo
{
    bool inited;
    int type;
    string name;
//    off64_t offset;
    Elf64_Shdr *addr;
    unsigned long str;
    char *strtab;
};

class ElfPtrs
{
public:
    ElfPtrs(string file, int rdwr, bool show = true);
    ~ElfPtrs();

    string getFilePath();
    TableInfo* getTableInfo(string name);

    //ELF文件头，在文件的开始，保存了路线图，描述了该文件的组织情况
    Elf64_Ehdr *elf_hdr = NULL;
    //节头表(Section header table)
    Elf64_Shdr *sh = NULL;
    //节头字符串表
    Elf64_Shdr *sh_str = NULL;
    char *strtab  = NULL;
private:
    int initPtrs(string file);

    int m_rw;
    bool m_show;
    bool m_inited;
    string m_filePath;
    struct stat m_st;
    map<string,TableInfo> m_tbinfo;
};

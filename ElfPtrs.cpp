#include "ElfPtrs.h"
ElfPtrs::ElfPtrs(string file, int rdwr, bool show)
{
    m_rw = rdwr;
    m_show = show;
    m_inited = !initPtrs(file);
}

ElfPtrs::~ElfPtrs()
{
    if(m_inited && elf_hdr && elf_hdr != MAP_FAILED)
    {
        if(m_rw && msync((void*)elf_hdr, m_st.st_size, MS_SYNC) < 0)
            ErrorLog::getErrorLog()->putErrInfo("msync error",m_filePath);
        munmap((void*)elf_hdr,m_st.st_size);
        elf_hdr = NULL;
    }
}

string fillWithSpaces(const string& str, size_t length) {
    string result = str;
    if (result.length() < length) {
        result.resize(length, ' '); // 使用空格填充到指定长度
    }
    return result;
}

int ElfPtrs::initPtrs(string file)
{
    int fd = -1;
    int fail = 0;
    const char *path = file.c_str();
    do
    {
        if(++fail && elf_hdr) break;

        m_filePath = path;
        fd = open(m_filePath.c_str(), m_rw ? O_RDWR : O_RDONLY);
        if(++fail && 0 > fd)
        {
            ErrorLog::getErrorLog()->putErrInfo("打开文件失败",m_filePath);
            break;
        }
        // 获取文件状态信息，主要是获取文件大小
        if(++fail && 0 > fstat(fd, &m_st))
        {
            ErrorLog::getErrorLog()->putErrInfo("获取文件状态失败",m_filePath);
            break;
        }
        // 进行内存映射文件，便于后面处理的时候直接操作
        elf_hdr = (Elf64_Ehdr *)mmap(0, m_st.st_size, m_rw ? (PROT_READ | PROT_WRITE) : (PROT_READ), MAP_SHARED, fd, 0);
        if(++fail && elf_hdr == MAP_FAILED)
        {
            ErrorLog::getErrorLog()->putErrInfo("内存映射文件失败",m_filePath);
            break;
        }

        sh = (Elf64_Shdr *)((char *)elf_hdr + elf_hdr->e_shoff);
        sh_str = sh + elf_hdr->e_shstrndx;
        strtab = (char *)elf_hdr + sh_str->sh_offset;
        if(m_show)
        {
            printf("TableInfo:\n");
            printf("\tstrtab addr = %p  %s\n",strtab,strtab);
        }
        // 遍历 节头 每一个 表
        for (int i = 1; i < elf_hdr->e_shnum; i++)
        {
            TableInfo info;
            info.addr = sh + i;
            info.name = strtab + info.addr->sh_name;
            info.type = info.addr->sh_type;
            info.str = info.addr->sh_link;
            info.strtab = (char *)elf_hdr + sh[info.str].sh_offset;
            info.strtab = (info.strtab == (char *)elf_hdr ? NULL : info.strtab);
            info.inited = true;

            if(m_show)
            {
                printf("\tname: %-56s type: %d addr: %p str: %02lu strtab: %-16s%p\n",
                       info.name.c_str(),
                       info.type,
                       info.addr,
                       info.str,
                       info.strtab,
                       info.strtab
                       );
            }
            m_tbinfo[info.name] = info;
        }
        fail = 0;
    }while(0);
    if(fd >= 0) close(fd);
//    if(!fail) printf("Ptrs init success.\n");
    return fail;
}

string ElfPtrs::getFilePath()
{
    return m_filePath;
}

TableInfo *ElfPtrs::getTableInfo(string name)
{
    TableInfo *info = NULL;
    do
    {
        map<string,TableInfo>::iterator it = m_tbinfo.find(name);
        if(it == m_tbinfo.end())
        {
            printf("Table %s is not found!!!\n",name.c_str());
            break;
        }
        info = &it->second;
    }while(0);
    return info;
}



#include "ElfModify.h"

// disagrees about version of symbol module_layout


//// include/linux/sysfs.h:30
//struct attribute {
//    const char      *name;
////    umode_t         mode;
//#ifdef CONFIG_DEBUG_LOCK_ALLOC
//    bool            ignore_lockdep:1;
//    struct lock_class_key   *key;
//    struct lock_class_key   skey;
//#endif
//};

//// include/linux/module.h:52
//struct module_attribute {
//    struct attribute attr;
////    ssize_t (*show)(struct module_attribute *, struct module_kobject *, char *);
////    ssize_t (*store)(struct module_attribute *, struct module_kobject *, const char *, size_t count);
////    void (*setup)(struct module *, const char *);
////    int (*test)(struct module *);
////    void (*free)(struct module *);
//    void *show;
//    void *store;
//    void *setup;
//    void *test;
//    void *free;
//};

//// kernel/module/internal.h:57
//struct load_info {
//    const char *name;
//    /* pointer to module in temporary copy, freed at end of load_module() */
//    struct module *mod;
//    Elf64_Ehdr *hdr;
//    unsigned long len;
//    Elf64_Shdr *sechdrs;
//    char *secstrings, *strtab;
//    unsigned long symoffs, stroffs, init_typeoffs, core_typeoffs;
////    struct _ddebug_info dyndbg;
//    bool sig_ok;
//#ifdef CONFIG_KALLSYMS
//    unsigned long mod_kallsyms_init_off;
//#endif
//#ifdef CONFIG_MODULE_DECOMPRESS
//    struct page **pages;
//    unsigned int max_pages;
//    unsigned int used_pages;
//#endif
//    struct {
//        unsigned int
//            sym,    /*.symtab*/
//            str,
//            mod,    /*.gnu.linkonce.this_module  */
//            vers,   /*__versions*/
//            info,   /*.modinfo*/
//            pcpu;
//    } index;
//};



// argv[1] = 符号表文件
// argv[2] = 内核模块文件
int main(int argc, char **argv)
{
    if(argc < 3) return -1;
    ElfModify m(argv[1],argv[2]);
    m.motify();
    return 0;
}

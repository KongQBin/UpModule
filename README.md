# UpModule [![Hits](https://hits.sh/github.com/KongQBin/UpModule.svg?label=%E7%82%B9%E5%87%BB%E9%87%8F&color=007ec6)](https://hits.sh/github.com/KongQBin/UpModule/)

> **Notice / 提示**  
> **[EN]** This repository is now archived and no longer actively maintained. All code and future updates have been merged into [CAdapt](https://github.com/KongQBin/CAdapt). Please refer to the new repository for the latest improvements and issue tracking.  
> **[ZH]** 本仓库已归档并停止维护。所有代码与后续开发已整体合并至 [CAdapt](https://github.com/KongQBin/CAdapt) 仓库。后续功能更新、缺陷修复及 Issue 讨论请移步新仓库。

---

## 项目起因 (Background)
- 为了应对内核小版本更新而不需要重新编译驱动。  
- Aimed at adapting kernel drivers across minor kernel version updates without the need for full recompilation.

## 现状与评估 (Status & Evaluation)
- 验证了方案在内核小版本差异不大时的可行性，确实可以规避重新编译流程。  
- Successfully demonstrated viability when differences between minor kernel versions remain small.

## 局限性与挑战 (Limitations & Challenges)
- **发行版补丁跨度过大 (Aggressive Backporting)**：部分低版本内核（如 3.3）通过大量补丁可能实际包含了 4.4 甚至更高版本的底层改动，但对外暴露的内核版本号并未改变。
- **预编译宏失效 (Pre-compilation Macros Ineffective)**：传统的通过内核版本宏进行接口调用的方案在大型补丁面前失效，必须依赖运行时状态判断，而运行时的特征检测也存在边界盲区。

## PS
- 引用代码时望注明出处，互相尊重对方劳动成果。  
- Please cite the source when referencing or using this code. Respect each other's work.

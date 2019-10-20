#ifndef SKIDS_FUNC_h
#define SKIDS_FUNC_h

#include <string>

#define skidsRet void
#define skidsArg
#define skidsFunc std::function<skidsRet(skidsArg)>

static std::string name1Register = "";
static std::string name2Register = "";
static std::string optRegister = "";

skidsRet cmds_init(skidsArg);
static skidsRet cmds_history(skidsArg) {};
static skidsRet cmds_info(skidsArg) {};
static skidsRet cmds_proj_add(skidsArg) {};
static skidsRet cmds_proj_rm(skidsArg) {};
static skidsRet cmds_proj_list(skidsArg) {};
static skidsRet cmds_skids_init(skidsArg) {};
static skidsRet cmds_skids_initNow(skidsArg) {};
static skidsRet cmds_skids_now(skidsArg) {};
static skidsRet cmds_skids_set(skidsArg) {};
static skidsRet cmds_skids_setThis(skidsArg) {};
static skidsRet cmds_skids_setLazy(skidsArg) {};
static skidsRet cmds_skids_setThisLazy(skidsArg) {};
static skidsRet cmds_skids_setInteractive(skidsArg) {};

#endif

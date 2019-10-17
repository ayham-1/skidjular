#ifndef SKIDS_FUNC_h
#define SKIDS_FUNC_h

#define skidsRet void
#define skidsArg
#define skidsFunc std::function<skidsRet(skidsArg)>

static std::string nameRegister = "";
static std::string dayRegister = "";
static std::string optRegister = "";

skidsRet cmds_init(skidsArg) {};
skidsRet cmds_history(skidsArg) {};
skidsRet cmds_info(skidsArg) {};
skidsRet cmds_proj_add(skidsArg) {};
skidsRet cmds_proj_rm(skidsArg) {};
skidsRet cmds_proj_list(skidsArg) {};
skidsRet cmds_skids_init(skidsArg) {};
skidsRet cmds_skids_initNow(skidsArg) {};
skidsRet cmds_skids_now(skidsArg) {};
skidsRet cmds_skids_set(skidsArg) {};
skidsRet cmds_skids_setThis(skidsArg) {};
skidsRet cmds_skids_setLazy(skidsArg) {};
skidsRet cmds_skids_setThisLazy(skidsArg) {};
skidsRet cmds_skids_setInteractive(skidsArg) {};

#endif

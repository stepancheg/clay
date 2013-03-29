#ifndef __ENV_HPP
#define __ENV_HPP


#include "clay.hpp"


namespace clay {

void addGlobal(ModulePtr module,
               IdentifierPtr name,
               Visibility visibility,
               ObjectPtr value);
ObjectPtr lookupPrivate(ModulePtr module, llvm::StringRef name);
ObjectPtr lookupPublic(ModulePtr module, llvm::StringRef name);
ObjectPtr safeLookupPublic(ModulePtr module, llvm::StringRef name);

void addLocal(EnvPtr env, IdentifierPtr name, ObjectPtr value);
ObjectPtr lookupEnv(EnvPtr env, llvm::StringRef name);
ObjectPtr safeLookupEnv(EnvPtr env, llvm::StringRef name);
ModulePtr safeLookupModule(EnvPtr env);
llvm::DINameSpace lookupModuleDebugInfo(EnvPtr env);

ObjectPtr lookupEnvEx(EnvPtr env, llvm::StringRef name,
                      EnvPtr nonLocalEnv, bool &isNonLocal,
                      bool &isGlobal);

ExprPtr foreignExpr(EnvPtr env, ExprPtr expr);

ExprPtr lookupCallByNameExprHead(EnvPtr env);
Location safeLookupCallByNameLocation(EnvPtr env);

bool lookupExceptionAvailable(const Env* env);

} // namespace clay

#endif // __ENV_HPP

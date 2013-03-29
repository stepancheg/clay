#include "types.hpp"
#include "error.hpp"

#include "string_literal.hpp"


namespace clay {


llvm::StringMap<StringLiteralRepr> StringLiteralRepr::stringLiterals;

StringLiteralRepr StringLiteralRepr::get(llvm::StringRef string) {
    llvm::StringMap<StringLiteralRepr>::const_iterator iter =
            stringLiterals.find(string);
    if (iter != stringLiterals.end()) {
        return iter->second;
    }

    size_t bits = typeSize(cSizeTType);
    size_t size = string.size();
    void *buf = malloc(size + bits + 1);
    switch (bits) {
    case 4:
        *(size32_t*)buf = (size32_t)size;
        break;
    case 8:
        *(size64_t*)buf = size;
        break;
    default:
        error("unsupported pointer width");
        break;
    }
    memcpy((void*)((char*)buf + bits), (const void*)string.begin(), string.size());
    ((char*)buf)[bits + string.size()] = 0;

    StringLiteralRepr r(buf);
    stringLiterals[string] = r;
    return r;
}

size_t StringLiteralRepr::size() {
    size_t bits = typeSize(cSizeTType);
    switch (bits) {
    case 4:
        return *(size32_t*)sizep;
    case 8:
        return *(size64_t*)sizep;
    default:
        error("unsupported pointer width");
        throw 1;
    }
}

llvm::StringRef StringLiteralRepr::stringRef() {
    size_t bits = typeSize(cSizeTType);
    return llvm::StringRef(((char*) sizep) + bits, size());
}

}

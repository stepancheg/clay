#ifndef __CLAY_STRING_LITERAL_HPP
#define __CLAY_STRING_LITERAL_HPP


#include "clay.hpp"


namespace clay {


struct StringLiteralRepr {
    void* sizep;

    size_t size();
    llvm::StringRef stringRef();

    StringLiteralRepr(void* sizep = 0): sizep(sizep) {}
    ~StringLiteralRepr() {}

    static llvm::StringMap<StringLiteralRepr> stringLiterals;

    static StringLiteralRepr get(llvm::StringRef);
};


}

#endif

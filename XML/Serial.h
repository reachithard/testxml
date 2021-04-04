//
// Created by 罗林one on 2021/4/4.
//

#ifndef TESTXML_SERIAL_H
#define TESTXML_SERIAL_H

#include "l1l2_expand.h"

#include <iostream>
using namespace std;
//=======DECODE
#define SERIAL_L1_DECODE(x)             { SERIAL_L1_DECODE_##x }
//----
#define SERIAL_L1_DECODE_X(...)   SERIAL_N2(SERIAL_L2, SERIAL_DECODE_ACT_O, __VA_ARGS__)
#define SERIAL_L1_DECODE_E(FLAG, ...)   SERIAL_N2(SERIAL_L2, SERIAL_DECODE_ACT_E, __VA_ARGS__)
#define SERIAL_L1_DECODE_B(FLAG, ...)   SERIAL_N2(SERIAL_L2, SERIAL_DECODE_ACT_B, __VA_ARGS__)
#define SERIAL_L1_DECODE_AF(FLAG, ...)  X_PACK_N2(SERIAL_L2_2, SERIAL_DECODE_ACT_A, __VA_ARGS__) // extend define in ACTION

#define SERIAL_L1_DECODE_O(...)         SERIAL_L1_DECODE_X(__VA_ARGS__)
#define SERIAL_L1_DECODE_M(...)         SERIAL_L1_DECODE_X(F(M), __VA_ARGS__)
#define SERIAL_L1_DECODE_A(...)         SERIAL_L1_DECODE_AF(F(0), __VA_ARGS__)

#define SERIAL_L1_DECODE_I(...)         X_PACK_N2(SERIAL_L2, SERIAL_DECODE_ACT_I, __VA_ARGS__)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ decode act ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SERIAL_DECODE_ACT_O(M) \
        cout << "SERIAL_DECODE_ACT_O" << endl;                       \
        //__x_pack_obj.decode(#M, __x_pack_self.M, &__x_pack_ext);

// enum for not support c++11
#define SERIAL_DECODE_ACT_E(M)      \
        __x_pack_obj.decode(#M, *((int*)&__x_pack_self.M), &__x_pack_ext);


#define SERIAL_DECODE_ACT_A(M, NAME)                                      \
    {                                                                     \
        static xpack::Alias __x_pack_alias(#M, NAME);                     \
        xpack::Extend __x_pack_ext(__x_pack_flag, &__x_pack_alias);       \
        const char *__new_name = __x_pack_alias.Name(__x_pack_obj.Type());\
        __x_pack_obj.decode(__new_name, __x_pack_self.M, &__x_pack_ext);  \
    }

// Inheritance B::__x_pack_decode(__x_pack_obj)
#define SERIAL_DECODE_ACT_I(P)   __x_pack_obj.decode(NULL, static_cast<P&>(__x_pack_self), NULL);

// bitfield, not support alias
#define SERIAL_DECODE_ACT_B(B)                                \
    {                                                         \
        x_pack_decltype(__x_pack_self.B) __x_pack_tmp;        \
        __x_pack_obj.decode(#B, __x_pack_tmp, &__x_pack_ext); \
        __x_pack_self.B = __x_pack_tmp;\
    }

#define SERIAL_COMMON \
public:               \
    static const bool __Serial_Value = true;

#define SERIAL_ENCODE_BEGIN                                         \
    template<class SERIAL_DOC, class SERIAL_ME>                     \
    void SerialEncode(SERIAL_DOC& obj,                              \
                        const SERIAL_ME& me                        \
                        /*pconst xpack::Extend *__x_pack_ext*/) const   \
    {                                                               \
//        (void) __x_pack_ext;

#define SERIAL_ENCODE_END }

#define SERIAL_DECODE_BEGIN                                         \
    template<class SERIAL_DOC, class SERIAL_ME>                     \
    void SerialDecode(SERIAL_DOC& obj,                              \
                        const SERIAL_ME& me                        \
                        /*pconst xpack::Extend *__x_pack_ext*/) const   \
    {                                                               \
//        (void) __x_pack_ext;

#define SERIAL_DECODE_END }

#define Serial(...) \
    SERIAL_COMMON   \
    SERIAL_ENCODE_BEGIN \
    SERIAL_N(SERIAL_L1, SERIAL_L1_DECODE, __VA_ARGS__)                \
    SERIAL_ENCODE_END                \
    SERIAL_DECODE_BEGIN \
    SERIAL_N(SERIAL_L1, SERIAL_L1_DECODE, __VA_ARGS__)                \
    SERIAL_DECODE_END\


#endif //TESTXML_SERIAL_H

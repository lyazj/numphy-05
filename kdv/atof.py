#!/usr/bin/env python3

import ctypes

libc = ctypes.CDLL('libc.so.6')
strtod = libc.strtod
strtod.restype = ctypes.c_double

# NOTE: the libc version of atof() does not detect errors, so here...
def atof(ss: str):
    s = str(ss).strip()
    n = len(s)
    if n == 0:
        raise ValueError(f'cannot convert to c_double: {ss}')
    nptr = ctypes.c_char_p(s.encode())
    endptr = ctypes.c_char_p()
    f = strtod(nptr, ctypes.byref(endptr))
    if endptr.value:
        raise ValueError(f'cannot convert to c_double: {ss}')
    return f

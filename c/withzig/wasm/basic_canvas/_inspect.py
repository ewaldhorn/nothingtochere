# _inspect.py — Minimal WASM binary inspector (no toolchain deps).
#
# Why: `wasm-objdump` isn't always installed. This parses the import and
# export sections of a .wasm file directly so we can debug which symbols
# Zig's `-dynamic` build expects from the host (env.memory, __memory_base,
# etc.) and which C functions are exported.
#
# Usage: python3 _inspect.py main.wasm

import sys

with open(sys.argv[1], 'rb') as f:
    data = f.read()

i = 8
while i < len(data):
    sec_id = data[i]; i += 1
    sec_len = 0; shift = 0
    while True:
        b = data[i]; i += 1
        sec_len |= (b & 0x7f) << shift; shift += 7
        if not (b & 0x80): break
    end = i + sec_len
    if sec_id == 2:
        cnt = 0; shift = 0
        while True:
            b = data[i]; i += 1
            cnt |= (b & 0x7f) << shift; shift += 7
            if not (b & 0x80): break
        print(f'Imports ({cnt}):')
        for _ in range(cnt):
            ml = 0; shift = 0
            while True:
                b = data[i]; i += 1
                ml |= (b & 0x7f) << shift; shift += 7
                if not (b & 0x80): break
            mod = data[i:i+ml].decode('latin-1'); i += ml
            nl = 0; shift = 0
            while True:
                b = data[i]; i += 1
                nl |= (b & 0x7f) << shift; shift += 7
                if not (b & 0x80): break
            name = data[i:i+nl].decode('latin-1'); i += nl
            kind = data[i]; i += 1
            idx = 0; shift = 0
            while True:
                b = data[i]; i += 1
                idx |= (b & 0x7f) << shift; shift += 7
                if not (b & 0x80): break
            kn = {0:'func',1:'table',2:'memory',3:'global'}
            if mod.isprintable():
                print(f'  {mod}.{name} ({kn.get(kind,kind)})')
            else:
                print(f'  [{mod!r}].{name} ({kn.get(kind,kind)})')
    elif sec_id == 7:
        cnt = 0; shift = 0
        while True:
            b = data[i]; i += 1
            cnt |= (b & 0x7f) << shift; shift += 7
            if not (b & 0x80): break
        print(f'Exports ({cnt}):')
        for _ in range(cnt):
            nl = 0; shift = 0
            while True:
                b = data[i]; i += 1
                nl |= (b & 0x7f) << shift; shift += 7
                if not (b & 0x80): break
            name = data[i:i+nl].decode('latin-1'); i += nl
            kind = data[i]; i += 1
            idx = 0; shift = 0
            while True:
                b = data[i]; i += 1
                idx |= (b & 0x7f) << shift; shift += 7
                if not (b & 0x80): break
            kn = {0:'func',1:'table',2:'memory',3:'global'}
            if name.isprintable():
                print(f'  {name} ({kn.get(kind,kind)})')
            else:
                print(f'  [{name!r}] ({kn.get(kind,kind)})')
    i = end

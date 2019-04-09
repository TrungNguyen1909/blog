#!/usr/bin/python
import random
from pwn import *
io = remote("34.216.132.109",9094)
io.sendline("trung")
for count_ in range(1000):
	generator = "xorshift"
	random.seed(generator)
	count = 0;
	user = "trung"
	for ch in user:
			ra = random.randint(1, ord(ch))
			rb = (ord(ch) * random.randint(1, len(user))) ^ random.randint(1, ord(ch))
			count += (ra + rb)/2
	code = 1
	for i in range(1,count+count_):
			code = (code + random.randint(1, i) ) % 1000000
	final = random.randint(1,9) * 1000000 + code
        io.sendline(str(final))
        data = io.recv()
        log.info(data)
        if "flag" in data:
           exit 



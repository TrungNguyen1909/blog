from pwn import *
from parse import * 
io = remote("34.216.132.109",9093)
request = io.recv()
log.info(request)
parsed=(parse("{} {} '{:w}' {:d} times followed by '{:w}' {:d} times, followed by the sum of their ASCII values.\nThis connection will close in 10 secs ;) You gotta be fassssssssst :D \n",str(request)))
p=parsed.fixed[2::]
res=''
sum=0
for i in range(len(p)):
	if len(str(p[i]))==1 and p[i].isalpha():
		res+=p[i]*int(p[i+1])
		log.info(str(ord(p[i])))
		log.info(int(p[i+1]))
		sum+=ord(p[i])
		
res+=str(sum)
log.info(repr(str(request)))
log.info(res)
io.sendline(res)
log.info(io.recv())


from bs4 import BeautifulSoup
import urllib2
import cookielib
import sys
cnt="/fp"
url ="http://34.216.132.109:8083"
cookies = cookielib.LWPCookieJar()
handlers = [
    urllib2.HTTPHandler(),
    urllib2.HTTPSHandler(),
    urllib2.HTTPCookieProcessor(cookies)
    ]
opener = urllib2.build_opener(*handlers)

def fetch(uri):
    req = urllib2.Request(uri)
    return opener.open(req)

def dump():
    for cookie in cookies:
        print cookie.name, cookie.value
i=0

with open('wb.log','w') as f:
    while True:
        sys.stdout.flush()
        res = fetch(url+cnt+'?')
        data = res.read()
        i+=1
        soup = BeautifulSoup(data, 'html.parser') 
        sys.stdout.write("\r"+ "Pages read: {}".format(i))
        f.write(str(data)+'\n')
        if "CodefestCTF" in data:
            print soup.prettify()
            exit
        cnt = str(soup.find('form')['action'])

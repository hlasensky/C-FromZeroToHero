import codecs

login = "xhlase01"

ls = []
invLs = []

for char in login:
    res = ''.join(format(ord(i), '09b') for i in char)
    ls.append(res)
    res = res.replace("1", "2")
    res = res.replace("0", "1")
    res = res.replace("2", "0")
    invLs.append(res)

print(ls)
print(invLs)

for c in invLs:
    print("-------------------")
    print(c)
    print(int(c, 2))
    print(hex(int(c, 2)))
    print("-------------------")

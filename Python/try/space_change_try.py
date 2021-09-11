name = 'a b c'
l = list(name)
for o in range(len(l)):
    if l[o] == ' ':
        l[o] = '%20'
s = ''
for i in range(len(l)):
    s = s + l[i]
print(s)

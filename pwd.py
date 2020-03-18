pwrdfile = open('passwordfile.txt', 'w+')
words = open('words.txt', 'r')

test = words.readlines()
allpass = ""
for x in test:
    allpass = allpass+x[:-1]

pwrdfile.write(allpass)

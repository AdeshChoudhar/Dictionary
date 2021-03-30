inp = open("./WORDS.txt", "r")
out = open("../dictionaries/large", "w")

for i in inp.readlines():
    print(i.lower())
    out.write(i.lower())

inp.close()
out.close()

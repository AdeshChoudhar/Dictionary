inp = open("../dictionaries/large", "r")

letters = set()
count = 0
for i in inp.readlines():
    for j in i.lower():
        if (j not in letters) and (j != '\n'):
            letters.add(j)
print("".join(sorted(list(letters))))

inp.close()

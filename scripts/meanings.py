from sys import argv

import requests

if len(argv) == 2:
    print(f"MEANING OF WORD '{argv[1]}':\n")
    response = requests.get(f"https://api.dictionaryapi.dev/api/v2/entries/en/{argv[1]}")
    if response.status_code == 200:
        meanings = response.json()[0]['meanings']
        if not meanings:
            print("NOT FOUND!\n")

        count = 0
        for i in meanings:
            count += 1
            print(f"#{count} {str(i['partOfSpeech']).capitalize()}:")
            for j in i["definitions"]:
                print(f"\u2022 {j['definition']}")
            print()
    else:
        print("NOT FOUND!\n")
else:
    print("Usage: python meanings.py <word>")


# from PyDictionary import PyDictionary
#
# dictionary = PyDictionary()
#
# if len(argv) == 2:
#     meanings = dictionary.meaning(argv[1])
#     print(f"\nMEANING OF WORD '{argv[1]}':\n")
#
#     if meanings is None:
#         print("NOT FOUND!\n")
#     else:
#         count = 0
#         for i in list(meanings.keys()):
#             count += 1
#             print(f"#{count} {i}:")
#             for j in meanings[i]:
#                 print(f"\u2022 {j}")
#             print()
# else:
#     print("Usage: python meanings.py <word>")

import requests
from sys import argv

if len(argv) == 2:
    print(f"MEANING OF WORD '{argv[1]}':\n")
    response = requests.get(f"https://api.dictionaryapi.dev/api/v2/entries/en/{argv[1].lower()}")
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
    print("Usage: python meaning.py <word>")

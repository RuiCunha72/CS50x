import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    # scratch = 0
    # c = 0
    # python = 0
    scratch, c, python = 0, 0, 0
    for row in reader:
        favortie = row["language"]
        if favortie == "Scratch":
            scratch += 1
        elif favortie == "C":
            c += 1
        else:
            python += 1

print(f"Scratch: {scratch}")
print(f"C: {c}")
print(f"Python: {python}")
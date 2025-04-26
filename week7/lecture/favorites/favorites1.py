import csv

with open("favorites.csv", "r") as file:
    reader = csv.reader(file)
    next(reader) #avança a primeira linha (neste caso previne o print do nome da coluna)
    for row in reader:
        #print(row[1])
        favorite = row[1]
        print(favorite)
import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file) #ao contrario do reader, o DictReader em vez de dar uma sequencia de listas (row[0], 
    #row[1], row[2], ... ,row[n-1, row [n]]) ordenadas numericamente, vai dar um Dictionary para cada linha, para em vez de usar indices
    #numéricos(0,1,2,...,n-1,n), vai nos dar strings como keys para aceder aos dados que queremos, podemos usar especificamente o nome 
    #de cada coluna que são definidas na primeira linha (row[0]) do ficheiro, neste caso: Timestamp, language, problem
    for row in reader:
        #favorite = row["language"]
        #print(favorite)
        print(row["language"])
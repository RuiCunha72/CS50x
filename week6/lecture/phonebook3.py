import csv

#file = open("phonebook.csv", "a")

# name = input("Name: ")
# number = input("Number: ")

# writer = csv.writer(file)
# writer.writerow([name, number])

#file.close()

########################################################

# name = input("Name: ")
# number = input("Number: ")

# with open("phonebook.csv", "a") as file:
    
#     writer = csv.writer(file)
#     writer.writerow([name, number])

#########################################################

name = input("Name: ")
number = input("Number: ")

with open("phonebook.csv", "a") as file:
    
    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow({"name": name, "number": number})
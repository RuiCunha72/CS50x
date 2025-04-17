# people = [
#     {"name": "Yullia", "number": "+1-617-495-1000"},
#     {"name": "David", "number": "+1-617-495-1000"},
#     {"name": "John", "number": "+1-949-468-2750"}
# ]

# name = input("Name: ")
# for person in people:
#     if person["name"] == name:
#         number = person["number"]
#         print(f"Found {number}")
#         break
# else:
#     print("Not found")


people = {
    "Yuliia": "+1-617-495-1000",
    "David": "+1-617-495-1000",
    "John": "+1-949-468-2750",
}

name = input("Name: ")

if name in people:
    print(f"Number: {people[name]}")
else:
    print("Not found")

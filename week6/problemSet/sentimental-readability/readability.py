def main():
    while (True):
        try:
            text = input("Text: ")
        except ValueError:
            False
        else:
            grade = gradeLevel(text)
            if 0 < grade < 16:
                print(f"Grade {round(grade)}")
            elif grade < 1:
                print("Before Grade 1")
            else:
                print("Grade 16+")
            break


def gradeLevel(text):

    count_letters = 0
    count_words = 1
    count_sentences = 0

    for i in text:
        if "a" <= i.lower() <= "z":
            count_letters += 1
        if i == " ":
            count_words += 1
        if i in [".", "!", "?"]:
            count_sentences += 1

    l = (count_letters/count_words) * 100
    s = (count_sentences/count_words) * 100
    index = (0.0588 * l) - (0.296 * s) - 15.8
    return index


main()
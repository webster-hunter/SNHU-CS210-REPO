import re
import string

# PURPOSE: all_items reads from input file and outputs a list of all products sold
def all_items():
    file = "p3_input.txt" # input file to be read, may need to be modified for future use
    items = {} # dictionary to track items and quantity

    # READ FROM FILE
    data = open(file, "r") 
    lines = data.readlines()
    data.close()

    # ADD WORDS TO DICTIONARY
    for word in lines:
        word = word.strip()
        if word not in items:
            items[word.strip()] = 1 # add new item
        else:
            items[word.strip()] += 1 # increment quantity of existing item

    # PRINT OUTPUT
    for product in items:
        print(product + ": " + str(items[product]))


# PURPOSE: item_cout prints the quantity sold of a specific item
def item_count():
    # ITEM TO BE SEARCHED
    word = input("Product: ")

    # OPENING PRODUCT INPUT FILE
    data = open("p3_input.txt", "r")
    lines = data.readlines()
    data.close()
    
    # COUNT NUMBER OF OCCURENCES OF INPUT FILE
    count = 0
    for line in lines:
        if line.find(word.capitalize()) != -1:
            count += 1
    
    # PRINT OUTPUT TO CONSOLE
    print(str(count) + " " + word.capitalize() + " has/have been sold.\n")

    



def write_frequency():
    file = "p3_input.txt" # input file
    items = {} # product dictionary

    # OPEN INPUT FILE
    data = open(file, "r")
    lines = data.readlines()
    data.close()

    # COUNT NUMBER OF OCCURENCES OF INPUT FILE
    for word in lines:
        word = word.strip()
        if word not in items:
            items[word.strip()] = 1 # add new item
        else:
            items[word.strip()] += 1 # increment quantity of existing item

    # OPEN FREQUENCY OUTPUT FILE
    output = "frequency.dat"
    outfile = open(output, "w")

    # WRITE TO FILE
    for word in items:
        outfile.write(word + " " + str(items[word]) +"\n")

    # CLOSE OUTPUT FILE
    outfile.close()

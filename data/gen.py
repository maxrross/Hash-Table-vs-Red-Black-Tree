import names
import random_address
import random

n = int(input("Enter the number of lines to generate: "))

with open("data.txt", "w") as file:
    for i in range(n):
        first_name = names.get_first_name()
        last_name = names.get_last_name()
        address = random_address.real_random_address()
        phone_number = random.randint(1000000000, 9999999999)
        try:
            file.write(f"{first_name},{last_name},{address['address1']},{address['city']},{address['state']},{address['postalCode']},{phone_number}\n")
        except:
            # some addresses from random_address do not have a city and can be ignored for our purposes
            print("error occurred")

print(f"{n} lines written to data.txt!")

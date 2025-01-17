
# import sys

# ENCRYPTION_KEY = "secretxorkey"

# def xor(input_data, encryption_key):
	
# 	encryption_key = str(encryption_key)
# 	l = len(encryption_key)
# 	output_string = ""

# 	for i in range(len(input_data)):
# 		current_data_element = input_data[i]
# 		current_key = encryption_key[i % len(encryption_key)]
# 		output_string += chr(ord(current_data_element) ^ ord(current_key))
	
# 	return output_string

# def printCiphertext(ciphertext):
# 	print('{ 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ciphertext) + ' };')



# try:
#     plaintext = open(sys.argv[1], "rb").read()
# except:
#     print("Usage: C:\Python27\python.exe encrypt_with_xor.py PAYLOAD_FILE > OUTPUT_FILE")
#     sys.exit()


# ciphertext = xor(plaintext, ENCRYPTION_KEY)
# print('{ 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ciphertext) + ' };')


import sys

ENCRYPTION_KEY = b"secretxorkey"  # Ensure the key is a byte string

def xor(input_data, encryption_key):
    encryption_key = bytearray(encryption_key)  # Convert the key to a byte array
    l = len(encryption_key)
    output_bytes = bytearray()

    for i in range(len(input_data)):
        current_data_element = input_data[i]
        current_key = encryption_key[i % l]
        output_bytes.append(current_data_element ^ current_key)

    return output_bytes

def printCiphertext(ciphertext):
    print('{ 0x' + ', 0x'.join(hex(x)[2:] for x in ciphertext) + ' };')

try:
    plaintext = open(sys.argv[1], "rb").read()
except IndexError:
    print("Usage: C:\\Python27\\python.exe encrypt_with_xor.py PAYLOAD_FILE > OUTPUT_FILE")
    sys.exit(1)

ciphertext = xor(plaintext, ENCRYPTION_KEY)
printCiphertext(ciphertext)


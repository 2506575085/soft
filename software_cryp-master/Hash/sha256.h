typedef unsigned int uint;
typedef unsigned char ubyte;
typedef unsigned long long ull;

void declare();
uint rrot(uint val, int pos);
void sha_256(char* digest, const char* str);
char* FileSHA256(const char* file, char* sha256);

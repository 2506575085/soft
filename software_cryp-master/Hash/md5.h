#include <string>
struct md_5 {
    unsigned int count[2];
    unsigned int state[4];
    unsigned char huan_chong[64];
};

void Init(md_5 *text);
void encode(unsigned char *output, unsigned int *input, unsigned int len);
void decode(unsigned int *output, unsigned char *input, unsigned int len);
void transform(unsigned int state[4], unsigned char block[64]);
void Update(md_5 *text, unsigned char *input, unsigned int length);
void Update_file(md_5 *text, std::string input_filename);
void final_step(md_5 *text, unsigned char result[16]);
std::string fengzhuang(std::string input, md_5 *text);

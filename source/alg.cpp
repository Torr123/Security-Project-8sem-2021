#include "alg.hpp"


char* base64(const unsigned char* input, int length) {
  const auto pl = 4*((length+2)/3);
  auto output = reinterpret_cast<char *>(calloc(pl+1, 1)); //+1 for the terminating null that EVP_EncodeBlock adds on
  const auto ol = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(output), input, length);
  if (pl != ol) { std::cerr << "Whoops, encode predicted " << pl << " but we got " << ol << "\n"; }
  return output;
}

unsigned char* decode64(const char* input, int length) {
  const auto pl = 3*length/4;
  auto output = reinterpret_cast<unsigned char *>(calloc(pl+1, 1));
  const auto ol = EVP_DecodeBlock(output, reinterpret_cast<const unsigned char *>(input), length);
  if (pl != ol) { std::cerr << "Whoops, decode predicted " << pl << " but we got " << ol << "\n"; }
  return output;
}

int Cezar_Encrypt(std::ifstream& file, std::ofstream& file_out, std::vector<uint8_t> vec)
{

	uint8_t key = vec[0];
	char cr;

	if(!file.is_open())
	{
		printf("Error - open input file!\n");
		return -1;
	}


	while(file.eof() != 1)
	{

		cr = file.get();
		if(file.eof() != 1)
		{
			cr = (cr+key)%256;
			file_out.put(cr);
		}

	}
	return 0;

}

int Cezar_Decrypt(std::ifstream& encrypted_file, std::ofstream& file_out, std::vector<uint8_t> vec)
{

        uint8_t key = vec[0];
        char cr;

        if(!encrypted_file.is_open())
	{
                printf("Error - open input file!\n");
		return -1;
	}


        while(encrypted_file.eof() != 1)
        {

                cr = encrypted_file.get();
		if(encrypted_file.eof() != 1)
		{
			cr = (cr-key)%256;

			file_out.put(cr);
		}

        }
	return 0;
}

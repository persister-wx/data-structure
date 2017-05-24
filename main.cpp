#include"FileCompress1.h"

//压缩
void Testcompress()
{
	FileCompress<int> fc;
	fc.Compress("Input.txt");
}

//解压缩
void TestUncompress()
{
	FileCompress<int> fc;
	fc.Uncompress("Input.txt.huffman");
}

int main()
{
	Testcompress();
	TestUncompress();
	return 0;
}

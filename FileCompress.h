#include"HuffmanTree1.h"

typedef long long Type;

struct CharInfo
{
	CharInfo()
	:_count(0)
	{}
	bool operator != (const CharInfo& value)const
	{
		return _count != value._count;
	}

	bool operator <(const CharInfo& value)const
	{
		return _count < value._count;
	}

	CharInfo operator+(const CharInfo& data)
	{
		CharInfo ret;
		ret._count = _count + data._count;
		return ret;
	}
    unsigned char _ch;
	Type _count;
	string code;
};

template<class W>
class FileCompress
{
	typedef HuffmanTreeNode<CharInfo>  Node;

	struct _HunffmanInfo
	{
		unsigned char _ch;
		Type _count;
	};
public:
	FileCompress()
	{	
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
		}
	}

	void Compress(const char* filename)
	{
		assert(filename);
		FILE* fout = fopen(filename,"rb");
		assert(fout);
	
		//1.统计字符出现的次数
		unsigned char ch = fgetc(fout);
		while (!feof(fout))
		{
			_infos[ch]._count++;
			ch = fgetc(fout);
		}
//--------------------------------------------------------------------
//将字符出现的次数写进压缩文件
		CharInfo invalid;
		invalid._count = 0;
//---------------------------------------------------------------------
		//2.构建HuffmanTree
		HuffmanTree<CharInfo> tree(_infos,256,invalid);

		//3.生成Huffmancode
		GenerateHuffmanCode(tree.GetRoot());

		//4.压缩
		//input.txt ---》input.txt.huffman
		//获取压缩文件名
		string comPressname(filename);
		comPressname += ".huffman";
		FILE* fin = fopen(comPressname.c_str(),"wb+");//打开压缩文件
		assert(fin);
		_HunffmanInfo info;
		size_t size = 0;
		for (size_t index = 0; index < 256; ++index)
		{
			if (_infos[index]._count != 0)
			{
				info._ch = _infos[index]._ch;
				info._count = _infos[index]._count;
				size = fwrite(&info, sizeof(_HunffmanInfo),1,fin);
				assert(size == 1);//防御式编程
			}
		}

		info._count = 0;
		size = fwrite(&info, sizeof(_HunffmanInfo), 1, fin);//写进去一个标记
		assert(size == 1);//防御式编程

//----------------------------将压缩的信息（字符出现的次数）存放在压缩文件中
		//string tmp;
		//unsigned char buf[20];
		//for (size_t index = 0; index < 256; ++index)
		//{
		//	if (_infos[index] != invalid)
		//	{
		//		tmp.push_back(_infos[index]._ch);
		//		tmp.push_back(':');
		//		tmp += _itoa(_infos[index]._count,(char*)buf,16);
		//		tmp.push_back('\n');
		//		fputs(tmp.c_str(),fin);
		//		tmp.clear();//清空字符串
		//	}
		//}

		//tmp = "####\n";//结束标志
		//fputs(tmp.c_str(), fin);
//-------------------------------------------------
		size_t reCount = 1;
		fseek(fout,0,SEEK_SET);
		ch = fgetc(fout);
		char value = 0;
		int count = 0;
		while (!feof(fout))
		{
			string code = _infos[ch].code;//取到叶子节点的编码
			for (size_t index = 0; index < code.size(); ++index)
			{
				value <<= 1;
				if (code[index] == '0')
				{
					value |= 0;
				}
				else
				{
					value |= 1;
				}
				++count;
				if (count == 8)
				{
					fputc(value,fin);
					value = 0;
					count = 0;
				}
			}//读完一个字符
			ch = fgetc(fout);
			reCount++;
		}
		cout << "压缩的字符个数：" << reCount << endl;
		if (count != 0)
		{
			value <<= (8 - count);
			fputc(value,fin);
		}
		fclose(fin);
		fclose(fout);
	}

	void GenerateHuffmanCode(Node* root)
	{
		if (NULL == root)
		{
			return;
		}
		if (root->_left == NULL && root->_right == NULL)//root为叶子节点
		{
			string& code = _infos[root->_w._ch].code;
			Node* parent = root->_parent;
			Node* cur = root;
			while (parent)
			{
				if (cur == parent->_left)//cur为左节点
				{
					code.push_back('0');
					cur = parent;
					parent = cur->_parent;
				}
				else //cur为右节点
				{
					code.push_back('1');
					cur = parent;
					parent = cur->_parent;
				}
			}
			reverse(code.begin(),code.end());
		}
		GenerateHuffmanCode(root->_left);
		GenerateHuffmanCode(root->_right);
	}

	//解压缩
	//Input.txt.huffman----》Input.txt
	void Uncompress(const char* filename)
	{
		//1.获取解压缩后的文件名
		string Uncompressname = filename;
		size_t position = Uncompressname.rfind('.');
		assert(position != string::npos);
		Uncompressname = Uncompressname.substr(0, position);//pos指的是子串字符的个数
		Uncompressname += ".Unhuffman";
		FILE* fin = fopen(Uncompressname.c_str(),"wb");
		assert(fin);
		FILE* fout = fopen(filename, "rb");
		assert(fout);
		
		//-------------------------------读取字符出现的次数
		_HunffmanInfo info;
		size_t size = fread(&info, sizeof(_HunffmanInfo),1,fout);
		assert(size == 1);
		while (info._count > 0)
		{
			_infos[info._ch]._ch = info._ch;
			_infos[info._ch]._count = info._count;
		     size = fread(&info, sizeof(_HunffmanInfo), 1, fout);
			assert(size == 1);
		}
		////----------------------------------------------------
		//2.重建Huffmantree
		CharInfo invalid;
		invalid._count = 0;
		
		////char buf[20];
		////fgets(buf, 20, fout);//读取第一个字符串
		////while (strcmp(buf, "####\n") != 0)
		////{
		////	char  ch = buf[0];//获取字符
		////	_infos[ch]._count = atoi(buf+2);
		////	memset(buf,0,sizeof(buf)/sizeof(char));//清理字符数组中的内容
		////	fgets(buf, 20, fout);
		////}

		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		Node* root = tree.GetRoot();
		size = root->_w._count;//根节点的权值即是所有叶子节点的和(所有字符出现的总次数)

		char ch = fgetc(fout);//读取到8个位的编码
		char test = 1;
		Node* cur = root;
		size_t wCount = 0;
		while (size)
		{
			int pos = 7;
			while (pos >= 0)//处理从压缩文件中读出的8个位的编码
			{
				if (ch & (test << pos))//---》说明为1
				{
					cur = cur->_right;
				}
				else//说明为0
				{
					cur = cur->_left;
				}
				--pos;
				if (cur->_left == NULL && cur->_right == NULL)//到达叶子节点
				{
					fputc(cur->_w._ch, fin);
					wCount++;
					if (--size == 0)
					{
						break;
					}
					cur = root;//重置为根节点
				}
			}	
			ch = fgetc(fout);
		}
		cout << "解压缩的字符个数：" << wCount << endl;
		fclose(fin);
		fclose(fout);
	}
	
private:
	CharInfo _infos[256];
};

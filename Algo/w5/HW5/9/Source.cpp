/*
�������� ��� ������� ��� �������� ������ �� ������ ����� � ���������� ����� �� ������.


// ����� ���������� ������ �� ������ original
void Encode(IInputStream& original, IOutputStream& compressed);
// ����� ��������������� ������������ ������
void Decode(IInputStream& compressed, IOutputStream& original);
 ���:
typedef unsigned char byte;

struct IInputStream {
	// ���������� false, ���� ����� ����������
	bool Read(byte& value) = 0;
};

struct IOutputStream {
	void Write(byte value) = 0;
};

� ������� ���������� ��������� .cpp ���� ���������� ������� Encode, Decode, � ����� ���������� ���� Huffman.h. ����������� ��������� ������� ������� ��������� �� ����������� ������� ������� ����� � ���������.
*/



//#include "Huffman.h"

static void copyStream(IInputStream& input, IOutputStream& output)
{
	byte value;
	while (input.Read(value))
	{
		output.Write(value);
	}
}

void Encode(IInputStream& original, IOutputStream& compressed)
{
	copyStream(original, compressed);
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
	copyStream(compressed, original);
}

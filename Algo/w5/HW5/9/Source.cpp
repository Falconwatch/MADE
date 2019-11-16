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

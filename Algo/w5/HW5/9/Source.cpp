/*
Напишите две функции для создания архива из одного файла и извлечения файла из архива.


// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);
 где:
typedef unsigned char byte;

struct IInputStream {
	// Возвращает false, если поток закончился
	bool Read(byte& value) = 0;
};

struct IOutputStream {
	void Write(byte value) = 0;
};

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит скоринг зависящий от соотношения размера сжатого файла и исходного.
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

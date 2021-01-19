#include "Error.h"
#include <iostream>	
namespace Error
{
	// серии ошибок: 0 - 99 - системные
	//               100 - 109 - ошибки параматеров
	//               110 - 119 - ошибки открытия и чтения файлов
	//               120 - 139 - ошибки в процессе лексического анализа
	//				 200 - 299 - ошибки в процессе семантического анализа
	//				 600 - 699 - синтаксический анализ 
	ERROR errors[ERROR_MAX_ENTRY] = // Таблица ошибок
	{
	ERROR_ENTRY(0, "Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
	ERROR_ENTRY(1, "Системный сбой"),
	ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100, "Парамаетр -in должен быть задан"),
	ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102) ,ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104, "Превышена длина входного параметра"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
	ERROR_ENTRY(111, "Недопустимый символ в исходной файле (-in)"),
	ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
	ERROR_ENTRY_NODEF(113),	ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY(120, "Элемент не распознан"),
	ERROR_ENTRY(121, "Ошибка при создании лексической таблицы (превышен максимальный размер)"),
	ERROR_ENTRY(122, "Ошибка при добавлении строки в лексическую таблицу (превышен максимальный размер)"),
	ERROR_ENTRY(123, "Ошибка при получении строки лексической таблицы (нет элемента)"),
	ERROR_ENTRY(124, "Ошибка при создании таблицы идентификаторов (превышен максимальный размер)"),
	ERROR_ENTRY(125, "Ошибка при добавлении в таблицу идентификаторов (превышен максимальный размер)"),
	ERROR_ENTRY(126, "Ошибка при получении строки таблицы идентификаторов (нет элемента)"),
	ERROR_ENTRY(127, "Превышен максимальный размер строки"),
	ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),
	ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY(200,"Функция main должна быть уникальна"), 
	ERROR_ENTRY(201,"Отсутствует функция main"), 
	ERROR_ENTRY(202,"Использование необъявленного идентификатора"), 
	ERROR_ENTRY(203,"Возвращаемый тип не соответствует типу функции"),
	ERROR_ENTRY(204,"Идентификатор с таким именем уже задан в этой области видимости"),
	ERROR_ENTRY(205,"Недопустимо объявление переменной в глобальной области"), 
	ERROR_ENTRY(206,"Имя функции не может совпадать с именем функции стандартной библиотеки"), 
	ERROR_ENTRY(207,"Неверное количество параметров у вызываемой функции"),
	ERROR_ENTRY(208,"Неверные типы параметров у вызываемой функции"), 
	ERROR_ENTRY(209,"Недопустимо использование разных типов данных в одном выражении"),
	ERROR_ENTRY(210,"Тип присваемого значения не соответствует типу идентификатора"),
	ERROR_ENTRY(211,"Сравнение разных типов данных"),
	ERROR_ENTRY(212,"Недопустимо использование арифметических операций над типом string"),
	ERROR_ENTRY(213,"Индексация допустима только к типу string"),
	ERROR_ENTRY(214,"Индекс должен иметь целочисленный тип" ),
	ERROR_ENTRY(215,"Переменная цикла должна иметь целочисленный тип"),	
	ERROR_ENTRY(216,"Диапазон цикла должен иметь целочисленный тип"),
	ERROR_ENTRY_NODEF(217),ERROR_ENTRY_NODEF(218),ERROR_ENTRY_NODEF(219),
	ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230),ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF10(250),
	ERROR_ENTRY_NODEF10(260),ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
	ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
	ERROR_ENTRY(600, "Неверная структура программы"),
	ERROR_ENTRY(601, "Ошибочный оператор"),
	ERROR_ENTRY(602, "Ошибка в выражении"),
	ERROR_ENTRY(603, "Ошибка в параметрах функции"),
	ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
	ERROR_ENTRY(605, "Ошибка в арифметическом выражении"),
	ERROR_ENTRY(606, "Ошибка в условном операторе"), 
	ERROR_ENTRY(607, "Ошибка в условной конструкции"),
	ERROR_ENTRY(608, "Ошибка в операторах тела условной конструкции"),
	ERROR_ENTRY(609, "Ошибка в индексе"),
	ERROR_ENTRY(610, "Ошибка в аргументах диапазона цикла"),
	ERROR_ENTRY(611, "Ошибка в шаге цикла"),
	ERROR_ENTRY(612, "Ошибка в теле цикла"),
	ERROR_ENTRY(613, "Ошибка в операторах после тела цикла или условия"),
	ERROR_ENTRY_NODEF(614),ERROR_ENTRY_NODEF(615),ERROR_ENTRY_NODEF(616),
	ERROR_ENTRY_NODEF(617),ERROR_ENTRY_NODEF(618),ERROR_ENTRY_NODEF(619),
	ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
	ERROR_ENTRY_NODEF10(690),ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR GetError::error(int id)
	{
		ERROR err;
		if (id < 0 || id >= ERROR_MAX_ENTRY) err = errors[0];
		else err = errors[id];
		return err;
	};

	ERROR GetError::error(int id, int line)
	{
		ERROR err;
		if (id < 0 || id >= ERROR_MAX_ENTRY) id = 0;
		err.id = id;
		strcpy_s(err.message, errors[id].message);
		err.inext = { line, -1 };
		return err;
	}

	ERROR GetError::error(int id, int line, int col)
	{
		ERROR err;
		if (id < 0 || id >= ERROR_MAX_ENTRY) id = 0;
		err.id = id;
		strcpy_s(err.message, errors[id].message);
		err.inext = { line, col };
		return err;
	}

}
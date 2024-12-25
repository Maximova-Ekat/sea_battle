#include "Exception.h"

std::string InputSizeException::what() {
	std::string msg = "Ошибка: введены некорректные данные. Пожалуйста, попробуйте снова.";
	return msg;
}

std::string InputValueException::what() {
	std::string msg = "Ошибка: введено некорректное значение. Пожалуйста, попробуйте снова.";
	return msg;
}

std::string InputCoordinatesException::what() {
	std::string msg = "Ошибка: введены некорректные координаты. Пожалуйста, попробуйте снова.";
	return msg;
}

std::string InputCoordAndOrientException::what() {
	std::string msg = "Ошибка: введены некорректные координаты и ориентация. Пожалуйста, попробуйте снова.";
	return msg;
}

std::string SetShipException::what() {
	std::string msg = "Корабль не может быть расположен в указанном месте.";
	return msg;
}

std::string UseAbilityException::what() {
	std::string msg = "В данный моменту вас нет способностей, которые можно применить.";
	return msg;
}

std::string OpenFileException::what() {
	std::string msg = "Не найдено сохранений";
	return msg;
}

std::string UnknownCommandException::what() {
	std::string msg = "Неизвестная команда";
	return msg;
}

std::string AttackCommandException::what() {
	std::string msg = "В данный момент невозможно атаковать";
	return msg;
}

std::string UseAbilityCommandException::what() {
	std::string msg = "В данный невозможно использовать способность";
	return msg;
}

std::string SaveCommandException::what() {
	std::string msg = "В данный момент невозможно сохранить игру";
	return msg;
}
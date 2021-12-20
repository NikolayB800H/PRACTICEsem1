#include <fstream>
#include <iostream>

#include "file_list.hpp"

static int menu() {
    int choice = 0;
    std::cout << "==================[Меню списка файлов]===================\n"
                 "\t1 - Добавить новый файл\n"
                 "\t2 - Изменить файл\n"
                 "\t3 - Удалить файл\n"
                 "\t4 - Показать файл\n"
                 "\t5 - Показать список файлов\n"
                 "\t6 - Сохранить список файлов в файл\n"
                 "\t7 - Загрузить список файлов из файла\n"
                 "=========================================================\n"
                 "\t8 - Выход\n"
                 "=========================================================\n"
                 ">> Ваш выбор:\n<< ";
    std::cin >> choice;
    while (std::cin.fail()) {
        std::cout << ">> Ввод должен быть натуральным числом. Попробуйте ещё:\n<< ";
        std::cin.clear();
        std::cin.ignore(10, '\n');
        std::cin >> choice;
    }
    return choice;
}

static void addFileDialog(FileList &file_list) {
    std::string name;
    std::string date;
    int size = 0;
    std::cout << ">> Пожалуйста, введите имя нового файла:\n<< ";
    std::cin >> name;
    std::cout << ">> Теперь, введите дату:\n<< ";
    std::cin >> date;
    std::cout << ">> Теперь, введите размер:\n<< ";
    std::cin >> size;
    if (file_list.addFile(name, date, size) == ERROR) {
        std::cout << ">> Файл с таким именем уже есть.\n";
    } else {
        std::cout << ">> Добавление выполнено.\n";
    }
}

static void editFileDialog(FileList &file_list) {
    std::string name;
    std::cout << ">> Пожалуйста, введите имя изменяемого файла:\n<< ";
    std::cin >> name;
    if (file_list.deleteFile(name) == ERROR) {
        std::cout << ">> Файла с таким именем нет.\n";
    }
    std::string date;
    int size = 0;
    std::cout << ">> Пожалуйста, введите новое имя файла:\n<< ";
    std::cin >> name;
    std::cout << ">> Теперь, введите новую дату:\n<< ";
    std::cin >> date;
    std::cout << ">> Теперь, введите новый размер:\n<< ";
    std::cin >> size;
    if (file_list.addFile(name, date, size) == ERROR) {
        std::cout << ">> Ошибка изменения файла.\n";
    } else {
        std::cout << ">> Изменение выполнено.\n";
    }
}

static void deleteFileDialog(FileList &file_list) {
    std::string name;
    std::cout << ">> Пожалуйста, введите имя удаляемого файла:\n<< ";
    std::cin >> name;
    if (file_list.deleteFile(name) == ERROR) {
        std::cout << ">> Файла с таким именем нет.\n";
    } else {
        std::cout << ">> Удаление выполнено.\n";
    }
}

static void findByNameDialog(FileList &file_list) {
    std::string name;
    std::cout << ">> Пожалуйста, введите имя интересующего файла:\n<< ";
    std::cin >> name;
    const File *res = file_list.findByName(name);
    if (!res) {
        std::cout << ">> Файла с таким именем нет.\n";
        return;
    }
    std::cout << ">> Файл " << res->name
              << "[дата: " << res->date
              << ", размер: " << res->size
              << "]" << std::endl;
}

static void toFileFilesDialog(FileList &file_list) {
    std::string file_to;
    std::cout << ">> Пожалуйста, введите имя файла для сохранения:\n<< ";
    std::cin >> file_to;
    std::ofstream os(file_to);
    os << file_list;
    if (os.fail()) {
        std::cout << ">> Ошибка сохранения.\n";
    } else {
        std::cout << ">> Сохранение завершено.\n";
    }
    os.close();
}

static void fromFileFilesDialog(FileList &file_list) {
    std::string file_from;
    std::cout << ">> Пожалуйста, введите имя загрузочного файла:\n<< ";
    std::cin >> file_from;
    std::ifstream is(file_from);
    is >> file_list;
    if (is.fail()) {
        std::cout << ">> Ошибка загрузки.\n";
    } else {
        std::cout << ">> Загрузка завершена.\n";
    }
    is.close();
}

static void autoSave(FileList &file_list) {
    std::ofstream os("autoSave.txt");
    os << file_list;
    if (os.fail()) {
        std::cout << ">> Ошибка автосохранения.\n";
    } else {
        std::cout << ">> Автосохранение выполнено.\n";
    }
    os.close();
}

static void autoLoad(FileList &file_list) {
    std::ifstream is("autoSave.txt");
    is >> file_list;
    if (is.fail()) {
        std::cout << ">> Нет автосохранений, старт с пустым списком файлов.\n";
    } else {
        std::cout << ">> Автосохранение загружено.\n";
    }
    is.close();
}

int main(int argc, char const *argv[]) {
    FileList file_list;
    autoLoad(file_list);
    while (true) {
        switch (menu()) {
            case 1: addFileDialog(file_list); break;
            case 2: editFileDialog(file_list); break;
            case 3: deleteFileDialog(file_list); break;
            case 4: findByNameDialog(file_list); break;
            case 5: std::cout << ">> Список файлов, кол-во файлов = " << file_list; break;
            case 6: toFileFilesDialog(file_list); break;
            case 7: fromFileFilesDialog(file_list); break;
            case 8: autoSave(file_list); return 0;
            default: std::cout << ">> Выбор должен быть натуральным числом от 1 до 8.\n";
        }
    }
    return 0;
}

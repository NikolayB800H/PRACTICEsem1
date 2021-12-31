#include <fstream>
#include <iostream>

#include "file_list.hpp"

static void getSize(int &size) {
    std::cin >> size;
}

static int menu(size_t variants_cnt, const std::string (&variants)[]) {
    std::cout << "=================[Меню выбора действий]==================\n";
    for (size_t i = 0; i < variants_cnt; ++i) {
        std::cout << '\t' << i + 1 << " - " << variants[i] << std::endl;
    }
    std::cout << "=========================================================\n"
                 ">> Ваш выбор:\n<< ";
    int choice = 0;
    std::cin >> choice;
    while (std::cin.fail() || (1 > choice || choice > variants_cnt)) {
        std::cout << ">> Ввод должен быть натуральным числом от 1 до " << variants_cnt << ". Попробуйте ещё:\n<< ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    //std::cin >> size;
    getSize(size);
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
    const File *res = file_list.findByName(name);
    if (!res) {
        std::cout << ">> Файла с таким именем нет.\n";
        return;
    }
    std::string date = res->date;
    int size = res->size;
    if (file_list.deleteFile(name) == ERROR) {
        std::cout << ">> Файла с таким именем нет.\n";
        return;
    }
    std::cout << ">> Что вы хотите изменить в файле " << name
              << "[дата: " << date
              << ", размер: " << size
              << "] ?" << std::endl;
    switch (menu(4, {
            std::string("Имя"),
            std::string("Дату"),
            std::string("Размер"),
            std::string("Ничего, назад")
        })) {
        case 1: {
            std::cout << ">> Пожалуйста, введите новое имя файла:\n<< ";
            bool already_exists = false;
            do {
                std::cin >> name;
                already_exists = static_cast<bool>(file_list.findByName(name));
                if (already_exists) {
                    std::cout << ">> Файл с таким именем уже есть, придумайте другое имя:\n<< ";
                }
            } while (already_exists);
            break;
        }
        case 2:
            std::cout << ">> Пожалуйста, введите новую дату файла:\n<< ";
            std::cin >> date;
            break;
        case 3:
            std::cout << ">> Пожалуйста, введите новый размер файла:\n<< ";
            //std::cin >> size;
            getSize(size);
            break;
        case 4: break;
        default: std::cout << ">> Выбор должен быть натуральным числом от 1 до 4.\n";
    }
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
        switch (menu(8, {
            std::string("Добавить новый файл"),
            std::string("Изменить файл"),
            std::string("Удалить файл"),
            std::string("Показать файл"),
            std::string("Показать список файлов"),
            std::string("Сохранить список файлов в файл"),
            std::string("Загрузить список файлов из файла"),
            std::string("Выход")
        })) {
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

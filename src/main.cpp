#include <fstream>
#include <iostream>

#include "file_list.hpp"

static int menu() {
    int choice = 0;
    std::cout << "====================[File list menu]=====================\n"
                 "\t1 - Add file\n"
                 "\t2 - Delete file\n"
                 "\t3 - Show stats by file name\n"
                 "\t4 - Print file list\n"
                 "\t5 - Write file list to file\n"
                 "\t6 - Read files from file\n"
                 "=========================================================\n"
                 "\t7 - Exit\n"
                 "=========================================================\n"
                 ">> Your choice:\n<< ";
    std::cin >> choice;
    while (std::cin.fail()) {
        std::cout << ">> Input failed. Try again:\n<< ";
        std::cin.clear();
        std::cin.ignore(10, '\n');
        std::cin >> choice;
    }
    return choice;
}

static void addFileDialog(FileList &file_list) {
    char name[MAX_WORD_SIZE];
    char date[MAX_WORD_SIZE];
    int size = 0;
    std::cout << ">> Please, enter file name:\n<< ";
    std::cin >> name;
    std::cout << ">> Please, enter file creation date:\n<< ";
    std::cin >> date;
    std::cout << ">> Please, enter file size:\n<< ";
    std::cin >> size;
    file_list.addFile(name, date, size);
}

static void deleteFileDialog(FileList &file_list) {
    char name[MAX_WORD_SIZE];
    std::cout << ">> Please, enter file name:\n<< ";
    std::cin >> name;
    file_list.deleteFile(name);
}

static void findByNameDialog(FileList &file_list) {
    char name[MAX_WORD_SIZE];
    std::cout << ">> Please, enter file name:\n<< ";
    std::cin >> name;
    const File *res = file_list.findByName(name);
    if (!res) {
        std::cout << ">> No such file.\n";
        return;
    }
    std::cout << ">> Name: " << res->name
              << ">> Date: " << res->date
              << ">> Size: " << res->size
              << std::endl;
}

static void toFileFilesDialog(FileList &file_list) {
    char file_to[MAX_WORD_SIZE];
    std::cout << ">> Please, enter file for saving:\n<< ";
    std::cin >> file_to;
    std::ofstream os(file_to);
    os << file_list;
    os.close();
}

static void fromFileFilesDialog(FileList &file_list) {
    char file_from[MAX_WORD_SIZE];
    std::cout << ">> Please, enter file for loading:\n<< ";
    std::cin >> file_from;
    std::ifstream is(file_from);
    is >> file_list;
    is.close();
}

int main(int argc, char const *argv[]) {
    FileList file_list;
    while (true) {
        switch (menu()) {
            case 1: addFileDialog(file_list); break;
            case 2: deleteFileDialog(file_list); break;
            case 3: findByNameDialog(file_list); break;
            case 4: std::cout << ">> File list, files count = " << file_list; break;
            case 5: toFileFilesDialog(file_list); break;
            case 6: fromFileFilesDialog(file_list); break;
            case 7: return 0;
            default: std::cout << ">> Input must be in range [1, 7].\n";
        }
    }
    return 0;
}

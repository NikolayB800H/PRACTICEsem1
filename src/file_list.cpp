#include <fstream>
#include <cstring>

#include "file_list.hpp"

void File::swap(File &other) {
    File tmp = other;
    other = *this;
    *this = tmp;
}

void FileList::binSearch(const char *name, int &back, int &front) const {
    back = -1;
    front = files_cnt;
    int mid = 0;
    while (front > back + 1) {
        mid = (back + front) / 2;
        int cmp = strcmp(name, file_arr[mid].name);
        if (cmp < 0) {
            front = mid;
        } else if (cmp > 0) {
            back = mid;
        } else {
            front = mid;
            back = mid;
        }
    }
    if (front == back) {
        return;
    }
    if (back != -1 && !strcmp(name, file_arr[back].name)) {
        front = back;
        return;
    }
    if (front != files_cnt && !strcmp(name, file_arr[front].name)) {
        back = front;
        return;
    }
}

void FileList::emplaceBack(const char *name, const char *date, int size) {
    strncpy(file_arr[files_cnt].name, name, MAX_WORD_SIZE - 1);
    file_arr[files_cnt].name[MAX_WORD_SIZE - 1] = 0;
    strncpy(file_arr[files_cnt].date, date, MAX_WORD_SIZE - 1);
    file_arr[files_cnt].date[MAX_WORD_SIZE - 1] = 0;
    file_arr[files_cnt].size = size;
    ++files_cnt;
}

FileList::FileList() : files_cnt(0) {
}

void FileList::addFile(const char *name, const char *date, int size) {
    int back = 0;
    int front = 0;
    if (!files_cnt) {
        emplaceBack(name, date, size);
        return;
    }
    binSearch(name, back, front);
    if (back == front) {
        return;
    }
    emplaceBack(name, date, size);
    for (int adding = files_cnt - 1; adding != front; --adding) {
        file_arr[adding].swap(file_arr[adding - 1]);
    }
}

void FileList::deleteFile(const char *name) {
    int back = 0;
    int front = 0;
    if (!files_cnt) {
        return;
    }
    binSearch(name, back, front);
    if (back != front) {
        return;
    }
    for (int deleting = front; deleting != files_cnt - 1; ++deleting) {
        file_arr[deleting].swap(file_arr[deleting + 1]);
    }
    --files_cnt;
}

const File *FileList::findByName(const char *name) const {
    int back = 0;
    int front = 0;
    if (!files_cnt) {
        return nullptr;
    }
    binSearch(name, back, front);
    if (back != front) {
        return nullptr;
    }
    return file_arr + front;
}

std::ostream &operator<<(std::ostream &os, const FileList &file_list) {
    os << file_list.files_cnt << '\n';
    for (int i = 0; i < file_list.files_cnt; ++i) {
        os << '\t' << file_list.file_arr[i].name << ' ' << file_list.file_arr[i].date << ' ' << file_list.file_arr[i].size << '\n';
    }
    os.flush();
    return os;
}

std::istream &operator>>(std::istream &is, FileList &file_list) {
    int add_cnt = 0;
    is >> add_cnt;
    char name[MAX_WORD_SIZE];
    char date[MAX_WORD_SIZE];
    int size = 0;
    for (int i = 0; i < add_cnt; ++i) {
        is >> name >> date >> size;
        file_list.addFile(name, date, size);
    }
    return is;
}

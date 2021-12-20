#include <fstream>
#include <cstring>

#include "file_list.hpp"

File::File(const std::string &name, const std::string &date, int size) : name(name), date(date), size(size) {
}

void File::swap(File &other) {
    File tmp = other;
    other = *this;
    *this = tmp;
}

void FileList::binSearch(const std::string &name, int &back, int &front) const {
    back = -1;
    // front = files_cnt;
    front = file_arr.size();
    int mid = 0;
    while (front > back + 1) {
        mid = (back + front) / 2;
        int cmp = strcmp(name.c_str(), file_arr[mid].name.c_str());
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
    if (back != -1 && !strcmp(name.c_str(), file_arr[back].name.c_str())) {
        front = back;
        return;
    }
    // if (front != files_cnt && !strcmp(name, file_arr[front].name)) {
    if (front != file_arr.size() && !strcmp(name.c_str(), file_arr[front].name.c_str())) {
        back = front;
        return;
    }
}

void FileList::emplaceBack(const std::string &name, const std::string &date, int size) {
    //strncpy(file_arr[files_cnt].name, name, MAX_WORD_SIZE - 1);
    // file_arr[files_cnt].name = name;
    //file_arr[files_cnt].name[MAX_WORD_SIZE - 1] = 0;
    //strncpy(file_arr[files_cnt].date, date, MAX_WORD_SIZE - 1);
    // file_arr[files_cnt].date = date;
    //file_arr[files_cnt].date[MAX_WORD_SIZE - 1] = 0;
    // file_arr[files_cnt].size = size;
    // ++files_cnt;
    file_arr.emplace_back(name, date, size);
}

/*FileList::FileList() : files_cnt(0) {
}*/

RetStatus FileList::addFile(const std::string &name, const std::string &date, int size) {
    int back = 0;
    int front = 0;
    // if (!files_cnt) {
    if (!file_arr.size()) {
        emplaceBack(name, date, size);
        return OK;
    }
    binSearch(name, back, front);
    if (back == front) {
        return ERROR;
    }
    emplaceBack(name, date, size);
    // for (int adding = files_cnt - 1; adding != front; --adding) {
    for (int adding = file_arr.size() - 1; adding != front; --adding) {
        file_arr[adding].swap(file_arr[adding - 1]);
    }
    return OK;
}

RetStatus FileList::deleteFile(const std::string &name) {
    int back = 0;
    int front = 0;
    // if (!files_cnt) {
    if (!file_arr.size()) {
        return ERROR;
    }
    binSearch(name, back, front);
    if (back != front) {
        return ERROR;
    }
    // for (int deleting = front; deleting != files_cnt - 1; ++deleting) {
    for (int deleting = front; deleting != file_arr.size() - 1; ++deleting) {
        file_arr[deleting].swap(file_arr[deleting + 1]);
    }
    file_arr.pop_back();
    //--files_cnt;
    return OK;
}

const File *FileList::findByName(const std::string &name) const {
    int back = 0;
    int front = 0;
    //if (!files_cnt) {
    if (!file_arr.size()) {
        return nullptr;
    }
    binSearch(name, back, front);
    if (back != front) {
        return nullptr;
    }
    return &file_arr[front];
}

std::ostream &operator<<(std::ostream &os, const FileList &file_list) {
    // os << file_list.files_cnt << '\n';
    os << file_list.file_arr.size() << '\n';
    // for (int i = 0; i < file_list.files_cnt; ++i) {
    for (int i = 0; i < file_list.file_arr.size(); ++i) {
        os << '\t' << file_list.file_arr[i].name << ' ' << file_list.file_arr[i].date << ' ' << file_list.file_arr[i].size << '\n';
    }
    os.flush();
    return os;
}

std::istream &operator>>(std::istream &is, FileList &file_list) {
    int add_cnt = 0;
    is >> add_cnt;
    std::string name;
    std::string date;
    int size = 0;
    for (int i = 0; i < add_cnt; ++i) {
        is >> name >> date >> size;
        file_list.addFile(name, date, size);
    }
    return is;
}

#pragma ONCE

#include <vector>
#include <string>

enum RetStatus {
    OK,
    ERROR
};

struct File {
    std::string name;
    std::string date;
    int size;

    File(const std::string &name, const std::string &date, int size);
    void swap(File &other);
};

class FileList {
    int files_cnt;
    std::vector<File> file_arr;

    void binSearch(const std::string &name, int &back, int &front) const;
    void emplaceBack(const std::string &name, const std::string &date, int size);

public:
    RetStatus addFile(const std::string &name, const std::string &date, int size);
    RetStatus deleteFile(const std::string &name);
    const File *findByName(const std::string &name) const;
    friend
    std::ostream &operator<<(std::ostream &os, const FileList &file_list);
    friend
    std::istream &operator>>(std::istream &is, FileList &file_list);
};

std::ostream &operator<<(std::ostream &os, const FileList &file_list);
std::istream &operator>>(std::istream &is, const FileList &file_list);

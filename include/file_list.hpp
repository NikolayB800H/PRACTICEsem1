#pragma ONCE

constexpr size_t MAX_WORDS_CNT = 100;
constexpr size_t MAX_WORD_SIZE = 31;

struct File {
    char name[MAX_WORD_SIZE];
    char date[MAX_WORD_SIZE];
    int size;

    void swap(File &other);
};

class FileList {
    int files_cnt;
    File file_arr[MAX_WORDS_CNT];

    void binSearch(const char *name, int &back, int &front) const;
    void emplaceBack(const char *name, const char *date, int size);

public:
    FileList();
    void addFile(const char *name, const char *date, int size);
    void deleteFile(const char *name);
    const File *findByName(const char *name) const;
    friend
    std::ostream &operator<<(std::ostream &os, const FileList &file_list);
    friend
    std::istream &operator>>(std::istream &is, FileList &file_list);
};

std::ostream &operator<<(std::ostream &os, const FileList &file_list);
std::istream &operator>>(std::istream &is, const FileList &file_list);

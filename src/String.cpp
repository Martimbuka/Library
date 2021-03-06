#include "String.hpp"
using namespace library;

// Private

size_t String :: strlen(const char* str) {
    const char *s;
	for (s = str; *s; ++s);
	return (s - str);
}

char* String :: create(const size_t& reserve) {
    char *buffer = nullptr;
    try
    {
        buffer = new char[reserve+1];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return buffer;
}

void String :: copy_string(const char* text) {
    size = strlen(text);
    char *buffer = nullptr;
    buffer = create(size+1);  
    strcpy_s(buffer, size+1, text);
    data = buffer;
}

void String :: copy_element(const char& element) {
    size = 1;
    char* buffer = nullptr;
    buffer = create(2);
    buffer[0] = element;
    buffer[1] = '\0';
    data = buffer;
}

void String :: erase() {
    delete[] data;
    data = nullptr;
    size = 0;
}

// Public

String :: String () : data{nullptr}, size{0} {

}

String :: String (const char& element) {
    copy_element(element);
}

String :: String(const char* text) {
    copy_string(text);
}

String :: String(const size_t& size, const char& value) : size{size} {
    char *buffer = nullptr;
    try
    {
        buffer = new char[size+1];
    }
    catch(const std::exception& e)
    {
        std::cerr << "Fill Constructor String: " << e.what() << '\n';
    }
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = value;
    }
    buffer[size] = '\0';
    data = buffer;
}

String :: String(const String& other) {
    copy_string(other.data);
}

String :: ~String() {
    delete[] data;
}

String& String :: operator=(const String &rhs) {
    if (this != &rhs) {
        erase();
        copy_string(rhs.data);
    }
    return *this;
}

String& String :: operator=(const char* rhs) {
    erase();
    copy_string(rhs);
    return *this;
}

String& String :: operator=(const char &rhs) {
    erase();
    copy_element(rhs);
    return *this;
}

const char& String :: operator[](const size_t& index) const {
    if (index > size) {
        throw std::out_of_range("index out of bound");
    }
    return data[index];
}

char& String :: operator[] (const size_t& index) {
    if (index > size) 
        throw std::out_of_range("index out of bound");
    return data[index];
}

bool String :: empty() const {
    if (!size) return true;
    return false;
}

void String :: setString(const char* text) {
    erase();
    copy_string(text);
}

const char* String :: getString() const {
    return data;
}

const size_t String :: length() const {
    return size;
}

String String :: operator+(const String& rhs) const {
    String result;
    result.size += this->size + rhs.size;
    char *buffer = nullptr;
    buffer = create(result.size);
    for (size_t i = 0; i < size ; ++i) {
        buffer[i] = data[i];
    }
    for (size_t i = size, j = 0; i < result.size && j < rhs.size; ++i, ++j) {
        buffer[i] = rhs.data[j];
    }
    buffer[result.size] = '\0';
    result.data = buffer;
    return result;
}

String String :: operator+(const char* rhs) const {
    String result;
    result.size += this->size + strlen(rhs);
    char *buffer = nullptr;
    buffer = create(result.size);
    for (size_t i = 0; i < size ; ++i) {
        buffer[i] = data[i];
    }
    for (size_t i = size, j = 0; i < result.size && j < strlen(rhs); ++i, ++j) {
        buffer[i] = rhs[j];
    }
    buffer[result.size] = '\0';
    result.data = buffer;
    return result;
}

String String :: operator+(const char& rhs) const {
    String result;
    result.size += this->size + 1;
    char *buffer = nullptr;
    buffer = create(result.size);
    for (size_t i = 0; i < size ; ++i) {
        buffer[i] = data[i];
    }
    buffer[result.size-1] = rhs;
    buffer[result.size] = '\0';
    result.data = buffer;
    return result;
}

String& String :: operator+=(const String& rhs) {
    *this = *this + rhs;
    return *this;
}

String& String :: operator+=(const char* rhs) {
    *this = *this + rhs;
    return *this;
}

String& String :: operator+=(const char& rhs) {
    *this = *this + rhs;
    return *this;
}

bool String :: operator==(const String& rhs) const {
    if (size != rhs.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool String :: operator==(const char *rhs) const {
    if (size != strlen(rhs)) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool String :: operator==(const char& rhs) const {
    if (size != 1) {
        return false;
    }
    if (data[0] != rhs) {
        return false;
    }
    return true;
}

bool String :: operator!=(const String& rhs) const {
    return !(*this == rhs);
}

bool String :: operator!=(const char* rhs) const {
    return !(*this == rhs);
}

bool String :: operator!=(const char& rhs) const {
    return !(*this == rhs);
}

bool String :: operator>(const String &other) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other[i]) {
            if (data[i] > other[i])
                return true;
            else
                return false;
        }
    }
    return true;
}

bool String :: operator<(const String &other) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other[i]) {
            if (data[i] < other[i])
                return true;
            else
                return false;
        }
    }
    return true;
}

void String :: clear() {
    erase();
}

void String :: insert(const char& element, const size_t& position) {
    ++size;
    for (size_t i = size; i > position; --i) {
        data[i] = data[i-1];
    }
    data[position] = element;
}

void String :: swap(String& lhs, String& rhs) {
    if (lhs.data == nullptr || rhs.data == nullptr) {
        std::cerr << "swap is imposible with nullptr\n";
        return;
    }
    String temp = lhs;
    lhs = rhs;
    rhs = temp;
}

size_t String :: find (const char& element,const size_t& from, const size_t& to) const {
    try {
        if (from > size || to > size || from > to) {
            throw std::out_of_range("index out of bound");
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    for (size_t i = from; i < to; ++i) {
            if (element == data[i]) {
                return i;
            }
        }
    return -1;
}

String String :: substr(const size_t& from, const size_t& to) const {
    if (from > size || to > size || from > to) {
        throw std::out_of_range("index out of bound");
    }
    String result;
    result.size = to - from + 1;
    char* buffer = create(result.size);
    for (size_t i = 0, j = from; i < result.size && j <= to; ++i, ++j) {
        buffer[i] = data[j];
    }
    buffer[result.size] = '\0';
    result.data = buffer;
    return result;
}

void String :: toLower() noexcept{
    for (size_t i = 0; i < size; ++i) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = data[i] + ('a'-'A');
        }
    }
}

void String :: toUpper() noexcept {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = data[i] - ('a'-'A');
        }
    }
}

void String :: removeElement(const size_t& index) {
    if (index >= size) throw std::invalid_argument("Removing index is out of range of the array!");
    for (size_t i = index; i < size; ++i) {
        data[i] = data[i+1];
    }
    if (size > 0)
        --size;
}

void String :: removeSpaces() {
    size_t index = 0;
    while (index < size) {
        if (data[0] == ' ') {
            removeElement(0);
        }
        else if (data[index] == ' ' && data[index+1] == ' ') {
            removeElement(index);
        }
        else ++index;
    }

    if (data[size-1] == ' ') {
        size_t lastIndex = size - 1;
        removeElement(lastIndex);
    }
}

unsigned String :: toUnisgned() const{
    unsigned num = 0;
    for (size_t i = size - 1, digit = 1; i >= 0; --i, digit *= 10) {
        num += (data[i] - '0') * digit;
    }
    return num;
}

int String :: toInt() const {
    int num = 0;
    for (size_t i = size - 1, digit = 1; i >= 0; --i, digit *= 10) {
        if (data[i] == '-')
            return num * -1;
        num += (data[i] - '0') * digit;
    }
    return num;
}

double String :: toDouble() const {
    double num = 0.0;
    for (size_t i = size - 1, digit = 1; i >= 0; --i, digit *= 10) {
        if (data[i] == '-')
            return num * -1;
        num += (data[i] - '0') * digit;
    }

    return num;
}

bool String :: toBool() const{
    if (*this == "true" || *this == "1")
        return true;
    else
        return false;
}

int String :: find(const String& find) {
    if (find.size > size) {
        return -1;
    }
    for (size_t i = 0; i < (size - find.size + 1); ++i) {
        if (find == substr(i,i+find.size-1)) {
            return i;
        }
    }
    return -1;
}
int String :: find(const char* find) {
    size_t find_size = strlen(find);
    if (find_size > size) {
        return -1;
    }
    for (size_t i = 0; i < (size - find_size + 1); ++i) {
        if (find == substr(i, i + find_size - 1)) {
            return i;
        }
    }
    return -1;
}

int String :: find(const char& find) {
    if (size == 0) {
        return -1;
    }
    for (size_t i = 0; i < size; ++i) {
        if (find == data[i]) {
            return i;
        }
    }
    return -1;
}



/*std::istream &operator>>(std::istream &in, String &object) {
    char ch;
    char *buffer;
    try {
        buffer = new char[1000];
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    const char BACKSPACE = 8;
    const char RETURN = 13;
    int i = 0;

    while (ch != RETURN) {
        if (i == 1000) {
            throw("Buffer overflow!");
        }
        ch = getch();
        if (ch != RETURN && ch != BACKSPACE) {
            std::cout << ch;
            buffer[i] = ch;
            ++i;
        }
        if (ch == BACKSPACE && i > 0) {
            --i;
            std::cout << "\b \b";
            continue;
        }
    }
    buffer[i] = '\0';
    object = String{buffer};
    delete[] buffer;
    std::cout << '\n';
    return in;
}*/
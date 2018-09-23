#include <algorithm>
#include <iostream>

using std::string;
using std::vector;

struct string_limits {
  char* start = nullptr;
  size_t length = 0;
  string_limits(char* start_) : start(start_), length(0) {}
};

void DirectSort(vector<string_limits> &strings_starts, const vector<char> &punctuation_marks) {
  std::sort(strings_starts.begin(), strings_starts.end(),
            [&punctuation_marks](string_limits string1, string_limits string2) -> bool {
              char *ch1 = string1.start;
              char *ch2 = string2.start;
              while (*ch1 != '\0' || *ch2 != '\0') {
                while ((std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch1)) !=
                    punctuation_marks.end()) {
                  ch1++;
                }
                while ((std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch2)) !=
                    punctuation_marks.end()) {
                  ch2++;
                }
                if (*ch1 == *ch2) {
                  ch1++;
                  ch2++;
                  continue;
                }
                return *ch1 < *ch2;
              }
              if (*ch1 == '\0') {
                return true;
              }
              return *ch2 != '\0';
            }
  );
}

void NonDirectSort(vector<string_limits> &strings_starts, const vector<char> &punctuation_marks) {
  std::sort(strings_starts.begin(), strings_starts.end(),
            [&punctuation_marks](string_limits string1, string_limits string2) -> bool {
              char *ch1 = string1.start + string1.length;
              char *ch2 = string2.start + string2.length;
              while (ch1 != string2.start || ch2 != string1.start) {
                while ((std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch1)) !=
                    punctuation_marks.end()) {
                  ch1--;
                }
                while ((std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch2)) !=
                    punctuation_marks.end()) {
                  ch2--;
                }
                if (*ch1 == *ch2) {
                  ch1--;
                  ch2--;
                  continue;
                }
                return *ch1 < *ch2;
              }
              if (ch1 == string1.start) {
                return true;
              }
              return ch2 != string2.start;
            }
  );
}

size_t GetFileLength(FILE *f) {
  fseek(f, 0, SEEK_END);
  size_t text_length = ftell(f);
  fseek(f, 0, SEEK_SET);
  return text_length;
}

void WriteStrings(FILE* f, vector<string_limits> &strings_starts) {
  for (int i = 0; i < strings_starts.size(); ++i) {
    fprintf(f, "%s", strings_starts[i].start);
    fprintf(f, "%c", '\n');
  }
}

void TextIndexing ( vector<string_limits> &strings_starts, char *text, size_t text_length){
  strings_starts.push_back(&text[0]);
  size_t previous_index = 0;
  for (size_t i = 1; i < text_length; i++) {
    if (text[i] == '\n') {
      text[i] = '\0';
      strings_starts.back().length = i - previous_index;
      if (text[i + 1] != '\n') {
        strings_starts.push_back(&text[i + 1]);
        previous_index = i + 1;
      }
    }
  }
}

int main() {

  setlocale(LC_ALL, "Russian");

  FILE *f_read = fopen("EugeneOnegin.txt", "r");
  if (f_read == NULL) {
    std::cout << "Файл EugeneOnegin.txt не удалось открыть." << std::endl;
    return 1;
  }

  FILE *f_write = fopen("result.txt", "w");
  if (f_write == NULL) {
    std::cout << "Файл result.txt не удалось открыть." << std::endl;
    return 1;
  }

  size_t text_length = GetFileLength(f_read);
  char *text = new char[text_length + 1];
  fread(text, sizeof(char), text_length, f_read);
  text[text_length] = '\0';

  fclose(f_read);

  vector<string_limits> strings_starts;
  TextIndexing(strings_starts, text, text_length);

  vector<char> punctuation_marks({' ', '.', ',', '?', '!', ':', ';', '-', '(', ')', '<', '>'});

  DirectSort(strings_starts, punctuation_marks);

  fprintf(f_write, "%s", "Результат стандартной сортировки строк, с сравнением с начала строки:\n\n");
  WriteStrings(f_write, strings_starts);

  NonDirectSort(strings_starts, punctuation_marks);

  fprintf(f_write, "%s", "\n\nРезультат нестандартной сортировки строк, с сравнением с конца строки:\n\n");
  WriteStrings(f_write, strings_starts);

  for (size_t i = 0; i < text_length; i++) {
    if (text[i] == '\0') {
      text[i] = '\n';
    }
  }

  fprintf(f_write, "%s", "\n\nОригинальный текст:\n\n");
  fprintf(f_write, "%s", text);
  fprintf(f_write, "%c", '\n');

  fclose(f_write);

  delete[] text;

  return 0;
}

#include <algorithm>
#include <iostream>

using std::string;
using std::vector;

void DirectSort(vector<char *> &strings_starts, const vector<char> &punctuation_marks) {
  std::sort(strings_starts.begin(), strings_starts.end(), [&punctuation_marks](char *string1, char *string2) -> bool {
              string str1_no_marks, str2_no_marks;
              for (char *ch = string1; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) ==
                    punctuation_marks.end())) continue;
                str1_no_marks.push_back(*ch);
              }
              for (char *ch = string2; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) ==
                    punctuation_marks.end())) continue;
                str2_no_marks.push_back(*ch);
              }
              return str1_no_marks < str2_no_marks;
            }
  );
}

void NonDirectSort(vector<char *> &strings_starts, const vector<char> &punctuation_marks) {
  std::sort(strings_starts.begin(), strings_starts.end(), [&punctuation_marks](char *string1, char *string2) -> bool {
              string str1_no_marks, str2_no_marks;
              for (char *ch = string1; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) ==
                    punctuation_marks.end())) continue;
                str1_no_marks = *ch + str1_no_marks;
              }
              for (char *ch = string2; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) ==
                    punctuation_marks.end())) continue;
                str2_no_marks = *ch + str2_no_marks;
              }
              return str1_no_marks < str2_no_marks;
            }
  );
}

size_t GetFileLength(FILE *f) {
  fseek(f, 0, SEEK_END);
  size_t text_length = ftell(f);
  fseek(f, 0, SEEK_SET);
  return text_length;
}

void WriteStrings(FILE* f, vector<char*> &strings_starts) {
  for (int i = 0; i < strings_starts.size(); ++i) {
    fprintf(f, "%s", strings_starts[i]);
    fprintf(f, "%c", '\n');
  }
}

int main() {

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
  char *text = new char[text_length + 1] {};
  fread(text, sizeof(char), text_length, f_read);
  text[text_length] = '\0';

  fclose(f_read);
  vector<char *> strings_starts;
  strings_starts.push_back(&text[0]);
  for (size_t i = 1; i < text_length; i++) {
    if (text[i] == '\n') {
      text[i] = '\0';
      if (text[i + 1] != '\n') {
        strings_starts.push_back(&text[i + 1]);
      }
    }
  }

  vector<char *> first_strings_starts(strings_starts);

  const vector<char> punctuation_marks({'.', ',', '?', '!', ' ', ':', ';', '-', '(', ')', '<', '>'});
  WriteStrings(f_write, strings_starts);
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
  WriteStrings(f_write, first_strings_starts);

  fclose(f_write);

  delete[] text;

  return 0;
}

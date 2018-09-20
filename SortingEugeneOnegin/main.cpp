#include <algorithm>
#include <iostream>


int main() {

  FILE *f_read = fopen("EugeneOnegin.txt", "r");
  if (f_read == NULL) {
    // файл EugeneOnegin.txt не удалось открыть для чтения
    std::cout << "Файл EugeneOnegin.txt не удалось открыть." << std::endl;
    return 1;
  }

  FILE *f_write = fopen("result.txt", "w");
  if (f_write == NULL) {
    // файл result.txt не удалось открыть для записи
    std::cout << "Файл result.txt не удалось открыть." << std::endl;
    return 1;
  }

  fseek(f_read, 0, SEEK_END);
  size_t text_length = ftell(f_read);
  fseek(f_read, 0, SEEK_SET);
  char *text = new char[text_length + 1];
  fread(text, sizeof(char), text_length, f_read);
  text[text_length] = '\0';

  fclose(f_read);

  std::vector<char *> strings_starts;
  strings_starts.push_back(&text[0]);
  for (size_t i = 1; i < text_length; i++) {
    if (text[i] == '\n') {
      text[i] = '\0';
      if (text[i + 1] != '\n') {
        strings_starts.push_back(&text[i + 1]);
      }
    }
  }

  std::vector<char> punctuation_marks({' ', '.', ',', '?', '!', ':', ';', '-', '(', ')', '<', '>'});

  std::sort(strings_starts.begin(), strings_starts.end(), [&punctuation_marks](char *string1, char *string2) -> bool {
              std::string str1, str2;
              for (char *ch = string1; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) == punctuation_marks.end())) continue;
                str1.push_back(*ch);
              }
              for (char *ch = string2; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) == punctuation_marks.end())) continue;
                str2.push_back(*ch);
              }
              return str1 < str2;
            }
  );

  fprintf(f_write, "%s", "Результат стандартной сортировки строк, с сравнением с начала строки:\n\n");
  for (int i = 0; i < strings_starts.size(); ++i) {
    fprintf(f_write, "%s", strings_starts[i]);
    fprintf(f_write, "%c", '\n');
  }

  std::sort(strings_starts.begin(), strings_starts.end(), [&punctuation_marks](char *string1, char *string2) -> bool {
              std::string str1, str2;
              for (char *ch = string1; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) == punctuation_marks.end())) continue;
                str1 = *ch + str1;
              }
              for (char *ch = string2; *ch != '\0'; ch++) {
                if (!(std::find(punctuation_marks.begin(), punctuation_marks.end(), *ch) == punctuation_marks.end())) continue;
                str2 = *ch + str2;
              }
              return str1 < str2;
            }
  );

  fprintf(f_write, "%s", "\n\nРезультат нестандартной сортировки строк, с сравнением с конца строки:\n\n");
  for (int i = 0; i < strings_starts.size(); ++i) {
    fprintf(f_write, "%s", strings_starts[i]);
    fprintf(f_write, "%c", '\n');
  }

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

/* Размеры вселенной 78х24 клеток, +2 сверху и снизу для организации тора */
#define _CRT_SECURE_NO_WARNINGS
bool selectMenuItem(void);											// Выбираем метод заполнения первого поколения, true - файл, false - вручную
void printAbout(void);												// Выводим информацию о программе, предлагаем выбрать пункт меню
void randomMattrix(int**, const int, const int);						// Заполняем первое поколение случайным образом
int fileMattrix(int**, const int, const int);							// Заполняем первое поколение из файла
inline void initTor(int**, const int, const int);							// Инициализируем тор
inline void tor(int**, const int, const int);						// Организуем бесконечную поверхность - тор
inline int  neighbors(int**, const int, const int);					// Подсчитывает количество соседей
inline bool isNull(int**, int**, const int, const int);				// Проверяем, если еще живые
inline bool lifeStep(int** &, int** &, const int, const int);		// Проверяем количество живых соседей и рожаем или убиваем клетку

void printMassive(int**, const int, const int);						// Печатаем весь массив
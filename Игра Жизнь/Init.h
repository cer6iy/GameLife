/* ������� ��������� 78�24 ������, +2 ������ � ����� ��� ����������� ���� */
#define _CRT_SECURE_NO_WARNINGS
bool selectMenuItem(void);											// �������� ����� ���������� ������� ���������, true - ����, false - �������
void printAbout(void);												// ������� ���������� � ���������, ���������� ������� ����� ����
void randomMattrix(int**, const int, const int);						// ��������� ������ ��������� ��������� �������
int fileMattrix(int**, const int, const int);							// ��������� ������ ��������� �� �����
inline void initTor(int**, const int, const int);							// �������������� ���
inline void tor(int**, const int, const int);						// ���������� ����������� ����������� - ���
inline int  neighbors(int**, const int, const int);					// ������������ ���������� �������
inline bool isNull(int**, int**, const int, const int);				// ���������, ���� ��� �����
inline bool lifeStep(int** &, int** &, const int, const int);		// ��������� ���������� ����� ������� � ������ ��� ������� ������

void printMassive(int**, const int, const int);						// �������� ���� ������
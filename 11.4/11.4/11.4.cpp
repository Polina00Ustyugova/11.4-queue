#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
struct point // узел
{
	string key; // Информация в узле
	point* prev, * next; // Указатель на следующий элемент
};

point* MakeQueue(int n) // Создание и заполнение очереди
{
	cout << "Введите информацию, которую хотите записать: " << endl;
	string s;
	getline(cin, s);
	getline(cin, s);
	point* p, * r, * van;
	p = new (point);
	p->key = s;
	p->prev = nullptr;
	p->next = nullptr;
	van = p;

	for (int i = 1; i < n; i++) //добавить элементы в конец очереди
	{
		r = new(point);
		cout << "Введите информацию, которую хотите записать: " << endl;
		string s;
		getline(cin, s);
		r->key = s;
		p->next = r;
		r->prev = p;
		r->next = nullptr;
		p = r;
	}
	return van;
}

void print_list(point* van) // Вывод очереди на консоль
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (van == 0) //если очередь пуста
	{
		cout << "Очередь пуста\n" << endl;
		return;
	}
	point* p = van;
	int i = 1;
	cout << "Ваша очередь:" << endl;
	while (p != 0) //пока не конец очереди
	{
		cout << i << ". " << p->key << endl; // Вывод информации, содержащейся в узле
		p = p->next; //перейти на следующий элемент
		i++;
	}
	cout << "\n";
}
point* push(point* ctrl) // Добавляет элемент в конец
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	point* p;
	p = new(point);
	cout << "Введите новую информацию: " << endl; // Заполнение нового нового узла информацией
	string s;
	getline(cin, s);
	getline(cin, s);
	p->key = s;
	point* r = ctrl; //встать на начало очереди
	while (r->next != nullptr)  r = r->next;
	r->next = p; //связать р с концом очереди
	p->prev = r; //связать р и r
	p->next = nullptr;
	return ctrl;
}
point* pop(point* van) // Удаляет первый элемент
{
	van = van->next;
	if (van == nullptr) return nullptr;
	van->prev = nullptr;
	return van;
}
point* delete_list(point* van) // Удалить очередь
{
	while (van) van = pop(van);
	return van;
}

void printINfile(point* van, string path) // Запись очереди в файл
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout;
	fout.open(path);
	if (!fout.is_open()) { cout << "Ошибка открытия файла!" << endl; }
	else {
		point* p = van;
		while (p != nullptr) {
			fout << p->key;
			fout << endl;
			p = p->next;
		}
	}
	cout << "Информация была внесена в файл" << endl;
	fout.close();
}

point* ReadFromFile(string path) // Восстановление информации из файла
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin;
	fin.open(path);
	point* van = new(point);
	if (!fin.is_open()) { cout << "Ошибка открытия файла!" << endl; }
	else {
		cout << "Информация была восстановлена!" << endl;
		string word;
		point* p, * r;
		p = new (point);
		fin >> word;
		p->key = word;
		p->prev = nullptr;
		p->next = nullptr;
		van = p;

		while (!fin.eof())
		{
			word = "";
			fin >> word;
			r = new(point);
			r->key = word;
			p->prev = nullptr;
			p->next = r;
			r->prev = p;
			r->next = nullptr;
			p = r;
		}
	}
	fin.close();
	return van;
}
void menu(int a, point* first, int n)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string path = "myFile.txt";
	switch (a)
	{
	case 0:
		exit(777);
	case 1:
	{
		cout << "Введите размер очереди: " << endl;
		cin >> n;
		first = MakeQueue(n);
		print_list(first);
		break;
	}
	case 2:
	{
		first = pop(first);
		print_list(first);
		break;
	}
	case 3:
	{
		first = push(first);
		print_list(first);
		break;
	}
	case 4:
	{
		first = delete_list(first);
		print_list(first);
		break;
	}
	case 5:
	{
		printINfile(first, path);
		break;
	}
	case 6:
	{
		first = ReadFromFile(path);
		print_list(first);
		break;
	}
	default:
	{
		cout << "Пожалуйста, введите номер операции верно" << endl;
		break;
	}
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int a = 1, n;
	cout << "Для работы с программой требуется создать очередь." << endl;
	cout << "Введите размер очереди: " << endl;
	cin >> n;
	point* first = MakeQueue(n);
	while (true)
	{
		system("pause");
		system("cls");
		cout << "0. Выход" << endl;
		cout << "1. Создать очередь." << endl;
		cout << "2. Удалить элементы из очереди. " << endl;
		cout << "3. Добавить элементы в очередь" << endl;
		cout << "4. Удалить очередь." << endl;
		cout << "5. Записать очередь в файл." << endl;
		cout << "6. Восстановить очередь." << endl;
		cout << "Выберите действие: ";
		cin >> a;
		system("cls");
		menu(a, first, n);
	}
	return 0;
}
#include <iostream>
using namespace std;

const int hashSize = 26;

//структура узла
struct Node {
    string data = "";
    Node* next = nullptr;
};

//структура данных хеш-множества
struct HashSet {

    //массив указателей на связанные списки для хранения слов
    Node* table[hashSize];
    int cnt;

    //конструктор хеш-множества
    HashSet() {
        cnt = 0;
        for (int i = 0; i < hashSize; i++) {
            table[i] = nullptr;
        }
    }

    //хеш-функция
    int hashFunction(string word) {
        int hash = 0;
        for (char c : word) {
            hash += c;
        }
        return hash % hashSize;
    }

    //добавление элемента в множество
    void add(string word) {
        int index = hashFunction(word);
        Node* temp = table[index];
        cnt++;
        if (temp == nullptr) {
            table[index] = new Node{ word };
            return;
        }
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node{ word };
    }

    //удаление элемента из множества
    void remove(string word) {
        int index = hashFunction(word);
        if (table[index] != nullptr) {
            Node* temp = table[index];
            if (temp->data == word) {
                table[index] = temp->next;
                delete temp;
                cnt--;
                return;
            }
            while (temp->next != nullptr) {
                if (temp->next->data != word) {
                    Node* current = temp->next->next;
                    delete temp->next;
                    temp->next = current;
                    cnt--;
                    return;
                }
                temp = temp->next;
            }
        }
    }

    //удаление всех элементов множества
    void clear() {
        for (int i = 0; i < hashSize; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                Node* next = temp->next;
                delete temp;
                cnt--;
                temp = next;
            }
            table[i] = nullptr;
        }
    }

    //определяет, содержится ли элемент в множестве
    bool contains(string word) {
        int index = hashFunction(word);
        Node* temp = table[index];
        while (temp != nullptr) {
            if (temp->data == word) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    //количество элементов коллекции
    int count() {
        return cnt;
    }

    //конвертация хеш-множества в динамический массив строк
    string* ToArray() {
        if (cnt == 0) {
            return nullptr;
        }
        string* arr = new string[cnt];
        int j = 0;
        for (int i = 0; i < hashSize; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                arr[j] = temp->data;
                j++;
                temp = temp->next;
            }
        }
        return arr;
    }
};

int main()
{
    HashSet hash;
    setlocale(LC_ALL, "Russian");

    cout << "Введите число для:" << endl;
    cout << "1. добавления элементов в множество" << endl << "2. удаления элемента из множества" << endl;
    cout << "3. удаления всех элементов коллекции" << endl << "4. определения, содержится ли указанный элемент в объекте HashSet" << endl;
    cout << "5. подсчета количества элементов в коллекции" << endl << "6. конвертирования хеш-множества в динамический массив строк" << endl;
    cout << "7. завершения работы программы" << endl;


    while (true) {
        int numb;
        string word;
        string* toArr;
        cin >> numb;
        switch (numb) {
        case 1:
            cout << "Введите слово для добавления: ";
            cin >> word;
            hash.add(word);
            break;
        case 2:
            cout << "Введите слово для удаления: ";
            cin >> word;
            hash.remove(word);
            break;
        case 3:
            hash.clear();
            cout << "Хеш-массив пуст!" << endl;
            break;
        case 4:
            cout << "введите слово для проверки: ";
            cin >> word;
            if (hash.contains(word)) {
                cout << "это слово есть в массиве!" << endl;
            }
            else {
                cout << "этого слова нет в массиве:(" << endl;
            }
            break;
        case 5:
            cout << "количество элементов в коллекции: " << hash.count() << endl;
            break;
        case 6:
            toArr = hash.ToArray();
            for (int i = 0; i < hash.count(); i++) {
                cout << toArr[i] << " ";
            }
            cout << endl;
            break;
        case 7:
            return 0;
        default:
            cout << "Ошибка!!! Введите корректный номер команды!";
            break;
        }
    }
}
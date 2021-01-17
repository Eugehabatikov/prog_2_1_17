#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;
//структурра хранения - стек
struct Stack {//структура для ввода
    Stack *next;
    int elem = 0;
};




struct Sumb//структура вывода - двунаправленный список
{
    Sumb* nexElem;// указатель на следующий элемент
    Sumb* prewElem;//указатель на предыдущее элемент
    int elem = 0; //элемент
//    int deleted = 0; // 0 - не удалено, 1 - удалено
}; // готово

struct MyStor {//структура хранения информации
    string nameOfFile;
    int rangTop = 0;
    int rangLast = 0;
    Sumb *firstElem = NULL;
    Sumb *lastElem = NULL;
    Stack *top = NULL;
};

MyStor myStor;
class NumberWorker//основной класс
{
public:


    void sort()
    {
        int finishFlag;
        while(true)// пока не отсортированно
        {
            finishFlag = 0;
            Sumb *elemTwo = new Sumb;
            elemTwo->elem = 0;
            elemTwo->nexElem = NULL;
            elemTwo->prewElem = NULL;

            Sumb *tempStor = new Sumb;
            tempStor->elem = 0;
            tempStor->prewElem = NULL;
            tempStor->nexElem = NULL;

            int prev = myStor.firstElem->elem;
            Sumb *temp = myStor.firstElem;
            while(true)
            {
                temp = temp->nexElem;
                if (temp == NULL) break;
                if(temp->elem < prev)
                {
                    finishFlag = 1;
                    elemTwo = temp->prewElem;// сохранил второй элемент пары
                    tempStor->nexElem = temp->nexElem;// сохранил ссылку на следующий, за участком смены
                    tempStor->prewElem = elemTwo->prewElem;// сохранил ссылку на участок до смены
                    elemTwo->prewElem = temp;// связал элементы
                    temp->nexElem = elemTwo;// связал элементы
                    elemTwo->nexElem = tempStor->nexElem; // привязал следующий участок
                    if(tempStor->prewElem == NULL) {
                        myStor.firstElem = temp;// если первый
                        temp->prewElem = NULL;
                    }
                    else {
                        temp->prewElem = tempStor->prewElem;// привязал предыдущий участок
                        temp->prewElem->nexElem = temp;// привязал предыдущий участок
                    }
                    if(tempStor->nexElem == NULL) {
                        myStor.lastElem = elemTwo;// если последний
                        break;
                    }
                    else{
                        tempStor->nexElem->prewElem = elemTwo; // привязал следующий участок
                    }
                   // tempStor = temp->elem;
                    //temp->elem = prev;
                    //temp->prewElem->elem = tempStor;
                    prev = elemTwo->elem;
                }
                else prev = temp->elem;
            }
            if(finishFlag == 0)
                break;
            /**else {
                prev = myStor.lastElem->elem;
                temp = temp->prewElem;// пропустили лишнюю проверку
                while (temp->prewElem != NULL) {
                    temp = temp->prewElem;
                    if (temp->elem > prev) {
                   //     tempStor = temp->elem;
                        temp->elem = prev;
                     //   temp->nexElem->elem = tempStor;
                        finishFlag = 1;
                    }
                    prev = temp->elem;
                }
            }**/
        }
    };// метод сортировки

    void cleaner(Sumb *element){
        delete element->nexElem;
        delete element->prewElem;
        element->elem = NULL;
    };

    void putL2(int elem, int flagLast)
    {
        if(myStor.firstElem == NULL)// самый маленький
        {
            myStor.firstElem = new Sumb;
            myStor.firstElem->elem = elem;
            myStor.firstElem->prewElem = NULL;
            myStor.firstElem->nexElem = NULL;
        }

        else
        {
            Sumb *temp = myStor.firstElem;
            while(true)
            {
                if(temp->nexElem == NULL)
                break;
                else temp = temp->nexElem;
            }

            if(flagLast == 1)
            {
                myStor.lastElem = new Sumb;
                myStor.lastElem->prewElem = temp;
                temp->nexElem = myStor.lastElem;
                myStor.lastElem->nexElem = NULL;
                myStor.lastElem->elem = elem;
            } else {
                Sumb *newElem = new Sumb;
                newElem->elem = elem;
                newElem->nexElem = NULL;
                newElem->prewElem = temp;
                temp->nexElem = newElem;
            }
        }
    };// метод вставки нового элемента в двунаправленную очередь

    void stackPut(int info)
    {
        if(info > (myStor.rangLast - 1) && info < (myStor.rangTop + 1)) //Проверка диапазона - все что вне отсекаеться
        {
            Stack *newElem = new Stack;
            newElem->next = myStor.top;
            newElem->elem = info;
            myStor.top = newElem;
        }
    };// метод вставки нового элемента в стек готов

    void moveToL2()
    {
        int flagFinish = 0;
        while(true)
        {
            Stack *temp = myStor.top->next;
            if(myStor.top->next == NULL)
            {
                putL2(myStor.top->elem, 1);//обработка
                flagFinish = 1;
            } else putL2(myStor.top->elem, 0);//обработка
            myStor.top->elem = NULL;
            delete myStor.top;
            myStor.top = temp;
            if (flagFinish == 1) break;// что бы не делать лишний шаг цикла
        }
    };//перенос данных из стека в двунаправленную очередь готово

    int intMaker(int rangeTemp, char elem)//готов
    {
        int rangeTempNew = rangeTemp;
        if (elem >= '0' && elem <= '9')
        {
            rangeTempNew *= 10;
            rangeTempNew += (elem - '0');
        }
        else
        {
            cout << "sorry, you write not a number";
            exit(0);
        }
        return rangeTempNew;
    }// вспомогательный метод для корректного перебора int

    void rangParser(string range) // парсим и заполняем данные границ
    {
        int i = 0;
        int rangeTemp = 0;
        for(i; range[i]!=' '; i++)
        {
            rangeTemp = this->intMaker(rangeTemp,range[i]);
        }
        i++;
        myStor.rangTop = rangeTemp;
        rangeTemp = 0;
        for(i; i<range.length(); i++)
        {
            rangeTemp = this->intMaker(rangeTemp,range[i]);
        }
        myStor.rangLast = rangeTemp;
        if (myStor.rangTop <= myStor.rangLast)
        {
            cout << "sorry, you write wrong boundaries. Pleas, check the specification again";
            exit(0);
        }
    };//готов, отдебажен

    void deleteStack() {
        while(true)
        {
            if(myStor.top == NULL) break;
            Stack *temp = myStor.top->next;
            myStor.top->elem = NULL;
            delete myStor.top;
            myStor.top = temp;
        }
    };// очистка стека Готово

    void deleteL2()
    {
        Sumb *temp = myStor.firstElem;

        while (true)
        {

            break;
        }
    };// Очистка двунаправленной очереди

    void exceptionHelper()
    {
        cout << "Somphing error in your path to file. Pleas, write all again.";
        exit(0);
    }

    void printer()
    {
        ofstream out;               // поток для записи
        out.open(myStor.nameOfFile, ios::app);// окрываем файл для записи
        if (out.is_open()) {
            Sumb *temp = myStor.firstElem;
            while (true)
            {
                out << temp->elem;
                out << '\n';
                temp->elem = NULL;
                if (temp->nexElem == NULL)
                {
                    temp->nexElem = nullptr;
                    break;
                }
                temp = temp->nexElem;
                temp->prewElem->nexElem = nullptr;
                temp->prewElem = nullptr;

            }
        }
        else exceptionHelper();
        out.close();
    };//финальный вывод отсортированного l2 списка

    void reader(string nameOfFile)// чтение списка
    {
        ifstream in;
        in.open(nameOfFile);
        string line;
        if (in.is_open())
        {
            getline(in,line);
            rangParser(line);
            while (getline(in, line))
            {
                stackPut(stoi(line));
            }
        }
        else exceptionHelper();
        in.close();
    };// готов

    //void writer(){};// писатель


};
int main() {
    string nameOfFile;
    cout << "Hello!\n"
            "This program can:\n";
    cin >> nameOfFile; // where i take text
    cin >> myStor.nameOfFile; // where i write answer

    NumberWorker().reader(nameOfFile);// считываю стек
    NumberWorker().moveToL2();//переношу данные в двунаправленный список
    NumberWorker().sort();//сортирую полученный список
    NumberWorker().printer();//вывожу данные в файл
    return 0;
}// написать вступление, не забыть четко описать граничные условия;
 /** схема работы
1) принимаем в мэйн ссылку на файл ввода и вывода, передаем данные сразу в метод чтения
2) читаем, заполняем стек, сразу отрезаем все, не входящее в диапазон
3) переводим в двунаправленную очередь, сортирвуем
4) выводим в файл

 проверить:
 1) некорректные данные границ
 2) некорректное имя файла
 3) меньшая граница больше большой
 4) проверка граничных значений
 5) проверка сортировки

  ++
  Если выделял внутри метода через new, то надо.
  Если это просто переменные типа int z; то не надо.
  Другими словами, если выделяешь память - то есть создаешь что-то, чем потом пользуешься через указатель, чистить память надо.

  C:\tmp\test0.txt
C:\tmp\output.txt
  **/
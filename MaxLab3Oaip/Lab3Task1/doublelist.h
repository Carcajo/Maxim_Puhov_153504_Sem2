#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include <QString>
#include <QDebug>
#include <QTime>

struct Elem
{
    QString date;
    QString number;
    QString location;
    QString time;
    QString free;
   Elem * next, * prev;
};

class DoubleList
{

    // Голова, хвост
       Elem * Head, * Tail;
       // Количество элементов
       int Count;
public:
    // Конструктор
    DoubleList()
    {
       // Изначально список пуст
       Head = Tail = NULL;
       Count = 0;
    }

    // Деструктор
    ~DoubleList()
    {
       // Удаляем все элементы
       DelAll();
    }

    // Получить количество
    int GetCount()
    {
        return Count;
    }
    // Получить элемент списка
    Elem* GetElem(int pos)
    {
       Elem *temp = Head;

       for(int i =0; i < pos;i++)
       {
          // Доходим до элемента,
          // перед которым вставляемся
          temp = temp->next;
       }

       if(temp == 0)
          return 0;
       else
          return temp;
    }

    // Удалить весь список
    void DelAll()
    {
       // Пока остаются элементы, удаляем по одному с головы
       while(Count != 0)
          Del(1);
    }
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos=0)
    {

       Elem * Del = Head;

       for(int i = 1; i < pos;i++)
       {
          // Доходим до элемента,
          // перед которым вставляемся
          Del = Del->next;
       }

       // Доходим до элемента,
       // который предшествует удаляемому
       Elem * PrevDel = Del->prev;
       // Доходим до элемента, который следует за удаляемым
       Elem * AfterDel = Del->next;

       // Если удаляем не голову
       if(PrevDel != 0 && Count != 1)
          PrevDel->next = AfterDel;
       // Если удаляем не хвост
        if(AfterDel != 0 && Count != 1)
          AfterDel->prev = PrevDel;

       // Удаляются крайние?
       if(pos == 1)
           Head = AfterDel;
       if(pos == Count)
           Tail = PrevDel;

       // Удаление элемента
       delete Del;

       Count--;
    }
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(QString number, QString date, QString location, QString time, QString free, int pos=0)
    {
       // Если вставка в конец списка
       if(pos == Count + 1)
       {
          // Добавление в конец списка
          AddTail(date, number, location, time, free);
          return;
       }
       else if(pos == 1)
       {
          // Добавление в начало списка
          AddHead(date, number, location, time, free);
          return;
       }
       // Отсчитываем от головы n - 1 элементов
       Elem * Ins = Head;

       for(int i =1; i < pos;i++)
       {
          // Доходим до элемента,
          // перед которым вставляемся
          Ins = Ins->next;
       }

       // Доходим до элемента,
       // который предшествует
       Elem * PrevIns = Ins->prev;

       // Создаем новый элемент
       Elem * temp = new Elem;

       // Вводим данные
       temp->date=date;
       temp->number=number;
       temp->location=location;
       temp->time=time;
       temp->free=free;

       // настройка связей
       if(PrevIns != 0 && Count != 1)
          PrevIns->next = temp;

       temp->next = Ins;
       temp->prev = PrevIns;
       Ins->prev = temp;

       Count++;
    }

    // Добавление в конец списка
    void AddTail(QString number, QString date, QString location, QString time, QString free)
    {
       // Создаем новый элемент
       Elem * temp = new Elem;
       // Следующего нет
       temp->next = 0;
       // Заполняем данные
       temp->date=date;
       temp->number=number;
       temp->location=location;
       temp->time=time;
       temp->free=free;

       // Предыдущий - бывший хвост
       temp->prev = Tail;

       // Если элементы есть?
       if(Tail != 0)
          Tail->next = temp;

       // Если элемент первый, то он одновременно и голова и хвост
       if(Count == 0)
          Head = Tail = temp;
       else
          // иначе новый элемент - хвостовой
       Tail = temp;

       Count++;
    }

    // Добавление в начало списка
    void AddHead(QString number, QString date, QString location, QString time, QString free)
    {
       // новый элемент
       Elem * temp = new Elem;

       // Предыдущего нет
       temp->prev = 0;
       // Заполняем данные
       temp->date=date;
       temp->number=number;
       temp->location=location;
       temp->time=time;
       temp->free=free;
       // Следующий - бывшая голова
       temp->next = Head;

       // Если элементы есть?
       if(Head != 0)
          Head->prev = temp;

       // Если элемент первый, то он одновременно и голова и хвост
       if(Count == 0)
          Head = Tail = temp;
       else
          // иначе новый элемент - головной
          Head = temp;

       Count++;
    }
    QString PrintAllSave()
    {
       // Если в списке присутствуют элементы, то пробегаем по нему
       // и печатаем элементы, начиная с головного

        QString buf;
       Elem * temp = Head;
       for(int a=1;temp != 0;a++)
       {
           buf+= temp->number+
                   "\n" + temp->date+
                   "\n" + temp->location+
                   "\n" + temp->time+
                   "\n" + temp->free+"\n\n";
           temp = temp->next;
       }
       return buf;
    }
    // Печать списка
    QString PrintAll()
    {
       // Если в списке присутствуют элементы, то пробегаем по нему
       // и печатаем элементы, начиная с головного

        QString buf;
       Elem * temp = Head;
       for(int a=1;temp != 0;a++)
       {
           buf+= "№" + QString::number(a)+
                   "\nНомер поезда: " + temp->number+
                   "\nДата выезда: " + temp->date+
                   "\nПункт назначения: " + temp->location+
                   "\nВремя отправления: " + temp->time+
                   "\nЧисло свободных мест: " + temp->free+"\n\n";
           temp = temp->next;
       }
       return buf;
    }
    // Печать определенного элемента
    QString Print(int pos=0)
    {
       Elem * temp;

       // Определяем с какой стороны
       // быстрее двигаться
       if(pos <= Count / 2)
       {
          // Отсчет с головы
          temp = Head;
          for(int i =0; i < pos;i++)
          {
             // Доходим до элемента,
             // перед которым вставляемся
             temp = temp->next;
          }
       }
       else
       {
           // Отсчет с хвоста
          temp = Tail;

          for(int i =Count; i <= Count-pos;i--)
          {
             // Доходим до элемента,
             // перед которым вставляемся
             temp = temp->prev;
          }
       }
       return temp->date+'\n'+ temp->number+'\n'+ temp->location+'\n'+ temp->time+'\n'+ temp->free+'n';
    }


    QString search(QString number, QString date){
        QString buf;
       Elem * temp = Head;
       for(int a=1;temp != 0;a++)
       {
           if(date==temp->date && number==temp->number){
               buf+= "№" + QString::number(a);
              if (temp->free.toInt()==0) buf+= "\nНЕВОЗМОЖНО СДЕЛАТЬ ЗАКАЗ";
                  buf+= "\nНомер поезда: " + temp->number+
                          "\nДата выезда: " + temp->date+
                          "\nПункт назначения: " + temp->location+
                          "\nВремя отправления: " + temp->time+
                          "\nЧисло свободных мест: " + temp->free+"\n\n";
           }
           temp = temp->next;
       }
       return buf;
    }

    QString search_2(QString location, QString time){
        QString buf;
       Elem * temp = Head;
       for(int a=1;temp != 0;a++)
       {
           if(QTime::fromString(time,"hh:mm")>=QTime::fromString(temp->time,"hh:mm") && location==temp->location) {
                buf+= "№" + QString::number(a);
               if (temp->free.toInt()==0) buf+= "\nНЕВОЗМОЖНО СДЕЛАТЬ ЗАКАЗ";
                   buf+= "\nНомер поезда: " + temp->number+
                           "\nДата выезда: " + temp->date+
                           "\nПункт назначения: " + temp->location+
                           "\nВремя отправления: " + temp->time+
                           "\nЧисло свободных мест: " + temp->free+"\n\n";
                   }
           temp = temp->next;
       }
       return buf;
    }


    void quicksort(Elem *k = 0,Elem *first = 0,Elem *last = 0,bool a=1){//быстрая сортировка(указатель на структуру, на начало списка,на конец списка)
        if(a){
            k=Head;
            first=Head;
            last = Tail;
        }
        Elem *i=first,*j=last;
        Elem *first1=i->prev,*last1=j->next;
        uint x=(first->number.toUInt()+last->number.toUInt())/2;

        do {
            while (i->number.toUInt() < x) i=i->next;
           while (j->number.toUInt() > x) j=j->prev;

            if(i!=j) {
                    if (i->number.toUInt() > j->number.toUInt()){
                i->next->prev=j;
                i->prev->next=j;
                j->prev->next=i;
                j->next->prev=i;
                j->next=i->next;
                i->next=last1;
                i->prev=j->prev;
                j->prev=first1;
                i=j->next;
                j=i->prev;
                first1=i->prev;
                last1=j->next;
                    }
            }
        } while (i!=j);
      if (last!=i)
            quicksort(k,i,last,0);
       if (first!=j)
           quicksort(k,first,j,0);
    }


    void sort(){

    }


};

#endif // DOUBLELIST_H

#ifndef LIST_H
#define LIST_H

#include "GameEntity/Tank.h"
#include "GameEntity/Basic.h"

class Tank;
class Basic;

class List
{
private:

    struct Node{

        Tank *tank;
        Tank::TYPE type;
        int num_of_enemies;
        int the_wave;
        Node *next = nullptr, *prev = nullptr;

    };

    Node *head = nullptr;

public:
    List();
    Node *create_node(Basic *tank, Tank::TYPE type, int num_of_enemies, int the_wave);
    void list_push_back(List *list, Node *node);
    Node *list_find_name(List *list, const int &wave);
    void list_clear(List *list);
    void list_clear(List *list, const int &wave);
    void list_delete(List *list);
    Tank *selected_tank(List *list);
    int selected_wave(List *list);
    int selected_num_of_enemies(List *list);
    Tank::TYPE return_type(List *list);

};

#endif // LIST_H

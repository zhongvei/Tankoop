#ifndef LIST_H
#define LIST_H

#include "GameEntity/Tank.h"
#include "GameEntity/Basic.h"

class Tank;
class Basic;

class List
{
private:

    /* A doubly circular linked list to store the game history */
    struct Node{

        Tank *tank;
        int num_of_enemies;
        int the_wave;
        Node *next = nullptr, *prev = nullptr;
        QString name;

    };

    Node *head = nullptr;

public:

    /*
     *  @funct: Constructs the Linked List with all of its attributes. Creates a sentinel node for the linked list
     *          and linked the linked list to itself
     *
     *  @param: name: a QString containing the user's name.
     *
     *  @return: N/A
     */
    List(QString name);

    /*
     *  @funct: Create a node and dynamically allocate a memory for Basic objects. Assigns the value of each properties
     *          of tank and inputs from the parameter to the new node.
     *
     *  @param: tank: the object that wants to be copied.
     *          num_of_enemies: current wave maximum number of enemies.
     *          the_wave: current wave.
     *
     *  @return: a new node to be linked inside the linked list.
     */
    Node *create_node(Basic *tank, int num_of_enemies, int the_wave);

    /*
     *  @funct: Linked the node from the parameter into the linked list.
     *
     *  @param: list: the selected linked list.
     *          node: the node that wants to be linked.
     *
     *  @return: N/A
     */
    void list_push_back(List *list, Node *node);

    /*
     *  @funct: Find the node based on the wave inputs.
     *
     *  @param: list: the selected linked list.
     *          wave: the wave that wants to be selected.
     *
     *  @return: the selected node.
     */
    Node *list_find_name(List *list, const int &wave);

    /*
     *  @funct: Deallocate all memories of the nodes and its data members inside the linked list, execpt for the sentinel node.
     *
     *  @param: list: the selected linked list.
     *
     *  @return: N/A
     */
    void list_clear(List *list);

    /*
     *  @funct: Deallocate memories of the nodes starting from the next wave (wave + 1) and its data members
     *          inside the linked list, execpt for the sentinel node.
     *
     *  @param: list: the selected linked list.
     *          wave: the wave that wants to be spared (delete only the waves after the selected wave).
     *
     *  @return: N/A
     */
    void list_clear(List *list, const int &wave);

    /*
     *  @funct: Delete the sentinel node of the linked list and deallocate the linked list's memory
     *
     *  @param: list: the selected linked list.
     *
     *  @return: N/A
     */
    void list_delete(List *list);

    /* Accessor */
    Tank *selected_tank(List *list) const;
    QString get_name() const;
    int selected_wave(List *list) const;
    int selected_num_of_enemies(List *list) const;

};

#endif // LIST_H

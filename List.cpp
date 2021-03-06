#include "List.h"
#include "GameWindow.h"
#include "QDebug"

List::List(QString nameValue)
{
    Node *sentinel = new Node;

    sentinel->tank = nullptr;
    sentinel->the_wave = 0;
    sentinel->num_of_enemies = 0;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    sentinel->name = nameValue;

    this->head = sentinel;
}


Tank* List::selected_tank(List *list) const{
    return list->head->prev->tank;
}


int List::selected_wave(List *list) const{
    return list->head->prev->the_wave;
}

int List::selected_num_of_enemies(List *list) const{
    return list->head->prev->num_of_enemies;
}

QString List::get_name() const{
    return this->head->name;
}

List::Node* List::create_node(Basic *tank, int num_of_enemies, int the_wave){

    Node *new_node = new Node;
    new_node->tank = new Basic(*tank);

    new_node->tank->set_type(tank->get_type());
    new_node->tank->set_subtank(tank->get_subtank());

    /* If the tank skill status is active when entering a new wave, set it back to its original status */
    if(tank->get_skill_status()){
        new_node->tank->skill_timer_timeout(); //Skill avtivated text
        new_node->tank->change_skill_status();
    }
    new_node->the_wave = the_wave;
    new_node->num_of_enemies = num_of_enemies;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    return new_node;
}

List::Node* List::list_find_name(List *list, const int &wave){
    for(Node *p = list->head; p->next != list->head; p = p->next){
        if(p->next->the_wave == wave)
            return p->next;
    }
    return nullptr;
}

void List::list_push_back(List *list, Node *node){

    Node *p = list->head;
    node->next = p;
    p->prev = node;
    if(p->next == list->head){
        p->next = node;
        node->prev = p;
    }
    else{
        for(p ; p->next != list->head; p = p->next){
            ;
        }
        p->next = node;
        node->prev = p;
    }
    for(Node *n = list->head->next; n != list->head; n = n->next){
        qDebug() << n->the_wave;
    }

}

void List::list_clear(List *list) {
    Node *start = list->head->next;
    Node *temp = start->next;
    for(start; start != list->head; temp = temp->next){
        start->prev = nullptr; // play safe
        delete start->tank;
        delete start;
        start = temp;
        if(temp == list->head)
            break;
    }
    list->head->next = list->head;
    list->head->prev = list->head;
}

void List::list_clear(List *list, const int &wave) {
    if(list->head->prev->the_wave == wave){
        return;
    }
    Node *start = list_find_name(list, wave)->next;
    Node *temp = start->next;
    for(start; start != list->head; temp = temp->next){
        start->prev = nullptr; // play safe
        delete start->tank;
        delete start;
        start = temp;
        if(temp == list->head)
            break;
    }

    Node *new_last_wave = list_find_name(list, wave);
    new_last_wave->next = list->head;
    list->head->prev = new_last_wave;

}

void List::list_delete(List *list){

    list_clear(list);
    delete list->head;
    list->head = nullptr; // play safe :)
    delete list;
    list = nullptr;

}

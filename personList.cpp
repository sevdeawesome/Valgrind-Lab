#include "personList.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

PersonList::PersonList(){
    capacity = 2;
    numPeople = 0;
    theList = new Person*[capacity];
}

PersonList::~PersonList(){
    delete [] theList;
}

void PersonList::addPerson(char* child_name, char* father_name, char* mother_name){
    Person *father = 0;
    Person *mother = 0;
    
    // try to find the three names in the theList
    for(int i = 0; i < numPeople; i++){
        if(!strcmp(theList[i]->getName(), child_name)){
            cout << "ERROR: " << child_name << " already has parents!!!";
            return;
        } else if(!strcmp(theList[i]->getName(), father_name)) {
            father = theList[i];
        } else if(!strcmp(theList[i]->getName(), mother_name)) {
            mother = theList[i];
        }
    }
   
    if(father == 0){
      // father_name is not in the theList so create a new person
      father = new Person(father_name, 0, 0);
      insertIntoList(father);
    }
    if(mother == 0){
      // mother_name is not in the theList so create a new person
      mother = new Person(mother_name, 0, 0);
      insertIntoList(mother);
    }
    Person *newChild = new Person(child_name, father, mother);
    insertIntoList(newChild);
    father->addChild(newChild);
    mother->addChild(newChild);
}

void PersonList::insertIntoList(Person *newPerson){
    if(numPeople == capacity) expand(&theList, &capacity);

    theList[numPeople++] = newPerson;
}

void PersonList::printLineage(char* person){
    for(int i = 0; i < numPeople; i++) {
        if(!strcmp(theList[i]->getName(), person)){
            theList[i]->printAncestors();
            theList[i]->printDecendents();
            return;
        }
    }
    cout << endl << person << " is not in the list!" << endl;
}

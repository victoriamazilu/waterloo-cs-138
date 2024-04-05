#include <vector>
#include <string>
#include "a5p1.h"

using namespace std;

Animal::Animal (string name) {
    this -> name = name;
}

Animal::~Animal (){} 

string Animal::getName () const {
    return this -> name;
}

Dog::Dog (string name) : Animal::Animal(name){} //MIL

Dog::~Dog (){} 

string Dog::speak () const {
    return "    Dog " + getName() + " says \"woof\".";
}

Sheep::Sheep (string name) : Animal::Animal(name){} //IML

Sheep::~Sheep (){} 

string Sheep::speak () const {
    return "    Sheep " + getName() + " says \"baaa\".";
}

Flock::Flock(string dogName) {
    this -> dog = new Dog(dogName);
}

Flock::~Flock() {
    delete dog;
    dog = nullptr;
    
    for (int i = 0; i < sheepList.size(); ++i) {
        delete sheepList[i];
        sheepList[i] = nullptr; 
    }

    sheepList.clear();

}

void Flock::addSheep (string name) {
    Sheep* newSheep = new Sheep(name);
    sheepList.push_back(newSheep);
}

string Flock::soundOff () const {
    std::string result;
    result += "The flock of " + std::to_string(sheepList.size()) + " sheep speaks!\n";

    result += dog->speak() + "\n";

    for (int i = 0; i < sheepList.size(); i++) {
        result += sheepList[i]->speak() + "\n";
    }

    return result;
}


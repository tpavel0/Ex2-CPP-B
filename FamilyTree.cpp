#include "FamilyTree.hpp"
#include <iostream>
#include <exception>

using namespace std;
using namespace family;

// both search are get_Node funtion, 1st by name , 2nd by relation
Tree* SearchName (Tree* ptr, string s){
	if (ptr->name==s)
	     return ptr; 
	if (ptr->mother!=nullptr){
        Tree* answer = SearchName(ptr->mother, s);
        if(answer != nullptr)
            return answer;
    }
	if (ptr->father!=nullptr){
        Tree* answer = SearchName(ptr->father, s);
        if(answer != nullptr)
            return answer;
    }
	return nullptr;
}
Tree* SearchRel(Tree* ptr, string str){
      if (ptr->rel==str)
        return ptr;
      if (ptr->mother!=nullptr){
            Tree* answer = SearchRel(ptr->mother, str);
            if(answer != nullptr)
                return answer;
      }
      if (ptr->father!=nullptr){
            Tree* answer = SearchRel(ptr->father, str);
            if(answer != nullptr)
                return answer;
      }
      return nullptr;
}

Tree &Tree::addFather(string name, string father){
	Tree* ptr = SearchName(this, name);
	if (ptr != nullptr) {
            if (ptr->father == nullptr){
                  ptr->father = new Tree(father);
                  ptr->father->son = ptr;
                  //if's for the relation
                  if (ptr->rel == "me") ptr->father->rel = "father";
                  else if ((ptr->rel == "father") || (ptr->rel == "mother") )
                            ptr->father->rel = "grandfather";
                  else if ((ptr->rel == "grandfather") || (ptr->rel == "grandmother") )
                            ptr->father->rel = "great-grandfather";
                  else{
                       string temp = "great-"+ptr->rel;
                       for (int i=0; i<6; i++) //delete the ending father/mother - both 6 letters
                            temp.pop_back();
                       temp+="father";
                       ptr->father->rel = temp;
                  }
                  return *ptr;
            }
		else { throw runtime_error(name +" already have a father !"); }
	}
	else{ throw runtime_error(name+" - not in the tree"); }
}

Tree &Tree::addMother(string name, string mother) {
	Tree* ptr = SearchName(this, name);
	if (ptr != nullptr) {
            if (ptr->mother == nullptr){
                  ptr->mother = new Tree(mother);
                  ptr->mother->son = ptr;
                  //if's for the relation
                  if (ptr->rel == "me") ptr->mother->rel = "mother";
                  else if ((ptr->rel == "mother") || (ptr->rel == "father") )
                            ptr->mother->rel = "grandmother";
                  else if ((ptr->rel == "grandmother") || (ptr->rel == "grandfather") )
                            ptr->mother->rel = "great-grandmother";
                  else{
                        string temp = "great-"+ptr->rel;
                        for (int i=0; i<6; i++) //delete the ending father/mother - both 6 letters
                             temp.pop_back();
                        temp+="mother";
                        ptr->mother->rel = temp;
                  }
                  return *ptr;
            }
		else { throw runtime_error(name +" already have a mother !"); }
	}
	else{ throw runtime_error(name+" - not in the tree"); }
}

/**from
* https://www.techiedelight.com/print-two-dimensional-view-binary-tree/
*
* It does reverse inorder traversal and print nodes by increasing space by fixed amount at every level
**/
void printBinaryTree(Tree *root, int space=0, int height=10)
{
    // Base case
    if (root == nullptr) // Base
        return;

    // increase distance between levels
    space += height;

    // print right child first
    printBinaryTree(root->father, space);
    cout << endl;

    // print current node after padding with spaces
    for (int i = height; i < space; i++)
        cout << ' ';
    cout << root->name;

    // print left child
    cout << endl;
    printBinaryTree(root->mother, space);
}


void Tree::display() {
      cout << "Tree Display:\n==============================================================";
      printBinaryTree(this);
      cout << "==============================================================" << endl;
}

string Tree::relation(string str) {
      Tree* ptr = SearchName(this, str);
      if (ptr != nullptr)
            return ptr->rel;
      return "unrelated";
}

string Tree::find(string s) {
      Tree* ptr = SearchRel(this, s);
      if (ptr != nullptr)
            return ptr->name;
	else{ throw runtime_error("The tree cannot handle the '" + s + "' relation"); }
}


void Tree::remove(string str) {
	Tree* ptr = SearchName(this, str);
	if (ptr == this) {throw runtime_error("Can't remove the root of the tree 'me' case");} 
	if(ptr!=nullptr){
            if (ptr->son->mother == ptr)
                ptr->son->mother = nullptr; 
            if (ptr->son->father == ptr)
                ptr->son->father = nullptr; 
            delete ptr;
      }
      else { throw runtime_error(str+" is not part of the tree"); }
}

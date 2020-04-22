#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace family{
	class Tree {
	public:
		string name;
		Tree *father, *mother, *son;
		string rel;

		Tree(string s):
			name(s),father(nullptr),mother(nullptr),son(nullptr), rel("me"){};

		~Tree(){
                  if(mother) delete mother;
                  if(father) delete father;
		};

		Tree &addFather(string name, string father);
		Tree &addMother(string name, string mother);
		void display();
		string relation(string s);
		string find(string s);
		void remove(string s);
	};
};

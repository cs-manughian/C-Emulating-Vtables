#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------//
// Animal "classes"
//-------------------------------------------------------------------//
typedef struct Animal {
	void* vtable[2];
	int age;
}Animal;

typedef struct Dog {
	void* vtable[2];
	int age;
	double weight;
}Dog;

typedef struct Cat {
	void* vtable[2];
	int age;
	int numberOfLives;
}Cat;

typedef struct Lion {
	void* vtable[2];
	int age;
	int numberOfLives;
	double weight;
}Lion;


//-------------------------------------------------------------------//
// Speak functions
//-------------------------------------------------------------------//
void Speak() {
}

void Speak_Dog(Animal* animal) {
	printf("Woof! I weigh %f pounds.", (((Dog *)animal)->weight));
}

void Speak_Cat(Animal* animal) {
	printf("Meow! I have %d lives.", ((Cat *)animal)->numberOfLives);
}

void Speak_Lion(Animal* animal) {
	printf("ROAR! I weigh %f pounds.", ((Lion *)animal)->weight);
}


//-------------------------------------------------------------------//
// Cost functions
//-------------------------------------------------------------------//
double GetCost_Dog(Animal* animal) {
	// The cost of a dog is $7.50 for every 3 lbs of dog
	double cost = 7.5 * (((Dog *)animal)->weight / 3);

	return cost;
}

double GetCost_Cat(Animal* animal) {
	// The cost of a cat is $100 plus $5.50 for 
	// every year of the cat’s age
	double cost = 100 + (((Cat *)animal)->age * 5.5);

	return cost;
}


//-------------------------------------------------------------------//
// Virtual Tables
//-------------------------------------------------------------------//
void* Dog_Vtable[2] = { Speak_Dog, GetCost_Dog };
void* Cat_Vtable[2] = { Speak_Cat, GetCost_Cat };
void* Lion_Vtable[2] = { Speak_Lion, GetCost_Cat };


//-------------------------------------------------------------------//
// Construct functions
//-------------------------------------------------------------------//
void Construct_Dog(Dog* dog) {
	dog->vtable[0] = Dog_Vtable[0];
	dog->vtable[1] = Dog_Vtable[1];
	dog->age = 0;
	dog->weight = 30.0;
}

void Construct_Cat(Cat* cat) {
	cat->vtable[0] = Cat_Vtable[0];
	cat->vtable[1] = Cat_Vtable[1];
	cat->age = 0;
	cat->numberOfLives = 9;
}

void Construct_Lion(Lion* lion) {
	lion->vtable[0] = Lion_Vtable[0];
	lion->vtable[1] = Lion_Vtable[1];
	lion->age = 0;
	lion->numberOfLives = 9;
	lion->weight = 300;
}


//-------------------------------------------------------------------//
// General functions
//-------------------------------------------------------------------//
int GetAge(Animal* animal) {
	return animal->age;
}


//-------------------------------------------------------------------//
// MAIN
//-------------------------------------------------------------------//
int main() {

	Animal* animal;
	double cost = 0;
	int choice = 0;
	int age = 0;

	// Let the user choose an animal
	printf("Choose an animal by number: \n1. dog\n2. cat\n3. lion\n\n");
	scanf_s("%d", &choice);

	// Get the animal’s age from the user
	printf("How old is the animal?\n");
	scanf_s("%d", &age);

	// Based on the choice...
	if (choice == 1) {

		// Create space for the chosen animal
		Dog *dog = (Dog*)malloc(sizeof(Dog));

		// Initialize values
		Construct_Dog(dog);

		// Set age
		dog->age = age;

		// Ask the user about the animal’s information
		printf("How much does the dog weigh?\n");
		scanf_s("%lf", &(dog->weight));

		// Initialize animal pointer
		animal = (Animal*)dog;

		printf("\nThe dog costs $%.2f per month.", GetCost_Dog(animal));
	}
	else if (choice == 2) {

		Cat *cat = (Cat*)malloc(sizeof(Cat));

		// Initialize values
		Construct_Cat(cat);

		// Set age
		cat->age = age;

		// Ask the user about the animal’s information
		printf("How many lives does the cat have?\n");
		scanf_s("%d", &(cat->numberOfLives));

		// Initialize animal pointer
		animal = (Animal*)cat;

		printf("\nThe cat costs $%.2f per month.", GetCost_Cat(animal));
	}
	else {

		Lion *lion = (Lion*)malloc(sizeof(Lion));

		// Initialize values
		Construct_Lion(lion);

		// Set age
		lion->age = age;

		// Ask the user about the animal’s information
		printf("How many lives does the lion have?\n");
		scanf_s("%d", &(lion->numberOfLives));

		// Initialize animal pointer
		animal = (Animal*)lion;

		printf("\nThe lion costs $%.2f per month.", GetCost_Cat(animal));
	}


	// Access V table:
	// Tell the animal to speak
	((void(*)(Animal*))animal->vtable[0])((Animal*)animal);

	// Tell how much the animal costs per month
	((void(*)(Animal*))animal->vtable[1])((Animal*)animal);

	// Done - Free the animal!
	free(animal);
	system("pause");
	return 0;
}




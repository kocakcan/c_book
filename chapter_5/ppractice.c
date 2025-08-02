#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FAMILY_SIZE	5

typedef struct {
	const char *name;
	int age;
	const char *occupation;
	double balance;
} Person;

Person *init_person(const char *name,
			int age,
			const char *occupation,
			double balance) {

	Person *person = malloc(sizeof(Person));

	if (person == NULL) {
		fprintf(stderr, "error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	// pointer pointing to valid memory
	// initialize the instance
	person->name = name;
	person->age = age;
	person->occupation = occupation;
	person->balance = balance;

	return person;
}

size_t strlen_(const char *s) {
	size_t i = 0;

	while (*s++)
		i++;

	return i;
}

size_t max_length(const Person **person, size_t count) {
	size_t max = strlen_((*person)->occupation);

	for (size_t i = 1; i < count; ++i)
		if (strlen_((*(person + i))->occupation) > max)
			max = strlen_((*(person + i))->occupation);

	return max;
}

/* printp: print a Person to stdout */
void printp(const Person *person, size_t width) {
	printf("Name: %-5s | Age: %d | Occupation: %-*s | Balance: $%.2f\n",
			person->name, person->age, (int)width, person->occupation, person->balance);
} 

double rand_double(double min, double max) {
	int scale = 100;	/* for precision=2 */
	int r = rand() % ((int)((max - min) * scale + 1));
	return min + (double)r / scale;
}

void fill_random_doubles(double *arr, size_t count, double min, double max) {
	for (size_t i = 0; i < count; ++i)
		arr[i] = rand_double(min, max);
}

/* main: practicing pointers and structs */
int main(void) {
	srand((unsigned int)time(NULL));	/* praise the RNG 🐒 */ 

	double random_doubles[5];
	fill_random_doubles(random_doubles, FAMILY_SIZE, 100.00, 10000.00);

	Person *me = init_person("Can", 27, "Software Engineer", random_doubles[0]);
	Person *dad = init_person("Seyfi", 60, "God", random_doubles[1]);
	Person *mom = init_person("Leyli", 55, "Goddess", random_doubles[2]);
	Person *sis = init_person("Dilan", 32, "Turkish Patent Attorney", random_doubles[3]);
	Person *bro = init_person("Medet", 32, "Metallurgical and Materials Engineer", random_doubles[4]);

	Person *kocaks[] = {me, dad, mom, sis, bro};
	Person **kp = kocaks;
	size_t longest = max_length((const Person **)kp, FAMILY_SIZE);
	size_t family_size = FAMILY_SIZE;

	while (family_size--)
		printp(*kp++, longest);

	for (size_t i = 0; i < FAMILY_SIZE; ++i)
		free(kocaks[i]);

	return 0;
}

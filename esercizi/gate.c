#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXG 50
#define MAXP 100
#define MAXL 30

typedef struct person_s {
    char name[MAXL+1], surname[MAXL+1];
} Person;

typedef struct groups_s {
    int n_people;
    Person people[MAXP];
} Group;

int digest(Person person);
void addPerson(Person person, Group group);
void orderGroup(Group group);
void printGroup(Group group, FILE *fp);

int main(int argc, char *argv[]) {
    FILE *fp;
    int n_groups, people, i, digestValue;
    Group groups[MAXG] = {0};
    Person person;

    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("ERRORE apertura file di input");
        return 1;
    }
    fscanf(fp,"%d %d", &n_groups, &people);
    for (i = 0; i < people; i++) {
        fscanf(fp, "%s %s", person.name, person.surname);
        digestValue = digest(person);
        addPerson(person, groups[digestValue]);
    }

    fclose(fp);

    if ((fp = fopen(argv[2], "w")) == NULL) {
        printf("ERRORE apertura file di output");
        return 2;
    }

    for (i = 0; i < n_groups; i++) {
        orderGroup(groups[i]);
        fprintf(fp,"Gruppo %d:\n", i);
        printGroup(groups[i], fp);
    }

    fclose(fp);

    return 0;
}

int digest(Person person) {
    int digest = 0, value;
    int i;

    for (i = 0; i < strlen(person.name); i++) {
        value = (isupper(person.name[i]) ? person.name[i] - 'A' + 1 : person.name - 'a' + 1);
        digest += value;
    }

    for (i = 0; i < strlen(person.surname); i++) {
        value = (isupper(person.surname[i]) ? person.surname[i] - 'A' + 1 : person.surname - 'a' + 1);
        digest += value;
    }

    return digest;
}

void addPerson(Person person, Group group) {
    group.people[group.n_people] = person;
    group.n_people++;
}

void orderGroup(Group group) {
    Person x;
    int i, j, l = 0, r = group.n_people - 1;

    // Insertion sort algorithm (stable)

    // Order by surname
    for (i = l + 1; i <= r; i++) {
        x = group.people[i];
        for (j = i - 1; j >= l && (strcmp(x.surname, group.people[j].surname) == 1); j--) {
            group.people[j+1] = group.people[j];
        }
        group.people[j+1] = x;
    }

    // Order by name
    for (i = l + 1; i <= r; i++) {
        x = group.people[i];
        for (j = i - 1; j >= l && (strcmp(x.name, group.people[j].name) == 1); j--) {
            group.people[j+1] = group.people[j];
        }
        group.people[j+1] = x;
    }
}

void printGroup(Group group, FILE *fp) {
    int i;

    for (i = 0; i < group.n_people; i++) {
        fprintf(fp, "%s %s\n", group.people[i].name, group.people[i].surname);
    }
}
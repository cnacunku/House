#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 100
#define FIRST 96
#define SECOND 96


struct person {
    char fam[20];
    char im[20];
    char ot[20];
    int vrst;
    char specialty[50];
    float zp;
    int opit; // ���� (� �����)
};
typedef struct person Person;

struct factory {
    int naz_factory;
    struct person persons[MAX];
    int col_person;
    float sr_oklad;
};
typedef struct factory Factory;

/* ���������� �������*/

void add_factory(Factory* factories, int* factory_count);                                       // ��������� ����� ����� � ������ �������.
void add_person(struct person* person);                                                         // ����������� � ��������� ������ � ����� ���������.
void print_factory(Factory factory, int index);                                                 // ������� ���������� � ������ � ��� ����������.
void print_factories(Factory* factories, int factory_count);                                    // ������� ���������� � ��  �� �������.
void create_factory_file(const char* filename, Factory* factories, int factory_count);          // ��������� ������ � ������� � ����.
void read_factory_file(const char* filename, Factory* factories, int* factory_count);           // ��������� ������ � ������� �� �����.
void edit_factory(Factory* factories, int factory_index, int person_index);                     // ��������� ������������� ������ � ������ � ��� ����������.
float calculate_sr_oklad(Factory* factories);                                                   // ��������� ������� ����� ���������� ������.
Factory* search_by_quantity_employees(Factory* factories, int factory_count, char* col_person); // ���� ����� �� ���������� ����������.
int compare_number_factory(const void* a, const void* b);                                       // ���������� ��� ������ �� �� �������.
int compare_average_salary(const void* a, const void* b);                                       // ���������� ��� ������ �� �������� ������.
void f_line(int f_size);                                                                        // ������� �������������� ����� � ��������� ~-, ��������� ����������� �������� [], �������� ������ f_size
void s_line(int s_size);                                                                        // ������� �������������� ����� � ��������� ~-, ��������� ������������� ������� [], �������� ������ s_size
void clear_factories(Factory* factories, int* factory_count);                                   // ������� ����������� ������ � �������
void clear_factory_file(const char* filename);                                                  // ������� ���������� ���������� �����.

int main() {
    printf("[~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-]\n");
    printf(" |  �������� ������                                 |\n");
    printf(" |  ����: ���������� �������� ���� ������ '������'  |\n");
    printf(" |  ��������: �������� �.�.                         |\n");
    printf(" |  ������: ���-241                                 |\n");
    printf("[~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-]\n\n");

    Factory* factories = (Factory*)malloc(MAX * sizeof(Factory));
    if (factories == NULL) {
        printf("������: ������������ ������.\n");
        return 1;
    }

    char filename[50];
    int choice, factory_count = 0;

    while (1) {
        printf("\n[~-~-~-~-~-~-~--~ ���� -~-~-~-~-~-~-~-~-~]\n");
        printf(" 1. ��������� ������ �� �����\n");
        printf(" 2. �������� ����� �����\n");
        printf(" 3. �������� ������\n");
        printf(" 4. ��������� ������ � ����\n");
        printf(" 5. ������� ������\n");
        printf(" 6. ����� ������ �� ���������� ����������\n");
        printf(" 7. ���������� �������\n");
        printf(" 8. ������� �����\n");
        printf(" 9. �����\n");
        printf("[~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-]\n\n");

        printf("������� ����� ��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            factory_count = 0;
            printf("������� ��� ����� ��� �������� ������: ");
            scanf("%s", filename);
            read_factory_file(filename, factories, &factory_count);
            printf("������ ��������� �� �����: %s\n", filename);
            break;
        case 2:
            add_factory(factories, &factory_count);
            break;
        case 3:
            if (factory_count == 0) {
                printf("��� ������ ��� ���������.\n");
                break;
            }

            printf("\n������ �������:\n");
            for (int i = 0; i < factory_count; i++) {
                printf("%d. ����� ������: %d\n", i + 1, factories[i].naz_factory);
            }

            int factory_index;
            printf("������� ����� ������ ��� ��������� (�� 1 �� %d): ", factory_count);
            scanf("%d", &factory_index);

            if (factory_index < 1 || factory_index > factory_count) {
                printf("������: �������� ����� ������.\n");
                break;
            }

            Factory* selected_factory = &factories[factory_index - 1];

            printf("\n��������� ������ %d:\n", selected_factory->naz_factory);
            for (int i = 0; i < selected_factory->col_person; i++) {
                printf("%d. �������: %s, ���: %s, ��������: %s\n", i + 1,
                    selected_factory->persons[i].fam,
                    selected_factory->persons[i].im,
                    selected_factory->persons[i].ot);
            }

            int person_index;
            printf("������� ����� ������ ��� ��������� (�� 1 �� %d): ", selected_factory->col_person);
            scanf("%d", &person_index);
            if (person_index < 1 || person_index > selected_factory->col_person) {
                printf("������: �������� ����� ������.\n");
                break;
            }

            edit_factory(factories, factory_index - 1, person_index - 1);
            create_factory_file(filename, factories, factory_count);
            printf("��������� ��������� � ����: %s\n", filename);
            break;
        case 4:
            printf("������� ����� ��� ����� ��� ���������� ������: ");
            scanf("%s", filename);
            create_factory_file(filename, factories, factory_count);
            printf("������ ��������� � ����: %s\n", filename);
            break;
        case 5:
            if (factory_count > 0) {
                print_factories(factories, factory_count);
            }
            else {
                printf("��� ������ ��� ������.\n");
            }
            break;
        case 6: {
            if (factory_count == 0) {
                printf("��� ������� ��� ������.\n");
                break;
            }
            int quantity;
            printf("������� ���������� ���������� ��� ������: ");
            scanf("%d", &quantity);

            Factory* found_factory = search_by_quantity_employees(factories, factory_count, quantity);

            if (found_factory != NULL) {
                printf("����� � ����������� ���������� %d:\n\n", quantity);
                print_factory(*found_factory, found_factory - factories); // ��������� ���������� � �� ���������� ���������� ��������� ����� ����
                f_line(FIRST);
            }
            else {
                printf("����� � ����������� ���������� %d �� ������.\n", quantity);
            }
            break;
        }
        case 7:
            if (factory_count == 0) {
                printf("��� ������� ��� ����������.\n");
                break;
            }
            int compare_choice;
            while (1) {
                printf("\n[~-~-~-~- ���������� -~-~-~-~]\n");
                printf("1. �� ������� �������\n");
                printf("2. �� �������� ������ ������\n");
                printf("3. ������\n");
                printf("[~-~-~-~-~-~-~-~-~-~-~-~-~-~-]\n");
                printf("�������� ��������: ");
                scanf("%d", &compare_choice);

                if (compare_choice == 3) {
                    break;
                }

                switch (compare_choice) {
                case 1:
                    qsort(factories, factory_count, sizeof(Factory), compare_number_factory);
                    printf("������ ������������� �� ������� �������.\n");
                    break;
                case 2:
                    qsort(factories, factory_count, sizeof(Factory), compare_average_salary);
                    printf("������ ������������� �� �������� ������.\n");
                    break;
                default:
                    printf("������������ ������� ������.\n");
                    continue;
                }
                print_factories(factories, factory_count);
            }
            break;
        case 8:
            printf("������� ��� ����� ��� �������: ");
            scanf("%s", filename);
            clear_factory_file(filename);
            printf("���� ������: %s\n", filename);
            break;
        case 9:
            printf("����� �� ���������.\n");
            free(factories); // ������������ ������
            return 0;
        default:
            printf("�������� �����, ���������� �����.\n");
            break;
        }
    }
}

/* ������� */

// ������� ���������� ������ � ������ �������.
void add_factory(Factory* factories, int* factory_count) {

    if (*factory_count >= MAX) {
        printf("������: ��������� ������������ ���������� �������.\n");
    }

    printf("������� ����� ������: ");
    scanf("%d", &factories[*factory_count].naz_factory);

    printf("������� ���������� ����������(�������� %d): ", MAX);
    scanf("%d", &factories[*factory_count].col_person);
    if (factories[*factory_count].col_person > MAX) {
        printf("������: ���������� ���������� �� ����� ��������� %d.\n", MAX);
    }

    for (int i = 0; i < factories[*factory_count].col_person; i++) {
        printf("������� ������ ��� ��������� %d:\n", i + 1);
        add_person(&factories[*factory_count].persons[i]);
    }
    factories[*factory_count].sr_oklad = calculate_sr_oklad(factories);
    (*factory_count)++;
}

// ������� ��� ���������� ������ � ����� ���������.
void add_person(struct person* person) {
    printf("������� �������, ���, ��������: ");
    scanf("%s %s %s", person->fam, person->im, person->ot);
    while (1) {
        printf("������� �������: ");
        scanf("%d", &person->vrst);
        if (person->vrst < 0) {
            printf("������: ������� �� ����� ���� �������������. ���������� �����.\n");
        }
        else {
            break;
        }
    }
    printf("������� �������������: ");
    scanf("%s", person->specialty);
    while (1) {
        printf("������� �����: ");
        scanf("%f", &person->zp);
        if (person->zp < 0) {
            printf("������: ����� �� ����� ���� �������������. ���������� �����.\n");
        }
        else {
            break;
        }
    }
    while (1) {
        printf("������� ���� (� �����): ");
        scanf("%d", &person->opit);
        if (person->opit < 0) {
            printf("������: ���� �� ����� ���� �������������. ���������� �����.\n");
        }
        else {
            break;
        }
    }
}

// ������� ��� ������ ���������� � ������ � ��� ����������.
void print_factory(Factory factory, int index) {
    f_line(FIRST);
    printf("| ������ �����: %-3d | ����� ������ : %-2d | ������� ����� ������: %-12.f | ����������: %-5d |\n",
        index + 1, factory.naz_factory, factory.sr_oklad, factory.col_person);
    s_line(SECOND);
    for (int i = 0; i < factory.col_person; i++) {
        printf("| %-2d | %-12s | %-11s | %-12s | %-7d | %-13s | %-12.f | %-4d |\n",
            i + 1, factory.persons[i].fam, factory.persons[i].im, factory.persons[i].ot, factory.persons[i].vrst, factory.persons[i].specialty, factory.persons[i].zp, factory.persons[i].opit);
    }
}

// ������� ��� ������ ���������� � ���� �������.
void print_factories(Factory* factories, int factory_count) {
    f_line(FIRST);
    printf("| N  | �������      | ���         | ��������     | ������� | ������������� | �����        | ���� |\n");
    f_line(FIRST);
    printf("\n");

    for (int i = 0; i < factory_count; i++) {
        print_factory(factories[i], i);
    }
    f_line(FIRST);
}


// ������� ��� ���������� ������ � ������� � ����.
void create_factory_file(const char* filename, Factory* factories, int factory_count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("������ �������� �����");
        return;
    }

    if (factory_count < 1) {
        printf("������: ��� ������ ��� ����������.\n");
        fclose(file);
        return;
    }

    for (int p = 0; p < factory_count; p++) {
        fprintf(file, "%d\n", factories[p].naz_factory);
        fprintf(file, "%d\n", factories[p].col_person);
        for (int i = 0; i < factories[p].col_person; i++) {
            fprintf(file, "%s %s %s %d %s %.2f %d\n",
                factories[p].persons[i].fam,
                factories[p].persons[i].im,
                factories[p].persons[i].ot,
                factories[p].persons[i].vrst,
                factories[p].persons[i].specialty,
                factories[p].persons[i].zp,
                factories[p].persons[i].opit);
        }
    }
    fclose(file);
}

// ������� ������ ������ �� �����.
void read_factory_file(const char* filename, Factory* factories, int* factory_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("������ ������ �����");
        return;
    }

    while (1) {
        if (fscanf(file, "%d", &factories[*factory_count].naz_factory) != 1) {
            break;
        }

        if (fscanf(file, "%d", &factories[*factory_count].col_person) != 1) {
            printf("������: �� ������� ��������� ���������� ���������� ��� ������ %d\n", factories[*factory_count].naz_factory);
            fclose(file);
            return;
        }

        if (factories[*factory_count].col_person > MAX) {
            printf("������: ���������� ���������� �� ����� ��������� %d. ����������� � %d.\n", MAX, MAX);
            factories[*factory_count].col_person = MAX;
        }

        for (int i = 0; i < factories[*factory_count].col_person; i++) {
            if (fscanf(file, "%s %s %s %d %s %f %d",
                factories[*factory_count].persons[i].fam,
                factories[*factory_count].persons[i].im,
                factories[*factory_count].persons[i].ot,
                &factories[*factory_count].persons[i].vrst,
                factories[*factory_count].persons[i].specialty,
                &factories[*factory_count].persons[i].zp,
                &factories[*factory_count].persons[i].opit) != 7) {
                break;
            }
        }
        factories[*factory_count].sr_oklad = calculate_sr_oklad(&factories[*factory_count]);
        (*factory_count)++;
    }
    fclose(file);
}

// ������� ��� �������������� ������ � ������ � ��� ����������.
void edit_factory(Factory* factories, int factory_index, int person_index) {
    printf("������� ����� ������ ���������:\n");
    printf("������� ����� �������: ");
    scanf("%s", factories[factory_index].persons[person_index].fam);
    printf("������� ����� ���: ");
    scanf("%s", factories[factory_index].persons[person_index].im);
    printf("������� ����� ��������: ");
    scanf("%s", factories[factory_index].persons[person_index].ot);
    printf("������� ����� �������: ");
    scanf("%d", &factories[factory_index].persons[person_index].vrst);
    printf("������� ����� �������������: ");
    scanf("%s", factories[factory_index].persons[person_index].specialty);
    printf("������� ����� �����: ");
    scanf("%f", &factories[factory_index].persons[person_index].zp);
    printf("������� ����� ����: ");
    scanf("%d", &factories[factory_index].persons[person_index].opit);
    factories[factory_index].sr_oklad = calculate_sr_oklad(&factories[factory_index]);
}

// ������� ��� ���������� �������� ������ ���������� ������.
float calculate_sr_oklad(Factory* factories) {
    if (factories->col_person == 0) {
        return 0.0;
    }

    float total_zp = 0.0;
    for (int i = 0; i < factories->col_person; i++) {
        total_zp += factories->persons[i].zp;
    }
    float result = total_zp / factories->col_person;
    return result;
}

// ������� ������ ������ �� ���������� ���������.
Factory* search_by_quantity_employees(Factory* factories, int factory_count, int col_person) {
    for (int i = 0; i < factory_count; i++) {
        if (factories[i].col_person == col_person)
            return (factories + i);
    }
    return NULL;
}

// ������� ���������� �� ������ ������.
int compare_number_factory(const void* a, const void* b) {
    if (((Factory*)a)->naz_factory < ((Factory*)b)->naz_factory) {
        return -1;
    }
    else
        return 1;
}

// ������� ���������� �� �������� ������
int compare_average_salary(const void* a, const void* b) {
    if (((Factory*)a)->sr_oklad < ((Factory*)b)->sr_oklad) {
        return -1;
    }
    else
        return 1;
}

// ������� �������������� ����� � ��������� ~-, ��������� ����������� �������� [], �������� ������ f_size
void f_line(f_size) {
    printf("x");
    for (int i = 0; i < f_size; i++) {
        printf("-");
    }
    printf("x\n");
}

// ������� �������������� ����� � ��������� ~-, ��������� ������������� ������� [], �������� ������ s_size
void s_line(s_size) {
    printf("|");
    for (int i = 0; i < s_size; i++) {
        printf("-");
    }
    printf("|\n");
}

// ������� ������� ����������� � ��������� �����.
void clear_factory_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("������ �������� ����� ��� �������");
        return;
    }
    fclose(file);
}
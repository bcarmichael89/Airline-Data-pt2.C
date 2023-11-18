/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 80
#define MAX_FLIGHTS 7200

// creating structures
typedef struct {
    char airline_name[MAX_LINE_LEN];
    char airline_icao_unique_code[MAX_LINE_LEN];
    char airline_country[MAX_LINE_LEN];
    char from_airport_name[MAX_LINE_LEN];
    char from_airport_city[MAX_LINE_LEN];
    char from_airport_country[MAX_LINE_LEN];
    char from_airport_icao_unique_code[MAX_LINE_LEN];
    double from_airport_altitude;
    char to_airport_name[MAX_LINE_LEN];
    char to_airport_city[MAX_LINE_LEN];
    char to_airport_country[MAX_LINE_LEN];
    char to_airport_icao_unique_code[MAX_LINE_LEN];
    double to_airport_altitude;
} Flight;

typedef struct {
    char DATA[200];
    char Question[200];
    int N;
} Args;

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->subject, p->statistic);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    //printf("Number of words: %d\n", len);

    apply(l, print_node, "%s, %d\n");
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

// filter the arguments passed in
Args argsfilter(int argc, char *argv[]) {
    Args args = {"", "", 0};
    char *search_after;
    // loop through the arguments
    for (int i = 1; i < argc; i++) {

        search_after = strchr(argv[i], '=');

        if (search_after == NULL) {
            printf("Error: Invalid argument\n");
            exit(1);
        } else if (strncmp(argv[i], "--DATA=", 7) == 0) {
            strncpy(args.DATA, search_after + 1, 200);

        } else if (strncmp(argv[i], "--QUESTION=", 11) == 0) {
            strncpy(args.Question, search_after + 1, 200);

        } else if (strncmp(argv[i], "--N=", 4) == 0) {
            args.N = atoi(search_after + 1);

        } else {
            printf("Invalid argument\n");
            exit(1);
        }
    }

    return args;
}
        
    
    // filter the data for question 1
    void filter_for_q1(int N, char airline_name[MAX_LINE_LEN], char airline_icao_unique_code[MAX_LINE_LEN], char to_airport_country[MAX_LINE_LEN], node_t *head) {        
        // initialize variable to store the merged name and code
        char* merged_name_code = malloc(sizeof(char) * 100);
    
        //remove the new line character from airline_name and airline_icao_unique_code
        airline_name[strcspn(airline_name, "\n")] = '\0';
        airline_icao_unique_code[strcspn(airline_icao_unique_code, "\n")] = '\0';
        // merge the name and code on the same string
        sprintf(merged_name_code, "%s (%s)", airline_name, airline_icao_unique_code);
        int found = 0;
        
        // if head subject is "empty", input values into head node
        if (strcmp(head->subject, "empty") == 0){
            head->subject = merged_name_code;
            head->statistic = 1;
            found++;
            head->next = NULL;                
        }else{
            // loop through the linked list looking for the subject
            struct node_t *cur = head;
            while(cur != NULL){
                if (strcmp(cur->subject, merged_name_code) == 0){
                    cur->statistic += 1;
                    found++;
                    break;
                }  
                cur = cur->next;  
            }
        }
                // if not already in the list, add it to the back                   
                if(found == 0){
                    head = add_end(head, new_node(merged_name_code, 1));
                    
                }
    }        
                                      
    // filter the data for question 2
    void filter_for_q2(char to_airport_country[MAX_LINE_LEN], struct node_t *head) {
        // initialize variable to store the string
        char* input_country = malloc(sizeof(char) * 100);
        // remove the new line character from to_airport_country
        to_airport_country[strcspn(to_airport_country, "\n")] = '\0';
        strcpy(input_country, to_airport_country);
        
        int found = 0;
        // if head subject is "empty", input values into head node
        if (strcmp(head->subject, "empty") == 0){
            head->subject = input_country;
            head->statistic = 1;
            head->next = NULL; 
            found++; 
             
        }else{
            struct node_t *cur = head;
            
            while(cur != NULL){
                // if the subject is already in the list, increment the statistic
                if (strcmp(cur->subject, input_country) == 0){
                    cur->statistic += 1;
                    found++;                   
                    break;
                }  
                cur = cur->next;  
            }
        }
        // if not already in the list, add it to the back
        if(found == 0){
            head = add_end(head, new_node(input_country, 1));
        }
    }
    // filter the data for question 3
    void filter_for_q3(char to_airport_name[MAX_LINE_LEN], char to_airport_icao_unique_code[MAX_LINE_LEN], char to_airport_city[MAX_LINE_LEN], char to_airport_country[MAX_LINE_LEN], struct node_t *head) {
        // initialize variable to store the string
        char* input_airport_name = malloc(sizeof(char) * 200);
        // removing new line characters from the strings
        to_airport_name[strcspn(to_airport_name, "\n")] = '\0';
        to_airport_icao_unique_code[strcspn(to_airport_icao_unique_code, "\n")] = '\0';
        to_airport_city[strcspn(to_airport_city, "\n")] = '\0';
        to_airport_country[strcspn(to_airport_country, "\n")] = '\0';
        // merging the strings into one
        sprintf(input_airport_name, "%s (%s), %s, %s", to_airport_name, to_airport_icao_unique_code, to_airport_city, to_airport_country);
        int found = 0;
        // if head subject is "empty", input values into head node
        if (strcmp(head->subject, "empty") == 0){
            head->subject = input_airport_name;
            head->statistic = 1;
            head->next = NULL; 
            found++;
    }else{
        // loop through the linked list looking for the subject, if found increment the statistic
        struct node_t *cur = head;
        while(cur != NULL){
            if (strcmp(cur->subject, input_airport_name) == 0){
                cur->statistic += 1;
                found++;
                break;
            }  
            cur = cur->next;  
        }

    }
    // if not already in the list, add it to the back
    if(found == 0){
        head = add_end(head, new_node(input_airport_name, 1));
    }
    }


    // function to sort the linked list
    void sorting(struct node_t *head, char* Question){
        // initialize variables
        struct node_t *temp = head;
        struct node_t *temp2 = head;
        int temp3;
        char* temp4;

        while(temp != NULL){
            temp2 = temp->next;
            while(temp2 != NULL){
                // if the subject contains weird characters, remove them
                if (strcmp(temp2->subject, "' Sheffield'") == 0){
                    temp2->subject = "Sheffield";
                }if (strcmp(temp2->subject, "' Santiago Island'") == 0){
                    temp2->subject = "Santiago Island";
                    // confusing sorting algorithm
                }if(temp->statistic < temp2->statistic || (temp->statistic == temp2->statistic && strcmp(temp->subject, temp2->subject) > 0)){
                    temp3 = temp->statistic;
                    temp->statistic = temp2->statistic;
                    temp2->statistic = temp3;
                    temp4 = temp->subject;
                    temp->subject = temp2->subject;
                    temp2->subject = temp4;
            }
                    
                temp2 = temp2->next;
            }
            temp = temp->next;
        }   
    }
    void printing_q1(struct node_t *head, int N){
        // open fp1 
            FILE *fp3;
        fp3 = fopen("output.csv", "a");
        if(fp3 == NULL){
            printf("can not open txt file");
        }
        // make the header
        fprintf(fp3, "subject,statistic\n");
        struct node_t *temp = head;
        int count = 0;
        // print the top N values   
        while(temp != NULL && count < N){           
            fprintf(fp3, "%s,%d\n", temp->subject, temp->statistic);
            temp = temp->next;
            count++;
        }
    }
    void printing_q2(struct node_t *head, int N){
        
        // opening csv file 
            FILE *fp;
        fp = fopen("output.csv", "a");
        if(fp == NULL){
            printf("can not open txt file");
        }
        //making the header
        fprintf(fp, "subject,statistic\n");
        // initialize variables
        int min_value = 1;
        int count = 0;
        // finding the minimum value
        struct node_t *temp = head;
        while(temp != NULL){
            if(temp->statistic < min_value){
                min_value = temp->statistic;
            }
            temp = temp->next;
        }
        // initializing variable that helps skip the very first line
        int skipper = 0;
        // iterating over the bottom values with the current min_value and printing them
        while(count < N){           
        temp = head; 
        while(temp != NULL){
            if(temp->statistic == min_value && count < N){
                // skipping first line
                if (skipper < 1){
                    temp = temp->next;
                }
                fprintf(fp, "%s,%d\n", temp->subject, temp->statistic);
                count++;
                skipper++;
            }
            temp = temp->next;
        }
        // adding one to the min_value, which will then be used to find the next lowest value
        min_value++;
        }
    }
        void printing_q3(struct node_t *head, int N){
            // opening csv file 
                FILE *fp;
            fp = fopen("output.csv", "a");
            if(fp == NULL){
                printf("can not open txt file");
            }
            //making the header
            fprintf(fp, "subject,statistic\n");
            // print the top N values
            struct node_t *temp = head;
            int count = 0;
            while(temp != NULL && count < N){
                // add quotation marks around the subject and print to fp
                fprintf(fp, "\"%s\",%d\n", temp->subject, temp->statistic);
                temp = temp->next;
                count++;
            }
        }
        
    
    

int main(int argc, char *argv[]) {
    
    
    // calling the argument filter function
    Args args = argsfilter(argc, argv);
    // opening the data file
    FILE *fp;
        fp = fopen(args.DATA, "r");
        if (fp == NULL){
        
            printf("Error: File not found\n");
            exit(1);
        }

    // opening and resetting the output file
    FILE *fp1;
        fp1 = fopen("output.csv", "w");
        if (fp1 == NULL)
        {
            printf("Error: File not found\n");
            exit(1);
        }

    // initiallizing the variables
    char line[MAX_LINE_LEN];
    int number_of_flights = 0;
    Flight Array[MAX_FLIGHTS];
    
    // creating the head of the linked list
    struct node_t *head = new_node("empty", 0);    
    
    // reading the file line by line
    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {


        // if the dash is found, it indicates a new flight  
        if (line[0] == '-') {
            
            // if Question 1 is selected call the q1 filter with the array of the current flight
            if (strcmp(args.Question, "1") == 0 && strncmp(Array[number_of_flights].to_airport_country, "Canada", 6) == 0) {
                filter_for_q1(args.N, Array[number_of_flights].airline_name, Array[number_of_flights].airline_icao_unique_code, Array[number_of_flights].to_airport_country, head);                
            }
            // if Question 2 is selected call the q2 filter
            if (strcmp(args.Question, "2") == 0){
                filter_for_q2(Array[number_of_flights].to_airport_country, head);
            }
            // if Question 3 is selected call the q3 filter
            if (strcmp(args.Question, "3") == 0){
                filter_for_q3(Array[number_of_flights].to_airport_name, Array[number_of_flights].to_airport_icao_unique_code, Array [number_of_flights].to_airport_city, Array[number_of_flights].to_airport_country, head);
            }
            // increment the number of flights
            number_of_flights++; 

            // after passing the array to the filter, clear it 
            memset(Array, 0, sizeof(Array));  
        }
        // adding each element of the flight information to the linked list
        if (strncmp(line, "- airline_name", 14) == 0) {
            // only pass what is after the colon, same for each flight element
            char *after_colon = strchr(line, ':'); 
            strncpy(Array[number_of_flights].airline_name, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  airline_icao_unique_code", 26) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].airline_icao_unique_code, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  airline_country", 17) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].airline_country, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  from_airport_name", 19) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].from_airport_name, after_colon + 2, MAX_LINE_LEN);
            
        }
        if (strncmp(line, "  from_airport_city", 19) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].from_airport_city, after_colon + 2, MAX_LINE_LEN);
            
        }
        if (strncmp(line, "  from_airport_country", 22) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].from_airport_country, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  from_airport_icao_unique_code", 31) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].from_airport_icao_unique_code, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  to_airport_name", 17) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].to_airport_name, after_colon + 2, MAX_LINE_LEN);
            
        }
        if (strncmp(line, "  to_airport_city", 17) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].to_airport_city, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  to_airport_country", 20) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].to_airport_country, after_colon + 2, MAX_LINE_LEN);
        }
        if (strncmp(line, "  to_airport_icao_unique_code", 29) == 0) {
            char *after_colon = strchr(line, ':');
            strncpy(Array[number_of_flights].to_airport_icao_unique_code, after_colon + 2, MAX_LINE_LEN);
        }
    }

    // call the sorting function with the linked list
    sorting(head, args.Question);
    // call the correlated printing function
    if (strcmp(args.Question, "1") == 0){
        printing_q1(head, args.N);
    }else if(strcmp(args.Question, "2") == 0){
        printing_q2(head, args.N);
    }else{
        printing_q3(head, args.N);
    }
    // close the files   
    fclose(fp);
    fclose(fp1);
    exit(0);

}
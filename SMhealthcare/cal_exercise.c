//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise

// To declare the structure of the exercises
Exercise exercise_list[MAX_EXERCISES]; //Delete static for use elsewhere
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (1) {
		
		int i;
		for(i=0; i<MAX_EXERCISES; i++){
			fscanf(file, "%s %d", exercise_list[i].exercise_name, &exercise_list[i].calories_burned_per_minute); 
			exercise_list_size++;
		}
			
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}	
    }
    
    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
	for(i=0; i<MAX_EXERCISES; i++){ 
		if(exercise_list[i].calories_burned_per_minute == 0) //To prevent 100 lines from coming out
			break; 
		printf("%d. %s (%d kcal burned per min.)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}
	printf("7. Exit\nChoose (1-7): ");
	scanf("%d", &choice);
	
	// ToCode: to enter the exercise to be chosen with exit option
	if(choice != 7){
		int j;
		health_data->exercise_count++;
		for(j=0; j<MAX_EXERCISE_NAME_LEN; j++){
		health_data->exercises[health_data->exercise_count-1].exercise_name[j] = exercise_list[choice-1].exercise_name[j]; //Use j to copy an array of names
		}
    
    // To enter the duration of the exercise
   		printf("Enter the duration of the exercise (in min.): ");
    	scanf("%d", &duration);
    	
    // ToCode: to enter the selected exercise and total calcories burned in the health data
		health_data->exercises[health_data->exercise_count-1].calories_burned_per_minute = (exercise_list[choice-1].calories_burned_per_minute)*duration;
		health_data->total_calories_burned = health_data->total_calories_burned + (exercise_list[choice-1].calories_burned_per_minute)*duration;	
	}

}

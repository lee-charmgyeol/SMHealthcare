//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for(i=0; i<MAX_EXERCISES; i++){
    	if(health_data->exercises[i].calories_burned_per_minute == 0) //To prevent 100 lines from being written down
    		break;
    	fprintf(file, "%s - %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
	}
    fprintf(file, "Total calories burned - %d kcal\n", health_data->total_calories_burned);
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
	for(i=0; i<MAX_DIETS; i++){
		if(health_data->diet[i].calories_intake == 0) //To prevent 100 lines from being written down
			break;
    	fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}
    fprintf(file, "Total calories intake - %d kcal\n", health_data->total_calories_intake);

    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
	fprintf(file, "Basal metabolic rate - 1300 kcal\nThe remaining calories - %d kcal", health_data->total_calories_intake - 1300 - health_data->total_calories_burned);  
	
	fclose(file);  
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	int remaining_kcal; //To express the remaining calories briefly
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for(i=0; i<MAX_EXERCISES; i++){
		if(health_data->exercises[i].calories_burned_per_minute == 0) //To prevent 100 lines from being written down
			break;
		printf("Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
	}
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
	for(i=0; i<MAX_DIETS; i++){
		if(health_data->diet[i].calories_intake == 0) //To prevent 100 lines from being written down
			break;
		printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}
    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
 	printf("Basal Metabolic Rate: 1300 kcal\n");
 	printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
 	printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
 	printf("The remaining calories: %d kcal\n", health_data->total_calories_intake - 1300 - health_data->total_calories_burned);
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    remaining_kcal = health_data->total_calories_intake - 1300 - health_data->total_calories_burned; //To express the remaining calories briefly
    if (remaining_kcal == 0){
    	printf("You have consumed all your calories for today!");
    	printf("Exit the system.\n");
    	printf("=======================================================================\n");
    }
    else if (remaining_kcal < 0){
    	printf("[warning] Too few calories!\n");
    	if (health_data->total_calories_intake == 2000)
    		printf("Your total calories intake for today has reached your goal!\n=======================================================================\n");
    	else if (health_data->total_calories_intake < 2000)
    		printf("Your total calories intake for today has not reached your goal, remember to eat more!!\n=======================================================================\n");
    	else 
    		printf("You have eaten more calories than planned today, but you have exercised too much!\n=======================================================================\n");
    }
    else{
    	printf("Please exercise for your health!\n");	
    	if (health_data->total_calories_intake >= 2000)
    		printf("Your total calories intake for today has reached your goal!\n=======================================================================\n");
    	else
    		printf("Your total calories intake for today has not reached your goal, remember to eat more!!\n=======================================================================\n");
	}
}

//Joy, Patrick - 344 - Project 1
# include<stdio.h>
# include<stdlib.h>
const char FILE_NAME[] = "project.c";

int stack(char inChar, int x);
static int count = 0;
static const int stackSize = 50;

int main(){
	char idSymbols[53] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
				'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
				'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
				'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
				'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};       
	
	int skipRead = 0; /*Flag used to indicate that next character was already read*/
        int inChar;	/*character variable*/
	int countId = 0; /*number of characters seen*/

        FILE *in_file; /*input file*/
       
        in_file = fopen(FILE_NAME, "r"); /*opens the file*/

	//If file cannot be open
        if (in_file == NULL) {
        	printf("Cannot open %s\n", FILE_NAME);		
        	return(0);
        }//end if statement

	//Read in the character and run until EOF is reached
        while(1){ 
		if(skipRead == 0){
			inChar = fgetc(in_file); /*get char*/
		}//end if statment
	
		else{
			skipRead = 0;
		}//end else statement
		
		//state q1:
		if(skipRead != 1 && (inChar == '{' || inChar == '(' || inChar == '[')){
			//add to the stack
			int x = stack(inChar, 0);
			
			if(x == 0){
				return 0;
			}//end if statement
		}//end else if statement

		//state q1:
		else if(skipRead != 1 && (inChar == '}' || inChar == ')' || inChar == ']')){
			//remove from the stack
			int x = stack(inChar, 1);

			if(x == 0){
				return 0;
			}//end if statement
		}//end else if statement
		

		else if(skipRead != 1 && inChar == '/'){
			//Here we have requested a new character, and have essentially skipped the first /
			inChar = fgetc(in_file);
			
			//check for // and ignore everything until the new line.
			if(inChar == '/'){
				//Ignore all characters until the next line.
				while(inChar != '\n'){
					//Continue along looking for EOF or \n
					inChar = fgetc(in_file); 
					
					//Warn them if the EOF command was found in a comment
					if(inChar == EOF){
						printf("NOTICE: File ended with \\\\ line comment\n");
						break;
					}//end if statement
				}//end while loop
			}//end if statement

			//check for /*...*/ and ignore everything in between.
			else if(inChar == '*'){
				while(1){
					//continue along looking for EOF or */
					inChar = fgetc(in_file);

					if(inChar == EOF){
						printf("ERROR: \\* was never closed.\n");					
						return 0;
					}//else if

					else if(inChar == '*'){
						//check the next character to see if it is a /
						inChar = fgetc(in_file);

						if(inChar == '/'){
							break;
						}//end if statement
					}//end if statement								
				}//end while loop

				if(inChar != EOF){
					//get the next character because the comment string is done.
					inChar = fgetc(in_file);
					//skip the next read character command to ensure you check the possibilities for this one.
					skipRead = 1;
				}//end if statement
			}//end else if statement
			
			//inform user that there is a misplaced / in  the code.
			else{
				printf("ERROR: Misplaced / in code.\n");
				return 0;
			}//end else statement				
		}//end else if statement 
	
		//Check for '...' and ignore anything in between.
		else if(skipRead != 1 && inChar == '\''){
			while(1){
				//get the next char to look for next single quote
				inChar = fgetc(in_file);
				
				//check to see if \' is in there, and ignore it if it is.
				if(inChar == '\\'){
					inChar = fgetc(in_file);
					
					if(inChar == '\''){
						inChar = fgetc(in_file);
					}//end if statement
				}//end if statement

				if(inChar == '\''){
					break;
				}//break
				
				//If EOF is found break the loop
				else if(inChar == EOF){
					printf("ERROR: ' was never closed.\n");
					return 0;
				}//end if statement
			}//end while loop
			
			if(inChar != EOF){
				inChar = fgetc(in_file);
				skipRead = 1;
			}//end if statement
		}//end else if statement
		
		//Check for "..." and ingore everything in between.
		else if(skipRead != 1 && inChar == '\"'){
			while(1){
				inChar = fgetc(in_file);

				//check to see if \' is in there, and ignore it if it is.
				if(inChar == '\\'){
					inChar = fgetc(in_file);
					
					if(inChar == '\"'){
						inChar = fgetc(in_file);
					}//end if statement
				}//end if statement

				if(inChar == '\"'){
					break;
				}//break

				else if(inChar == EOF){
					printf("ERROR: \" was never closed.\n");
					return 0;
				}//end if statement
			}//end while loop
			
			if(inChar != EOF){
				inChar = fgetc(in_file);
				skipRead = 1;
			}//end if statement
		}//end else if statement
		
		
		if(skipRead != 1){
			int i;
			for(i = 0; i < 53; i++){
				if(inChar == idSymbols[i]){
					while(1){
						inChar = fgetc(in_file);
						
						if(inChar == '{' || inChar == '(' || inChar == '[' ||
						inChar == '}' || inChar == ']' || inChar == ')' || 
						inChar == ' ' || inChar == ',' || inChar == ';' ||
						inChar == '=' || inChar == '>' || inChar == '<' ||
						inChar == '|' || inChar == '&' || inChar == '\\' || 
						inChar == '/'){
							countId++;
							break;
						}//end if statement							 
					}//end while loop

					if(inChar != EOF){
						skipRead = 1;
					}//end if statement*/
				}//end if statement
			}//end for loop
		}//end if statement

		if(skipRead != 1 && inChar == EOF){
        		break;
		}//end if statement
		
		//For testing
		/*if(skipRead != 1){
			printf("%c", inChar); 
		}//end if statement*/        			
    	}//end while loop
	
	if(count > 0){
		printf("Error: Symbols remain in stack. Not enough closing brackets.\n");
		return 0;
	}//end if statement

	else if(count < 0){
		printf("ERROR: (POPPING) Your count variable is negative.  Check your logic.\n");
		return 0;
	}//end else if

	else{
		printf("No Errors:\n");
	    	printf("Number of Keywords/Identifiers in %s = %d.\n", FILE_NAME, countId);

	    	fclose(in_file);
	    	return (0);
	}//end else statement
}//end main function

int stack(char inChar, int x){
	char array[stackSize];
	//PUSHING
	if(x == 0){
		if(count < stackSize && count >= 0){
			array[count] = inChar;
			count++;
			//printf("%c\n", inChar);  //For testing
			//printf("Count is %d\n", count);
	
			//continue the program
			return 1;
		}//end if statement
		
		else if (count >= stackSize){
			printf("ERROR: (PUSHING) The bracket stack is full.  Allocate more space and try again.\n");
			
			//Terminate Program
			return 0;
		}//end else statement
		
		else{
			printf("ERROR: (PUSHING) Your count variable is negative.  Check your logic.\n");
			//Terminate the program
			return 0;
		}//end else statement
	}//end if statement
	
	//POPPING
	else if(x == 1){
		if(count > 0 && count < stackSize){
			if((inChar == '}') && (array[count-1] == '{')){
				array[count-1] = 0;
				count--;				
				//printf("%c\n", inChar); //For testing
				//printf("Count is %d\n", count);

				//continue the program
				return 1;
			}//end if statement
		
			else if((inChar == ')') && (array[count-1] == '(')){
				array[count-1] = 0;
				count--;				
				//printf("%c\n", inChar); //For testing
				//printf("Count is %d\n", count);

				//continue the program
				return 1;
			}//end if statement
		
			else if((inChar == ']') && (array[count-1] == '[')){
				array[count-1] = 0;
				count--;				
				//printf("%c\n", inChar); //For testing
				//printf("Count is %d\n", count);

				//continue the program
				return 1;
			}//end if statement
			
			else if((array[count-1] != 0) && (inChar != array[count-1])){
				printf("ERROR: Scanned %c but popped %c. Bracket Mismatch.\n", inChar, array[count-1]);
				//Terminate the program
				return 0;
			}//end else if statement
			
			else if(array[count-1] == 0){
				printf("ERROR: Popping from the stack, but no value was in the slot.\n");
				//Terminate the program
				return 0;
			}//end else if statement
		}//end if statement
		
		else if(count >= stackSize){
			printf("ERROR: (POPPING) The bracket stack is full.  Allocate more space.\n");
			//Terminate Program
			return 0;
		}//end else statement
		
		else if(count == 0){
			printf("ERROR: %c was input, but nothing is in the stack to pop.\n", inChar);
			//Terminate Program
			return 0;
		}//end else if
		else{
			printf("ERROR: (POPPING) Your count variable is negative.  Check your logic.\n");
			//Terminate the program
			return 0;
		}//end else statement	
	}//end else if statement
}//end stack function

/*-------------------------------------------------------------------*/
/* ITS60304– Assignment #1 */
/* C Programming */
/* Student Name: <Balreen Kaur Badesha> <Lakshana Bunghoo> */
/* Student ID: <0319848> <0323400> */
/*-------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int menu(void);
void purchase_items(void);
void edit_items(void);
void delete_items(void);
void show_inventory(void);
void show_dailytransactions(void);
int count;
float s_gst,s_ngst,t_gst;
unsigned int u_quantity;
char useritem_code[100];
FILE *fp1, *fp2, *myfile1, *temp1;// myfile is for receipt purposes

struct read_calculate{
	char item_code[100];//array declared for the barcode of items
	char item_name[100];//array declared for the name of items
	float price;//price of item
	unsigned int quantity;// quantity of the item dealt with
	} reference ;

int main(void){
	menu();
}

int menu(void){
	
	int i;
	char selection;
	printf("\n");
	for (i=0;i<80;i++){
		printf("-");
	}
	printf("Grocery Retail\n");
	for (i=0;i<80;i++){
		printf("-");
	}
	printf("1. Purchase items\n");
	printf("2. Edit items\n");
	printf("3. Delete items\n");
	printf("4. Show inventory\n");
	printf("5. Show daily transaction\n");
	printf("6. Exit\n");
	printf("Please enter your selection:");
	scanf(" %c",&selection);
	
	switch(selection){
		case '1':
			purchase_items(); // Requirement 2
			break;
		case '2':
			edit_items();// Requirement 3
			break;
		case '3':
			delete_items(); // Requirement 5
			break;
		case '4':
			show_inventory(); // Requirement 6
			break;
		case '5':
			show_dailytransactions(); // Requirement 7
			break;
		case '6':
			printf("Program has been exited\n");
			fclose(fopen("purchase.txt", "w")); // clear contents of file for the next transaction / run
			exit(0); // exit the program
			break;
		default:
			printf("Your selection is not an option!\n");
			menu();
	}
}

void purchase_items(void){
	int check; // To avoid the item for being checked repeatedly
	int i;
	unsigned int remainder;
	char copy;
	float total_gst,total_ngst;
	float gst;
	float sum_gst;
	float sum_both;
	float purchase_sum;
	do{
		printf("Please enter item code <-1 to end>:");
		scanf("%s",useritem_code);
		if(strcmp(useritem_code,"-1")!=0){
			printf("Please enter quantity:");
			scanf("%d",&u_quantity);
			if ((fp1 = fopen("gst.txt","r"))==NULL){
				puts("File could not be opened!");
			}//end if
			else{
				while (!feof(fp1)) { 
					fscanf(fp1," %[^;];%[^;];%f;%u\n",reference.item_code, reference.item_name, &reference.price, &reference.quantity);
					if (strcmp(reference.item_code,useritem_code)==0){
						 while(u_quantity > reference.quantity){
							printf("Not enough items in inventory.\n");
							printf("Quantity of items only left: %d\n",reference.quantity);
							printf("Please enter new quantity:");
							scanf("%d",&u_quantity);
						}
						remainder = reference.quantity - u_quantity;
						total_gst = u_quantity * reference.price;
						gst = total_gst * 0.06;
						sum_gst = gst + total_gst;
						check = 1;
						count = count + u_quantity;
						s_gst = s_gst + sum_gst;
						t_gst = t_gst + gst;
						purchase_sum = sum_gst;
						printf("\n %s %15s %14s %12s %15s\n","Item Code","Item Name","Price(RM)","Quantity","Total(RM)");
						printf(" %7s %18s %10.2f %12u %16.2f\n",reference.item_code, reference.item_name,reference.price,u_quantity,purchase_sum);
						myfile1 = fopen("purchase.txt", "a");
	   					fprintf(myfile1, "%s;%s;%.2f;%u;%.2f\n",reference.item_code, reference.item_name,reference.price,u_quantity,purchase_sum);
	   					fclose(myfile1);
						temp1 = fopen("temp.txt","a");
	   					fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, reference.item_name,reference.price,remainder);
	   					fclose(temp1);	   	
					}//end if
					else{
						temp1 = fopen("temp.txt","a");
	   					fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, reference.item_name,reference.price,reference.quantity);
	   					fclose(temp1);
					}
				}//end while
				fclose(fp1);
			}//end else
			remove("gst.txt");
			rename("temp.txt","gst.txt");
			if(check!= 1){
				if ((fp2 = fopen("ngst.txt","r"))==NULL){
					puts("File could not be opened!");
				}//end if
				else{
					while (!feof(fp2)) { 
					fscanf(fp2," %[^;];%[^;];%f;%u\n",reference.item_code, reference.item_name, &reference.price, &reference.quantity);
					if (strcmp(reference.item_code,useritem_code)==0){
						while(u_quantity > reference.quantity){
							printf("Not enough items in inventory.\n");
							printf("Quantity of items only left: %d\n",reference.quantity);
							printf("Please enter new quantity:");
							scanf("%d",&u_quantity);
						}	
						total_ngst = u_quantity * reference.price;
						check = 1;
						count = count + u_quantity;
						s_ngst = s_ngst + total_ngst;
						purchase_sum = total_ngst;
						printf("\n %s %15s %14s %12s %13s\n","Item Code","Item Name","Price(RM)","Quantity","Total(RM)");
						printf(" %7s %15s %14.2f %12u %13.2f\n",reference.item_code, reference.item_name, reference.price,u_quantity,purchase_sum);
						myfile1 = fopen("purchase.txt", "a");/*Write to a file without overwriting to the file*/
   						fprintf(myfile1, "%s;%s;%.2f;%u;%.2f\n",reference.item_code, reference.item_name, reference.price,u_quantity,purchase_sum); 
   						fclose(myfile1);
   						temp1 = fopen("temp.txt","a");
	   					fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code,reference.item_name,reference.price,remainder);
	   					fclose(temp1);
						}//end if
					else{	
						temp1 = fopen("temp.txt","a");
		   				fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code,reference.item_name,reference.price,reference.quantity);
		   				fclose(temp1);
						}	
					}//end while
					fclose(fp2);
					remove("ngst.txt");
					rename("temp.txt","ngst.txt");
					if (check != 1){
						printf("-------Item not found! Please try again-------\n");
					}// end if
				}//end else
				
			}// end if
		}//end if
		check = 0;// Initalizing back the value to ensure the program is able to repeatedly check the item code for errors or matches.
	}while(strcmp(useritem_code,"-1")!=0);// end do-while loop
	sum_both = s_gst + s_ngst; /* To calculate the sum of the gst and ngst purchases and to avoid the receipt to be printed if nothing is purchased*/
	
	if (sum_both != 0){
		for (i=0;i<80;i++){
			printf("~");
		}
		printf("%40s\n","RECEIPT");
		printf("\n %s %15s %14s %12s %14s\n","Item Code","Item Name","Price(RM)","Quantity","Total(RM)"); // header
		for (i=0;i<80;i++){
			printf("~");
		}
		if ((myfile1 = fopen("purchase.txt","r"))==NULL){
			puts("File could not be opened!");
		}// end if 
		else{
			while(!feof(myfile1)){
				fscanf(myfile1," %[^;] ; %[^;] ;%f ;%u;%f " ,reference.item_code, reference.item_name, &reference.price,&u_quantity,&purchase_sum);
				printf("%8s %20s %9.2f %11u %15.2f\n",reference.item_code, reference.item_name, reference.price,u_quantity,purchase_sum);
			}// end while
			fclose(myfile1);
		}// end else
				
		printf("\nTotal of gst items          : RM %.2f\n",s_gst);
		printf("Total of ngst items         : RM %.2f\n",s_ngst);
		printf("Total of gst and ngst items : RM %.2f\n",sum_both);
		for (i=0;i<80;i++){
			printf("~");
		}	
	}
	menu();
}

void edit_items(void){
	int check,verify;
	float price;
	char decision;
	char newname[100];
	int i;
	for (i=0;i<80;i++){
		printf("~");
	}
	printf("%45s\n","EDITING ITEMS");
	
	for (i=0;i<80;i++){
		printf("~");
	}
	do{
		printf("Please enter item code <-1 to end>:");
		scanf("%s",useritem_code);
		if(strcmp(useritem_code,"-1")!=0){
			if ((fp1 = fopen("gst.txt","r"))==NULL){
				puts("File could not be opened!");
			}//end if
			else{
				while (!feof(fp1)) { 
					fscanf(fp1," %[^;];%[^;];%f;%u\n",reference.item_code, reference.item_name, &reference.price, &reference.quantity);
					if (strcmp(reference.item_code,useritem_code)==0){
						check = 1;
						printf("Please enter new name:");
						scanf("%s",newname);
						printf("Please enter new quantity:");
						scanf("%u",&u_quantity);
						printf("Please enter new price:");
						scanf("%f",&price);
						printf("Enter Y to continue or any other character to retype values:");
						scanf(" %c",&decision);
						if (decision == 'Y'){	
							temp1 = fopen("temp.txt","a");
			   				fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, newname,price,u_quantity);
			   				fclose(temp1);
			   				verify =1;
			   				printf("--------Edits were done-------\n");
						}
						
					}//end if
					else{
						temp1 = fopen("temp.txt","a");
		   				fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, reference.item_name,reference.price,reference.quantity);
		   				fclose(temp1);
					}// end else 	
				}//end while
				fclose(fp1);
				if(verify == 1){
					remove("gst.txt");
					rename("temp.txt","gst.txt");
				}// only done when changes are made
				verify = 0; // for further checking it is initilize to 0
			}//end else
			fclose(fopen("temp.txt", "w"));// clear content if any
			if(check!= 1){
				if ((fp2 = fopen("ngst.txt","r"))==NULL){
					puts("File could not be opened!");
				}//end if
				else{
					while (!feof(fp2)) { 
						fscanf(fp2," %[^;];%[^;];%f;%u\n",reference.item_code, reference.item_name, &reference.price, &reference.quantity);
						if (strcmp(reference.item_code,useritem_code)==0){
							check = 1;
							printf("Please enter new name:");
							scanf("%s",newname);
							printf("Please enter new quantity:");
							scanf("%u",&u_quantity);
							printf("Please enter new price:");
							scanf("%f",&price);
							printf("Enter Y to continue or any other character to retype values:");
							scanf(" %c",&decision);
							if (decision == 'Y'){	
								temp1 = fopen("temp.txt","a");
					   			fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, newname,price,u_quantity);
					   			fclose(temp1);
					   			verify = 1;
					   			printf("--------Edits were done-------\n");
							}// end if
						}//end if
						else{
							temp1 = fopen("temp.txt","a");
		   					fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, reference.item_name,reference.price,reference.quantity);
		   					fclose(temp1);
						}// end else
					}//end while
					fclose(fp2);
					if(verify == 1){
						remove("ngst.txt");
						rename("temp.txt","ngst.txt");
					}// only done when changes are made
					verify = 0;
					if (check != 1){
						printf("-------Item not found! Please try again-------\n");
					}// end if
				}//end else
				
			}// end if
		}//end if
		fclose(fopen("temp.txt", "w"));// clear content if any
		check = 0;// Initalizing back the value to ensure the program is able to repeatedly check the item code for errors or matches.
	}while(strcmp(useritem_code,"-1")!=0);// end do-while loop
	
	menu();
}


void delete_items(void){
	int check,verify;
	float price;
	char decision;
	char newname[100];
	int i;
	for (i=0;i<80;i++){
		printf("~");
	}
	printf("%45s\n","DELETE ITEMS");
	
	for (i=0;i<80;i++){
		printf("~");
	}
	do{
		printf("Please enter item code <-1 to end>:");
		scanf(" %s",useritem_code);
		if(strcmp(useritem_code,"-1")!=0){
			if ((fp1 = fopen("gst.txt","r"))==NULL){
				puts("File could not be opened!");
			}//end if
			else{
				while (!feof(fp1)) { 
					fscanf(fp1," %[^;];%[^;];%f;%u\n",reference.item_code, reference.item_name, &reference.price, &reference.quantity);
					if (strcmp(reference.item_code,useritem_code)==0){
						check = 1;
						if (reference.quantity == 0){	
							printf("Item was successfully delected.\n");
			   				verify =1;
						}
						else{
							printf("Item cannot be deleted.\n");
						}
						
					}//end if
					else{
						temp1 = fopen("temp.txt","a");
		   				fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, reference.item_name,reference.price,reference.quantity);
		   				fclose(temp1);
					}// end else 	
				}//end while
				fclose(fp1);
				if(verify == 1){
					remove("gst.txt");
					rename("temp.txt","gst.txt");
				}// only done when changes are made
				verify = 0; // for further checking it is initilize to 0
			}//end else
			fclose(fopen("temp.txt", "w"));// clear content if any
			if(check!= 1){
				if ((fp2 = fopen("ngst.txt","r"))==NULL){
					puts("File could not be opened!");
				}//end if
				else{
					while (!feof(fp2)) { 
						fscanf(fp1," %[^;];%[^;];%f;%u\n",reference.item_code, reference.item_name, &reference.price, &reference.quantity);
						if (strcmp(reference.item_code,useritem_code)==0){
							check = 1;
							if (reference.quantity == 0){	
								printf("Item was successfully delected.\n");
				   				verify =1;
							}
							else{
								printf("Item cannot be deleted.\n");
							}	
						}//end if
						else{
							temp1 = fopen("temp.txt","a");
			   				fprintf(temp1,"%s;%s;%.2f;%u\n",reference.item_code, reference.item_name,reference.price,reference.quantity);
			   				fclose(temp1);
						}// end else 	
					}//end while
					fclose(fp2);
					if(verify == 1){
						remove("ngst.txt");
						rename("temp.txt","ngst.txt");
					}// only done when changes are made	
					verify = 0;
					if (check != 1){
						printf("-------Item not found! Please try again-------\n");
					}// end if
				}//end else
				
			}// end if
		}//end if
		fclose(fopen("temp.txt", "w"));// clear content if any
		check = 0;// Initalizing back the value to ensure the program is able to repeatedly check the item code for errors or matches.
	}while(strcmp(useritem_code,"-1")!=0);// end do-while loop
	
	menu();
}

void show_inventory(void){
	int i;
	FILE *fp1, *fp2;
	if ((fp1 = fopen("gst.txt","r"))==NULL){
		puts("File could not be opened!");
	}// end if
	else{
		for (i=0;i<80;i++){
		printf("-");
		}
		
		printf("Taxable items\n");
		
		for (i=0;i<80;i++){
			printf("-");
		}
		printf("\n %s %15s %14s %12s\n","Item Code","Item Name","Price(RM)","Quantity");
		
		for (i=0;i<54;i++){
			printf("=");
		}
		while(!feof(fp1)){
			fscanf(fp1,"%[^;] ; %[^;] ;%f ;%d " ,reference.item_code, reference.item_name, &reference.price, &reference.quantity);
			printf("\n %6s %20s %10.2f %11d",reference.item_code,reference.item_name,reference.price,reference.quantity);
		}// end while
		fclose(fp1);
	}//end else
	if ((fp2 = fopen("ngst.txt","r"))==NULL){
		puts("File could not be opened!");
	}// end if
	else{
		printf("\n");
		for (i=0;i<80;i++){
		printf("-");
		}
		printf("Nontaxable items\n");
		
		for (i=0;i<80;i++){
			printf("-");
		}
		printf("\n %s %15s %14s %12s\n","Item Code","Item Name","Price(RM)","Quantity");
		
		for (i=0;i<54;i++){
			printf("=");
		}
		while(!feof(fp2)){
			fscanf(fp2,"%[^;] ; %[^;] ;%f ;%d " ,reference.item_code, reference.item_name, &reference.price, &reference.quantity);
			printf("\n %6s %20s %10.2f %11d",reference.item_code,reference.item_name,reference.price,reference.quantity);
		}// end while
		
		fclose(fp2);
	}// end else
	menu();
}

void show_dailytransactions(void){
	int i;
	unsigned int u_quantity;
	float purchase_sum;
	if (count!=0){
		for (i=0;i<80;i++){
		printf("~");
		}	
		printf("%50s\n","Purchased items\n");
		printf("\n %s %15s %14s %12s %14s\n","Item Code","Item Name","Price(RM)","Quantity","Total(RM)"); // header
		for (i=0;i<80;i++){
			printf("~");
		}
		if ((myfile1 = fopen("purchase.txt","r"))==NULL){
			puts("File could not be opened!");
			}// end if 
		else{
			while(!feof(myfile1)){
				fscanf(myfile1," %[^;] ; %[^;] ;%f ;%u;%f " ,reference.item_code, reference.item_name, &reference.price,&u_quantity,&purchase_sum);
				printf("%8s %20s %9.2f %11u %15.2f\n",reference.item_code, reference.item_name, reference.price,u_quantity,purchase_sum);
			}// end while
				fclose(myfile1);
			}// end else
	
		printf("Total Transactions :    %d\n",count); // The total number of transaction in one run
		printf("Sales with GST     : RM %.2f\n",s_gst); // The sum of GST purchases
		printf("Sales with NGST    : RM %.2f\n",s_ngst);// The sum of NGST purchases
		printf("GST collected      : RM %.2f\n",t_gst); // The sum of GST appplied
	}
	else{
		for (i=0;i<80;i++){
			printf("~");
		}
		printf("No items were purchased\n");
		for (i=0;i<80;i++){
			printf("~");
		}
	}
	menu();
}










#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STREQ(s1,s2,n) (strncmp((s1),(s2),n) == 0)

static const char* main_prompt = "Names Db > ";
static const char* db_name = "Db.txt";
static const char* temp_db_name = "NamesDbTemp";
#define MAXLENGTH 15
unsigned long db_pos = 0;

struct name_element {
	char is_deleted;
	char* name;
	char* adress1;
	char* adress2;
	char* phone_no;
	char* add_info;
};

/*name_element* read_name_element(db_ptr){

	int len;
	struct name_element* temp = calloc(sizeof*temp,1);
	if ( fread(&len,sizeof(len),1,db_ptr) && !feof(db_ptr) ){
		temp->name = malloc(len);
		fread(temp->name,len,1,db_ptr);
		
		fread(&len,sizeof(len),1,db_ptr)
		temp->adress = malloc(len);
		fread(temp->adress1,len,1,db_ptr);
		
		fread(&len,sizeof(len),1,db_ptr)
		temp->adress2 = malloc(len);
		fread(temp->adress2,len,1,db_ptr);
		
		fread(&len,sizeof(len),1,db_ptr)
		temp->phone_no = malloc(len);
		fread(temp->phone_no,len,1,db_ptr);
		
		fread(&len,sizeof(len),1,db_ptr)
		temp->add_info = malloc(len);
		fread(temp->add_info,len,1,db_ptr);

		return temp;
	}
	return NULL;
}*/

void free_name_element(struct name_element* temp) {
	
	free(temp->name);
	free(temp->adress1);
	free(temp->adress2);
	free(temp->phone_no);
	free(temp->add_info);
	free(temp);
}


struct name_element* read_name_element(FILE* file_ptr){
	
	struct name_element* temp = calloc(sizeof*temp,1);
	temp->name = malloc(MAXLENGTH);
	temp->is_deleted = 0;
	
	if(file_ptr != stdin)
		temp->is_deleted = fgetc(file_ptr);
	if (file_ptr == stdin) printf("Enter Name: ");
	if (fgets(temp->name,MAXLENGTH,file_ptr) && !feof(file_ptr) ){
		
		temp->adress1 = malloc(MAXLENGTH);
		temp->adress2 = malloc(MAXLENGTH);
		temp->phone_no = malloc(MAXLENGTH);
		temp->add_info = malloc(MAXLENGTH);
		
		if (file_ptr == stdin) printf("Enter Adress: ");
		fgets(temp->adress1,MAXLENGTH,file_ptr);
		if (file_ptr == stdin) printf("Enter Adress2: ");
		fgets(temp->adress2,MAXLENGTH,file_ptr);
		if (file_ptr == stdin) printf("Enter Phone No: ");
		fgets(temp->phone_no,MAXLENGTH,file_ptr);
		if (file_ptr == stdin) printf("Enter AddInfo: ");
		fgets(temp->add_info,MAXLENGTH,file_ptr);
		
		return temp;
	}
	free_name_element(temp);
	return NULL;
}

void write_name_element(struct name_element* temp,FILE* file_ptr){

	if (file_ptr == stdout) fprintf(file_ptr,"***********************************\n");
	if (file_ptr == stdout) printf("Name: ");
	fputs(temp->name,file_ptr);
	if (file_ptr == stdout) printf("Adress1: ");
	fputs(temp->adress1,file_ptr);
	if (file_ptr == stdout) printf("Adress2: ");
	fputs(temp->adress2,file_ptr);
	if (file_ptr == stdout) printf("Phone No: ");
	fputs(temp->phone_no,file_ptr);
	if (file_ptr == stdout) printf("Add Info: ");
	fputs(temp->add_info,file_ptr);
	if (file_ptr == stdout) fprintf(file_ptr,"***********************************\n");
	
}

int delete_element(const char* name,FILE* db_ptr){

	fpos_t pos;
	struct name_element* temp;
	while ( fgetpos(db_ptr,&pos) , temp = read_name_element(db_ptr)) {
		if (STREQ(temp->name,name)){
			fsetpos(db_ptr,&pos);
			fputc(1);
			return 0;
		}
	}	
	return 1;
}

void output_db(FILE* db_ptr,FILE* file_ptr) {
	rewind(db_ptr);
	struct name_element* temp;
	while ( temp = read_name_element(db_ptr)) {
		if (!temp->is_deleted)
			write_name_element(temp,file_ptr);
		free_name_element(temp);
	}			
}

void save_db(FILE* db_ptr) {

	rewind(db_ptr);
	FILE* temp = fopen(temp_db_name,"w");
	output_db(db_ptr,temp);
	rename(db_name,"old.db");
	rename(temp_db_name,db_name);
	renmove("old.db");	
}



void add_data(FILE* file_ptr) {

	struct name_element* temp;
	temp = read_name_element(stdin);
	write_name_element(temp,file_ptr);
	free_name_element(temp);
	db_pos = ftell(file_ptr);
}


void process_input(char* input,FILE* db_ptr){

	if (STREQ(input,".print",6))
		output_db(db_ptr,stdout);
	else if (STREQ(input,".add",4))
		add_data(db_ptr);
	else if (STREQ(input,".delete",7)){
		char name[MAXLENGTH];
		fgets(name,MAXLENGTH,stdin);
		if (delete_element(name,db_ptr) == 1)
			puts("cannot find element");
	}else if (STREQ(input,".save",5))
		save_db(db_ptr);
	else
		fprintf(stderr,"Invalid input\n");

	
}

FILE* open_db(){

	FILE* db_ptr = fopen(db_name,"a+");
	if (db_ptr == NULL)
		perror(NULL);
	return db_ptr;
}

void start_shell() {
	char user_input[10] = {0} ;
	FILE* db_ptr = open_db();
	if (db_ptr) {
		printf("\nNames Db v1\n""type .help for Help\n");
		while (42){
			printf("%s",main_prompt);
			fgets(user_input,10,stdin);
			if (STREQ(user_input,".quit",5))
				break;
			process_input(user_input,db_ptr);
		}
		fclose(db_ptr);
	}
	return;
	
}

int main (void) {
	
	//start_shell();
	return 0;
}


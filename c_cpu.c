#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define  ADRESS_FIELD_LENGHT 11
#define INSTRUCTION_LENGHT 17
#define NUM_BLOCKS 16      
#define BLOCK_SIZE 1024    


//Сложение двух чисел
int value_num_add(char a,char b,int c){
	return a - '0' + b  - '0' + c;
}

//Вычитание двух чисел
int value_num_sub(char a,char b){
	return (a - '0') - (b - '0');
}

//Перестановка чисел, для умножения.
void shift(char* str_a, int index){
	if(index != 0){
		int len = strlen(str_a)-1;
		for(int i = 0; i < index; i++){
			for(int j = 0; j != (int)len; j++){
				str_a[j] = str_a[j + 1];
			}
		str_a[strlen(str_a)-1] = '0';
		}	
	}

}

//Сложение двоичных чисел
void add_two(char* a, char* b,char* res){
    if(strlen(a) != strlen(b)){
		printf("not equal");
		exit(1);
    }
    int c = 0;
    for(int i = strlen(a) - 1; i >= 0; i--){
		if(value_num_add(a[i],b[i],c) == 3){
			c = 1;
			res[i] = '1';
		}else if(value_num_add(a[i],b[i],c) == 2){
			c = 1;
			res[i] = '0';
		}else{
			res[i] = value_num_add(a[i],b[i],c) + '0';
			c = 0;
		}
    }
}

//Увелечение на +1 двоичного числа.
void increment(char* string){
	size_t length = strlen(string);
	char one[length + 1];
	
	for(int i = 0; i < (int)length;i++){
		one[i] = '0';
	}
	
	one[length - 1] = '1';
	one[length] = '\0';
	add_two(string,one,string);
}

//Проверка двоичного числа на больше или меньше
int less_or_more(char* string_1,char* string_2){
	int len = strlen(string_1);
	for(int i = 0; i < (int)len; i++){
		if(string_1[i] != string_2[i]){
			return (string_1[i] > string_2[i]) ? 1 : -1;
		}
	}
	return 0;
}

//Перестановка числа
void change_num(int index, char* string){
	for(int i = index; i >= 0; i--){
		if(string[i] - '0' == 1){
			string[i] = '0';
			string[index] = '1';
			for(int j = i + 1; j != index;j++){
				string[j] = '1';
			}
			break;
		}
	}
}

//Вычитание
void sub(char* string_1,char* string_2,char* result){
	if(strlen(string_1) != strlen(string_2)){
		printf("not equal");
		exit(1);
    }
	for(int i = strlen(string_1) - 1; i >= 0; i--){
		if(value_num_sub(string_1[i],string_2[i]) == -1){
			change_num(i,string_1);
			result[i] = '1';//value_num_sub(string_1[i],string_2[i]) + '0';
		}else{
			result[i] = value_num_sub(string_1[i],string_2[i]) + '0';
		}
	}
	
}

//Деление
void divs(char* string_1,char* string_2,char* result){
	if(strlen(string_1) != strlen(string_2)){
		printf("not equal");
		exit(1);
    }

	size_t length = strlen(string_1);
	char result_f[length + 1];
	
	for(int i = 0; i < (int)length;i++){
		result_f[i] = '0';
	}
	result_f[length] = '\0';

	if(less_or_more(string_1,string_2)){
		for(int i = 0; i <= less_or_more(string_1,string_2);){
			sub(string_1,string_2,string_1);
			increment(result_f);
		}
		for(int i = 0;i < (int)length;i++){
			result[i] = result_f[i];
		}
	}else if(less_or_more(string_1,string_2) == -1){
		for(int i = strlen(string_1) - 1; i >= 0; i--){
			result[i] = result_f[i];
		}
	}else{
		increment(result_f);
		for(int i = 0;i < (int)length;i++){
			result[i] = result_f[i];
		}
	}

}

//Функция деление команд
void range(char* string,int start,int end, char* result){
    for(int i = 0; i < end - start; i++){
		result[i] = string[i+start];
    }
}

//разбивание команды команды поля
void operation_field(char* string,char* result){
    range(string,0,4,result);
}

//разбивание команды на режим адрес поля
void address_mode_field(char* string,char* result){
    range(string,4,6,result);

}

//разбивание команды на адрес поля
void address_field(char* string, char* result){
    range(string,6,16,result);
}

//Умножение двух двоичных чисел
void mul_two(char* a,char* b,char* res){
	if(strlen(a) != strlen(b)){
		printf("not equal");
		exit(1);
    }

	for(int i = strlen(a)-1; i >= 0; i--){
		if(b[i] - '0' == 1){
			char str_copy[strlen(a)];
			strcpy(str_copy,a);
			shift(str_copy, strlen(b) - i - 1);
			add_two(res,str_copy,res);
		}
	}

}

//Сравнивание строк
int equal_string(char* string_1,char* string_2){
    if(strlen(string_1) != strlen(string_2)){
		//printf("not_equal");
		return 0;
    }
	int len = strlen(string_1);
    for(int i = 0; i < (int)len;i++){
		if(string_1[i] != string_2[i]){
			return 0;
		}
    }
    return 1;
}

//Десятичное в двоичное число
void int_str(int value,char* instruction){
	int len = strlen(instruction);
	for(int i = len - 1;value != 0 && i >= 0;i--,value /= 2){
		if(value % 2){
			instruction[i] = '1';
		}
	}
}

//Двоичное число в десятичное число
int str_int(char* next_inst){
	int result = 0;
	for(int i = 0, j = strlen(next_inst)-1; j >= 0; i++,j--){
		int number = 1;
		if(next_inst[i] - '0'){
			for(int k = j; k > 0; k--){
				number *= 2;
			}
			result += number;
		}
	}
	return result;
}

//Запись в - 1(17), запись откуда - 2(11), память - 3
void read_memory(char current_inst[INSTRUCTION_LENGHT] ,char next_insct[ADRESS_FIELD_LENGHT],char memory[NUM_BLOCKS][BLOCK_SIZE]){
	int num_adress = str_int(next_insct);
    for(int i = 0;i < INSTRUCTION_LENGHT - 1; i++){
		current_inst[i] = memory[i][num_adress];
    }
}

//операция записи данных в память
void write_memory(char* index_in_memory,char* write_in_memory,char memory[NUM_BLOCKS][BLOCK_SIZE]){
	int index_in_mem = str_int(index_in_memory);
	for(int i = 0; i < INSTRUCTION_LENGHT; i++){
		memory[i][index_in_mem] = write_in_memory[i];
	}
}

//Запись в - из
void inv_write(char* in_rec,char* from_rec){
	int lenght_from_rec = strlen(from_rec);
	int len_in_rec = strlen(in_rec);
	if(len_in_rec != lenght_from_rec){
		int value = len_in_rec - lenght_from_rec;
		for(int i = lenght_from_rec; i >= 0; i--){
			in_rec[i+value] = from_rec[i];
		}
    }else{
		for(int i = lenght_from_rec; i >= 0; i--){
			in_rec[i] = from_rec[i];
		} 
	}

}

//Печать в консоль мнемонической команды(Команды поля)
void mnemonicCodeOp(char* operationF){
	if(equal_string(operationF,"0000")){
		printf("HALT");
	}else if(equal_string(operationF,"0001")){
		printf("LOAD");
	}else if(equal_string(operationF,"0010")){
		printf("STORE");
	}else if(equal_string(operationF,"0011")){
		printf("CALL");
	}else if(equal_string(operationF,"0100")){
		printf("BR");
	}else if(equal_string(operationF,"0101")){
		printf("BREQ");
	}else if(equal_string(operationF,"0110")){
		printf("BRGE");
	}else if(equal_string(operationF,"0111")){
		printf("BRLT");
	}else if(equal_string(operationF,"1000")){
		printf("ADD");
	}else if(equal_string(operationF,"1001")){
		printf("SUB");
	}else if(equal_string(operationF,"1010")){
		printf("MUL");
	}else if(equal_string(operationF,"1011")){
		printf("DIV");
	}	
}

//Печать в консоль мнемонической команды(режим адреса поля)
void mnemonicCodeAdModeField(char* adressModeF){
	if(equal_string(adressModeF,"00")){
		printf(" ");
	}else if(equal_string(adressModeF,"01")){
		printf("=");
	}else if(equal_string(adressModeF,"10")){
		printf("$");
	}else if(equal_string(adressModeF,"11")){
		printf("@");
	}
}

//Расшифровка 2-ого кода на мнемонический вывод
void mnemonic_code(char* command){
	char command_op[5] = "0000";
	char command_adModeField[3] = "00";
	operation_field(command,command_op);
	mnemonicCodeOp(command_op);
	address_mode_field(command,command_adModeField);
	mnemonicCodeAdModeField(command_adModeField);
}

void write_inst(char* instr,char* bin,int start,int end){
	for(int i = 0;i < end - start; i++){
		instr[i+start] = bin[i];
	}
}

//mnemonic_to_bin("ADD","@",13,0,mem);
void mnemonic_to_bin_op(char* mnem_op,char* instr){
	if(equal_string(mnem_op,"HALT")){
		write_inst(instr,"0000",0,4);
	}else if(equal_string(mnem_op,"LOAD")){
		write_inst(instr,"0001",0,4);
	}else if(equal_string(mnem_op,"STORE")){
		write_inst(instr,"0010",0,4);
	}else if(equal_string(mnem_op,"CALL")){
		write_inst(instr,"0011",0,4);
	}else if(equal_string(mnem_op,"BR")){
		write_inst(instr,"0100",0,4);
	}else if(equal_string(mnem_op,"BREQ")){
		write_inst(instr,"0101",0,4);
	}else if(equal_string(mnem_op,"BRGE")){
		write_inst(instr,"0110",0,4);
	}else if(equal_string(mnem_op,"BRLT")){
		write_inst(instr,"0111",0,4);
	}else if(equal_string(mnem_op,"ADD")){
		write_inst(instr,"1000",0,4);
	}else if(equal_string(mnem_op,"SUB")){
		write_inst(instr,"1001",0,4);
	}else if(equal_string(mnem_op,"MUL")){
		write_inst(instr,"1010",0,4);
	}else if(equal_string(mnem_op,"DIV")){
		write_inst(instr,"1011",0,4);
	}	
}

void mnemonic_to_bin_adF(char* mnem_ad,char* instr){
	if(equal_string(mnem_ad," ")){
		write_inst(instr,"00",4,6);
	}else if(equal_string(mnem_ad,"=")){
		write_inst(instr,"01",4,6);
	}else if(equal_string(mnem_ad,"$")){
		write_inst(instr,"10",4,6);
	}else if(equal_string(mnem_ad,"@")){
		write_inst(instr,"11",4,6);
	}
}

void mnemonic_to_bin_number(int num,char* instr){
	char bin_num[ADRESS_FIELD_LENGHT] = "0000000000";
	int_str(num,bin_num);
	write_inst(instr,bin_num,6,16);
}

void mnemonic_to_bin(char* mnem_OP,char* mnem_ADF,int num,int adress, char memory[NUM_BLOCKS][BLOCK_SIZE]){
	char instruction[INSTRUCTION_LENGHT] = "0000000000000000";
	mnemonic_to_bin_op(mnem_OP,instruction);
	mnemonic_to_bin_adF(mnem_ADF,instruction);
	mnemonic_to_bin_number(num,instruction);
	for(int i = 0; i < 16;i++){
		memory[i][adress] = instruction[i];
	}
}

void print_registr(char* PC,char* IR, char* MAR,char* MBR,char* XR,char* AC){
	printf("PC:%s\n",PC);
	printf("IR:%s\n",IR);
	printf("MAR:%s\n",MAR);
	printf("MBR:%s\n",MBR);
	printf("XR:%s\n",XR);
	printf("AC:%s\n",AC);
}

void main_loop(){
    char op_fil[5] = "0000";
    char ad_mode_field[3] = "00";
    char PC[ADRESS_FIELD_LENGHT] = "0000000000"; // Указатель на след.инструкцию
    char IR[INSTRUCTION_LENGHT] = "0000000000000000";//значение текущей инструкции
    char MAR[ADRESS_FIELD_LENGHT] = "0000000000";//
    char MBR[INSTRUCTION_LENGHT] = "0000000000000000";
    char XR[ADRESS_FIELD_LENGHT] = "0000000000";//
    char AC[INSTRUCTION_LENGHT] = "0000000000000000";//результат или (неявно)аргумент инструкции
	char adress_f_IR[ADRESS_FIELD_LENGHT] = "0000000000";// адрес текущей инструкции
	char adress_f_MBR[ADRESS_FIELD_LENGHT] = "0000000000";
    char memory [NUM_BLOCKS][BLOCK_SIZE];
    for(int i = 0; i < NUM_BLOCKS; i++){
		for(int j = 0; j < BLOCK_SIZE;j++){
			memory[i][j] = '0';
		}
    }
	//!!!!!AC = 15
	
	mnemonic_to_bin("LOAD","=",13,0,memory);
	mnemonic_to_bin("ADD","=",2,1,memory);
    mnemonic_to_bin("HALT"," ",0,2,memory);
	// print_registr(PC,IR, MAR, MBR, XR, AC);
	//mnemonic_to_bin("LOAD","=",13,0,memory);
  	
	

	while(1){
		// printf("START\n");
		// print_registr(PC, IR, MAR, MBR, XR, AC);
	//1.
		read_memory(IR,PC,memory);
		
	//2.
		address_mode_field(IR,ad_mode_field);
		address_field(IR,adress_f_IR);
		address_field(MBR,adress_f_MBR);

		if(equal_string(ad_mode_field,"00")){
			//printf("\ndirect mode\n");
			inv_write(MAR,adress_f_IR);
		}else if(equal_string(ad_mode_field,"01")){
			//printf("\nimmediate mode\n");
			inv_write(MAR,adress_f_IR);
			inv_write(MBR,MAR);
		}else if(equal_string(ad_mode_field,"10")){
			//printf("\nindexed mode\n");
			inv_write(MAR,adress_f_IR);
			add_two(MAR,XR,MAR);
			
		}else if(equal_string(ad_mode_field,"11")){
			//printf("\nindirect mode\n");
			inv_write(MAR,adress_f_IR);
			read_memory(MBR,MAR,memory);
			inv_write(MAR,adress_f_MBR);
		}
	//3.
		increment(PC);    
	//4.
		operation_field(IR,op_fil);
		if(equal_string(op_fil,"0000")){//halt
			printf("\nexit");
			exit(1);
		}else if(equal_string(op_fil,"0001")){//load
			if(!equal_string(ad_mode_field,"01")){
				read_memory(MBR,MAR,memory);
			}
			inv_write(AC,MBR);
		}else if(equal_string(op_fil,"0010")){//store
			read_memory(MBR,AC,memory);
			write_memory(MAR,MBR,memory);
		}else if(equal_string(op_fil,"0011")){//call
			inv_write(MBR,PC);
			write_memory(MAR,MBR,memory);
			inv_write(PC,MAR);
			increment(PC);
		}else if(equal_string(op_fil,"0100")){//br
			inv_write(PC,MAR);
		}else if(equal_string(op_fil,"0101")){//breq 
			if(equal_string(AC,"0000000000000000")){//прыжки
				inv_write(PC,MAR);
			}
		}else if(equal_string(op_fil,"0110")){//brge
			printf("\nnone_brge");
			exit(1);
			//прыжки на участок памяти
		}else if(equal_string(op_fil,"0111")){//brlt
			printf("\nnone_brlt");
			exit(1);
			//прыжки(циклы) на участок памяти
		}else if(equal_string(op_fil,"1000")){//add
			if(!equal_string(ad_mode_field,"01")){
				read_memory(MBR,MAR,memory);
			}
			add_two(AC,MBR,AC);

		}else if(equal_string(op_fil,"1001")){//sub
			if(!equal_string(ad_mode_field,"01")){
				read_memory(MBR,MAR,memory);
			}
			sub(AC,MBR,AC);
		}else if(equal_string(op_fil,"1010")){//mul
			if(!equal_string(ad_mode_field,"01")){
				read_memory(MBR,MAR,memory);
			}
			mul_two(AC,MBR,AC);
		}else if(equal_string(op_fil,"1011")){//div
			if(!equal_string(ad_mode_field,"01")){
				read_memory(MBR,MAR,memory);
			}
			divs(AC,MBR,AC);
		}
		// printf("END\n");
		print_registr(PC, IR, MAR, MBR, XR, AC);
		printf("\n");
	}
}


int main(){
    main_loop();
	//printf("asd");
	//char str2[17] = "1000110000001101";   // ADD @13
	//mnemonic_code(str2);
	//mnemonic_to_bin("ADD","@",13,0,mem);
	//char str1[10] = "001000001";
	//char str2[10] = "000001011";
	//char res1[10] = "000000000";
	//divs(str1,str2,str1);//,str1);
	//printf("%s",str1);
	//char res1[16] = "000000000000000";
	//int value = 103;
	//printf("\n%s\n",str2);
	//int_str(value,str2);
	//printf("\n%s\n",str2);

	return 0;
}

// мнемонический вид:
// LOAD 100
// ADD @30
// STORE 20

//mnemonic_to_bin("ADD","@",13,0,mem);!!!
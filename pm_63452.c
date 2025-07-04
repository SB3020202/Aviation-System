#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct Dados_para_cada_lugar {
	char ocupado;             
	char name[100];
	char checked_in;
	int id_luggage;
	int id_reservation_code;
}DADOS_PARA_CADA_LUGAR;
	

void help( ) {
	   puts("Sintax:  ./rsrv1  flight_name    aircraft_type");  
           puts("or:  ./rsrv1  aircraftType");   
    	   puts("Example:  ./rsrv1  TP1048      A318"); 
           puts("or:  ./rsrv1  A318");  
}
int menu() {
	int input=0;
	puts("     Aircraft Business ");
	puts("0 - Exit ");
	puts("1 - Show the structure of a plane");
	puts("2 - Show the occupancy of a flight\n");
	puts("3 - Show the passenger names with a reservation for this flight");
	puts("4 - Reserve a flight with seat number");
	puts("5 - Change the seat of a reservation");
	puts("6 - Assign a plane to a specific flight (opening of a flight)\n");
	puts("7 - Fill in a flight with random passengers\n");
	puts("8 - Histogram of flight occupancy per type of seat");
	puts("9 - Generation of the files \"names\" and \"surnames\"");
	printf("PLease choose a option: ");
	
	scanf(" %d", &input);	
return input;
}	



/**
 * Lê o ficheiro de configuração de um Airbus 3xx e conta o número de filas turísticas e executivas.
 * @param file_name_ Nome do ficheiro de configuração (e.g., "Airbus318").
 * @param turi       Ponteiro para armazenar o número de filas turísticas.
 * @param excu       Ponteiro para armazenar o número de filas executivas.
 * @return 1 em sucesso, -1 em caso de erro ao abrir o ficheiro.
 */	
int n_filas_excutivas_turisticas_de_Airbus3xx( char file_name_[] , int *turi, int *excu ) {      	
	int i= 1;			
	FILE *fp= fopen( file_name_, "r");
	char filas [7];
	
	if( fp==NULL) { /* No caso de o ficheiro n puder ser aberto*/
	    printf("Error opening file %s. Please correct it\n", file_name_);
	    i= -1;
	}
	else {
		while( fscanf( fp, "%s", filas ) !=EOF) { /* enontra posi para onde pf esta a apontar, le strings e coloca as em filas ate o final do ficheiro*/
			if( filas[4]=='\0') {
				(*excu)++;		
			}
			else {
				(*turi)++;
			}	
		} 
		fclose(fp);	
	}
return i;
}




/**
 * Exibe a estrutura de filas de um avião Airbus 3xx, determinando quantas filas executivas e turísticas existem.
 * Se for passado o tipo de avião como argumento, usa-o diretamente; caso contrário, solicita ao utilizador.
 * @param argc_ Número de argumentos passados (deve ser 1 ou 2).
 * @param argv_ String contendo o tipo de aeronave (e.g., "A318") quando argc_ == 2.
 * @return Sempre retorna 0.
 */
int Mostrar_estrutura_aviao( int argc_, char argv_[] ) { 
	char aircraft_type[5];
	char file_name[10]= "Airbus";	
        int n_filas_turisticas=0, n_filas_excutivas=0; // n_filas_xxx
	if( argc_==2 ) {
		file_name[6]= argv_[1];
		file_name[7]= argv_[2];
		file_name[8]= argv_[3];
		file_name[9]= '\0' ;		
		n_filas_excutivas_turisticas_de_Airbus3xx( file_name , &n_filas_turisticas, &n_filas_excutivas );
	}
	else if( argc_ ==1 ) {
		printf("Please indicate the aircraft type (Ex: A318): ");
		scanf(" %4s", aircraft_type );          // string     
		file_name[6]= aircraft_type[1];
		file_name[7]= aircraft_type[2];
		file_name[8]= aircraft_type[3];		
		file_name[9]= aircraft_type[4];
		n_filas_excutivas_turisticas_de_Airbus3xx( file_name , &n_filas_turisticas, &n_filas_excutivas );
	}
	if (n_filas_turisticas!=0) {
	       printf("\n     %s:  Excutive rows = %d, Turistic rows = %d\n\n\n\n", file_name, n_filas_excutivas, n_filas_turisticas);
	}
	
return 0;			
}








/**
 * Exibe a ocupação de um voo a partir de um ficheiro binário, desenhando um mapa de assentos.
 * Recebe o ponteiro para o ficheiro já posicionado após o inteiro de identificação do avião.
 * @param fp                   Ponteiro para o ficheiro binário aberto do voo.
 * @param n_lugares_executiva  Número total de lugares na classe executiva.
 * @param n_lugares_turistica  Número total de lugares na classe turística.
 */
void Mostrar_ocupacao_voo_auxiliar ( FILE *fp, int n_lugares_excutiva, int n_lugares_turistica ) {  /* Recebe binary file*/
	int i=0, ascii= 97, trocar_letra= 1, numero_=1 ; // p, trocar_letra, numero=1, ascii= 97; 
	int l=0, c=0;
	
//	int saber_qnd_printar_numeros= 1;
//	int printar_espacos_finais=1;
	
	int n_filas_total= (n_lugares_excutiva/4) + (n_lugares_turistica/6);
	int n_filas_excutiva= (n_lugares_excutiva/4);
	int n_lugares_total= n_lugares_excutiva + n_lugares_turistica;
	DADOS_PARA_CADA_LUGAR lugar_voo_info_318[ n_lugares_total ];	
	puts("          The reserved seats have the mark . \n\n\n");	
	 
	char matriz[7][33]= {0};	
	fseek( fp, sizeof(int), SEEK_SET);					
	
/*Guarda as structure do file no vetor		    	
	while( i< n_lugares_total ) {   
		printf("%d", (lugar_voo_info_318[i].ocupado));
		fread( &lugar_voo_info_318[i], sizeof(DADOS_PARA_CADA_LUGAR), 1, fp);
		i++;		 	
	}
Guarda as structure do file no vetor*/
	
	puts("\n\n\n\n");

	i=0;
	for ( l=0; l<7; l++ ) {   
	
		for (c=0; c<n_filas_total; c++ ) {
			
			if(  ((c<n_filas_excutiva) && l==0)  ||  ((c<n_filas_excutiva) && l==6) ){
				matriz[l][c]= ' ';	
			}

			else {
				if( trocar_letra== n_filas_total) {
					ascii++;
					trocar_letra=1;
				}
				if(  ((int)(lugar_voo_info_318[i].ocupado))==0  ) {
					matriz[l][c]= ((char)ascii);
					trocar_letra++;
					i++;
				}
				else if ( ((int)(lugar_voo_info_318[i].ocupado))==1 ) {
					matriz[l][c]= '.';
					trocar_letra++;
					i++;
				}
			}	
		} 
	}
	
	for ( l=0; l<7; l++ ) {
		for (c=0; c<n_filas_total; c++ ) {
		
			if( l==3){
				if( numero_<=8 ) {
					printf("%d ", numero_);
				}			
				else if( numero_>8) {
					printf("%d", numero_);
				}
				numero_++;
			}
			else {	
				printf("%c ", matriz[l][c]);	
			}
		} 
		puts("");
	}
	
puts("  \n\n\n\n");
}






/**
 * Solicita ao utilizador o código de voo e lê o ficheiro binário correspondente,
 * extraindo o tipo de avião (318, 319, 320 ou 321) e delegando em
 * Mostrar_ocupacao_voo_auxiliar a impressão do mapa de assentos.
 * @return 0 em todos os casos.
 */
int Mostrar_ocupacao_voo () {
	char fligth_file_name[256]= {0}, file_name_aviao[10]= "Airbus",  aux_guarda_aviao_numero[4]= {0};
	int n_aviao= 0; 
	int n_filas_turisticas=0, n_filas_excutivas=0;

	printf("Which is the flight that you want to see the occupancy? ");
	scanf(" %s", fligth_file_name ); 

	FILE *fp_= fopen( fligth_file_name, "rb" );   
						
	if ( fp_ !=NULL) { 
		fread( &n_aviao, sizeof(int), 1, fp_);
		
		sprintf( aux_guarda_aviao_numero, "%d", n_aviao); /* convetrte n_aviao numa string e guarda em aux_guarda_aviao_numero*/

		file_name_aviao[6]= aux_guarda_aviao_numero[0];
		file_name_aviao[7]= aux_guarda_aviao_numero[1];
		file_name_aviao[8]= aux_guarda_aviao_numero[2];		
		file_name_aviao[9]= aux_guarda_aviao_numero[3];  // <-- \0
		
		n_filas_excutivas_turisticas_de_Airbus3xx( file_name_aviao , &n_filas_turisticas, &n_filas_excutivas );   

		if ( n_aviao==318 ) {  /* Caso seja:  Airbus318*/
			Mostrar_ocupacao_voo_auxiliar ( fp_, n_filas_excutivas*4, n_filas_turisticas*6 );
		}
		else if( n_aviao==319) {  /* Caso seja:  Airbus319*/
			Mostrar_ocupacao_voo_auxiliar ( fp_, n_filas_excutivas*4, n_filas_turisticas*6 );
		}
		else if( n_aviao==320) {  /* Caso seja:  Airbus320*/
			Mostrar_ocupacao_voo_auxiliar ( fp_, n_filas_excutivas*4, n_filas_turisticas*6 );
		}
		else if( n_aviao==321) {  /*Caso seja:  Airbus321*/
			Mostrar_ocupacao_voo_auxiliar ( fp_, n_filas_excutivas*4, n_filas_turisticas*6 );
		}	
		
		fclose( fp_);	
	}
	else {
		printf("Error opening file %s. Please correctit\n", fligth_file_name);	
	}
	
return 0;
}







/**
 * Imprime os nomes dos passageiros com reservas para um voo,
 * organizando primeiro a classe executiva e depois a turística.
 * @param fp_                  Ponteiro para o ficheiro binário do voo (já posicionado após o inteiro de identificação).
 * @param n_lugares_turistica  Número de lugares na classe turística.
 * @param n_lugares_excutiva   Número de lugares na classe executiva.
 */
/*Funcao serve para mostar o resultado*/  
void Mostar_nome_passageiros_com_reservas_num_voo_auxliar( FILE *fp_ , int n_lugares_turistica, int n_lugares_excutiva ) {	
	DADOS_PARA_CADA_LUGAR lugar_voo_info_318[n_lugares_turistica + n_lugares_excutiva];	
	int row= 1, seat= 97;
	int percorre= 0;				
	int n_lugares_total= n_lugares_turistica + n_lugares_excutiva;
	fseek(fp_, 4, SEEK_SET);	
	puts("Passagers");
	
/* Guarda estruturas no vetor*/	
	while( percorre< n_lugares_total ) {   
		//printf("%d", (lugar_voo_info_318[percorre].ocupado));
		fread( &lugar_voo_info_318[percorre], sizeof(DADOS_PARA_CADA_LUGAR), 1, fp_);
		percorre++;		 	
	}
/*Guarda estruturas no vetor*/
	

/* Fazer print da parte Excutiva*/
	puts("   Excutive:");
	percorre= 0;
	while( percorre< n_lugares_excutiva ) {   	
		if( ((int)(lugar_voo_info_318[percorre].ocupado))==1 ){
			printf("	  Row %d, seat %c, name %s\n", row, seat, lugar_voo_info_318[percorre].name );
		}		 	
		if( ((percorre+1)%4)==0 ){
			row++;
			seat= 96;
		}
		percorre++;
		seat++;
	}
/*Fazer print da parte Excutiva*/


/*Fazer print da parte Turistica*/
	printf("\n   Turistic: \n");
	while( percorre< n_lugares_total ) {   
		
		if( ((int)(lugar_voo_info_318[percorre].ocupado))==1 ){
			printf("	  Row %d, seat %c: name %s\n", row, seat, lugar_voo_info_318[percorre].name );
		}		 	
		if( ((percorre+1)%6)==0 ){
			row++;
			seat= 96;
		}
		percorre++;
		seat++;
	}	
/*Fazer print da parte Turistica*/
	
}







/* Funcao serve para por de forma completa o nome  do aviao*/ 
int Mostar_nome_passageiros_com_reservas_num_voo() {
	char fligth_file_name[256]= {0}, file_name_aviao[10]= "Airbus",  aux_guarda_aviao_numero[4]= {0};
	int n_aviao= 0; 
	int n_filas_turisticas=0, n_filas_excutivas=0;  
	printf("Show the passenger names with a reservation for this flight ");
	scanf(" %s", fligth_file_name ); 
	
// After successfully getting the strings

	FILE *fp_= fopen( fligth_file_name, "rb" );   
						
	if ( fp_ !=NULL) {
		fread( &n_aviao, sizeof(int), 1, fp_);
		
		sprintf( aux_guarda_aviao_numero, "%d", n_aviao); /* convetrte n_aviao numa string e guarda em aux_guarda_aviao_numero*/
	/*Ecrever o noome do ficheiro ( do aviao ) copmpleto para passar a funcao e csg ler as filas*/
		file_name_aviao[6]= aux_guarda_aviao_numero[0];
		file_name_aviao[7]= aux_guarda_aviao_numero[1];
		file_name_aviao[8]= aux_guarda_aviao_numero[2];		
		file_name_aviao[9]= aux_guarda_aviao_numero[3];  // <-- \0
		
		n_filas_excutivas_turisticas_de_Airbus3xx( file_name_aviao , &n_filas_turisticas, &n_filas_excutivas );
		
		if ( n_aviao==318 ) {  /*Caso seja:  Airbus318*/
			Mostar_nome_passageiros_com_reservas_num_voo_auxliar( fp_ ,n_filas_turisticas*6, n_filas_excutivas*4 );
		}			
		else if( n_aviao==319) {  /* Caso seja:  Airbus319*/
			Mostar_nome_passageiros_com_reservas_num_voo_auxliar( fp_ , n_filas_turisticas*6 , n_filas_excutivas*4 );
		}
		else if( n_aviao==320) {  /* Caso seja:  Airbus320*/
			Mostar_nome_passageiros_com_reservas_num_voo_auxliar( fp_ , n_filas_turisticas*6, n_filas_excutivas*4 );
		}
		else if( n_aviao==321) {  /*Caso seja:  Airbus321*/
			Mostar_nome_passageiros_com_reservas_num_voo_auxliar( fp_ , n_filas_turisticas*6, n_filas_excutivas*4 );
		}
		puts("\n\n");
		fclose( fp_);
 
	}
	else {
		printf("Error opening file %s. Please correctit\n", fligth_file_name);
	
	}
return 0;

}




void Efetuar_reserva_de_um_voo() {   
	char fligth_file_name[256]= {0}, plane_file_name[10]="Airbus";
	char n_aviao_str[4]= {0};
	char current_seat[2]= {0}; 
	
	int n_aviao=0;
	int n_filas_excutivas= 0, n_filas_turisticas= 0, n_filas_total= 0;
	int n_lugares_total= 0;
	int n_lugares_excutiva= 0,  n_lugares_turistica= 0;	
	
	int current_row_number= 1;
		
/* var auxiliares*/
	int percorre_structure_to_structure_de_binary_file_e_guarda_estruturas= 0;
	int encontrei_lugar= 1;
	int estrutura= 0;	
/* var auxiliares*/


	printf("What is the flight code for the reservation? ");		
	scanf(" %s", fligth_file_name );
	
	FILE *fp= fopen( fligth_file_name, "rb+" );
	
	
	if( fp !=NULL ) {
		
	/*Ver o numero do aviao*/
		fread( &n_aviao, sizeof(int), 1, fp);
		sprintf( n_aviao_str, "%d", n_aviao);	
	/*Ver o numero do aviao*/
	
	
	/*Organiar dos dados*/ 
		plane_file_name[6]= n_aviao_str[0];
		plane_file_name[7]= n_aviao_str[1];
		plane_file_name[8]= n_aviao_str[2];		
		plane_file_name[9]= n_aviao_str[3];  // <-- \0
		
		n_filas_excutivas_turisticas_de_Airbus3xx( plane_file_name , &n_filas_turisticas, &n_filas_excutivas );
		
		n_filas_total= n_filas_excutivas + n_filas_turisticas;
		n_lugares_total= (n_filas_excutivas*4) + (n_filas_turisticas*6);
		n_lugares_excutiva= n_filas_excutivas*4;  
		n_lugares_turistica= n_filas_turisticas*6;
	/*Organiar dos dados */
	
		
	/*Ler e guardar a structure do aviao*/
		DADOS_PARA_CADA_LUGAR lugar[n_lugares_total];
		
		percorre_structure_to_structure_de_binary_file_e_guarda_estruturas= 0;
		
		while( percorre_structure_to_structure_de_binary_file_e_guarda_estruturas < n_lugares_total) {
			
			fread( &lugar[percorre_structure_to_structure_de_binary_file_e_guarda_estruturas], sizeof(DADOS_PARA_CADA_LUGAR), 1, fp);
			percorre_structure_to_structure_de_binary_file_e_guarda_estruturas++;		 			
		}
	/*Ler e guardar a structure do aviao*/	
	
		
		while(1){		
			
		/* Mostar ocupaçao do voo ( 444444444444444444444.222222222222222222222222222)*/
			Mostrar_ocupacao_voo_auxiliar ( fp, n_lugares_excutiva,  n_lugares_turistica );		
		/* Mostar ocupaçao do voo ( 444444444444444444444.222222222222222222222222222)*/	
				
			printf("    Insert the row number for the reservation ");
			scanf(" %d", &current_row_number );
		
		/*fila n esxiste*/	
			if( (current_row_number<1) || (current_row_number> n_filas_total) ){
				puts("This row does not exist.");
				continue;
			}
		/* fila n existe*/
		
			
			printf("    What is the seat in this row? ");
			scanf(" %1s", current_seat );
			
		/*descobriir lugar currente*/
			if( (current_row_number<= n_filas_excutivas) && ( (current_seat[0]=='a') || (current_seat[0]=='b') || (current_seat[0]=='c') || (current_seat[0]=='d') )) {
				if( current_seat[0]=='a' ){
					encontrei_lugar=1;
				}
				else if( current_seat[0]=='b' ){
					encontrei_lugar=2;
				}					
				else if( current_seat[0]=='c' ){
					encontrei_lugar=3;
				}					
				else if( current_seat[0]=='d' ){
					encontrei_lugar=4;
				}	
				encontrei_lugar= ((current_row_number-1)*4)+ encontrei_lugar;	
			}		
			else if( (current_row_number>n_filas_excutivas) && ( (current_seat[0]=='a') || (current_seat[0]=='b') || (current_seat[0]=='c') || (current_seat[0]=='d') || (current_seat[0]=='e') || (current_seat[0]=='f') )) {							
				if( current_seat[0]=='a' ){
					encontrei_lugar=1;
				}
				else if( current_seat[0]=='b' ){
					encontrei_lugar=2;
				}					
				else if( current_seat[0]=='c' ){
					encontrei_lugar=3;
				}					
				else if( current_seat[0]=='d' ){
					encontrei_lugar=4;
				}	
				else if( current_seat[0]=='e' ){
					encontrei_lugar=5;
				}					
				else if( current_seat[0]=='f' ){
					encontrei_lugar=6;
				}							
				encontrei_lugar= ((current_row_number-1)*6)+ encontrei_lugar-6;				
			}
			
		/*descobriir lugar currente*/
			else {
				printf("Wrong seat for this row: row = %d; seat = %s	\n", current_row_number, current_seat );
				continue;
			}
			
		/*Confirmaar se lugar ocupado*/
			estrutura= 0;	
			while( estrutura < encontrei_lugar) {		 	
				estrutura++;	 			
			}
			if( (lugar[estrutura-1].ocupado)==1 ){
				puts("This seat is already reserved.");
				continue;
			}
		    		
			else if( (lugar[estrutura-1].ocupado)==0 ){				
				
				printf("Please write the name and surname: ");
				scanf(" %[^\n]", (lugar[estrutura-1].name));   /*le ate encontrar ate encontrar \n*/ 
				
				printf("Please write a number for the identifier of the luggage: ");
				scanf(" %d", &(lugar[estrutura-1].id_luggage));
				
				printf("Please write a number for the reservation code: ");
				scanf(" %d", &(lugar[estrutura-1].id_reservation_code));
				
				fseek(fp, sizeof(int), SEEK_SET);
				fseek(fp, (sizeof(DADOS_PARA_CADA_LUGAR)*(estrutura-1)) , SEEK_CUR); /* Ja estou no lugar certo no file*/
				
				(lugar[estrutura-1].ocupado)= 1;
				
				fwrite( &(lugar[estrutura-1].ocupado), sizeof(lugar[estrutura-1].ocupado), 1 , fp );
				fwrite( (lugar[estrutura-1].name), sizeof(lugar[estrutura-1].name), 1 , fp );	
			/*Para saltar checked_in*/		
				fseek( fp, sizeof(lugar[estrutura-1].checked_in), SEEK_CUR ); /*fwrite( &(lugar[estrutura-1].ocupado), sizeof(lugar[estrutura-1].ocupado), 1 , fp );*/
			/*Para saltar checked_in*/	
				fwrite( &lugar[estrutura-1].id_luggage, sizeof(lugar[estrutura-1].id_luggage), 1 , fp );
				fwrite( &lugar[estrutura-1].id_reservation_code, sizeof(lugar[estrutura-1].id_reservation_code), 1 , fp );
				break;
				 
			}	
			
		/* Confirmaar se lugar ocupado*/		
		
		}	

	fclose( fp);
	}
	else {
		printf("Error opening file %s. Please correct it\n", fligth_file_name);
	}

}
	

			

int Descobrir_lugar( int current_row_number, int n_filas_excutivas, char current_seat[], int encontrei_lugar ) {

	if( (current_row_number<= n_filas_excutivas) && ( (current_seat[0]=='a') || (current_seat[0]=='b') || (current_seat[0]=='c') || (current_seat[0]=='d') )) {
				
		if( current_seat[0]=='a' ){
			encontrei_lugar=1;
		}
		else if( current_seat[0]=='b' ){
			encontrei_lugar=2;
		}					
		else if( current_seat[0]=='c' ){
			encontrei_lugar=3;
		}					
		else if( current_seat[0]=='d' ){
			encontrei_lugar=4;
		}	
										
		encontrei_lugar= ((current_row_number-1)*4)+ encontrei_lugar;	
	}
	else if( (current_row_number>n_filas_excutivas) && ( (current_seat[0]=='a') || (current_seat[0]=='b') || (current_seat[0]=='c') || (current_seat[0]=='d') || (current_seat[0]=='e') || (current_seat[0]=='f') )) {	
		
				if( current_seat[0]=='a' ){
					encontrei_lugar=1;
				}
				else if( current_seat[0]=='b' ){
					encontrei_lugar=2;
				}					
				else if( current_seat[0]=='c' ){
					encontrei_lugar=3;
				}					
				else if( current_seat[0]=='d' ){
					encontrei_lugar=4;
				}	
				else if( current_seat[0]=='e' ){
					encontrei_lugar=5;
				}					
				else if( current_seat[0]=='f' ){
					encontrei_lugar=6;
				}							
		encontrei_lugar= ((current_row_number-1)*6)+ encontrei_lugar-6;				
	}
	else {
		printf("Wrong seat for this row: row = %d; seat = %s	\n", current_row_number, current_seat );
		return -10;
	}

	
return encontrei_lugar;		

}

int Ver_se_novo_lugar_ocupado( int encontrei_lugar, DADOS_PARA_CADA_LUGAR *lugar , FILE *fp) {

	int estrutura= encontrei_lugar;			
	
	if( (lugar[estrutura-1].ocupado)==1 ){
		puts("This seat is already taken.");
		return -1;
	}
    		
	else if( (lugar[estrutura-1].ocupado)==0 ){				
		
		printf("Please write the name and surname: ");
		scanf(" %[^\n]", (lugar[estrutura-1].name));   /* le ate encontrar ate find \n */
				
		printf("Please write a number for the identifier of the luggage: ");
		scanf(" %d", &(lugar[estrutura-1].id_luggage));
		
		printf("Please write a number for the reservation code: ");
		scanf(" %d", &(lugar[estrutura-1].id_reservation_code));
		
		fseek(fp, sizeof(int), SEEK_SET);
		fseek(fp, (sizeof(DADOS_PARA_CADA_LUGAR)*(estrutura-1)) , SEEK_CUR); /* Ja estou na posi certo no file*/
		
		(lugar[estrutura-1].ocupado)= 1;
		
		fwrite( &(lugar[estrutura-1].ocupado), sizeof(lugar[estrutura-1].ocupado), 1 , fp );	
		fwrite( (lugar[estrutura-1].name), sizeof(lugar[estrutura-1].name), 1 , fp );	
	/*Para saltar checked_in*/		
		fseek( fp, sizeof(lugar[estrutura-1].checked_in), SEEK_CUR );
	/*Para saltar checked_in*/	
		fwrite( &lugar[estrutura-1].id_luggage, sizeof(lugar[estrutura-1].id_luggage), 1 , fp );
		fwrite( &lugar[estrutura-1].id_reservation_code, sizeof(lugar[estrutura-1].id_reservation_code), 1 , fp );	 
	}
		
return 1;	
}




void Alterar_lugar_reserva() {

	char fligth_file_name[256]= {0}, plane_file_name[10]="Airbus";
	char current_seat[2]= {0}, new_seat[2]= {0};
	char confirmar_nome[100]= {0};
	char n_aviao_str[4]= {0};
	
	int n_aviao= 0;
	
	int current_row_number= 0, new_row_number= 0;
	int n_filas_total= 0, n_filas_excutivas=0, n_filas_turisticas=0; 
	int n_lugares_total= 0, n_lugares_excutiva= 0, n_lugares_turistica= 0; 


	int encontrei_lugar= 0, encontrei_novo_lugar= 0;
	
	int ver_se_novo_lugar_ocupado= 0;
	int guarda_lugar_antigo_para_desocupar= 0;
	int percorre_structure_to_structure_de_binary_file_e_guarda_estruturas= 0;	
	printf("What is the flight code for the reservation? ");		
	scanf(" %s", fligth_file_name );
	
	FILE *fp= fopen( fligth_file_name, "wb+" );	
	
	if( fp !=NULL ) {
		
	// Ver o numero do aviao
		fread( &n_aviao, sizeof(int), 1, fp);
		sprintf( n_aviao_str, "%d", n_aviao);	
	// Ver o numero do aviao
	
	
	//Organiar dos dados 
		plane_file_name[6]= n_aviao_str[0];
		plane_file_name[7]= n_aviao_str[1];
		plane_file_name[8]= n_aviao_str[2];		
		plane_file_name[9]= n_aviao_str[3];  // <-- \0
		
		n_filas_excutivas_turisticas_de_Airbus3xx( plane_file_name , &n_filas_turisticas, &n_filas_excutivas );
		
		n_filas_total= n_filas_excutivas + n_filas_turisticas;
		n_lugares_total= (n_filas_excutivas*4) + (n_filas_turisticas*6);
		n_lugares_excutiva= n_filas_excutivas*4;  
		n_lugares_turistica= n_filas_turisticas*6;
	//Organiar dos dados 
	
		
	//Ler e guardar a structure do aviao	// comea do 0
		DADOS_PARA_CADA_LUGAR lugar[n_lugares_total];
		
		
		while( percorre_structure_to_structure_de_binary_file_e_guarda_estruturas < n_lugares_total) {
			
			fread( &lugar[percorre_structure_to_structure_de_binary_file_e_guarda_estruturas], sizeof(DADOS_PARA_CADA_LUGAR), 1, fp);
			percorre_structure_to_structure_de_binary_file_e_guarda_estruturas++;		 			
		}
	//Ler e guardar a structure do aviao	
	
	
		while(1){			
		
		// Mostar ocupaçao do voo ( 444444444444444444444.222222222222222222222222222)
			Mostrar_ocupacao_voo_auxiliar ( fp, n_lugares_excutiva,  n_lugares_turistica );		
		// Mostar ocupaçao do voo ( 444444444444444444444.222222222222222222222222222)	
				
		
		
			
		// descobriir lugar currente
			printf("    What is the original row? ");
			scanf(" %d", &current_row_number );		
			// fila n esxiste	
			if( (current_row_number<1) || (current_row_number> n_filas_total) ){
				puts("This row does not exist.");
				continue;
			}
			// fila n existe
		
			printf("    What is your original seat in this row( a, b, ...)? ");
			scanf(" %1s", current_seat );

			encontrei_lugar= Descobrir_lugar( current_row_number, n_filas_excutivas, current_seat, encontrei_lugar );
		
			if ( encontrei_lugar== -10 ) {
				continue;
			}
			//Se lugar vazio
			if( ((int)(lugar[encontrei_lugar-1].ocupado))==0 ) {
				puts("This seat is empty");
				continue;
			}
			//Se lugar vazio
			
			printf( "Write your name and surname (Just for testing:-------> the reservation name is %s:) ", (lugar[encontrei_lugar-1].name) );
			scanf(" %[^\n]", confirmar_nome);
			
			// Ver se os nomes sao o mesmo
			if( strcmp(confirmar_nome, (lugar[encontrei_lugar-1].name) )!=0) {
				puts("Wrong name. You must start the process again.");
				printf("Please Press Enter to continue");
				getchar();
				while(  (((int)getchar()))!=10 ) {
									
				}
				continue;				
			}
			// Ver se os nomes sao o mesmo
			guarda_lugar_antigo_para_desocupar= encontrei_lugar; 
		// descobriir lugar currente
		
		
			
		// descobriir novo lugar
			do {		
				printf("    What is the new in this row? ");
				scanf(" %d", &new_row_number);	

				if( (new_row_number<1) || (new_row_number> n_filas_total) ){
					puts("This row does not exist.");
					continue;
				}			
						
				printf("    What is the new seat in this row( a, b, ...)? ");
				scanf(" %1s", new_seat );			
			
				encontrei_novo_lugar= Descobrir_lugar( new_row_number,  n_filas_excutivas, new_seat, encontrei_novo_lugar );
				
				if ( encontrei_lugar== -10 ) {
					continue;
				}
			
			// Ver se novo lugar ocupado 
				ver_se_novo_lugar_ocupado= Ver_se_novo_lugar_ocupado( encontrei_novo_lugar, lugar , fp);	
				
				if( ver_se_novo_lugar_ocupado== -1 ){
					continue;
				}
				else if( ver_se_novo_lugar_ocupado==1 ) {
					break;
				}	
			// Ver se novo lugar ocupado
			}while(1);										
		// descobriir novo lugar
		
		
		// Desocupar lugar antigo
			if( ver_se_novo_lugar_ocupado==1 ) { 
				
				fseek(fp, sizeof(int), SEEK_SET);
			
				fseek(fp, (sizeof(DADOS_PARA_CADA_LUGAR)*(guarda_lugar_antigo_para_desocupar-1)) , SEEK_CUR); // Ja estou no lugar certo no file
				
				lugar[guarda_lugar_antigo_para_desocupar-1].ocupado= 0;
				
				fwrite( &(lugar[guarda_lugar_antigo_para_desocupar-1].ocupado), sizeof(lugar[guarda_lugar_antigo_para_desocupar-1].ocupado), 1 , fp );	
				break;
			}
		// Desocupar lugar antigo
		}	
	
	fclose( fp);
	}
	else {
		printf("Error opening file %s. Please correct it\n", fligth_file_name);
	}
	
}

void remover_char( char*s, int pos ) {

	int i=0;
	int length= strlen(s);
	
	for( i= pos; i<length; i++) {
		s[i]= s[i+1];
	}
}

int Atribuir_um_aviao_a_um_voo( int argc, char nome_voo[], char tipo_aviao[] ) {

	char fligth_file_name[256]= {0}, plane_file_name[10]="Airbus"; 
	char aircraft_type[5]= {0};
	
	int n_filas_turisticas= 0, n_filas_excutivas= 0; 
	int n_lugares_turistica= 0, n_lugares_excutiva= 0;
	
	int n_aviao= 0;
	int file_null= 1;
	int percorre_structure_do_file= 0;
	
	FILE *fp= NULL;

	if( argc==1 ) {
		printf("Write a flight code without blank spaces (Ex. TP1048): " );
		scanf("%s", fligth_file_name);
		printf("Write the type of aircraft (Ex. A318): ");
		scanf("%4s", aircraft_type);
			
		plane_file_name[6]= aircraft_type[1];
		plane_file_name[7]= aircraft_type[2];
		plane_file_name[8]= aircraft_type[3];
		plane_file_name[9]= aircraft_type[4];
		
	}
	else if( argc==3 ) {
		strcpy(fligth_file_name, nome_voo);
		
		plane_file_name[6]= tipo_aviao[1];
		plane_file_name[7]= tipo_aviao[2];
		plane_file_name[8]= tipo_aviao[3];
		plane_file_name[9]= tipo_aviao[4];		
	}	
	
	file_null= n_filas_excutivas_turisticas_de_Airbus3xx( plane_file_name, &n_filas_turisticas, &n_filas_excutivas );
		
	n_lugares_excutiva= n_filas_excutivas*4;
	n_lugares_turistica= n_filas_turisticas*6;

	remover_char( aircraft_type, 0);
	n_aviao=  atoi(aircraft_type); 	
			
	if( file_null ==-1) {
		return 0;
	}

	DADOS_PARA_CADA_LUGAR lugar[n_lugares_turistica + n_lugares_excutiva];
	fp= fopen( fligth_file_name, "wb+" );
	

/* Prencher o arquivo com as estrututras e o inteiro do aviao*/
	fwrite( &n_aviao, sizeof(int), 1 , fp );	

	while( percorre_structure_do_file < (n_lugares_turistica + n_lugares_excutiva)){
		lugar[percorre_structure_do_file].ocupado =0;
		fwrite( &(lugar[percorre_structure_do_file].ocupado), sizeof( lugar[percorre_structure_do_file].ocupado ), 1 , fp );		
		fseek( fp, sizeof(sizeof( DADOS_PARA_CADA_LUGAR)-sizeof( lugar[percorre_structure_do_file].ocupado)), SEEK_CUR );
		percorre_structure_do_file++;
	}
/* Prencher o arquivo com as estrututras e o inteiro do aviao*/				

	fclose(fp);

/* Mostra a estrututra*/
	Mostrar_ocupacao_voo_auxiliar ( fp, n_lugares_excutiva,  n_lugares_turistica );
/* Mostra a estrututra*/

	

return 0;	
}


int Prencher_voo_aleatoriamente() {

	char fligth_file_name[256]= {0}, plane_file_name[10]="Airbus"; 
	char aircraft_type[5]= {0};
	
	char sobre_nome[50]= {0};
	
	int n_filas_turisticas= 0, n_filas_excutivas= 0; 
	int n_lugares_total= 0, n_lugares_turistica= 0, n_lugares_excutiva= 0;
	
	int n_aviao= 0;
	int file_null= 1;
	int percorre_structure_do_file= 0;
	
	int n_lugares_ocupados= 0;
	
	int numero_da_linha_do_nome_a_por_no_ficheiro= 0;
	int vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[900]={0};
	int parte_do_index_x= 0;
	int i=0;
	int n_linha_repetido= 1;
	int g=0;
	 int p=0; 
	 int linha= 1;	
	 char nomes_pessoas[50]= {0};	
	
	FILE *fp= NULL;
	FILE* fp_names= NULL;
	FILE* fp_surnames=NULL;
	
	printf("Write a flight code without blank spaces (Ex. TP1048): " );
	scanf("%s", fligth_file_name);
	printf("Write the type of aircraft (Ex. A318): ");
	scanf("%4s", aircraft_type);
		

/*  Organizar os dados */
	plane_file_name[6]= aircraft_type[1];
	plane_file_name[7]= aircraft_type[2];
	plane_file_name[8]= aircraft_type[3];
	plane_file_name[9]= aircraft_type[4];
	
	file_null= n_filas_excutivas_turisticas_de_Airbus3xx( plane_file_name, &n_filas_turisticas, &n_filas_excutivas );
		
	n_lugares_excutiva= n_filas_excutivas*4;
	n_lugares_turistica= n_filas_turisticas*6;

	n_lugares_total= n_lugares_turistica+n_lugares_excutiva;

	remover_char( aircraft_type, 0);
	n_aviao=  atoi(aircraft_type); 	
			
	if( file_null ==-1) {
		return 0;
	}

	DADOS_PARA_CADA_LUGAR lugar[n_lugares_turistica + n_lugares_excutiva];
/*  Organizar os dados */



/* Abrir ficheiros */
	fp= fopen( fligth_file_name, "wb+" );	
	fp_names= fopen("names","r" );
	fp_surnames= fopen("surnames","r" );
/* Abrir ficheiros */	





/* Calcular quantidade de lugares que vao ser ocupados random */
	while(percorre_structure_do_file< n_lugares_total){
	
		lugar[percorre_structure_do_file].ocupado=  ( rand() % (3-2+1  ))+ 2;             //rand()%2; 
		percorre_structure_do_file++;
		if(  ((int)lugar[percorre_structure_do_file].ocupado) ==3 ) {
			n_lugares_ocupados++;
		}		
	}
/* Calcular quantidade de lugares que vao ser ocupados random */




/* Por n aviao no inicio */
	fwrite( &n_aviao, sizeof(int), 1 , fp );	
/* Por n aviao no inicio */





/* Gerar as linhas de cada nome aleatoriamnete*/
	
	numero_da_linha_do_nome_a_por_no_ficheiro= 1 + rand()%900;
	vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[0]= numero_da_linha_do_nome_a_por_no_ficheiro;
	
	
	for( parte_do_index_x= 1; parte_do_index_x<900; parte_do_index_x++ ){
		
		n_linha_repetido= 0;
		
		/* Verificar se nome se repete*/ 	
		do{
			numero_da_linha_do_nome_a_por_no_ficheiro= 1 + rand()%900;
			
			vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[parte_do_index_x]= numero_da_linha_do_nome_a_por_no_ficheiro; 
		
			i= 0;
			while( i< parte_do_index_x ) {
		
			/*  Aqui numeo se repetiu*/	
				if( numero_da_linha_do_nome_a_por_no_ficheiro == vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[i] ) {	 
					n_linha_repetido= 1;			
					break;			
				}
			/*  Aqui numeo se repetiu*/	
			
			
			/*numero n repetido	*/
				if( vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[parte_do_index_x]== vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[i+1] ) {
					n_linha_repetido= -1;
				} 
			/*numero n repetido	*/
				i++;		
			}
			
			if( n_linha_repetido==-1) {
				break;
			} 	
		}while( 1 );
		/* Verificar se nome se repete*/
	}
/* Gerar as linhas de cada nome aleatoriamnete*/

	
	  
	
/*  GGuardar os nomes das pessoas	*/

	 for( p=0; p<900; p++ ) {
	 	
		while( fscanf( fp_names, "%s", nomes_pessoas ) !=EOF      ) { /* enontra posi para onde pf esta a apontar, le strings e coloca as em filas ate o final do ficheiro*/
			
			if(vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[p]== linha) {			
				break;
				
			}
			linha++;
		}
		for ( g=0; g< n_lugares_total; g++) {

			if(  ((int)lugar[g].ocupado) ==3 ) {
				
				lugar[g].ocupado= 1;
				strcpy( lugar[g].name, nomes_pessoas);
				lugar[g].id_luggage=  rand();
				lugar[g].id_reservation_code= rand();	
				break;
			}
			if(  ((int)lugar[g].ocupado) ==2 ) {
				lugar[g].ocupado= 0;	
			}	
		}
		 
	 	
	 	
	 
	 }   	
	 for( p=0; p<900; p++ ) {
	 	
		while( fscanf( fp_surnames, "%s", sobre_nome ) !=EOF      ) { /* enontra posi para onde pf esta a apontar, le strings e coloca as em filas ate o final do ficheiro*/
			
			if(vetor_que_guarda_linhas_dos_nomes_ja_escolhidos[p]== linha) {			
				break;
				
			}
			linha++;
		}
		for ( g=0; g< n_lugares_total; g++) {

			if(  ((int)lugar[g].ocupado) ==1 ) {
				
				strcat( lugar ->name,  sobre_nome );
			}

		}
		 
	 	
	 	
	 
	 }   		 
	 
	 
/*  GGuardar os nomes das pessoas	*/	
	


    



/* Fechar arquivo*/
	fclose(fp);
	fclose(fp_names);
	fclose(fp_surnames);
/* Fechar arquivo*/


	
	
	

return 0;
} 




















int main( int argc, char* argv[]) {   

	int menu_escolha=1;
	if( (argc==2) && (strcmp( argv[1], "-h")==0 )) {	
		help();  
		return 0;
	}
	
	
	if( ((strcmp(argv[0],"./tf")==0 ) && argc==2) || ( strcmp(argv[0],"./tf")==0  && argc==3) || ((strcmp(argv[0],"./tf")==0) && argc==1)  ) {
	
		if ( (strcmp(argv[0],"./tf")==0 ) && argc==2 ) {
			Mostrar_estrutura_aviao(argc, (argv[1]) );
			argc= 1;
		}
		if ( (strcmp(argv[0],"./tf")==0 ) && argc==3 ) {
			Atribuir_um_aviao_a_um_voo(argc, argv[1], argv[2]  );
			argc= 1;
		}		 	
		menu_escolha= menu();
	
		while( menu_escolha<0 || menu_escolha>9 ) {
	       		puts("\n\n\n\nInvalid option:\n\n\n\n ");	
	        		menu_escolha= menu();			
		}
		
		while(menu_escolha !=0 ){
		         switch(menu_escolha) {
		        	 case 1: Mostrar_estrutura_aviao(argc, (argv[1]) ); 
			         break;
		           case 2: Mostrar_ocupacao_voo (); 
		              	         break;
		        	 case 3: Mostar_nome_passageiros_com_reservas_num_voo(); 
			         break;		
			 case 4: Efetuar_reserva_de_um_voo();
			         break;		 
		         	 case 5: Alterar_lugar_reserva();
	                	         break;
		      	 case 6: Atribuir_um_aviao_a_um_voo( argc, argv[1], argv[2]);
		      	         break;  
		  	 case 7: Prencher_voo_aleatoriamente();
		         	         break;
		         } 
		         menu_escolha= menu();
		}
	}	
	puts( "Good By.... YOU FUCKING PEAKY BLINDER");


return 0;
}











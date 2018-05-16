#include <stdlib.h>
#include <stdio.h>
#include "listaDE.h"
#include <string.h>


Lista* cria_lista(){
  Lista* li = (Lista*)malloc(sizeof(Lista));
  if (li != NULL)
    *li = NULL;
  return li;
}


void Libera_lista(Lista* li){
    if(li != NULL){
      Elem* no;
      while((*li) != NULL){
        no = *li;
        *li = (*li)->prox;
        free (no);
      }
      free(li);
    }
}


void imprimir(Lista* li){
    Lista* p = li;

    if((*li) == NULL){
    printf("Lista vazia\n");
    //exit(1);

    } else {

      while((*p) != NULL){
          imprimir_elemento(&(*p));
          p = &(*p)->prox;
      }

    }
}

void imprimir_elemento(Lista* li){
    printf(" Nome: %s \n", (*li)->dados.nome);
    printf(" celular: %s \n", (*li)->dados.Celular);
    printf(" Endereco: %s \n", (*li)->dados.Endereco);
    printf(" Cep: %d \n", (*li)->dados.cep);
    printf(" Nascimento: %s \n\n", (*li)->dados.Data);
}

int count(Lista *temp)
{
  int count = 0;  // Initialize count
    Lista* current = temp;  // Initialize current
    while ((*current) != NULL)
    {
        count++;
        current = &(*current)->prox;
    }
    return count;
}

void salva_arquivo(Lista* p){
    FILE *fp = fopen("contatos.txt", "w+");
    int n = count(p);

      printf("Salvando lista no arquivo contatos.txt...\n");

      while((*p) != NULL){

        fprintf(fp,"%s\n",(*p)->dados.nome);
        fprintf(fp,"%s\n",(*p)->dados.Celular);
        fprintf(fp,"%s\n",(*p)->dados.Endereco);
        fprintf(fp,"%d\n",(*p)->dados.cep);
        fprintf(fp,"%s\n$\n",(*p)->dados.Data);

        p = &(*p)->prox;
      }
      printf("!!!!!!!!!!!!! %d !!!!!!!!!111\n", n);
      fclose (fp);
}

void abre_arquivo(char lines[][101], int n, Lista* li){
  int a0 = 0,a1 = 1,a2 =2,a3 =3, a4=4, a5=5, i=0;
  struct Pessoa *dados_pessoa;
  for (i = 0; i < n; i++){
    if(i==a0){
      dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
      dados_pessoa->nome =lines[i] ;
     a0 += 6;
    }
    if(i==a1){
      dados_pessoa->Celular = lines[i];
     a1 += 6;
    }
    if(i==a2){
      dados_pessoa->Endereco = lines[i];
     a2 += 6;
    }
    if(i==a3){
      int num1 = atoi(lines[i]);

      dados_pessoa->cep =num1;
    	a3+= 6;
    }
    if(i==a4){
      dados_pessoa->Data = lines[i];
     a4 += 6;
    }

    if(i==a5){
  	insere_lista_final(li, *dados_pessoa);
    free(dados_pessoa);
     a5 += 6;
    }

  }
  a0 = 0,a1 = 1,a2 =2,a3 =3, a4=4, a5=5;
}


int insere_lista_inicio(Lista* li, struct Pessoa p){
  if(li == NULL) return 0;
  Elem* no = (Elem*) malloc(sizeof(Elem));
  if(no == NULL) return 0;
  no->dados = p;
  no->prox = (*li);
  no->ant = NULL;
  //lista não vazia, apontar para o anterior
  if(*li != NULL)
    (*li)->ant = no;
  *li = no;
  return 1;

}


int insere_lista_final(Lista* li, struct Pessoa p){
  if(li == NULL) return 0;
  Elem *no = (Elem*) malloc(sizeof(Elem));
  if (no == NULL) return 0;
  no->dados = p;
  no->prox = NULL;
  if((*li) == NULL){ //lista vazia, insiro no começo
    no->ant = NULL;
    *li = no;
  }
  else {
    Elem *aux = *li;
    while(aux->prox != NULL)
      aux = aux->prox;
    aux->prox = no;
    no->ant = aux;
  }
  return 1;
}


int insere_lista_ordenada(Lista* li, struct Pessoa p){
  if(li == NULL) return 0;
  Elem *no = (Elem*) malloc(sizeof(Elem));
  if (no == NULL) return 0;
  no->dados = p;
  if((*li) == NULL){//insere inicio
    no->prox = NULL;
    no->ant = NULL;
    *li = no;
    return 1;
  }
  else { //procura onde inserir
    Elem *ante, *atual = *li;
    while(atual != NULL && atual->dados.cep <p.cep){
      ante=atual;
      atual = atual->prox;
    }
    if(atual == *li){//insere no inicio
      no->ant = NULL;
      (*li)->ant = no;
      no->prox = (*li);
      *li = no;
    }
    else {
      no->prox = ante->prox;
      no->ant = ante;
      ante->prox = no;
      if(atual != NULL)
        atual->ant = no;
    }
    return 1;
  }

}


int remove_lista_inicio(Lista* li){
  if(li == NULL)
    return 0;
  if((*li) == NULL)
    return 0;

  Elem *no = *li;
  *li = no->prox;
  if(no->prox != NULL)
    no->prox->ant = NULL;

  free(no);
  return 1;
}


int remove_lista_final(Lista* li){
  if(li == NULL) return 0;
  if((*li) == NULL)//lista vazia
    return 0;

  Elem *no = *li;
  while(no->prox != NULL)
    no = no->prox;

  if(no->ant == NULL)//remover o primeiro e único
    *li = no->prox;
  else
    no->ant->prox = NULL;

  free(no);
  return 1;
}


int remove_lista(Lista* li, int cep){
  if(li == NULL) return 0;
  Elem *no = *li;
  while(no != NULL && no->dados.cep  != cep){
    no = no->prox;
  }
  if (no == NULL)// não encontrado
    return 0;
  if(no->ant == NULL)//remover o primeiro
    *li = no->prox;
  else
    no->ant->prox = no->prox;
  //não é o ultimo?
  if(no->prox != NULL)
    no->prox->ant = no->ant;
    free(no);
    return 1;
}


int consulta_lista_pos(Lista* li, int pos, struct Pessoa *p){
  if(li == NULL || pos<= 0) return 0;
  Elem *no = *li;
  int i = 1;
  while (no != NULL && i<pos) {
    no = no->prox;
    i++;
  }
  if(no == NULL)
    return 0;
  else{
    *p = no->dados;
  return 1;
  }
}


int consulta_lista_cep(Lista* li, int cep, struct Pessoa *p){
  if(li == NULL) return 0;
  Elem *no = *li;
  while (no != NULL && no->dados.cep != cep) {
    no = no->prox;
  }
  if(no == NULL)
    return 0;
  else{
    *p = no->dados;
    return 1;
  }
}

void pegar_contato(Lista *li,char *name,char *celular,char *endereco,char *data,int cep){

  struct Pessoa *dados_pessoa;
  dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));

  dados_pessoa->nome = strdup(name);
  dados_pessoa->Celular = strdup(celular);
  dados_pessoa->Endereco = strdup(endereco);
  dados_pessoa->cep = cep;
  dados_pessoa->Data = strdup(data);
  insere_lista_final(li, *dados_pessoa);
  free(dados_pessoa);


}

void criar_contato(Lista* li){
  char *name;
  char *endereco;
  char *celular;
  char *data;
  unsigned int cep;

  name = (char *)malloc(101*sizeof(char));
  endereco = (char *)malloc(101*sizeof(char));
  celular = (char *)malloc(11*sizeof(char));
  data = (char *)malloc(11*sizeof(char));

  struct Pessoa *dados_pessoa;
  dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));

  printf("Nome: \n");
  int verify = 0;
  do{
  scanf(" %[^\n]s", name);
    verify = validar_nome(name);
    if (verify != 1) {
    printf("Nome não pode passar 100 caracteres!\n");
    }
  }while(verify != 1);

  printf("Celular: \n");

  verify = 0;
  do{
    scanf(" %[^\n]", celular);
    verify = validar_telefone(celular);
    if (verify != 1) {
      printf("Entrada inválida. Formato: XXXXX-XXXX\n");
    }
  }while(verify != 1);

  printf("Endereço: \n");
  verify = 0;
  do{
  scanf(" %[^\n]", endereco);
  verify = validar_nome(endereco);
  if (verify != 1) {
    printf("Endereço não pode passar 100 caracteres!\n");
  }
  }while(verify != 1);

  printf("Data: \n");

  verify = 0;
  do{
    scanf(" %[^\n]", data);
    verify = validar_data(data);
    if (verify != 1) {
      printf("Entrada inválida. Formato: XX/XX/XXXX\n");
    }
  }while(verify != 1);

  printf("Cep: \n");
  scanf(" %d", &cep);

  pegar_contato(li, name, celular, endereco, data, cep);

  free(name);
  free(endereco);
  free(celular);
  free(data);
}

int validar_telefone(char *telefone) {


	int tamanho = strlen(telefone);
  int i;

	if (tamanho != 10) {
		return 0;
	}

	// formato XXXXX-XXXX
	for (i = 0; i < tamanho - 1; i++) {
		if (telefone[i] < '0' || telefone[i] > '9') {

      if (i == 5 && telefone[i] != '-') {
  			return 0;
  		}
		}

	}

	return 1;

}

int validar_nome(char *palavra){
    int tamanho = strlen(palavra);

    if (tamanho > 101) {
  		return 0;
  	}

    return 1;
}

int validar_data(char *data) {


	int tamanho = strlen(data);

	if (tamanho != 10) {
		return 0;
	}

	// formato XX/XX/XXXX
	for (int i = 0; i < tamanho - 1; i++) {
		if (data[i] < '0' || data[i] > '9') {

      if (i == 2 && data[i] != '/') {
  			return 0;
  		}
      if (i == 5 && data[i] != '/') {
  			return 0;
  		}
		}

	}

	return 1;

}

void compara_nome();
void menu(){

  printf("\n Agenda \n");
  printf("\n 1 - Inserir novo registro");
  printf("\n 2 - Remover registros");
  printf("\n 3 - Visualizar registros");
  printf("\n 4 - Visualizar todos os registros");
  printf("\n 5 - Sair");
  printf("\n");

}

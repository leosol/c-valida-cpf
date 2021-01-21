#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validarCPF(char *cpf);
int validarCNPJ(char *cnpj);


int main(int argc, char **argv) {

	if(argc==1) {
		printf("%s\n", "Thanks to  eduardoedson (Validar CPF.c)");
		printf("%s\n", "Validation inside loop by Leandro Oliveira");
		printf("%s\n", "USAGE: c-valida-cpf [CPFs...|Files...]");
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		FILE *ptr;
		ptr = fopen(argv[1], "r");
		if (ptr) {
			//loops file contents
			char *line = NULL;
			size_t len = 0;
			ssize_t read;
			while ((read = getline(&line, &len, ptr)) != -1) {
				int str_len = strlen(line);
				char trimmed_line[12];
				if(str_len>10) {
					strncpy(trimmed_line, line, 11);
					trimmed_line[11] = '\0';
					int res = validarCPF(trimmed_line);
					int new_len = strlen(trimmed_line);
					//printf("Trimmed CPF: %s - %d\n", trimmed_line, new_len);
					if (res) {
						printf("Valid CPF: %s\n", trimmed_line);
						continue;
					} else {
						//printf("Invalid CPF: %s\n", trimmed_line);
					}
				}
				char trimmed_line2[15];
				if(str_len>13) {
					strncpy(trimmed_line2, line, 14);
					trimmed_line2[14] = '\0';
					int res = validarCNPJ(trimmed_line2);
					int new_len = strlen(trimmed_line2);
					//printf("Trimmed CNPJ: %s - %d\n", trimmed_line2, new_len);
					if (res) {
						printf("Valid CNPJ: %s\n", trimmed_line2);
						continue;
					} else {
						//printf("Invalid CNPJ: %s\n", trimmed_line2);
					}
				}
			}
			fclose(ptr);
		} else {
			char *test_str = argv[i];
			//printf("Validating: %s\n", test_str);
			int res = validarCPF(test_str);
			if(res){
				printf("Valid CPF: %s\n", test_str);
			} else {
				printf("Invalid CPF: %s\n", test_str);
			}
			res = validarCNPJ(test_str);
			if (res) {
				printf("Valid CNPJ: %s\n", test_str);
			}else{
				printf("Invalid CNPJ: %s\n", test_str);
			}
		}

	}
	printf("%s\n", "CVALIDACPF");
	printf("%s\n", "By Leandro Oliveira - SPI/IC/PCDF ");
	int valido = validarCPF("00238462162");
	printf("%d\n", valido);
	return 0;
}

int validarCPF(char *cpf) {
	int i, j, digito1 = 0, digito2 = 0;
	if (strlen(cpf) != 11)
		return 0;
	else if ((strcmp(cpf, "00000000000") == 0)
			|| (strcmp(cpf, "11111111111") == 0)
			|| (strcmp(cpf, "22222222222") == 0)
			|| (strcmp(cpf, "33333333333") == 0)
			|| (strcmp(cpf, "44444444444") == 0)
			|| (strcmp(cpf, "55555555555") == 0)
			|| (strcmp(cpf, "66666666666") == 0)
			|| (strcmp(cpf, "77777777777") == 0)
			|| (strcmp(cpf, "88888888888") == 0)
			|| (strcmp(cpf, "99999999999") == 0))
		return 0; ///se o CPF tiver todos os números iguais ele é inválido.
	else {
		///digito 1---------------------------------------------------
		for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
			digito1 += (cpf[i] - 48) * j;
		digito1 %= 11;
		if (digito1 < 2)
			digito1 = 0;
		else
			digito1 = 11 - digito1;
		if ((cpf[9] - 48) != digito1)
			return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
		else
		///digito 2--------------------------------------------------
		{
			for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
				digito2 += (cpf[i] - 48) * j;
			digito2 %= 11;
			if (digito2 < 2)
				digito2 = 0;
			else
				digito2 = 11 - digito2;
			if ((cpf[10] - 48) != digito2)
				return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
		}
	}
	return 1;
}




int validarCNPJ(char *cnpj) {
	int i, j, digito1 = 0, digito2 = 0;
	if (strlen(cnpj) != 14)
		return 0;
	else if ((strcmp(cnpj, "00000000000000") == 0)
			|| (strcmp(cnpj, "11111111111111") == 0)
			|| (strcmp(cnpj, "22222222222222") == 0)
			|| (strcmp(cnpj, "33333333333333") == 0)
			|| (strcmp(cnpj, "44444444444444") == 0)
			|| (strcmp(cnpj, "55555555555555") == 0)
			|| (strcmp(cnpj, "66666666666666") == 0)
			|| (strcmp(cnpj, "77777777777777") == 0)
			|| (strcmp(cnpj, "88888888888888") == 0)
			|| (strcmp(cnpj, "99999999999999") == 0))
		return 0; ///se o CNPJ tiver todos os números iguais ele é inválido.
	else {
		int tamanho = strlen(cnpj) - 2;
		int soma = 0;
    		int pos = tamanho - 7;
		for (i = tamanho; i >= 1; i--) {
			soma += (cnpj[tamanho-i]-48)*pos--;
		      	if (pos < 2){
			    	pos = 9;
			}
		}
		int resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
		if (resultado != (cnpj[12]-48)){
			return 0;
		}

		tamanho = tamanho + 1;
		soma = 0;
		pos = tamanho - 7;
		for (i = tamanho; i >= 1; i--) {
			soma += (cnpj[tamanho-i]-48) * pos--;
		      	if (pos < 2){
			    pos = 9;
			}
		}
		resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
		if (resultado != (cnpj[13]-48)){
			return 0;
		}
		   
		return 1;

	}
	return 0;
}




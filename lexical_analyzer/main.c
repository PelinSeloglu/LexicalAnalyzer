#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h> 

//E�er ch bir delimiter ise true d�nd�r�r.
bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '=' || 
		ch == '(' || ch == ')' || ch == ':' || ch == '\n'||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
		ch == '"') 
        return (true); 
    return (false); 
} 
  
//E�er ch bir operator ise true d�nd�r�r.
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '=' || ch == ':') 
        return (true); 
    return (false); 
}

//E�er ch ; ise true d�nd�r�r.
bool isEndOfLine(char ch)
{
	if (ch == ';' )
		return (true);
	return (false);	
}

//E�er ch bir bracket ise true d�nd�r�r.
bool isBracket(char ch)
{
	if (ch == '('||ch == ')'||
	    ch == '['||ch == ']'||
		ch == '{'||ch == '}')
		return (true);
	return (false);	 	
}
	
//E�er str ge�erli bir identifier ise true d�nd�r�r. 
bool validIdentifier(char* str) 
{ 
	int len = strlen(str);
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true || len > 20) 
        return (false); 
    return (true); 
}

//E�er str bir keyword ise true d�nd�r�r. 
bool isKeyword(char* str) 
{ 
		
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") || !strcmp(str, "record") || 
        !strcmp(str, "continue") || !strcmp(str, "int") 
        ||!strcmp(str, "float") ||!strcmp(str, "enum") 
        ||!strcmp(str, "return") || !strcmp(str, "char") 
        ||!strcmp(str, "case") ||!strcmp(str, "for") 
        ||!strcmp(str, "const") || !strcmp(str, "long") 
        ||!strcmp(str, "static") 
        ||!strcmp(str, "goto")) 
        return (true); 
    return (false); 
}

//E�er str integer ise true d�nd�r�r. 
bool isInteger(char* str) 
{ 
    int i, len = strlen(str); 
  
    if (len == 0) 
        return (false); 
          
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
            return (false); 
    } 
    return (true); 
} 
  
//E�er str basamakl� bir say� ise true d�nd�r�r.
bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str); 
    bool hasDecimal = false; 
  
    if (len == 0) 
        return (false); 
      
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 
  
//Verilen belirli indexler aras�nda ki charlar i�in malloc la dinamik haf�za olu�turur ve str nin o indexleri aras�nda yer alan charlar� buraya atar.
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 

//main fonsiyondur tokenlar burada belirlenir ve yaz�l�r.
int main() {
	
	//Okunacak olan dosya a��l�r.
	FILE *fl;
	size_t n = 0;
	char *str;
	int c;
    char* filename = "code.psi.txt";
    fl = fopen(filename, "r");
    
    //dosya bulunup bulunamama kontrol�
	if (fl == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    fseek(fl, 0, SEEK_END);
    long f_size = ftell(fl);
    fseek(fl, 0, SEEK_SET);
    str = malloc(f_size);	
	 while ((c = fgetc(fl)) != EOF) {
        str[n++] = (char)c;
        
    }
    str[n] = '\0';
    
	//yazd�r�lacak dosyan�n olu�turulmas�
	FILE *fl2;
    char* filename1 = "code.lex.txt";
    fl2 = fopen(filename1, "w");
	
	//token i�lemlerinin ba�lang�c�
	int left = 0, right = 0; 
    int i, len = strlen(str); 
    //file dosyas� k���k karfe �evriliyor
	for (i = 0; i < len; i++){
    	str[i]=tolower(str[i]);
	}
  
    while (right <= len && left <= right)
	{ 
        if (isDelimiter(str[right]) == false) 
			right++; 
			
			
  		//comment section olup olmad��� ve hata kontrol�n�n yap�ld��� yer
  		if (isDelimiter(str[right]) == true && str[right] == '(' && str[right+1] == '*' ){ 
  			if(str[right] == len)
				{
  					printf("Comment cannot terminate before the file end.Please close your comment section before the file end.\n");
  					fprintf(fl2,"Comment cannot terminate before the file end.Please close your comment section before the file end.\n");
  					break;
  				}
			right=right + 2;
  		
  			while(true){
  				right++;
				if(str[right] == len)
				{
  					printf("Comment cannot terminate before the file end.Please close your comment section before the file end.\n");
  					fprintf(fl2,"Comment cannot terminate before the file end.Please close your comment section before the file end.\n");
  					break;
  				}
  				else if(str[right] == '(' && str[right+1] == '*')
				{
  					printf("Please close your comment section before new comment section.\n");
  						fprintf(fl2,"Please close your comment section before new comment section.\n");
  					break;
  					
				}
				else if(str[right] == '*' && str[right + 1] == ')'){
					
					right = right + 2;
					left = right;
					break;
				}
			}	
		}
		
		//Stringlerin belirlenmesi burada yap�l�r.String hata kontrol� yap�lamamaktad�r.
		else if(isDelimiter(str[right]) == true && str[right] == '"'){
		
			right++;
			
			while(true){
				
				right++;
				
				if(str[right] == '"' ){
					
					right++;
					
					
					char* Strsection = subString(str, left, right -1);
					printf("%s: This is a string.\n",Strsection);
					fprintf(fl2,"%s: This is a string.\n",Strsection);
				
					left = right;
					
					break;
				}	
			}
		}	  
		
		//Operatorlerin,Bracketlar�n ve EndOfLine tokenlerinin belirlenip yazd�r�lmas� burada ger�ekle�ir.
        else if (isDelimiter(str[right]) == true && left == right) 
		{ 
      
			if (isOperator(str[right]) == true && isOperator(str[right+1]) == true){
			
				printf("Operator(%c%c)\n",str[right],str[right+1]);
				fprintf(fl2,"Operator(%c%c)\n",str[right],str[right+1]);
				right++;
				}
			
			else if (isOperator(str[right]) == true) {
			
                printf("Operator(%c)\n", str[right]);
                fprintf(fl2,"Operator(%c)\n", str[right]);
				}
           
			else if (isBracket(str[right]) == true ){
				if (str[right] == '(')	{
				
					printf("LeftPar\n");
					fprintf(fl2,"LeftPar\n");
					}
				if ( str[right] == ')'){
				
					printf("RightPar\n");
					fprintf(fl2,"RightPar\n");
					}
				if ( str[right] == '{'){
				
					printf("LeftCurlyBracket\n");
					fprintf(fl2,"LeftCurlyBracket\n");
					}	
				if ( str[right] == '}'){
					
					printf("RightCurlyBracket\n");
					fprintf(fl2,"RightCurlyBracket\n");
					}	
				if ( str[right] == '['){
				
					printf("LeftSquareBracket\n");	
					fprintf(fl2,"LeftSquareBracket\n");
					}
				if ( str[right] == ']'){
				
					printf("RightCurlyBracket\n");
					fprintf(fl2,"RightCurlyBracket\n");
					}
			}
		
			
			else if (isEndOfLine(str[right]) == true ){
			
				printf("EndOfLine\n");
				fprintf(fl2,"EndOfLine");
				}
			
            right++; 
            left = right;
		}
		
		//Keyword, Intcost ve Identifierlar�n tokenlerinin belirlenmesi, hata kontrol� yap�lmas� ve yazd�r�lmas� burada ger�ekle�ir.
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
		{ 
            //belirli indexler aras�ndaki kelimeyi olu�turur.
			char* subStr = subString(str, left, right - 1);
  
            //Keyword tokeni.
			if (isKeyword(subStr) == true) {
			
                printf("Keyword(%s)\n", subStr);
				fprintf(fl2,"Keyword(%s)\n", subStr);
				} 
  			
  			//intcost hata kontrol�.
            else if (isInteger(subStr) == true && strlen(subStr) >10){
			
                printf("'%s' is not an integer (IntCost) because max length is 10.\n", subStr);	
				fprintf(fl2,"'%s' is not an integer (IntCost) because max length is 10.\n", subStr);  
			}
			
			//IntCost tokeni.
			else if (isInteger(subStr) == true) {
				printf("IntConst(%s)\n", subStr); 
				fprintf(fl2,"IntConst(%s)\n", subStr);  
			}
                
  
            //basamakl� say�lar i�in intcost hata kontrol�.
			else if (isRealNumber(subStr) == true && strlen(subStr) >10){
		 
                printf("'%s' is not an integer (IntCost) because max length is 10.\n", subStr);
                fprintf(fl2,"'%s' is not an integer (IntCost) because max length is 10.\n", subStr);  
			}
			//basamakl� say�lar i�in IntCost tokeni.
			else if (isRealNumber(subStr) == true){
				printf("IntConst(%s)\n", subStr);
				fprintf(fl2,"IntConst(%s)\n", subStr);  
			} 
                
  			
  			//Identifier tokeni.
            else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false){
			
                printf("Identifier(%s)\n", subStr);
				fprintf(fl2,"Identifier(%s)\n", subStr); 
			}
  			
  			//Identifier hata kontrol�.
            else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false){
			 
                //20 karakteri ge�me hatas�
				if (strlen(subStr) >20){
				
					printf("'%s' is not a valid identifier because max legth is 20.\n", subStr);
					fprintf(fl2,"'%s' is not a valid identifier because max legth is 20.\n", subStr); 
					}
				
				else{
				
					printf("'%s' is not a valid identifier.\n", subStr);
					fprintf(fl2,"'%s' is not a valid identifier.\n", subStr); 
					}		 
        	}
			left = right;
		
		
        } 
    } 
    
    
	
	return 0;
}

  


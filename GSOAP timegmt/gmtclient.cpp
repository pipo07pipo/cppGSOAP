#include "soapH.h"
#include "gmt.nsmap"
int main() { 
time_t t; 
struct soap *soap = soap_new(); 
soap_call_t__gmt(soap, "http://localhost:8080", "", &t); 
printf("The current time is %s\n", ctime(&t)); 
soap_destroy(soap); 
soap_end(soap); 
soap_free(soap); 
return 0; 
}

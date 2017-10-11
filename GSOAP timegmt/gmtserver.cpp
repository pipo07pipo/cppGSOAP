#include "soapH.h"
#include "gmt.nsmap"

#include <math.h>  
int main()  
{ int m, s; /* master and slave sockets */
  struct soap *soap = soap_new();
 m = soap_bind(soap, NULL, 8080, 100); /* bind to the port supplied as command-line argument */
    if (m < 0)
    { soap_print_fault(soap, stderr);
      exit(-1);
    }
    fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
    for (;;)
    { s = soap_accept(soap);
      fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
      if (s < 0)
      { soap_print_fault(soap, stderr);
        exit(1);
      } 
      soap_serve(soap);
      soap_end(soap);
    }
  
  soap_done(soap);
  free(soap);
  return 0;
} 
int t__gmt(struct soap *soap, time_t *t)
{
  *t = time(0);
  return SOAP_OK;
}

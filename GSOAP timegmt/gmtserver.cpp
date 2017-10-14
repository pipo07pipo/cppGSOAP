#include "soapH.h"
#include "gmt.nsmap"

#include <math.h>  
int http_get(struct soap *soap)
{
  FILE *fd;
  fprintf(stderr, "request wsdl \n");
  char *s = strchr(soap->path, '?'); // soap->path has the URL path (soap->endpoint has the full URL)
  fprintf(stderr,soap->path);
  fprintf(stderr,"\n");
  if (!s || strcmp(s, "?wsdl")){ 
    fprintf(stderr, "get method not supported \n");
    return SOAP_GET_METHOD; // GET method not supported
  }
  fd = fopen("gmt.wsdl", "rb"); // open WSDL file to copy as a response
  if (!fd){ 
    fprintf(stderr, "return 404 \n");
    return 404; // return HTTP 404 not found
  }
  soap->http_content = "text/xml; charset=utf-8"; // HTTP header with text/xml content 
  soap_response(soap, SOAP_FILE); 
  fprintf(stderr,"send");
  for (;;) 
  {
    size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd); 
    if (!r || soap_send_raw(soap, soap->tmpbuf, r)) 
      break;
  } 
  fclose(fd); 
  soap_end_send(soap); 
  return SOAP_OK; 
}

int main()  
{ int m, s; /* master and slave sockets */
  struct soap *soap = soap_new();
  soap->fget = http_get;
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
  //soap->fget = http_get;
  soap_done(soap);
  free(soap);
  return 0;
} 
int t__gmt(struct soap *soap, time_t *t)
{
  *t = time(0);
  return SOAP_OK;
}


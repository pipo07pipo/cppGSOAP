from zeep import Client
import os

client = Client('http://localhost:8080?wsdl')
result = client.service.gmt()

print(result)

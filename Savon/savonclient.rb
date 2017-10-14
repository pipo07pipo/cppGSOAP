require 'savon'

client = Savon.client(wsdl: "http://localhost:8080?wsdl")

response = client.call(:gmt).to_hash[:gmt_response][:param_1]
print response
puts ""

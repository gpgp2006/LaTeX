def soma_pequena():
    soma = 0
    for i in range(10000):
        soma = soma + 0.0001
    return soma

print (soma_pequena())
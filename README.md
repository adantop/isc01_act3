# RSA

1. Generate keys
    1. Select 2 prime numbers (p, q)
    2. Calculate mod n = p * q
    3. Calc Euler function phi(n) = (p - 1) * (q - 1)
    4. Select public factor (e):
       1 <= e <= phi(n)
       such that: MCD(e, phi(n)) = 1
       meaning: e and phi(n) are co-prime
    5. Select private factor (d)
       such that: e * d = 1 mod(phi(n))
2. Private key: (e, n)
3. Public key:  (d, n)
4. Encrypt: C = (M^e) mod (n)
5. Decrypt: M = (C^d) mod (n)

# Estudiar algoritmo de Euclides

Encontrar d

Find x such that:

C⋅x ≡ A mod(b)

## Find C^-1 and multiply the equation

x ≡ C^-1 ⋅ A mod(b)

## Verify that **C** can be coprime of **b**

mcd(C, b) = 1

Euler tells us that if mcd(C, b) = 1

C^-1 = C^phi(b)-1 mod b

Where phi(b) is Euler's totient function: the number of integers from 1 to b that are coprime with b, meaning mcd(n,b) == 1


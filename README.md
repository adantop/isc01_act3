# RSA Algorithm Implementation

This project implements the **RSA encryption algorithm** in C. It includes basic modules for key generation, encryption, and decryption, following the RSA standard procedure.

## How It Works

1. **Key Generation**:
   - Select two prime numbers `p` and `q`.
   - Compute the modulus `n = p * q`.
   - Calculate Euler's totient function `phi(n) = (p-1)*(q-1)`.
   - Select a public exponent `e` such that `1 < e < phi(n)` and `gcd(e, phi(n)) = 1`.
   - Calculate the private exponent `d` such that `e * d ≡ 1 (mod phi(n))`.

2. **Keys**:
   - **Public Key**: `(e, n)`
   - **Private Key**: `(d, n)`

3. **Encryption**:
   - Ciphertext `C = (M^e) mod n`

4. **Decryption**:
   - Message `M = (C^d) mod n`

## Project Structure

- `main.c` — Handles key generation, encryption, and decryption operations.
- `crypto.c`, `crypto.h` — RSA algorithm core functions.
- `mod.c`, `mod.h` — Modular arithmetic helper functions (e.g., modular inverse).
- `types.h` — Type definitions.
- `CMakeLists.txt` — Build configuration file.

## Compilation

```bash
mkdir build
cd build
cmake ..
make
./rsa_program
```

> Requires a C compiler and CMake installed.

## Notes

- Modular arithmetic relies on the **Extended Euclidean Algorithm**.
- Prime numbers are currently hardcoded for demonstration purposes.
- This is a learning project and not intended for production use.

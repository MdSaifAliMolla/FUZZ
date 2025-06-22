# 🐚 FUZZ — A Minimal Custom Shell

FUZZ is a lightweight custom shell implementation written in C.  

| Command     | Description                             |
|-------------|-----------------------------------------|
| `fecho`     | Like `echo`, but fuzzier                |
| `fenv`      | Prints environment variables            |
| `fexit`     | Exits the shell gracefully              |
| `uwu`       | Just try it. You’ll see 😉               |
| `fwhoami`   | Prints the current user                 |
| `fls`       | Lists files in the current directory    |
| `fcd`       | Changes the current directory           |
| `fpwd`      | Prints the working directory            |
| `help`      | Shows all supported commands            |
| `history`   | Displays command history                |

---
## 👾 demo

<img src='https://github.com/user-attachments/assets/a5e02cc4-e996-4c2c-adc4-5e9760edddaf' alt="Sample Image" height="400" />
<img src='https://github.com/user-attachments/assets/0a5f2765-4d00-47dd-ace1-3a14fc52de60' alt="Sample Image" height="400" />
<img src='https://github.com/user-attachments/assets/eab8ac75-e3cb-40ea-b502-52b902b84aa3' alt="Sample Image" height="400" />

## 🚀 How to Run This Project

### 1. 🛠️ Compile the Code

compile using `gcc`:

```bash
gcc fuzz.c utils.c builtin.c -o fuzz -Wall
```
### 2. Run the shell
After compiling, start the shell with:
```bash
./fuzz
```

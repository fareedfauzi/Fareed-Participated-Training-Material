# Question
Parse employee.db by using the structures below:
```
typedef struct _EMPLOYEE {
    char name[40];
    int age;
    int salary;
} EMPLOYEE, *PEMPLOYEE;

typedef struct _FILE_HEADER {
    char MAGIC[4]; //"DATA"
    int NumberOfRecords;
}FILE_HEADER, *PFILE_HEADER;
```
Make sure your output is similar to output_sepatutnya.txt

# Files description
employee.db = File to parse

employee_code.c = My codes

my_output.txt = My coding output

output_sepatutnya.txt = Output that we wish for, after parsing the binary


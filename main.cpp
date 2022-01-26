/*
* Задание из двух частей. В первом задании необходимо подсчитать количество чисел,
* соответствующих определенному условию на некотором числовом промежутке.
* Во втором задании требуется модифицировать свою программу так,
* чтобы найти и вывести на экран двухсотое число или пару чисел соответствующих заданному условию. 
* Если таких чисел меньше двухсот, то вывести об этом сообщение на экран.
* 
* На промежутке от 1 до 90 000. Подсчитать количество таких чисел X,
* что (Х + Х - 1) - простое число. Ответ вывести на экран.
*/

#include <iostream>
#include <cstdlib>

int primcpp(int num) // определение, простое ли число
{
    int sq = sqrt(num);

    if (num == 2)
        return 1;

    if (num < 2 || num % 2 == 0) 
        return 0;

    for (int i = 3; i <= sq; i += 2)
        if (num % i == 0) 
            return 0;

    return 1;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    int countcpp = 0, xrcpp = 0;

    for (int Xcpp = 1; Xcpp <= 90000; Xcpp++)
    {
        countcpp += primcpp(Xcpp + Xcpp - 1);

        if (countcpp == 200)
            xrcpp = Xcpp;
    }

    printf("Количество чисел, соответствующих условию (СPP) = %d\n"
           "Двухсотое число, соответствующее условию (CPP) = %d\n\n", countcpp, xrcpp);

    unsigned _int32 X, count = 0, Xr = 0;

    _asm
    {
        mov dword ptr[X], 1 // начальное значение X
        mov ecx, 90000 // конечное значение X

        /* процедура перехода к следующему X */
        NEXT:
            call PRIME
            add dword ptr[X], 2 // X + 2, т.к. каждое новое число больше предыдущего на 2: 1, 3, 5...
            loop NEXT 
            jmp QUIT // безусловный переход

        /* процедура определения, простое ли число */
        PRIME:
            cmp dword ptr[X], 2
            je XR // условный переход, если X = 2
            ja JMP1 // условный переход, если X > 2
            ret // возврат из процедуры

        JMP1:
            or byte ptr[X], 1 
            jnz JMP2 // если X != 0
            ret // возврат из процедуры

        JMP2:
            mov ebx, 3

        JMP4:
            mov eax, ebx
            mul eax
            cmp eax, X
            ja XR // если eax > X
            mov eax, X
            div ebx
            or edx, edx
            jnz JMP3 // если edx = 0
            ret // возврат из процедуры

        JMP3:
            add ebx, 2 // ebx + 2
            jmp JMP4 // безусловный переход

        /* нахождение двухсотого числа*/
        XR:
            inc dword ptr[count] // dword ptr[count] + 1
            cmp dword ptr[count], 200 
            jne METKA // переход если dword ptr[count] != 200
            mov eax, dword ptr[X]
            inc eax // eax + 1
            shr eax, 1 // побитовый сдвиг операнда вправо
            mov dword ptr[Xr], eax

        METKA:
            ret // возврат из процедуры

        QUIT:
    } 
       
    printf("Количество чисел, соответствующих условию (ASM) = %d\n"  
           "Двухсотое число, соответствующее условию (ASM) = %d\n\n", count, Xr);

    system("PAUSE");
    return 0;
}
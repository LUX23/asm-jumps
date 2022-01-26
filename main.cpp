/*
* ������� �� ���� ������. � ������ ������� ���������� ���������� ���������� �����,
* ��������������� ������������� ������� �� ��������� �������� ����������.
* �� ������ ������� ��������� �������������� ���� ��������� ���,
* ����� ����� � ������� �� ����� ��������� ����� ��� ���� ����� ��������������� ��������� �������. 
* ���� ����� ����� ������ �������, �� ������� �� ���� ��������� �� �����.
* 
* �� ���������� �� 1 �� 90 000. ���������� ���������� ����� ����� X,
* ��� (� + � - 1) - ������� �����. ����� ������� �� �����.
*/

#include <iostream>
#include <cstdlib>

int primcpp(int num) // �����������, ������� �� �����
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

    printf("���������� �����, ��������������� ������� (�PP) = %d\n"
           "��������� �����, ��������������� ������� (CPP) = %d\n\n", countcpp, xrcpp);

    unsigned _int32 X, count = 0, Xr = 0;

    _asm
    {
        mov dword ptr[X], 1 // ��������� �������� X
        mov ecx, 90000 // �������� �������� X

        /* ��������� �������� � ���������� X */
        NEXT:
            call PRIME
            add dword ptr[X], 2 // X + 2, �.�. ������ ����� ����� ������ ����������� �� 2: 1, 3, 5...
            loop NEXT 
            jmp QUIT // ����������� �������

        /* ��������� �����������, ������� �� ����� */
        PRIME:
            cmp dword ptr[X], 2
            je XR // �������� �������, ���� X = 2
            ja JMP1 // �������� �������, ���� X > 2
            ret // ������� �� ���������

        JMP1:
            or byte ptr[X], 1 
            jnz JMP2 // ���� X != 0
            ret // ������� �� ���������

        JMP2:
            mov ebx, 3

        JMP4:
            mov eax, ebx
            mul eax
            cmp eax, X
            ja XR // ���� eax > X
            mov eax, X
            div ebx
            or edx, edx
            jnz JMP3 // ���� edx = 0
            ret // ������� �� ���������

        JMP3:
            add ebx, 2 // ebx + 2
            jmp JMP4 // ����������� �������

        /* ���������� ���������� �����*/
        XR:
            inc dword ptr[count] // dword ptr[count] + 1
            cmp dword ptr[count], 200 
            jne METKA // ������� ���� dword ptr[count] != 200
            mov eax, dword ptr[X]
            inc eax // eax + 1
            shr eax, 1 // ��������� ����� �������� ������
            mov dword ptr[Xr], eax

        METKA:
            ret // ������� �� ���������

        QUIT:
    } 
       
    printf("���������� �����, ��������������� ������� (ASM) = %d\n"  
           "��������� �����, ��������������� ������� (ASM) = %d\n\n", count, Xr);

    system("PAUSE");
    return 0;
}
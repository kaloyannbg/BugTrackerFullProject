# BugTrackerFullProject

# BUG TRACKER BY KALOYAN ANGELOV

YOU CAN LOG AS TESTER IF YOU ARE TESTER
YOU CAN LOG AS PROGRAMMER, IF YOU ARE PROGRAMMER

TESTER CAN CREATE NEW REPORT (FOR BUG);
TESTER CAN CHECK SPECIFIC REPORT (BUG)
TESTER CAN CHECK ALL REPORTS (FOR BUG);
TESTER CAN CHANGE STATUS OF SPECIFIC REPORT (BUG)
TESTER CAN CHANGE SPECIFIC REPORT (BUG)

PROGRAMMER CAN GET REPORT (BUG)
PROGRAMMER CAN CHANGE STATUS OF SPECIFIC REPORT (BUG)
PROGRAMMER CAN CHECK ALL REPORTS (BUGS)
PROGRAMMER CAN BACK FEEDBACK WITH CHANGES

    уникален номер, кратко описание, описание,
    дата на откриване, дата на поправяне, дата на закриване,
    тестер, програмист, състояние (new, fixed, closed)

CREATE NEW REPORT (TESTER)
1. UNIQUE ID NUMBER
2. SHORT DESCRIPTION
3. DESCRIPTION
4. DATE OF CREATION = (CURRENT DATE AND TIME)
5. DATE OF FIXED = 0 HERE
6. DATE OF CLOSED = 0 HERE
7. LAST WRITER IN REPORT : TESTER
8. STATUS : NEW

FIX REPORT  (PROGRAMMER)
1. UNIQUE ID NUMBER (ITS CONST)
2. SHORT DESCRIPTION (ITS CONST)
3. DESCRIPTION (ITS CONST)
4. DATE OF CREATION (ITS CONST)
5. DATE OF FIXED = (CURRENT DATE AND TIME) -- > CHANGE THIS
6. DATE OF CLOSED = 0 HERE
7. LAST WRITER IN REPORT : PROGRAMMER
8. STATUS : FIXED -->CHANGED STATUS

VERIFY REPORT  (TESTER)
1. UNIQUE ID NUMBER (ITS CONST)
2. SHORT DESCRIPTION (ITS CONST)
3. DESCRIPTION (ITS CONST)
4. DATE OF CREATION (ITS CONST)
5. DATE OF FIXED = (ITS CONST)
6. DATE OF CLOSED = (CURRENT DATE AND TIME) -- > CHANGE THIS
7. LAST WRITER IN REPORT : TESTER
8. STATUS : CLOSED -->CHANGED STATUS

Направете програма за управление на дефекти.
Всеки дефект трябва да има следните атрибути: уникален номер,
кратко описание, описание, дата на откриване, дата на поправяне, дата на закриване,
тестер, програмист, състояние (new, fixed, closed). Дефектът се създава в състояние
'new' и преминава в състояние 'fixed'когато програмист го поправи,
след като тестера го провери минава в състояние  'closed'. Да се даде възможност да
се добавя дефект със съответните атрибути и да се променя неговото състояние. Да има
възможност за извеждане на нови дефекти и на дефект, които са оправени и чакат да бъдат верифицирани.
Всичко дефекти със съответните атрибути трябва да могат да бъдат записвани и четени от cvs файлове формат.
